#include "../cms_palette.h"

void drawHeader()
{
    TLatex *latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(26);
    latex->DrawLatex(0.15, 0.92, "#bf{CMS} #it{Internal Simulation}");
    latex->DrawLatex(0.48, 0.92, "PYTHIA8 GNucleus (5.36 TeV)");
}

void formatCanvas(TCanvas *c)
{
    c->SetLeftMargin(0.15);
    c->SetRightMargin(0.05);
    c->SetBottomMargin(0.15);
    c->SetTopMargin(0.1);
}

void formatGraph(TGraph *gr, TString xlabel, TString ylabel, Int_t color, Int_t shape)
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
    if (ylabel.Contains("JES")) gr->GetYaxis()->SetRangeUser(0.9, 1.2);
    else if (ylabel.Contains("JER")) gr->GetYaxis()->SetRangeUser(0, 0.8);

    gr->SetLineWidth(4);
    gr->SetLineColor(color);
    gr->SetMarkerColor(color);
    gr->SetMarkerStyle(shape);
    if (shape==0) gr->SetLineColorAlpha(color, 0.5);
}

std::pair<TGraph *, TGraph *> get_jes_jer_vs_refpt(TH2F *h)
{
    // Expecting h with x=refpt, y=jtpt/refpt within a given jteta range
    std::cout << "Calculating JES and JER vs refpt from " << h->GetName() << std::endl;
    int nX = h->GetNbinsX();
    TGraph *jes = new TGraph();
    TGraph *jer = new TGraph();

    // for each refpt, fit the jtpt/refpt distribution
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

        jes->SetPoint(ix-1, h->GetXaxis()->GetBinCenter(ix), mean);
        jer->SetPoint(ix-1, h->GetXaxis()->GetBinCenter(ix), sigma);

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

        // std::cout << mean << " +/- " << sigma << std::endl;

        jes->SetPoint(ix-1, h->GetXaxis()->GetBinCenter(ix), mean);
        jer->SetPoint(ix-1, h->GetXaxis()->GetBinCenter(ix), sigma);

        delete fit;
        delete proj;
    }

    return std::pair<TGraph *, TGraph *>(jes, jer);
}

void draw_jes_jer_v2()
{
    gStyle->SetErrorX(0.5);
    TString sample = "beamB_diffraction_pthat10";
    TString suffix = "_newJEC_wIDVM";

    // Load files
    TFile *fin = new TFile("histos/" + sample + "_jes" + suffix + ".root");

    TH3F *h_rawpt_jes_vs_refpt_vs_jteta = (TH3F *) fin->Get("h_rawpt_jes_vs_refpt_vs_jteta");
    TH3F *h_jtpt_jes_vs_refpt_vs_jteta = (TH3F *) fin->Get("h_jtpt_jes_vs_refpt_vs_jteta");
    TH3F *h_corpt_jes_vs_refpt_vs_jteta = (TH3F *) fin->Get("h_corpt_jes_vs_refpt_vs_jteta");

    std::vector<TH3F *> h_jes_vs_refpt_vs_jteta_vec = {
        // h_rawpt_jes_vs_refpt_vs_jteta,
        // h_jtpt_jes_vs_refpt_vs_jteta,
        h_corpt_jes_vs_refpt_vs_jteta,
    };

    TH3F *h_rawpt_jes_vs_refpt_vs_jteta_lead = (TH3F *) fin->Get("h_rawpt_jes_vs_refpt_vs_jteta_lead");
    TH3F *h_jtpt_jes_vs_refpt_vs_jteta_lead = (TH3F *) fin->Get("h_jtpt_jes_vs_refpt_vs_jteta_lead");
    TH3F *h_corpt_jes_vs_refpt_vs_jteta_lead = (TH3F *) fin->Get("h_corpt_jes_vs_refpt_vs_jteta_lead");

    std::vector<TH3F *> h_jes_vs_refpt_vs_jteta_lead_vec = {
        h_rawpt_jes_vs_refpt_vs_jteta_lead,
        h_jtpt_jes_vs_refpt_vs_jteta_lead,
        h_corpt_jes_vs_refpt_vs_jteta_lead,
    };

    TH3F *h_rawpt_jes_vs_refpt_vs_jteta_sub = (TH3F *) fin->Get("h_rawpt_jes_vs_refpt_vs_jteta_sub");
    TH3F *h_jtpt_jes_vs_refpt_vs_jteta_sub = (TH3F *) fin->Get("h_jtpt_jes_vs_refpt_vs_jteta_sub");
    TH3F *h_corpt_jes_vs_refpt_vs_jteta_sub = (TH3F *) fin->Get("h_corpt_jes_vs_refpt_vs_jteta_sub");

    std::vector<TH3F *> h_jes_vs_refpt_vs_jteta_sub_vec = {
        h_rawpt_jes_vs_refpt_vs_jteta_sub,
        h_jtpt_jes_vs_refpt_vs_jteta_sub,
        h_corpt_jes_vs_refpt_vs_jteta_sub,
    };

    TH3F *h_rawpt_jes_vs_refpt_vs_jteta_third = (TH3F *) fin->Get("h_rawpt_jes_vs_refpt_vs_jteta_third");
    TH3F *h_jtpt_jes_vs_refpt_vs_jteta_third = (TH3F *) fin->Get("h_jtpt_jes_vs_refpt_vs_jteta_third");
    TH3F *h_corpt_jes_vs_refpt_vs_jteta_third = (TH3F *) fin->Get("h_corpt_jes_vs_refpt_vs_jteta_third");

    std::vector<TH3F *> h_jes_vs_refpt_vs_jteta_third_vec = {
        h_rawpt_jes_vs_refpt_vs_jteta_third,
        h_jtpt_jes_vs_refpt_vs_jteta_third,
        h_corpt_jes_vs_refpt_vs_jteta_third,
    };

    std::vector<TString> titles = {"Raw", "Old JEC", "New JEC"};

    // ----- 1 canvas per jet rank and correction -----

    std::vector<std::vector<TH3F *>> h_jes_vs_refpt_vs_jteta_vecs = {
        // h_jes_vs_refpt_vs_jteta_vec,
        // h_jes_vs_refpt_vs_jteta_lead_vec,
        h_jes_vs_refpt_vs_jteta_sub_vec,
        // h_jes_vs_refpt_vs_jteta_third_vec,
    };

    for (int i = 0; i < h_jes_vs_refpt_vs_jteta_vecs.size(); i++) {
        for (int j = 0; j < h_jes_vs_refpt_vs_jteta_vecs[i].size(); j++) {
            TCanvas *c_jes = new TCanvas(Form("c_jes_%d_%d", i, j), titles[j], 1200, 600);
            c_jes->Divide(2, 1);
            
            // ----- DRAW BY ETA REGIONS -----
            TH3F *h3d = h_jes_vs_refpt_vs_jteta_vecs[i][j];
            h3d->RebinX(5);

            // Barrel region : |jteta|<1.3
            double lim = 2.5; // edited for analysis
            h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(-lim), h3d->GetZaxis()->FindBin(+lim));
            TH2F *h2d_BB = (TH2F *) h3d->Project3D("BB_yx");
            h3d->GetZaxis()->SetRange(); // reset range
            auto [jes_BB, jer_BB] = get_jes_jer_vs_refpt(h2d_BB);
            
            // Inner endcap : 1.3 < |jteta| < 2.5
            double lim1 = 1.3, lim2 = 2.5;
            // h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(-lim2), h3d->GetZaxis()->FindBin(-lim1));
            // TH2F *h2d_EC1 = (TH2F *) h3d->Project3D("C1_yx");
            // h3d->GetZaxis()->SetRange(); // reset range
            // h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(lim1), h3d->GetZaxis()->FindBin(lim2));
            // h2d_EC1->Add((TH2F *) h3d->Project3D("C1_2_yx"));
            // h3d->GetZaxis()->SetRange(); // reset range
            // auto [jes_EC1, jer_EC1] = get_jes_jer_vs_refpt(h2d_EC1);
    
            // Outer endcap : 2.5 < |jteta| < 3.0
            // lim1 = 2.5; lim2 = 3.0;
            // h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(-lim2), h3d->GetZaxis()->FindBin(-lim1));
            // TH2F *h2d_EC2 = (TH2F *) h3d->Project3D("C2_yx");
            // h3d->GetZaxis()->SetRange(); // reset range
            // h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(lim1), h3d->GetZaxis()->FindBin(lim2));
            // h2d_EC2->Add((TH2F *) h3d->Project3D("C2_2_yx"));
            // h3d->GetZaxis()->SetRange(); // reset range
            // auto [jes_EC2, jer_EC2] = get_jes_jer_vs_refpt(h2d_EC2);

            // Forward : 3.0 < |jteta| < 5.2
            // lim1 = 3.0; lim2 = 5.2;
            // h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(-lim2), h3d->GetZaxis()->FindBin(-lim1));
            // TH2F *h2d_HF = (TH2F *) h3d->Project3D("HF_yx");
            // h3d->GetZaxis()->SetRange(); // reset range
            // h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(lim1), h3d->GetZaxis()->FindBin(lim2));
            // h2d_HF->Add((TH2F *) h3d->Project3D("HF_2_yx"));
            // h3d->GetZaxis()->SetRange(); // reset range
            // auto [jes_HF, jer_HF] = get_jes_jer_vs_refpt(h2d_HF);

            c_jes->cd(1);             

            formatGraph(jes_BB, "p_{T}^{ref} (GeV)", "JES", cmsBlue, kFullCircle);
            // formatGraph(jes_EC1, "p_{T}^{ref} (GeV)", "JES", cmsViolet, kFullTriangleUp);
            // formatGraph(jes_EC2, "p_{T}^{ref} (GeV)", "JES", cmsOrange, kFullTriangleDown);
            // formatGraph(jes_HF, "p_{T}^{ref} (GeV)", "JES", cmsRed, kFullDiamond);

            jes_BB->Draw("AP");
            // jes_EC1->Draw("P same");
            // jes_EC2->Draw("P same");
            // jes_HF->Draw("P same");

            // TLegend *leg_jes = new TLegend(0.2, 0.2, 0.8, 0.8);
            // leg_jes->AddEntry(jes_BB, "|#eta|<1.3", "pl");
            // leg_jes->AddEntry(jes_EC1, "1.3<|#eta|<2.5", "pl");
            // leg_jes->AddEntry(jes_EC2, "2.5<|#eta|<3.0", "pl");
            // leg_jes->AddEntry(jes_HF, "3.0<|#eta|<5.2", "pl");
            // leg_jes->Draw();

            double xmin = jes_BB->GetHistogram()->GetXaxis()->GetXmin();
            double xmax = jes_BB->GetHistogram()->GetXaxis()->GetXmax();

            TLine *line1 = new TLine(xmin, 1., xmax, 1.);
            line1->SetLineColor(kBlack);
            line1->Draw();

            TLine *line2 = new TLine(xmin, 1.01, xmax, 1.01);
            line2->SetLineColor(kGray);
            line2->SetLineStyle(kDashed);
            line2->Draw();

            TLine *line3 = new TLine(xmin, 0.99, xmax, 0.99);
            line3->SetLineColor(kGray);
            line3->SetLineStyle(kDashed);
            line3->Draw();

            // -------- DRAW BY REFPT ---------------

            h3d->RebinZ(10);

            // refpt in [5, 10] GeV
            lim1 = 5; lim2 = 10 - (1e-2);
            h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(lim1), h3d->GetXaxis()->FindBin(lim2));
            TH2F *h2d_pt1 = (TH2F *) h3d->Project3D("ptbin1_yz");
            h3d->GetXaxis()->SetRange(); // reset range
            auto [jes_pt1, jer_pt1] = get_jes_jer_vs_jteta(h2d_pt1);

            // refpt in [10, 15] GeV
            lim1 = 10; lim2 = 15 - (1e-2);
            h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(lim1), h3d->GetXaxis()->FindBin(lim2));
            TH2F *h2d_pt2 = (TH2F *) h3d->Project3D("ptbin2_yz");
            h3d->GetXaxis()->SetRange(); // reset range
            auto [jes_pt2, jer_pt2] = get_jes_jer_vs_jteta(h2d_pt2);

            // refpt in [15, 20] GeV
            lim1 = 15; lim2 = 20 - (1e-2);
            h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(lim1), h3d->GetXaxis()->FindBin(lim2));
            TH2F *h2d_pt3 = (TH2F *) h3d->Project3D("ptbin3_yz");
            h3d->GetXaxis()->SetRange(); // reset range
            auto [jes_pt3, jer_pt3] = get_jes_jer_vs_jteta(h2d_pt3);

            // refpt in [20, 30] GeV
            lim1 = 20; lim2 = 30 - (1e-2);
            h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(lim1), h3d->GetXaxis()->FindBin(lim2));
            TH2F *h2d_pt4 = (TH2F *) h3d->Project3D("ptbin4_yz");
            h3d->GetXaxis()->SetRange(); // reset range
            auto [jes_pt4, jer_pt4] = get_jes_jer_vs_jteta(h2d_pt4);

            // refpt in [30, 50] GeV
            lim1 = 30; lim2 = 50 - (1e-2);
            h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(lim1), h3d->GetXaxis()->FindBin(lim2));
            TH2F *h2d_pt5 = (TH2F *) h3d->Project3D("ptbin5_yz");
            h3d->GetXaxis()->SetRange(); // reset range
            auto [jes_pt5, jer_pt5] = get_jes_jer_vs_jteta(h2d_pt5);

            c_jes->cd(2);

            formatGraph(jes_pt1, "#eta^{jet}", "JES", cmsBlue, kFullCircle);
            formatGraph(jes_pt2, "#eta^{jet}", "JES", cmsViolet, kFullTriangleUp);
            formatGraph(jes_pt3, "#eta^{jet}", "JES", cmsRed, kFullTriangleDown);
            formatGraph(jes_pt4, "#eta^{jet}", "JES", cmsOrange, kFullDiamond);
            formatGraph(jes_pt5, "#eta^{jet}", "JES", cmsYellow, kFullCross);

            jes_pt1->Draw("AP");
            jes_pt2->Draw("P same");
            jes_pt3->Draw("P same");
            jes_pt4->Draw("P same");
            jes_pt5->Draw("P same");

            TLegend *leg_pt = new TLegend(0.5, 0.7, 0.9, 0.9);
            leg_pt->AddEntry(jes_pt1, "5 < p_{T}^{ref} < 10", "pl");
            leg_pt->AddEntry(jes_pt2, "10 < p_{T}^{ref} < 15", "pl");
            leg_pt->AddEntry(jes_pt3, "15 < p_{T}^{ref} < 20", "pl");
            leg_pt->AddEntry(jes_pt4, "20 < p_{T}^{ref} < 30", "pl");
            leg_pt->AddEntry(jes_pt5, "30 < p_{T}^{ref} < 50", "pl");
            leg_pt->Draw();

            xmin = jes_pt1->GetHistogram()->GetXaxis()->GetXmin();
            xmax = jes_pt1->GetHistogram()->GetXaxis()->GetXmax();
            
            TLine *line4 = new TLine(xmin, 1., xmax, 1.);
            line4->SetLineColor(kBlack);
            line4->Draw();

            TLine *line5 = new TLine(xmin, 1.01, xmax, 1.01);
            line5->SetLineColor(kGray);
            line5->SetLineStyle(kDashed);
            line5->Draw();

            TLine *line6 = new TLine(xmin, 0.99, xmax, 0.99);
            line6->SetLineColor(kGray);
            line6->SetLineStyle(kDashed);
            line6->Draw();
        }
    }

    

    

    // // Draw JER vs jteta
    // TCanvas *c_jer_vs_jteta = new TCanvas("c_jer_vs_jteta", "", 1400, 600);
    // TPad *left_pad = new TPad("left_pad", "", 0, 0, 0.5, 1);
    // TPad *right_pad = new TPad("right_pad", "", 0.5, 0, 1, 1);
    // left_pad->SetLeftMargin(0.15);
    // left_pad->SetRightMargin(0.05);
    // left_pad->SetBottomMargin(0.15);
    // left_pad->SetTopMargin(0.1);
    // right_pad->SetLeftMargin(0.15);
    // right_pad->SetRightMargin(0.05);
    // right_pad->SetBottomMargin(0.15);
    // right_pad->SetTopMargin(0.1);

    // left_pad->cd();
    // jes_jer_ptbin1_vec[3].second->Draw("APZ");
    // jes_jer_ptbin1_vec[1].second->Draw("C same");

    // formatGraph(jes_jer_ptbin1_vec[3].second, "#eta^{jet}", "JER", cmsBlue, kFullCircle);
    // formatGraph(jes_jer_ptbin1_vec[1].second, "#eta^{jet}", "JER", cmsBlue, 0);

    // right_pad->cd();
    // jes_jer_ptbin1_vec[2].second->Draw("APZ");
    // jes_jer_ptbin1_vec[0].second->Draw("C same");

    // formatGraph(jes_jer_ptbin1_vec[2].second, "#eta^{jet}", "JER", cmsBlue, kFullCircle);
    // formatGraph(jes_jer_ptbin1_vec[0].second, "#eta^{jet}", "JER", cmsBlue, 0);

    // c_jer_vs_jteta->cd();
    // left_pad->Draw();
    // right_pad->Draw();
    

    // formatCanvas(c_jer_vs_jteta);
    // formatGraph(jer_stdPlusGausJEC_ptbin1, "#eta^{jet}", "JER", cmsViolet);
    // formatGraph(jer_stdPlusGausJEC_ptbin2, "#eta^{jet}", "JER", cmsBlue);
    // formatGraph(jer_stdPlusGausJEC_ptbin3, "#eta^{jet}", "JER", cmsLightBlue);
    // formatGraph(jer_stdPlusGausJEC_ptbin4, "#eta^{jet}", "JER", cmsRed);
    // formatGraph(jer_stdPlusGausJEC_ptbin5, "#eta^{jet}", "JER", cmsOrange);
    // jer_stdPlusGausJEC_ptbin1->GetYaxis()->SetRangeUser(0.9, 2.);
    // drawHeader();

    // TLegend *leg_per_pt = new TLegend(0.5, 0.55, 0.8 , 0.85);
    // leg_per_pt->SetBorderSize(0);
    // leg_per_pt->SetTextSize(22);
    // leg_per_pt->AddEntry(jer_stdPlusGausJEC_ptbin1, "  5 < p_{T}^{ref} < 10 GeV", "pl");
    // leg_per_pt->AddEntry(jer_stdPlusGausJEC_ptbin2, "10 < p_{T}^{ref} < 15 GeV", "pl");
    // leg_per_pt->AddEntry(jer_stdPlusGausJEC_ptbin3, "15 < p_{T}^{ref} < 20 GeV", "pl");
    // leg_per_pt->AddEntry(jer_stdPlusGausJEC_ptbin4, "20 < p_{T}^{ref} < 30 GeV", "pl");
    // leg_per_pt->AddEntry(jer_stdPlusGausJEC_ptbin5, "30 < p_{T}^{ref} < 50 GeV", "pl");
    // leg_per_pt->Draw();

    // c_jer_vs_jteta->Print("plots/jer_vs_jteta_per_pt_" + suffix + ".png");

    // Draw JER vs jteta
    // TCanvas *c_jer_vs_jteta = new TCanvas("c_jer_vs_jteta", "", 700, 600);
    // jer_stdPlusGausJEC_ptbin1->Draw("APZ");  
    // jer_stdPlusGausJEC_ptbin2->Draw("P same");
    // jer_stdPlusGausJEC_ptbin3->Draw("P same");
    // jer_stdPlusGausJEC_ptbin4->Draw("P same");
    // jer_stdPlusGausJEC_ptbin5->Draw("P same");

    // formatCanvas(c_jer_vs_jteta);
    // formatGraph(jer_stdPlusGausJEC_ptbin1, "#eta^{jet}", "JER", cmsViolet);
    // formatGraph(jer_stdPlusGausJEC_ptbin2, "#eta^{jet}", "JER", cmsBlue);
    // formatGraph(jer_stdPlusGausJEC_ptbin3, "#eta^{jet}", "JER", cmsLightBlue);
    // formatGraph(jer_stdPlusGausJEC_ptbin4, "#eta^{jet}", "JER", cmsRed);
    // formatGraph(jer_stdPlusGausJEC_ptbin5, "#eta^{jet}", "JER", cmsOrange);

    // drawHeader();
    // leg_per_pt->Draw();

    // c_jer_vs_jteta->Print("plots/jer_vs_jteta_per_pt_" + suffix + ".png");
}