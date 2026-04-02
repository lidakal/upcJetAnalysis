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
    if (ylabel.Contains("JES")) gr->GetYaxis()->SetRangeUser(0.9, 1.4);
    else if (ylabel.Contains("JER")) gr->GetYaxis()->SetRangeUser(0, 0.8);

    gr->SetLineWidth(4);
    gr->SetLineColor(color);
    gr->SetMarkerColor(color);
}

void get_jes_jer_vs_refpt(TH2F *h, TGraph *jes, TGraph *jer)
{
    // Expecting h with x=refpt, y=jtpt/refpt within a given jteta range
    std::cout << "Calculating JES and JER vs refpt from " << h->GetName() << std::endl;
    int nX = h->GetNbinsX();

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

        delete proj;
    }
}

void get_jes_jer_vs_jteta(TH2F *h, TGraph *jes, TGraph *jer)
{
    // Expecting h with x=jteta, y=jtpt/refpt within a given refpt range
    std::cout << "Calculating JES and JER vs jteta from " << h->GetName() << std::endl;
    int nX = h->GetNbinsX();

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

        delete proj;
    }
}

void draw_jec_jer_comparison()
{
    gStyle->SetErrorX(0.5);
    TString suffix = "stdPlusGaus82EtaBinsJEC";

    // Load files
    TFile *f_ppJEC = new TFile("histos/beamAPlusB_pthat0_ppJEC_kinematics.root");
    TH3F *h_jes_vs_refpt_vs_jteta_ppJEC = (TH3F *) f_ppJEC->Get("h_jes_w_jec_vs_refpt_vs_jteta")->Clone("h_jes_vs_refpt_vs_jteta_ppJEC");
    TH3F *h_jes_vs_refpt_vs_jteta_noJEC = (TH3F *) f_ppJEC->Get("h_jes_vs_refpt_vs_jteta")->Clone("h_jes_vs_refpt_vs_jteta_noJEC");

    TFile *f_stdPlusGausJEC = new TFile("histos/beamAPlusB_pthat0_"+suffix+"_kinematics.root");
    TH3F *h_jes_vs_refpt_vs_jteta_stdPlusGausJEC = (TH3F *) f_stdPlusGausJEC->Get("h_jes_w_jec_vs_refpt_vs_jteta")->Clone("h_jes_vs_refpt_vs_jteta_stdPlusGausJEC");

    std::vector<TH3F *> h_jes_vs_refpt_vs_jteta_vec = {h_jes_vs_refpt_vs_jteta_noJEC, h_jes_vs_refpt_vs_jteta_ppJEC, h_jes_vs_refpt_vs_jteta_stdPlusGausJEC};
    size_t ncor = h_jes_vs_refpt_vs_jteta_vec.size();

    // ----- DRAW BY ETA REGIONS -----

    // Barrel region : |jteta|<1.3
    TH2F    *h_jes_vs_refpt_noJEC_BB = new TH2F(), 
            *h_jes_vs_refpt_ppJEC_BB = new TH2F(), 
            *h_jes_vs_refpt_stdPlusGausJEC_BB = new TH2F();
    TGraph  *jes_noJEC_BB = new TGraph(), 
            *jes_ppJEC_BB = new TGraph(), 
            *jes_stdPlusGausJEC_BB = new TGraph();
    TGraph  *jer_noJEC_BB = new TGraph(), 
            *jer_ppJEC_BB = new TGraph(), 
            *jer_stdPlusGausJEC_BB = new TGraph();
    std::vector<TH2F *>     h_jes_vs_refpt_BB_vec       = {h_jes_vs_refpt_noJEC_BB, h_jes_vs_refpt_ppJEC_BB, h_jes_vs_refpt_stdPlusGausJEC_BB};
    std::vector<TGraph *>   jes_BB_vec                  = {jes_noJEC_BB, jes_ppJEC_BB, jes_stdPlusGausJEC_BB};
    std::vector<TGraph *>   jer_BB_vec                  = {jer_noJEC_BB, jer_ppJEC_BB, jer_stdPlusGausJEC_BB};
    for (size_t i = 0; i < ncor; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        TH2F *h2d = (TH2F *) h_jes_vs_refpt_BB_vec[i];
        TGraph *jes = jes_BB_vec[i];
        TGraph *jer = jer_BB_vec[i];
        h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(-1.3), h3d->GetZaxis()->FindBin(1.3));
        std::cout << "bin " << h3d->GetZaxis()->FindBin(-1.3) << " to " << h3d->GetZaxis()->FindBin(1.3) << std::endl;
        std::cout << "eta " << h3d->GetZaxis()->GetBinLowEdge(h3d->GetZaxis()->FindBin(-1.3)) << " to " << h3d->GetZaxis()->GetBinUpEdge(h3d->GetZaxis()->FindBin(1.3)) << std::endl;
        h2d = (TH2F *) h3d->Project3D("BB_yx");
        h3d->GetZaxis()->SetRange(); // reset range
        get_jes_jer_vs_refpt(h2d, jes, jer);
    }
    
    // Endcap with tracker : 1.3 < |jteta| < 2.5
    TH2F    *h_jes_vs_refpt_noJEC_EC1 = new TH2F(), 
            *h_jes_vs_refpt_ppJEC_EC1 = new TH2F(), 
            *h_jes_vs_refpt_stdPlusGausJEC_EC1 = new TH2F();
    TGraph  *jes_noJEC_EC1 = new TGraph(), 
            *jes_ppJEC_EC1 = new TGraph(), 
            *jes_stdPlusGausJEC_EC1 = new TGraph();
    TGraph  *jer_noJEC_EC1 = new TGraph(), 
            *jer_ppJEC_EC1 = new TGraph(), 
            *jer_stdPlusGausJEC_EC1 = new TGraph();
    std::vector<TH2F *>     h_jes_vs_refpt_EC1_vec  = { h_jes_vs_refpt_noJEC_EC1, 
                                                        h_jes_vs_refpt_ppJEC_EC1, 
                                                        h_jes_vs_refpt_stdPlusGausJEC_EC1};
    std::vector<TGraph *>   jes_EC1_vec             = { jes_noJEC_EC1, 
                                                        jes_ppJEC_EC1, 
                                                        jes_stdPlusGausJEC_EC1};
    std::vector<TGraph *>   jer_EC1_vec             = { jer_noJEC_EC1,  
                                                        jer_ppJEC_EC1, 
                                                        jer_stdPlusGausJEC_EC1};
    for (size_t i = 0; i < ncor; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        TH2F *h2d = (TH2F *) h_jes_vs_refpt_EC1_vec[i];
        TGraph *jes = jes_EC1_vec[i];
        TGraph *jer = jer_EC1_vec[i];
        h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(-2.5), h3d->GetZaxis()->FindBin(-1.3));
        h2d = (TH2F *) h3d->Project3D("C1_yx");
        h3d->GetZaxis()->SetRange(); // reset range
        h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(1.3), h3d->GetZaxis()->FindBin(2.5));
        h2d->Add((TH2F *) h3d->Project3D("C1_2_yx"));
        h3d->GetZaxis()->SetRange(); // reset range
        get_jes_jer_vs_refpt(h2d, jes, jer);
    }

    // Endcap without tracker : 2.5 < |jteta| < 3.0
    TH2F    *h_jes_vs_refpt_noJEC_EC2 = new TH2F(), *h_jes_vs_refpt_ppJEC_EC2 = new TH2F(), *h_jes_vs_refpt_stdPlusGausJEC_EC2 = new TH2F();
    TGraph  *jes_noJEC_EC2 = new TGraph(), *jes_ppJEC_EC2 = new TGraph(), *jes_stdPlusGausJEC_EC2 = new TGraph();
    TGraph  *jer_noJEC_EC2 = new TGraph(), *jer_ppJEC_EC2 = new TGraph(), *jer_stdPlusGausJEC_EC2 = new TGraph();
    std::vector<TH2F *>     h_jes_vs_refpt_EC2_vec       = {h_jes_vs_refpt_noJEC_EC2, h_jes_vs_refpt_ppJEC_EC2, h_jes_vs_refpt_stdPlusGausJEC_EC2};
    std::vector<TGraph *>   jes_EC2_vec                  = {jes_noJEC_EC2, jes_ppJEC_EC2, jes_stdPlusGausJEC_EC2};
    std::vector<TGraph *>   jer_EC2_vec                  = {jer_noJEC_EC2, jer_ppJEC_EC2, jer_stdPlusGausJEC_EC2};
    for (size_t i = 0; i < ncor; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        TH2F *h2d = (TH2F *) h_jes_vs_refpt_EC2_vec[i];
        TGraph *jes = jes_EC2_vec[i];
        TGraph *jer = jer_EC2_vec[i];
        h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(-3.0), h3d->GetZaxis()->FindBin(-2.5));
        h2d = (TH2F *) h3d->Project3D("C2_yx");
        h3d->GetZaxis()->SetRange(); // reset range
        h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(2.5), h3d->GetZaxis()->FindBin(3.0));
        h2d->Add((TH2F *) h3d->Project3D("C2_2_yx"));
        h3d->GetZaxis()->SetRange(); // reset range
        get_jes_jer_vs_refpt(h2d, jes, jer);
    }

    // Forward : 3.0 < |jteta| < 5.2
    TH2F    *h_jes_vs_refpt_noJEC_HF = new TH2F(), *h_jes_vs_refpt_ppJEC_HF = new TH2F(), *h_jes_vs_refpt_stdPlusGausJEC_HF = new TH2F();
    TGraph  *jes_noJEC_HF = new TGraph(), *jes_ppJEC_HF = new TGraph(), *jes_stdPlusGausJEC_HF = new TGraph();
    TGraph  *jer_noJEC_HF = new TGraph(), *jer_ppJEC_HF = new TGraph(), *jer_stdPlusGausJEC_HF = new TGraph();
    std::vector<TH2F *>     h_jes_vs_refpt_HF_vec       = {h_jes_vs_refpt_noJEC_HF, h_jes_vs_refpt_ppJEC_HF, h_jes_vs_refpt_stdPlusGausJEC_HF};
    std::vector<TGraph *>   jes_HF_vec                  = {jes_noJEC_HF, jes_ppJEC_HF, jes_stdPlusGausJEC_HF};
    std::vector<TGraph *>   jer_HF_vec                  = {jer_noJEC_HF, jer_ppJEC_HF, jer_stdPlusGausJEC_HF};
    for (size_t i = 0; i < ncor; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        TH2F *h2d = (TH2F *) h_jes_vs_refpt_HF_vec[i];
        TGraph *jes = jes_HF_vec[i];
        TGraph *jer = jer_HF_vec[i];
        h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(-5.2), h3d->GetZaxis()->FindBin(-3.0));
        h2d = (TH2F *) h3d->Project3D("HF_yx");
        h3d->GetZaxis()->SetRange(); // reset range
        h3d->GetZaxis()->SetRange(h3d->GetZaxis()->FindBin(3.0), h3d->GetZaxis()->FindBin(5.2));
        h2d->Add((TH2F *) h3d->Project3D("HF_2_yx"));
        h3d->GetZaxis()->SetRange(); // reset range
        get_jes_jer_vs_refpt(h2d, jes, jer);
    }

    // Draw JES vs refpt
    TCanvas *c_jes = new TCanvas("c_jes", "", 700, 600);
    jes_stdPlusGausJEC_BB->Draw("APZ");
    jes_stdPlusGausJEC_EC1->Draw("P same");
    jes_stdPlusGausJEC_EC2->Draw("P same");
    jes_stdPlusGausJEC_HF->Draw("P same");

    formatCanvas(c_jes);
    formatGraph(jes_stdPlusGausJEC_BB, "p_{T}^{ref} (GeV)", "JES", cmsBlue);
    formatGraph(jes_stdPlusGausJEC_EC1, "p_{T}^{ref} (GeV)", "JES", cmsRed);
    formatGraph(jes_stdPlusGausJEC_EC2, "p_{T}^{ref} (GeV)", "JES", cmsOrange);
    formatGraph(jes_stdPlusGausJEC_HF, "p_{T}^{ref} (GeV)", "JES", cmsViolet);
    drawHeader();

    TLegend *leg_per_eta = new TLegend(0.6, 0.6, 0.88, 0.8);
    leg_per_eta->SetBorderSize(0);
    leg_per_eta->SetTextSize(22);
    leg_per_eta->AddEntry(jes_stdPlusGausJEC_BB, "0.0 < |#eta| < 1.3", "pl");
    leg_per_eta->AddEntry(jes_stdPlusGausJEC_EC1, "1.3 < |#eta| < 2.5", "pl");
    leg_per_eta->AddEntry(jes_stdPlusGausJEC_EC2, "2.5 < |#eta| < 3.0", "pl");
    leg_per_eta->AddEntry(jes_stdPlusGausJEC_HF, "3.0 < |#eta| < 5.2", "pl");
    leg_per_eta->Draw();

    c_jes->Print("plots/jes_vs_refpt_per_eta_" + suffix + ".png");

    // Draw JER vs refpt
    TCanvas *c_jer = new TCanvas("c_jer", "", 700, 600);
    jer_stdPlusGausJEC_BB->Draw("APZ");  
    jer_stdPlusGausJEC_EC1->Draw("P same");
    jer_stdPlusGausJEC_EC2->Draw("P same");
    jer_stdPlusGausJEC_HF->Draw("P same");

    formatCanvas(c_jer);
    formatGraph(jer_stdPlusGausJEC_BB, "p_{T}^{ref} (GeV)", "JER", cmsBlue);
    formatGraph(jer_stdPlusGausJEC_EC1, "p_{T}^{ref} (GeV)", "JER", cmsRed);
    formatGraph(jer_stdPlusGausJEC_EC2, "p_{T}^{ref} (GeV)", "JER", cmsOrange);
    formatGraph(jer_stdPlusGausJEC_HF, "p_{T}^{ref} (GeV)", "JER", cmsViolet);
    drawHeader();
    leg_per_eta->Draw();

    c_jer->Print("plots/jer_vs_refpt_per_eta_" + suffix + ".png");

    // --------------------------------------

    // -------- DRAW BY REFPT ---------------

    // refpt in [5, 10] GeV
    TH2F    *h_jes_vs_jteta_noJEC_ptbin1 = new TH2F(), 
            *h_jes_vs_jteta_ppJEC_ptbin1 = new TH2F(), 
            *h_jes_vs_jteta_stdPlusGausJEC_ptbin1 = new TH2F();
    TGraph  *jes_noJEC_ptbin1 = new TGraph(), 
            *jes_ppJEC_ptbin1 = new TGraph(), 
            *jes_stdPlusGausJEC_ptbin1 = new TGraph();
    TGraph  *jer_noJEC_ptbin1 = new TGraph(), 
            *jer_ppJEC_ptbin1 = new TGraph(), 
            *jer_stdPlusGausJEC_ptbin1 = new TGraph();
    std::vector<TH2F *>     h_jes_vs_jteta_ptbin1_vec       = {h_jes_vs_jteta_noJEC_ptbin1, h_jes_vs_jteta_ppJEC_ptbin1, h_jes_vs_jteta_stdPlusGausJEC_ptbin1};
    std::vector<TGraph *>   jes_ptbin1_vec                  = {jes_noJEC_ptbin1, jes_ppJEC_ptbin1, jes_stdPlusGausJEC_ptbin1};
    std::vector<TGraph *>   jer_ptbin1_vec                  = {jer_noJEC_ptbin1, jer_ppJEC_ptbin1, jer_stdPlusGausJEC_ptbin1};
    for (size_t i = 0; i < ncor; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        TH2F *h2d = (TH2F *) h_jes_vs_jteta_ptbin1_vec[i];
        TGraph *jes = jes_ptbin1_vec[i];
        TGraph *jer = jer_ptbin1_vec[i];
        h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(5), h3d->GetXaxis()->FindBin(9.9));
        std::cout << h3d->GetXaxis()->FindBin(5) << " to " << h3d->GetXaxis()->FindBin(9.9) << std::endl;
        std::cout << h3d->GetXaxis()->GetBinLowEdge(h3d->GetXaxis()->FindBin(5)) << " to " << h3d->GetXaxis()->GetBinUpEdge(h3d->GetXaxis()->FindBin(9.9)) << std::endl;
        h2d = (TH2F *) h3d->Project3D("ptbin1_yz");
        h3d->GetXaxis()->SetRange(); // reset range
        get_jes_jer_vs_jteta(h2d, jes, jer);
    }

    // refpt in [10, 15] GeV
    TH2F    *h_jes_vs_jteta_noJEC_ptbin2 = new TH2F(), 
            *h_jes_vs_jteta_ppJEC_ptbin2 = new TH2F(), 
            *h_jes_vs_jteta_stdPlusGausJEC_ptbin2 = new TH2F();
    TGraph  *jes_noJEC_ptbin2 = new TGraph(), 
            *jes_ppJEC_ptbin2 = new TGraph(), 
            *jes_stdPlusGausJEC_ptbin2 = new TGraph();
    TGraph  *jer_noJEC_ptbin2 = new TGraph(), 
            *jer_ppJEC_ptbin2 = new TGraph(), 
            *jer_stdPlusGausJEC_ptbin2 = new TGraph();
    std::vector<TH2F *>     h_jes_vs_jteta_ptbin2_vec       = {h_jes_vs_jteta_noJEC_ptbin2, h_jes_vs_jteta_ppJEC_ptbin2, h_jes_vs_jteta_stdPlusGausJEC_ptbin2};
    std::vector<TGraph *>   jes_ptbin2_vec                  = {jes_noJEC_ptbin2, jes_ppJEC_ptbin2, jes_stdPlusGausJEC_ptbin2};
    std::vector<TGraph *>   jer_ptbin2_vec                  = {jer_noJEC_ptbin2, jer_ppJEC_ptbin2, jer_stdPlusGausJEC_ptbin2};
    for (size_t i = 0; i < ncor; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        TH2F *h2d = (TH2F *) h_jes_vs_jteta_ptbin2_vec[i];
        TGraph *jes = jes_ptbin2_vec[i];
        TGraph *jer = jer_ptbin2_vec[i];
        h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(10), h3d->GetXaxis()->FindBin(14.9));
        std::cout << h3d->GetXaxis()->FindBin(10) << " to " << h3d->GetXaxis()->FindBin(14.9) << std::endl;
        std::cout << h3d->GetXaxis()->GetBinLowEdge(h3d->GetXaxis()->FindBin(10)) << " to " << h3d->GetXaxis()->GetBinUpEdge(h3d->GetXaxis()->FindBin(14.9)) << std::endl;
        h2d = (TH2F *) h3d->Project3D("ptbin2_yz");
        h3d->GetXaxis()->SetRange(); // reset range
        get_jes_jer_vs_jteta(h2d, jes, jer);
    }

    // refpt in [15, 20] GeV
    TH2F    *h_jes_vs_jteta_noJEC_ptbin3 = new TH2F(), 
            *h_jes_vs_jteta_ppJEC_ptbin3 = new TH2F(), 
            *h_jes_vs_jteta_stdPlusGausJEC_ptbin3 = new TH2F();
    TGraph  *jes_noJEC_ptbin3 = new TGraph(), 
            *jes_ppJEC_ptbin3 = new TGraph(), 
            *jes_stdPlusGausJEC_ptbin3 = new TGraph();
    TGraph  *jer_noJEC_ptbin3 = new TGraph(), 
            *jer_ppJEC_ptbin3 = new TGraph(), 
            *jer_stdPlusGausJEC_ptbin3 = new TGraph();
    std::vector<TH2F *>     h_jes_vs_jteta_ptbin3_vec       = {h_jes_vs_jteta_noJEC_ptbin3, h_jes_vs_jteta_ppJEC_ptbin3, h_jes_vs_jteta_stdPlusGausJEC_ptbin3};
    std::vector<TGraph *>   jes_ptbin3_vec                  = {jes_noJEC_ptbin3, jes_ppJEC_ptbin3, jes_stdPlusGausJEC_ptbin3};
    std::vector<TGraph *>   jer_ptbin3_vec                  = {jer_noJEC_ptbin3, jer_ppJEC_ptbin3, jer_stdPlusGausJEC_ptbin3};
    for (size_t i = 0; i < ncor; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        TH2F *h2d = (TH2F *) h_jes_vs_jteta_ptbin3_vec[i];
        TGraph *jes = jes_ptbin3_vec[i];
        TGraph *jer = jer_ptbin3_vec[i];
        h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(15), h3d->GetXaxis()->FindBin(19.9));
        std::cout << h3d->GetXaxis()->FindBin(15) << " to " << h3d->GetXaxis()->FindBin(19.9) << std::endl;
        std::cout << h3d->GetXaxis()->GetBinLowEdge(h3d->GetXaxis()->FindBin(15)) << " to " << h3d->GetXaxis()->GetBinUpEdge(h3d->GetXaxis()->FindBin(19.9)) << std::endl;
        h2d = (TH2F *) h3d->Project3D("ptbin3_yz");
        h3d->GetXaxis()->SetRange(); // reset range
        get_jes_jer_vs_jteta(h2d, jes, jer);
    }

    // refpt in [20, 30] GeV
    TH2F    *h_jes_vs_jteta_noJEC_ptbin4 = new TH2F(), 
            *h_jes_vs_jteta_ppJEC_ptbin4 = new TH2F(), 
            *h_jes_vs_jteta_stdPlusGausJEC_ptbin4 = new TH2F();
    TGraph  *jes_noJEC_ptbin4 = new TGraph(), 
            *jes_ppJEC_ptbin4 = new TGraph(), 
            *jes_stdPlusGausJEC_ptbin4 = new TGraph();
    TGraph  *jer_noJEC_ptbin4 = new TGraph(), 
            *jer_ppJEC_ptbin4 = new TGraph(), 
            *jer_stdPlusGausJEC_ptbin4 = new TGraph();
    std::vector<TH2F *>     h_jes_vs_jteta_ptbin4_vec       = {h_jes_vs_jteta_noJEC_ptbin4, h_jes_vs_jteta_ppJEC_ptbin4, h_jes_vs_jteta_stdPlusGausJEC_ptbin4};
    std::vector<TGraph *>   jes_ptbin4_vec                  = {jes_noJEC_ptbin4, jes_ppJEC_ptbin4, jes_stdPlusGausJEC_ptbin4};
    std::vector<TGraph *>   jer_ptbin4_vec                  = {jer_noJEC_ptbin4, jer_ppJEC_ptbin4, jer_stdPlusGausJEC_ptbin4};
    for (size_t i = 0; i < ncor; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        TH2F *h2d = (TH2F *) h_jes_vs_jteta_ptbin4_vec[i];
        TGraph *jes = jes_ptbin4_vec[i];
        TGraph *jer = jer_ptbin4_vec[i];
        h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(20), h3d->GetXaxis()->FindBin(29.9));
        std::cout << h3d->GetXaxis()->FindBin(20) << " to " << h3d->GetXaxis()->FindBin(29.9) << std::endl;
        std::cout << h3d->GetXaxis()->GetBinLowEdge(h3d->GetXaxis()->FindBin(20)) << " to " << h3d->GetXaxis()->GetBinUpEdge(h3d->GetXaxis()->FindBin(29.9)) << std::endl;
        h2d = (TH2F *) h3d->Project3D("ptbin4_yz");
        h3d->GetXaxis()->SetRange(); // reset range
        get_jes_jer_vs_jteta(h2d, jes, jer);
    }

    // refpt in [30, 50] GeV
    TH2F    *h_jes_vs_jteta_noJEC_ptbin5 = new TH2F(), 
            *h_jes_vs_jteta_ppJEC_ptbin5 = new TH2F(), 
            *h_jes_vs_jteta_stdPlusGausJEC_ptbin5 = new TH2F();
    TGraph  *jes_noJEC_ptbin5 = new TGraph(), 
            *jes_ppJEC_ptbin5 = new TGraph(), 
            *jes_stdPlusGausJEC_ptbin5 = new TGraph();
    TGraph  *jer_noJEC_ptbin5 = new TGraph(), 
            *jer_ppJEC_ptbin5 = new TGraph(), 
            *jer_stdPlusGausJEC_ptbin5 = new TGraph();
    std::vector<TH2F *>     h_jes_vs_jteta_ptbin5_vec       = {h_jes_vs_jteta_noJEC_ptbin5, h_jes_vs_jteta_ppJEC_ptbin5, h_jes_vs_jteta_stdPlusGausJEC_ptbin5};
    std::vector<TGraph *>   jes_ptbin5_vec                  = {jes_noJEC_ptbin5, jes_ppJEC_ptbin5, jes_stdPlusGausJEC_ptbin5};
    std::vector<TGraph *>   jer_ptbin5_vec                  = {jer_noJEC_ptbin5, jer_ppJEC_ptbin5, jer_stdPlusGausJEC_ptbin5};
    for (size_t i = 0; i < ncor; ++i) {
        TH3F *h3d = h_jes_vs_refpt_vs_jteta_vec[i];
        TH2F *h2d = (TH2F *) h_jes_vs_jteta_ptbin5_vec[i];
        TGraph *jes = jes_ptbin5_vec[i];
        TGraph *jer = jer_ptbin5_vec[i];
        h3d->GetXaxis()->SetRange(h3d->GetXaxis()->FindBin(30), h3d->GetXaxis()->FindBin(49.9));
        std::cout << h3d->GetXaxis()->FindBin(30) << " to " << h3d->GetXaxis()->FindBin(49.9) << std::endl;
        std::cout << h3d->GetXaxis()->GetBinLowEdge(h3d->GetXaxis()->FindBin(30)) << " to " << h3d->GetXaxis()->GetBinUpEdge(h3d->GetXaxis()->FindBin(49.9)) << std::endl;
        h2d = (TH2F *) h3d->Project3D("ptbin5_yz");
        h3d->GetXaxis()->SetRange(); // reset range
        get_jes_jer_vs_jteta(h2d, jes, jer);
    }

    // Draw JES vs jteta
    TCanvas *c_jes_vs_jteta = new TCanvas("c_jes_vs_jteta", "", 700, 600);
    jes_stdPlusGausJEC_ptbin1->Draw("APZ");
    jes_stdPlusGausJEC_ptbin2->Draw("P same");
    jes_stdPlusGausJEC_ptbin3->Draw("P same");
    jes_stdPlusGausJEC_ptbin4->Draw("P same");
    jes_stdPlusGausJEC_ptbin5->Draw("P same");

    formatCanvas(c_jes_vs_jteta);
    formatGraph(jes_stdPlusGausJEC_ptbin1, "#eta^{jet}", "JES", cmsViolet);
    formatGraph(jes_stdPlusGausJEC_ptbin2, "#eta^{jet}", "JES", cmsBlue);
    formatGraph(jes_stdPlusGausJEC_ptbin3, "#eta^{jet}", "JES", cmsLightBlue);
    formatGraph(jes_stdPlusGausJEC_ptbin4, "#eta^{jet}", "JES", cmsRed);
    formatGraph(jes_stdPlusGausJEC_ptbin5, "#eta^{jet}", "JES", cmsOrange);
    jes_stdPlusGausJEC_ptbin1->GetYaxis()->SetRangeUser(0.9, 2.);
    drawHeader();

    TLegend *leg_per_pt = new TLegend(0.5, 0.55, 0.8 , 0.85);
    leg_per_pt->SetBorderSize(0);
    leg_per_pt->SetTextSize(22);
    leg_per_pt->AddEntry(jes_stdPlusGausJEC_ptbin1, "  5 < p_{T}^{ref} < 10 GeV", "pl");
    leg_per_pt->AddEntry(jes_stdPlusGausJEC_ptbin2, "10 < p_{T}^{ref} < 15 GeV", "pl");
    leg_per_pt->AddEntry(jes_stdPlusGausJEC_ptbin3, "15 < p_{T}^{ref} < 20 GeV", "pl");
    leg_per_pt->AddEntry(jes_stdPlusGausJEC_ptbin4, "20 < p_{T}^{ref} < 30 GeV", "pl");
    leg_per_pt->AddEntry(jes_stdPlusGausJEC_ptbin5, "30 < p_{T}^{ref} < 50 GeV", "pl");
    leg_per_pt->Draw();

    c_jes_vs_jteta->Print("plots/jes_vs_jteta_per_pt_" + suffix + ".png");

    // Draw JER vs jteta
    TCanvas *c_jer_vs_jteta = new TCanvas("c_jer_vs_jteta", "", 700, 600);
    jer_stdPlusGausJEC_ptbin1->Draw("APZ");  
    jer_stdPlusGausJEC_ptbin2->Draw("P same");
    jer_stdPlusGausJEC_ptbin3->Draw("P same");
    jer_stdPlusGausJEC_ptbin4->Draw("P same");
    jer_stdPlusGausJEC_ptbin5->Draw("P same");

    formatCanvas(c_jer_vs_jteta);
    formatGraph(jer_stdPlusGausJEC_ptbin1, "#eta^{jet}", "JER", cmsViolet);
    formatGraph(jer_stdPlusGausJEC_ptbin2, "#eta^{jet}", "JER", cmsBlue);
    formatGraph(jer_stdPlusGausJEC_ptbin3, "#eta^{jet}", "JER", cmsLightBlue);
    formatGraph(jer_stdPlusGausJEC_ptbin4, "#eta^{jet}", "JER", cmsRed);
    formatGraph(jer_stdPlusGausJEC_ptbin5, "#eta^{jet}", "JER", cmsOrange);

    drawHeader();
    leg_per_pt->Draw();

    c_jer_vs_jteta->Print("plots/jer_vs_jteta_per_pt_" + suffix + ".png");
}