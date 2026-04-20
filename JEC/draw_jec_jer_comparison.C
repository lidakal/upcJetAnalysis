#include "../cms_palette.h"

void drawHeader()
{
    TLatex *latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(26);
    latex->DrawLatex(0.15, 0.92, "#bf{CMS} #it{Simulation}");
    latex->DrawLatex(0.48, 0.92, "PYTHIA8 GNucleus (5.36 TeV)");
}

void formatCanvas(TCanvas *c)
{
    c->SetLeftMargin(0.15);
    c->SetRightMargin(0.05);
    c->SetBottomMargin(0.15);
    c->SetTopMargin(0.1);
}

void formatGraph(TGraph *gr, TString xlabel, TString ylabel, Int_t color)
{    
    // Need to be run after Draw() 

    gr->GetXaxis()->SetTitle(xlabel);
    gr->GetXaxis()->SetTitleSize(28);
    gr->GetXaxis()->SetTitleOffset(1.2);
    gr->GetXaxis()->SetLabelSize(22);

    gr->GetYaxis()->SetTitle(ylabel);
    gr->GetYaxis()->SetTitleSize(28);
    gr->GetYaxis()->SetTitleOffset(1.7);
    gr->GetYaxis()->SetLabelSize(22);
    if (ylabel.Contains("JES")) gr->GetYaxis()->SetRangeUser(0.8, 1.4);
    else if (ylabel.Contains("JER")) gr->GetYaxis()->SetRangeUser(0, 1.0);

    // use this for no JEC and vs refpt for std+gaus
    // if (ylabel.Contains("JES")) gr->GetYaxis()->SetRangeUser(0., 2.);
    // else if (ylabel.Contains("JER")) gr->GetYaxis()->SetRangeUser(0, 1.0);

    if (xlabel.Contains("p_{T}^{ref}")) gr->GetXaxis()->SetRangeUser(5, 50);
    else if (xlabel.Contains("#eta")) gr->GetXaxis()->SetRangeUser(-5.2, 5.2);

    gr->SetLineWidth(4);
    gr->SetLineColor(color);
    gr->SetMarkerColor(color);
}

std::pair<TGraph *, TGraph *> get_jes_jer_vs_refpt(TH2F *h)
{
    // Expecting h with x=refpt, y=jtpt/refpt within a given jteta range
    std::cout << "Calculating JES and JER vs refpt from " << h->GetName() << std::endl;
    int nX = h->GetNbinsX();
    TGraph *jes = new TGraph();
    TGraph *jer = new TGraph();

    // for each refpt, fit the jtpt/refpt distribution
    int iN = 0;
    for (int ix = 1; ix <= nX; ix++) {
        TH1F *proj = (TH1F *) h->ProjectionY(Form("proj_%d", ix), ix, ix);

        // avoid empty refpt bins
        if (proj->GetEntries() < 20) {
            std::cout << "Skipping refpt bin " << h->GetXaxis()->GetBinCenter(ix) << " due to low statistics (" << proj->GetEntries() << " entries)" << std::endl;
            delete proj;
            continue;
        }

        // fit jtpt/refpt with a gaussian: jes=mean, jer=sigma
        TF1* fit = new TF1(Form("fit_%d", ix), "gaus", 0.5, 1.5);
        proj->Fit(fit, "QN");  // Q = quiet

        // TCanvas *c_fit = new TCanvas(Form("c_fit_%d", ix), "", 700, 600);
        // proj->Draw();
        // fit->Draw("same");

        double mean  = fit->GetParameter(1);
        double sigma = fit->GetParameter(2);

        // std::cout << mean << " +/- " << sigma << std::endl;

        jes->SetPoint(iN, h->GetXaxis()->GetBinCenter(ix), mean);
        jer->SetPoint(iN, h->GetXaxis()->GetBinCenter(ix), sigma);
        iN++;

        delete fit;
        delete proj;
    }

    return std::pair<TGraph *, TGraph *>(jes, jer);
}

std::pair<TGraph *, TGraph *> get_jes_jer_vs_jteta(TH2F *h)
{
    // Expecting h with x=jteta, y=jtpt/refpt within a given refpt range
    std::cout << "Calculating JES and JER vs jteta from " << h->GetName() << std::endl;
    int nX = h->GetNbinsX();
    TGraph *jes = new TGraph();
    TGraph *jer = new TGraph();

    // for each jteta, fit the jtpt/refpt distribution
    int iN = 0;
    for (int ix = 1; ix <= nX; ix++) {
        TH1F *proj = (TH1F *) h->ProjectionY(Form("proj_%d", ix), ix, ix);
        // avoid empty jteta bins
        if (proj->GetEntries() < 20) {
            std::cout << "Skipping jteta bin " << h->GetXaxis()->GetBinCenter(ix) << " due to low statistics (" << proj->GetEntries() << " entries)" << std::endl;
            delete proj;
            continue;
        }

        // fit jtpt/refpt with a gaussian: jes=mean, jer=sigma
        TF1* fit = new TF1(Form("fit_%d", ix), "gaus", 0.5, 1.5);
        proj->Fit(fit, "QN");  // Q = quiet

        // TCanvas *c_fit = new TCanvas(Form("c_fit_%d", ix), "", 700, 600);
        // proj->Draw();
        // fit->Draw("same");

        double mean  = fit->GetParameter(1);
        double sigma = fit->GetParameter(2);

        if (sigma < 0.1)
            std::cout << "bin " << h->GetXaxis()->GetBinCenter(ix) << ": " << mean << " +/- " << sigma << std::endl;

        jes->SetPoint(iN, h->GetXaxis()->GetBinCenter(ix), mean);
        jer->SetPoint(iN, h->GetXaxis()->GetBinCenter(ix), sigma);
        iN++;

        delete fit;
        delete proj;
    }

    return std::pair<TGraph *, TGraph *>(jes, jer);
}

void draw_jec_jer_comparison()
{
    gStyle->SetErrorX(0.5);
    TString nbins = "26";
    TString algo = "erfXGaus";
    TString suffix = algo+nbins+"EtaBinsJEC";
    TString fin_name = "histos/beamAPlusB_pthat0_"+suffix+"_kinematics.root";

    // Load files
    TFile *fin = new TFile(fin_name);
    TH3F *h_jes_vs_refpt_vs_jteta_wJEC = (TH3F *) fin->Get("h_jes_w_jec_vs_refpt_vs_jteta")->Clone("h_jes_vs_refpt_vs_jteta_wJEC"); // custom bins
    TH3F *h_jes_vs_refpt_vs_jteta_s_wJEC = (TH3F *) fin->Get("h_jes_w_jec_vs_refpt_vs_jteta_s")->Clone("h_jes_vs_refpt_vs_jteta_s_wJEC"); // original bins
    TH3F *h_jes_vs_refpt_vs_jteta_noJEC = (TH3F *) fin->Get("h_jes_vs_refpt_vs_jteta")->Clone("h_jes_vs_refpt_vs_jteta_noJEC"); // custom bins
    TH3F *h_jes_vs_refpt_vs_jteta_s_noJEC = (TH3F *) fin->Get("h_jes_vs_refpt_vs_jteta_s")->Clone("h_jes_vs_refpt_vs_jteta_s_noJEC"); // original bins

    std::vector<TH3F *> h_jes_vs_refpt_vs_jteta_vec = {
        h_jes_vs_refpt_vs_jteta_wJEC, 
        h_jes_vs_refpt_vs_jteta_s_wJEC,
        h_jes_vs_refpt_vs_jteta_noJEC,
        h_jes_vs_refpt_vs_jteta_s_noJEC
    };
    std::vector<TString> labels = {
        algo+nbins+"EtaBins",
        algo+"82EtaBins",
        "noJEC"+nbins+"EtaBins",
        "noJEC82EtaBins",
    };

    size_t nhist = h_jes_vs_refpt_vs_jteta_vec.size();

    // --------------------------------------//
    //                                       //
    //           DRAW BY JTETA               //
    //                                       //
    // --------------------------------------//

    // Barrel region : |jteta|<1.3;
   double lim = 1.305;
    std::vector<std::pair<TGraph *, TGraph *>> jes_jer_BB_vec;
    for (size_t i = 0; i < nhist; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(-lim), h3d->GetZaxis()->FindBin(+lim-(1e-2)));
        TH2F *h2d = (TH2F *) h3d->Project3D("BB_yx");
        h3d->GetZaxis()->SetRange(); // reset range
        jes_jer_BB_vec.push_back(get_jes_jer_vs_refpt(h2d));
    }
    
    // Endcap with tracker : 1.3 < |jteta| < 2.5
    double lim1 = 1.305, lim2 = 2.5;
    std::vector<std::pair<TGraph *, TGraph *>> jes_jer_EC1_vec;
    for (size_t i = 0; i < nhist; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(-lim2), h3d->GetZaxis()->FindBin(-lim1-(1e-2)));
        TH2F *h2d = (TH2F *) h3d->Project3D("C1_yx");
        h3d->GetZaxis()->SetRange(); // reset range
        h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(lim1), h3d->GetZaxis()->FindBin(lim2-(1e-2)));
        h2d->Add((TH2F *) h3d->Project3D("C1_2_yx"));
        h3d->GetZaxis()->SetRange(); // reset range
        jes_jer_EC1_vec.push_back(get_jes_jer_vs_refpt(h2d));
    }

    // Endcap without tracker : 2.5 < |jteta| < 3.0
    lim1 = 2.5; lim2 = 2.964;
    std::vector<std::pair<TGraph *, TGraph *>> jes_jer_EC2_vec;
    for (size_t i = 0; i < nhist; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(-lim2), h3d->GetZaxis()->FindBin(-lim1-(1e-2)));
        TH2F *h2d = (TH2F *) h3d->Project3D("C2_yx");
        h3d->GetZaxis()->SetRange(); // reset range
        h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(lim1), h3d->GetZaxis()->FindBin(lim2-(1e-2)));
        h2d->Add((TH2F *) h3d->Project3D("C2_2_yx"));
        h3d->GetZaxis()->SetRange(); // reset range
        jes_jer_EC2_vec.push_back(get_jes_jer_vs_refpt(h2d));
    }

    // Forward : 3.0 < |jteta| < 5.2
    lim1 = 2.964; lim2 = 5.191;
    std::vector<std::pair<TGraph *, TGraph *>> jes_jer_HF_vec;
    for (size_t i = 0; i < nhist; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(-lim2), h3d->GetZaxis()->FindBin(-lim1-(1e-2)));
        TH2F *h2d = (TH2F *) h3d->Project3D("HF_yx");
        h3d->GetZaxis()->SetRange(); // reset range
        h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(lim1), h3d->GetZaxis()->FindBin(lim2-(1e-2)));
        h2d->Add((TH2F *) h3d->Project3D("HF_2_yx"));
        h3d->GetZaxis()->SetRange(); // reset range
        jes_jer_HF_vec.push_back(get_jes_jer_vs_refpt(h2d));
    }

    for (size_t i = 0; i < nhist; ++i) {
        // Draw JES vs refpt
        TString label = "jes_vs_refpt_per_eta_" + labels[i];
        TCanvas *c_jes = new TCanvas(label, "", 700, 600);
        jes_jer_BB_vec[i].first->Draw("APZ");
        jes_jer_EC1_vec[i].first->Draw("P same");
        jes_jer_EC2_vec[i].first->Draw("P same");
        jes_jer_HF_vec[i].first->Draw("P same");

        formatCanvas(c_jes);
        formatGraph(jes_jer_BB_vec[i].first, "p_{T}^{ref} (GeV)", "JES", cmsBlue);
        formatGraph(jes_jer_EC1_vec[i].first, "p_{T}^{ref} (GeV)", "JES", cmsRed);
        formatGraph(jes_jer_EC2_vec[i].first, "p_{T}^{ref} (GeV)", "JES", cmsOrange);
        formatGraph(jes_jer_HF_vec[i].first, "p_{T}^{ref} (GeV)", "JES", cmsViolet);
        drawHeader();

        TLegend *leg_per_eta = new TLegend(0.25, 0.7, 0.9, 0.85);
        leg_per_eta->SetBorderSize(0);
        leg_per_eta->SetFillStyle(0);
        leg_per_eta->SetTextSize(22);
        leg_per_eta->SetNColumns(2);
        leg_per_eta->AddEntry(jes_jer_BB_vec[i].first, "0.0 < |#eta| < 1.305", "pl");
        leg_per_eta->AddEntry(jes_jer_EC1_vec[i].first, "1.305 < |#eta| < 2.5", "pl");
        leg_per_eta->AddEntry(jes_jer_EC2_vec[i].first, "2.5 < |#eta| < 2.964", "pl");
        leg_per_eta->AddEntry(jes_jer_HF_vec[i].first, "2.964 < |#eta| < 5.191", "pl");
        leg_per_eta->Draw();

        c_jes->Print("plots/"+label+".png");

        // Draw JER vs refpt
        label = "jer_vs_refpt_per_eta_" + labels[i];
        TCanvas *c_jer = new TCanvas(label, "", 700, 600);
        jes_jer_BB_vec[i].second->Draw("APZ");
        jes_jer_EC1_vec[i].second->Draw("P same");
        jes_jer_EC2_vec[i].second->Draw("P same");
        jes_jer_HF_vec[i].second->Draw("P same");

        formatCanvas(c_jer);
        formatGraph(jes_jer_BB_vec[i].second, "p_{T}^{ref} (GeV)", "JER", cmsBlue);
        formatGraph(jes_jer_EC1_vec[i].second, "p_{T}^{ref} (GeV)", "JER", cmsRed);
        formatGraph(jes_jer_EC2_vec[i].second, "p_{T}^{ref} (GeV)", "JER", cmsOrange);
        formatGraph(jes_jer_HF_vec[i].second, "p_{T}^{ref} (GeV)", "JER", cmsViolet);
        drawHeader();

        leg_per_eta->Draw();

        c_jer->Print("plots/"+label+".png");
    }

    // --------------------------------------//
    //                                       //
    //           DRAW BY REFPT               //
    //                                       //
    // --------------------------------------//

    // refpt in [5, 10] GeV
    lim1 = 5; lim2 = 10;
    std::vector<std::pair<TGraph *, TGraph *>> jes_jer_ptbin1_vec;
    for (size_t i = 0; i < nhist; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(lim1), h3d->GetXaxis()->FindBin(lim2-(1e-2)));
        TH2F *h2d = (TH2F *) h3d->Project3D("ptbin1_yz");
        h3d->GetXaxis()->SetRange(); // reset range
        jes_jer_ptbin1_vec.push_back(get_jes_jer_vs_jteta(h2d));
    }

    // refpt in [10, 15] GeV
    lim1 = 10; lim2 = 15;
    std::vector<std::pair<TGraph *, TGraph *>> jes_jer_ptbin2_vec;
    for (size_t i = 0; i < nhist; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(lim1), h3d->GetXaxis()->FindBin(lim2-(1e-2)));
        TH2F *h2d = (TH2F *) h3d->Project3D("ptbin2_yz");
        h3d->GetXaxis()->SetRange(); // reset range
        jes_jer_ptbin2_vec.push_back(get_jes_jer_vs_jteta(h2d));
    }

    // refpt in [15, 20] GeV
    lim1 = 15; lim2 = 20;
    std::vector<std::pair<TGraph *, TGraph *>> jes_jer_ptbin3_vec;
    for (size_t i = 0; i < nhist; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(lim1), h3d->GetXaxis()->FindBin(lim2-(1e-2)));
        TH2F *h2d = (TH2F *) h3d->Project3D("ptbin3_yz");
        h3d->GetXaxis()->SetRange(); // reset range
        jes_jer_ptbin3_vec.push_back(get_jes_jer_vs_jteta(h2d));
    }

    // refpt in [20, 30] GeV
    lim1 = 20; lim2 = 30;
    std::vector<std::pair<TGraph *, TGraph *>> jes_jer_ptbin4_vec;
    for (size_t i = 0; i < nhist; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(lim1), h3d->GetXaxis()->FindBin(lim2-(1e-2)));
        TH2F *h2d = (TH2F *) h3d->Project3D("ptbin4_yz");
        h3d->GetXaxis()->SetRange(); // reset range
        jes_jer_ptbin4_vec.push_back(get_jes_jer_vs_jteta(h2d));
    }

    // refpt in [30, 50] GeV
    lim1 = 30; lim2 = 50;
    std::vector<std::pair<TGraph *, TGraph *>> jes_jer_ptbin5_vec;
    for (size_t i = 0; i < nhist; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(lim1), h3d->GetXaxis()->FindBin(lim2-(1e-2)));
        TH2F *h2d = (TH2F *) h3d->Project3D("ptbin5_yz");
        h3d->GetXaxis()->SetRange(); // reset range
        jes_jer_ptbin5_vec.push_back(get_jes_jer_vs_jteta(h2d));
    }

    for (size_t i = 0; i < nhist; ++i) {
        // Draw JES vs jteta
        TString label = "jes_vs_jteta_per_refpt_" + labels[i];
        TCanvas *c_jes = new TCanvas(label, "", 700, 600);
        jes_jer_ptbin1_vec[i].first->Draw("APZ");
        jes_jer_ptbin2_vec[i].first->Draw("P same");
        jes_jer_ptbin3_vec[i].first->Draw("P same");
        jes_jer_ptbin4_vec[i].first->Draw("P same");
        jes_jer_ptbin5_vec[i].first->Draw("P same");

        formatCanvas(c_jes);
        formatGraph(jes_jer_ptbin1_vec[i].first, "#eta^{jet}", "JES", cmsViolet);
        formatGraph(jes_jer_ptbin2_vec[i].first, "#eta^{jet}", "JES", cmsBlue);
        formatGraph(jes_jer_ptbin3_vec[i].first, "#eta^{jet}", "JES", cmsLightBlue);
        formatGraph(jes_jer_ptbin4_vec[i].first, "#eta^{jet}", "JES", cmsRed);
        formatGraph(jes_jer_ptbin5_vec[i].first, "#eta^{jet}", "JES", cmsOrange);
        drawHeader();

        TLegend *leg_per_pt = new TLegend(0.4, 0.7, 0.9, 0.85);
        leg_per_pt->SetBorderSize(0);
        leg_per_pt->SetFillStyle(0);
        leg_per_pt->SetTextSize(22);
        leg_per_pt->SetNColumns(2);
        leg_per_pt->AddEntry(jes_jer_ptbin1_vec[i].first, "5 < p_{T}^{ref} < 10", "pl");
        leg_per_pt->AddEntry(jes_jer_ptbin2_vec[i].first, "10 < p_{T}^{ref} < 15", "pl");
        leg_per_pt->AddEntry(jes_jer_ptbin3_vec[i].first, "15 < p_{T}^{ref} < 20", "pl");
        leg_per_pt->AddEntry(jes_jer_ptbin4_vec[i].first, "20 < p_{T}^{ref} < 30", "pl");
        leg_per_pt->AddEntry(jes_jer_ptbin5_vec[i].first, "30 < p_{T}^{ref} < 50", "pl");
        leg_per_pt->Draw();

        c_jes->Print("plots/"+label+".png");

        // Draw JER vs jteta
        label = "jer_vs_jteta_per_refpt_" + labels[i];
        TCanvas *c_jer = new TCanvas(label, "", 700, 600);
        jes_jer_ptbin1_vec[i].second->Draw("APZ");
        jes_jer_ptbin2_vec[i].second->Draw("P same");
        jes_jer_ptbin3_vec[i].second->Draw("P same");
        jes_jer_ptbin4_vec[i].second->Draw("P same");
        jes_jer_ptbin5_vec[i].second->Draw("P same");

        formatCanvas(c_jer);
        formatGraph(jes_jer_ptbin1_vec[i].second, "#eta^{jet}", "JER", cmsViolet);
        formatGraph(jes_jer_ptbin2_vec[i].second, "#eta^{jet}", "JER", cmsBlue);
        formatGraph(jes_jer_ptbin3_vec[i].second, "#eta^{jet}", "JER", cmsLightBlue);
        formatGraph(jes_jer_ptbin4_vec[i].second, "#eta^{jet}", "JER", cmsRed);
        formatGraph(jes_jer_ptbin5_vec[i].second, "#eta^{jet}", "JER", cmsOrange);
        drawHeader();

        leg_per_pt->Draw();

        c_jer->Print("plots/"+label+".png");
    }
}