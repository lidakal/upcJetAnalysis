void get_jes_jer(TH2F *h, TH1F *jes, TH1F *jer)
{
    int nX = h->GetNbinsX();

    // for each refpt, fit the jtpt/refpt distribution
    for (int ix = 1; ix <= nX; ix++) {
        TH1F *proj = (TH1F *) h->ProjectionY(Form("proj_%d", ix), ix, ix);

        // avoid empty refpt bins
        if (proj->GetEntries() < 100) {
            jes->SetBinContent(ix, 0);
            jer->SetBinContent(ix, 0);
            delete proj;
            continue;
        }

        // fit jtpt/refpt with a gaussian: jes=mean, jer=sigma
        TF1* fit = new TF1(Form("fit_%d", ix), "gaus", 0.5, 1.5);
        proj->Fit(fit, "QN");  // Q = quiet

        double mean  = fit->GetParameter(1);
        double sigma = fit->GetParameter(2);

        jes->SetBinContent(ix, mean);
        jer->SetBinContent(ix, sigma);

        delete proj;
    }
}

void draw_kinematics()
{
    // Load histograms
    TFile *f_mc = new TFile("histos/mc_kinematics.root");
    TH1F *rawpt_mc = (TH1F *) f_mc->Get("rawpt")->Clone("rawpt_mc");
    TH1F *jtpt_mc = (TH1F *) f_mc->Get("jtpt")->Clone("jtpt_mc");
    TH1F *jtpt_new_jec_mc = (TH1F *) f_mc->Get("jtpt_new_jec")->Clone("jtpt_new_jec_mc");
    TH1F *jteta_mc = (TH1F *) f_mc->Get("jteta")->Clone("jteta_mc");
    TH1F *jtphi_mc = (TH1F *) f_mc->Get("jtphi")->Clone("jtphi_mc");
    TH2F *jtpt_new_jec_vs_refpt_mc = (TH2F *) f_mc->Get("jtpt_new_jec_vs_refpt")->Clone("jtpt_new_jec_vs_refpt_mc");
    TH2F *rawpt_vs_refpt_mc = (TH2F *) f_mc->Get("rawpt_vs_refpt")->Clone("rawpt_vs_refpt_mc");

    // JES and JER extraction
    TH1F *jes = (TH1F *) jtpt_new_jec_vs_refpt_mc->ProjectionX("jes");
    jes->Clear();
    jes->SetLineColor(kBlue);
    jes->SetTitle("w/ ppRef JEC");
    TH1F *jer = (TH1F *) jtpt_new_jec_vs_refpt_mc->ProjectionX("jer");
    jer->Clear();
    jer->SetLineColor(kBlue);
    jer->SetTitle("w/ ppRef JEC");
    get_jes_jer(jtpt_new_jec_vs_refpt_mc, jes, jer);

    TH1F *jes_raw = (TH1F *) rawpt_vs_refpt_mc->ProjectionX("jes_raw");
    jes_raw->Clear();
    jes_raw->SetLineColor(kRed);
    jes_raw->SetTitle("w/o JEC");
    TH1F *jer_raw = (TH1F *) rawpt_vs_refpt_mc->ProjectionX("jer_raw");
    jer_raw->Clear();
    jer_raw->SetLineColor(kRed);
    jer_raw->SetTitle("w/o JEC");
    get_jes_jer(rawpt_vs_refpt_mc, jes_raw, jer_raw);
    
    TCanvas *c_jes = new TCanvas("c_jes", "", 700, 600);
    jes_raw->Draw();
    jes->Draw("same");
    c_jes->BuildLegend();

    TCanvas *c_jer = new TCanvas("c_jer", "", 700, 600);
    jer_raw->Draw();
    jer->Draw("same");
    c_jer->BuildLegend();

    // MC VS DATA 
    // TFile *f_data = new TFile("data_jet_kinematics.root");
    // TH1F *jtpt_data = (TH1F *) f_data->Get("jtpt")->Clone("jtpt_data");
    // TH1F *jteta_data = (TH1F *) f_data->Get("jteta")->Clone("jteta_data");
    // TH1F *jtphi_data = (TH1F *) f_data->Get("jtphi")->Clone("jtphi_data");

    // Normalize histograms
    // for (auto h : {
    //     jtpt_mc, jtpt_data,
    //     jteta_mc, jteta_data,
    //     jtphi_mc, jtphi_data,
    // }) {
    //     h->Scale(1/h->Integral(),"width");
    // }

    // Format histograms
    // for (auto h : {
    //     jtpt_mc, jtphi_mc, jteta_mc,
    // }) {
    //     h->SetMarkerColor(kBlue);
    //     h->SetLineColor(kBlue);
    //     h->SetTitle("MC");
    // }

    // for (auto h : {
    //     jtpt_data, jtphi_data, jteta_data,
    // }) {
    //     h->SetMarkerColor(kBlack);
    //     h->SetLineColor(kBlack);
    //     h->SetTitle("Data");
    // }
    
    // Draw histograms
    // TCanvas *c_jtpt = new TCanvas("c_jtpt", "", 700, 600);
    // jtpt_data->GetYaxis()->SetRangeUser(0., 0.25);
    // jtpt_data->GetYaxis()->SetTitle("1/N dN/dp_{T}");
    // jtpt_data->GetXaxis()->SetTitle("p_{T}^{jet, reco}");
    // jtpt_data->Draw();
    // jtpt_mc->Draw("same");
    // c_jtpt->BuildLegend();

    // TCanvas *c_jteta = new TCanvas("c_jteta", "", 700, 600);
    // jteta_data->GetYaxis()->SetRangeUser(0., 0.5);
    // jteta_data->GetYaxis()->SetTitle("1/N dN/d#eta");
    // jteta_data->GetXaxis()->SetTitle("#eta^{jet, reco}");
    // jteta_data->Draw();
    // jteta_mc->Draw("same");
    // c_jteta->BuildLegend();

    // TCanvas *c_jtphi = new TCanvas("c_jtphi", "", 700, 600);
    // jtphi_data->GetYaxis()->SetRangeUser(0., 0.35);
    // jtphi_data->GetYaxis()->SetTitle("1/N dN/d#phi");
    // jtphi_data->GetXaxis()->SetTitle("#phi^{jet, reco}");
    // jtphi_data->Draw();
    // jtphi_mc->Draw("same");
    // c_jtphi->BuildLegend();

}