void drawHeader()
{
    TLatex *cms = new TLatex();
    cms->SetTextSize(32);
    cms->SetTextAlign(11);
    cms->DrawLatexNDC(0.1, 0.92, "#bf{CMS} #it{Simulation Preliminary}");

    TLatex *pythia = new TLatex();
    pythia->SetTextSize(32);
    pythia->SetTextAlign(31);
    pythia->DrawLatexNDC(0.95, 0.92, "PYTHIA8 #gammaPb + Pb#gamma (5.36 TeV)");

}

void draw_fits()
{
    gStyle->SetPalette(kViridis); 
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);

    TString fdir = "Files/";
    TString alg = "ak4pf";

    TFile *fin = new TFile(fdir + "l2.root");
    TDirectory *dir = (TDirectory*)fin->Get(alg);

    // double xmin = 5, xmax = 50;
    
    std::vector<TGraphErrors*> vBBp, vEC1p, vEC2p, vHFp, vBBm, vEC1m, vEC2m, vHFm;
    TIter next(dir->GetListOfKeys());
    TKey *key;
    while ((key = (TKey *) next())) {
        TString histname = key->GetName();
        TString classname = key->GetClassName();
        if (std::string(histname).find("AbsCorVsJetPt") == std::string::npos) continue;
        if (std::string(classname).find("TGraphErrors") == std::string::npos) continue;
        auto gr = (TGraphErrors*) dir->Get(histname);

        double eta1, eta2;
        sscanf(histname, "AbsCorVsJetPt_JetEta%lfto%lf", &eta1, &eta2);
        if (eta1 >= 0. && eta2 <= 1.305) vBBp.push_back(gr);
        else if (eta1 >= 1.305 && eta2 <= 2.5) vEC1p.push_back(gr);
        else if (eta1 >= 2.5 && eta2 <= 2.964) vEC2p.push_back(gr);
        else if (eta1 >= 2.964 && eta2 <= 5.191) vHFp.push_back(gr);
        else if (eta1 >= -1.305 && eta2 <= 0.) vBBm.push_back(gr);
        else if (eta1 >= -2.5 && eta2 <= -1.305) vEC1m.push_back(gr);
        else if (eta1 >= -2.964 && eta2 <= -2.5) vEC2m.push_back(gr);
        else if (eta1 >= -5.191 && eta2 <= -2.964) vHFm.push_back(gr);
    }

    TMultiGraph *mgBBp = new TMultiGraph(), 
                *mgEC1p = new TMultiGraph(),
                *mgEC2p = new TMultiGraph(),
                *mgHFp = new TMultiGraph(),
                *mgBBm = new TMultiGraph(),
                *mgEC1m = new TMultiGraph(),
                *mgEC2m = new TMultiGraph(),
                *mgHFm = new TMultiGraph();

    std::vector<std::tuple<TString, TMultiGraph*, std::vector<TGraphErrors*>*>> graphGroups = {
        {"cBBp", mgBBp, &vBBp}, {"cEC1p", mgEC1p, &vEC1p}, {"cEC2p", mgEC2p, &vEC2p}, {"cHFp", mgHFp, &vHFp},
        {"cBBm", mgBBm, &vBBm}, {"cEC1m", mgEC1m, &vEC1m}, {"cEC2m", mgEC2m, &vEC2m}, {"cHFm", mgHFm, &vHFm}
    };
    
    for (const auto& [cname, mg, vgr] : graphGroups) {
        int ngraphs = vgr->size();
        std::cout << "Processing " << ngraphs << " graphs for " << cname << std::endl;

        TLegend *legend = new TLegend(0.5, 0.2, 0.85, 0.35); 
        legend->SetNColumns(2); 

        for (int i = 0; i < ngraphs; i++) {
            double fraction = (ngraphs > 1) ? (double )i / (ngraphs - 1) : 1;  // 0.0 to 1.0
            int colorIdx = TColor::GetPalette()[(int)(fraction * 254)];

            TGraphErrors *&g = (*vgr)[i];
            g->SetLineColor(colorIdx);
            g->SetMarkerColorAlpha(colorIdx, 1);
            g->SetLineColorAlpha(colorIdx, 1);
            g->SetMarkerStyle(1);

            TF1 *fit = (TF1 *) g->GetListOfFunctions()->First();
            if (fit) {
                fit->SetLineWidth(1);
                fit->SetLineColorAlpha(colorIdx, 1);
            }

            double eta1, eta2;
            sscanf(g->GetName(), "AbsCorVsJetPt_JetEta%lfto%lf", &eta1, &eta2);
            legend->AddEntry(g, Form("%.3f < #eta < %.3f", eta1, eta2), "lp");

            mg->Add(g);
        }

        TCanvas *c = new TCanvas(cname, cname, 1600, 800);
        c->SetRightMargin(0.05);
        c->SetLeftMargin(0.1);
        c->SetBottomMargin(0.15);
        c->SetTopMargin(0.1);
        mg->Draw("AP");
        mg->SetTitle(";p_{T}^{jet}; 1/JES");
        double ymin = 0.8, ymax = 1.2;
        if (cname.Contains("EC1")) ymax = 1.4;
        else if (cname.Contains("EC2")) ymax = 2.4;
        else if (cname.Contains("HF")) ymax = 2.;
        mg->GetYaxis()->SetRangeUser(ymin, ymax);
        legend->Draw();
        drawHeader();
        c->Print(fdir + cname + ".pdf");
    }
    
}