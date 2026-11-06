#include "../../cms_palette.h"

void draw_PF_distribution_0n0n_vs_0nXn_vs_XnXn()
{
    // Plotting style

    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);

    // Load histograms
    TFile *f_0nXn = new TFile("histos/hiforwardAll_2024rereco_pf_distribution_0nXnOneSided_HFm_trkLim3p0.root");
    std::cout << "0nXn: Loaded " << f_0nXn->GetName() << std::endl;
    TH3F *h_PF_0nXn = (TH3F*)f_0nXn->Get("h_PF")->Clone("h_PF_0nXn");
    TH3F *h_PF_pt_0nXn = (TH3F*)f_0nXn->Get("h_PF_pt")->Clone("h_PF_pt_0nXn");
    TH3F *h_PFch_0nXn = (TH3F*)f_0nXn->Get("h_PFch")->Clone("h_PFch_0nXn");
    TH3F *h_PFch_pt_0nXn = (TH3F*)f_0nXn->Get("h_PFch_pt")->Clone("h_PFch_pt_0nXn");
    TH3F *h_Nch_vs_rapgap_Etamax_tracker_0nXn = (TH3F*)f_0nXn->Get("h_Nch_vs_rapgap_fb_Etamax_tracker_wSwap")->Clone("h_Nch_vs_rapgap_Etamax_tracker_0nXn");
    
    TFile *f_0n0n = new TFile("histos/hiforwardAll_2024rereco_pf_distribution_0n0n_oppHF_trkLim3p0.root");
    std::cout << "0n0n: Loaded " << f_0n0n->GetName() << std::endl;
    TH3F *h_PF_0n0n = (TH3F*)f_0n0n->Get("h_PF")->Clone("h_PF_0n0n");
    TH3F *h_PF_pt_0n0n = (TH3F*)f_0n0n->Get("h_PF_pt")->Clone("h_PF_pt_0n0n");
    TH3F *h_PFch_0n0n = (TH3F*)f_0n0n->Get("h_PFch")->Clone("h_PFch_0n0n");
    TH3F *h_PFch_pt_0n0n = (TH3F*)f_0n0n->Get("h_PFch_pt")->Clone("h_PFch_pt_0n0n");
    TH3F *h_Nch_vs_rapgap_Etamax_tracker_0n0n = (TH3F*)f_0n0n->Get("h_Nch_vs_rapgap_fb_Etamax_tracker_wSwap")->Clone("h_Nch_vs_rapgap_Etamax_tracker_0n0n");

    TFile *f_XnXn = new TFile("histos/hiforwardAll_2024rereco_pf_distribution_XnXn_oppHF_trkLim3p0.root");
    std::cout << "XnXn: Loaded " << f_XnXn->GetName() << std::endl;
    TH3F *h_PF_XnXn = (TH3F*)f_XnXn->Get("h_PF")->Clone("h_PF_XnXn");
    TH3F *h_PF_pt_XnXn = (TH3F*)f_XnXn->Get("h_PF_pt")->Clone("h_PF_pt_XnXn");
    TH3F *h_PFch_XnXn = (TH3F*)f_XnXn->Get("h_PFch")->Clone("h_PFch_XnXn");
    TH3F *h_PFch_pt_XnXn = (TH3F*)f_XnXn->Get("h_PFch_pt")->Clone("h_PFch_pt_XnXn");
    TH3F *h_Nch_vs_rapgap_Etamax_tracker_XnXn = (TH3F*)f_XnXn->Get("h_Nch_vs_rapgap_fb_Etamax_tracker_wSwap")->Clone("h_Nch_vs_rapgap_Etamax_tracker_XnXn");

    // Projections

    TH1F *h_eta_0nXn = (TH1F*)h_PF_0nXn->ProjectionX("h_eta_0nXn");
    TH1F *h_eta_0n0n = (TH1F*)h_PF_0n0n->ProjectionX("h_eta_0n0n");
    TH1F *h_eta_XnXn = (TH1F*)h_PF_XnXn->ProjectionX("h_eta_XnXn");

    TH1F *h_phi_0nXn = (TH1F*)h_PF_0nXn->ProjectionY("h_phi_0nXn");
    TH1F *h_phi_0n0n = (TH1F*)h_PF_0n0n->ProjectionY("h_phi_0n0n");
    TH1F *h_phi_XnXn = (TH1F*)h_PF_XnXn->ProjectionY("h_phi_XnXn");

    TH1F *h_E_0nXn = (TH1F*)h_PF_0nXn->ProjectionZ("h_E_0nXn");
    TH1F *h_E_0n0n = (TH1F*)h_PF_0n0n->ProjectionZ("h_E_0n0n");
    TH1F *h_E_XnXn = (TH1F*)h_PF_XnXn->ProjectionZ("h_E_XnXn");

    TH1F *h_pt_0nXn = (TH1F*)h_PF_pt_0nXn->ProjectionZ("h_pt_0nXn");
    TH1F *h_pt_0n0n = (TH1F*)h_PF_pt_0n0n->ProjectionZ("h_pt_0n0n");
    TH1F *h_pt_XnXn = (TH1F*)h_PF_pt_XnXn->ProjectionZ("h_pt_XnXn");

    TH1F *h_ch_eta_0nXn = (TH1F*)h_PFch_0nXn->ProjectionX("h_ch_eta_0nXn");
    TH1F *h_ch_eta_0n0n = (TH1F*)h_PFch_0n0n->ProjectionX("h_ch_eta_0n0n");
    TH1F *h_ch_eta_XnXn = (TH1F*)h_PFch_XnXn->ProjectionX("h_ch_eta_XnXn");

    TH1F *h_ch_phi_0nXn = (TH1F*)h_PFch_0nXn->ProjectionY("h_ch_phi_0nXn");
    TH1F *h_ch_phi_0n0n = (TH1F*)h_PFch_0n0n->ProjectionY("h_ch_phi_0n0n");
    TH1F *h_ch_phi_XnXn = (TH1F*)h_PFch_XnXn->ProjectionY("h_ch_phi_XnXn");

    TH1F *h_ch_E_0nXn = (TH1F*)h_PFch_0nXn->ProjectionZ("h_ch_E_0nXn");
    TH1F *h_ch_E_0n0n = (TH1F*)h_PFch_0n0n->ProjectionZ("h_ch_E_0n0n");
    TH1F *h_ch_E_XnXn = (TH1F*)h_PFch_XnXn->ProjectionZ("h_ch_E_XnXn");

    TH1F *h_ch_pt_0nXn = (TH1F*)h_PFch_pt_0nXn->ProjectionZ("h_ch_pt_0nXn");
    TH1F *h_ch_pt_0n0n = (TH1F*)h_PFch_pt_0n0n->ProjectionZ("h_ch_pt_0n0n");
    TH1F *h_ch_pt_XnXn = (TH1F*)h_PFch_pt_XnXn->ProjectionZ("h_ch_pt_XnXn");

    TH1F *h_Nch_0nXn = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_0nXn->ProjectionX("h_Nch_0nXn");
    TH1F *h_Nch_0n0n = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_0n0n->ProjectionX("h_Nch_0n0n");
    TH1F *h_Nch_XnXn = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_XnXn->ProjectionX("h_Nch_XnXn");

    TH1F *h_frg_0nXn = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_0nXn->ProjectionY("h_frg_0nXn");
    TH1F *h_frg_0n0n = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_0n0n->ProjectionY("h_frg_0n0n");
    TH1F *h_frg_XnXn = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_XnXn->ProjectionY("h_frg_XnXn");

    TH1F *h_brg_0nXn = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_0nXn->ProjectionZ("h_brg_0nXn");
    TH1F *h_brg_0n0n = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_0n0n->ProjectionZ("h_brg_0n0n");
    TH1F *h_brg_XnXn = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_XnXn->ProjectionZ("h_brg_XnXn");

    // Preprocess

    // h_eta_XnXn->Add(h_eta_beamB_diffraction);
    // h_ch_eta_XnXn->Add(h_ch_eta_beamB_diffraction);

    for (auto h : { 
        h_eta_0nXn, h_eta_0n0n, h_eta_XnXn,
        h_phi_0nXn, h_phi_0n0n, h_phi_XnXn,

        h_ch_eta_0nXn, h_ch_eta_0n0n, h_ch_eta_XnXn,
        h_ch_phi_0nXn, h_ch_phi_0n0n, h_ch_phi_XnXn,
    }) {
        // h->Rebin(2);
        h->Scale(1.0 / h->Integral());
        h->GetXaxis()->SetTitleOffset(1.2);
    }

    for (auto h : { 
        h_E_0nXn, h_E_0n0n, h_E_XnXn,
        h_pt_0nXn, h_pt_0n0n, h_pt_XnXn,

        h_ch_E_0nXn, h_ch_E_0n0n, h_ch_E_XnXn,
        h_ch_pt_0nXn, h_ch_pt_0n0n, h_ch_pt_XnXn,
    }) {
        h->Rebin(2);
        h->Scale(1.0 / h->Integral());
        h->GetXaxis()->SetTitleOffset(1.2);
    }

    for (auto h : { 
        h_frg_0nXn, h_frg_0n0n, h_frg_XnXn,
        h_brg_0nXn, h_brg_0n0n, h_brg_XnXn,
    }) {
        // h->Rebin(2);
        h->Scale(1.0 / h->Integral());
        h->GetXaxis()->SetTitleOffset(1.2);
    }

    for (auto h : { 
        h_Nch_0nXn, h_Nch_0n0n, h_Nch_XnXn,
    }) {
        h->Rebin(2);
        h->GetXaxis()->SetTitleOffset(1.2);
        h->Scale(1.0 / h->Integral());
    }
    
    // Draw eta, phi, E+pt
    TCanvas *c_kinematics = new TCanvas("c_kinematics", "c_kinematics", 2400, 800);
    c_kinematics->Divide(3,1);

    c_kinematics->cd(3);

    h_E_0nXn->SetLineColor(cmsRed);
    h_E_0nXn->SetMarkerColor(cmsRed);
    h_E_0nXn->SetMarkerStyle(kFullTriangleUp);
    h_pt_0nXn->SetLineColor(cmsRed);
    h_pt_0nXn->SetMarkerColor(cmsRed);
    h_pt_0nXn->SetMarkerStyle(kOpenTriangleUp);

    h_E_0n0n->SetLineColor(cmsViolet);
    h_E_0n0n->SetMarkerColor(cmsViolet);
    h_E_0n0n->SetMarkerStyle(kFullCircle);
    h_pt_0n0n->SetLineColor(cmsViolet);
    h_pt_0n0n->SetMarkerColor(cmsViolet);
    h_pt_0n0n->SetMarkerStyle(kOpenCircle);

    h_E_XnXn->SetLineColor(cmsBlue);
    h_E_XnXn->SetMarkerColor(cmsBlue);
    h_E_XnXn->SetMarkerStyle(kFullTriangleDown);
    h_pt_XnXn->SetLineColor(cmsBlue);
    h_pt_XnXn->SetMarkerColor(cmsBlue);
    h_pt_XnXn->SetMarkerStyle(kOpenTriangleDown);

    h_E_0n0n->GetXaxis()->SetTitle("E^{PF} or p_{T}^{PF} (GeV)");
    h_E_0n0n->GetYaxis()->SetTitle("Normalized entries");
    h_E_0n0n->GetYaxis()->SetRangeUser(1e-4, 10.);
    h_E_0n0n->GetXaxis()->SetRangeUser(0., 70.);
    h_E_0n0n->Draw();
    h_E_XnXn->Draw("same");
   h_pt_0n0n->Draw("same");
    h_pt_XnXn->Draw("same");
    h_E_0nXn->Draw("same");
    h_pt_0nXn->Draw("same");
    c_kinematics->cd(3)->SetLogy();

    TLegend *legend = new TLegend(0.2, 0.65, 0.8, 0.85);
    legend->SetBorderSize(0);
    legend->SetNColumns(2);
    legend->AddEntry(new TH1F(), "E^{PF}", "");
    legend->AddEntry(new TH1F(), "p_{T}^{PF}", "");
    legend->AddEntry(h_E_0n0n, "0n0n", "pl");
    legend->AddEntry(h_pt_0n0n, "0n0n", "pl");
    legend->AddEntry(h_E_0nXn, "0nXn", "pl");
    legend->AddEntry(h_pt_0nXn, "0nXn", "pl");
    legend->AddEntry(h_E_XnXn, "XnXn", "pl");
    legend->AddEntry(h_pt_XnXn, "XnXn", "pl");
    legend->Draw();

    c_kinematics->cd(1);

    h_eta_0nXn->SetLineColor(cmsRed);
    h_eta_0nXn->SetMarkerColor(cmsRed);
    h_eta_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_eta_0n0n->SetLineColor(cmsViolet);
    h_eta_0n0n->SetMarkerColor(cmsViolet);
    h_eta_0n0n->SetMarkerStyle(kFullCircle);

    h_eta_XnXn->SetLineColor(cmsBlue);
    h_eta_XnXn->SetMarkerColor(cmsBlue);
    h_eta_XnXn->SetMarkerStyle(kFullTriangleDown);

    h_eta_0n0n->GetXaxis()->SetTitle("#eta^{PF}");
    h_eta_0n0n->GetYaxis()->SetTitle("Normalized entries");
    h_eta_0n0n->GetYaxis()->SetRangeUser(0, 0.06);
    // h_eta_0n0n->GetYaxis()->SetRangeUser(1e-4, 10);
    h_eta_0n0n->GetXaxis()->SetRangeUser(-5., 5.);
    h_eta_0n0n->Draw();
    h_eta_XnXn->Draw("same");
    h_eta_0nXn->Draw("same");
    // c_kinematics->cd(1)->SetLogy();

    TLegend *legend_m = new TLegend(0.2, 0.7, 0.8, 0.85);
    legend_m->SetBorderSize(0);
    legend_m->SetFillStyle(0);
    legend_m->AddEntry(h_eta_0n0n, "0n0n", "pl");
    legend_m->AddEntry(h_eta_0nXn, "0nXn", "pl");
    legend_m->AddEntry(h_eta_XnXn, "XnXn", "pl");
    legend_m->Draw();

    c_kinematics->cd(2);

    h_phi_0nXn->SetLineColor(cmsRed);
    h_phi_0nXn->SetMarkerColor(cmsRed);
    h_phi_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_phi_0n0n->SetLineColor(cmsViolet);
    h_phi_0n0n->SetMarkerColor(cmsViolet);
    h_phi_0n0n->SetMarkerStyle(kFullCircle);

    h_phi_XnXn->SetLineColor(cmsBlue);
    h_phi_XnXn->SetMarkerColor(cmsBlue);
    h_phi_XnXn->SetMarkerStyle(kFullTriangleDown);

    h_phi_0n0n->GetXaxis()->SetTitle("#phi^{PF} (radians)");
    h_phi_0n0n->GetYaxis()->SetTitle("Normalized entries");
    h_phi_0n0n->GetXaxis()->SetRangeUser(-3.14159, 3.14159);
    h_phi_0n0n->GetYaxis()->SetRangeUser(0., 0.18);
    h_phi_0n0n->Draw();
    h_phi_XnXn->Draw("same");
    h_phi_0nXn->Draw("same");

    TLegend *legend_phi = (TLegend *) legend_m->Clone("legend_phi");
    legend_phi->Draw();


    c_kinematics->Print("plots/pf_distributions/0n0n_vs_0nXn_vs_XnXn_PF_kinematics.pdf");

    TCanvas *c_kinematics_ch = new TCanvas("c_kinematics_ch", "c_kinematics_ch", 2400, 800);
    c_kinematics_ch->Divide(3,1);

    c_kinematics_ch->cd(3);

    h_ch_E_0nXn->SetLineColor(cmsRed);
    h_ch_E_0nXn->SetMarkerColor(cmsRed);
    h_ch_E_0nXn->SetMarkerStyle(kFullTriangleUp);
    h_ch_pt_0nXn->SetLineColor(cmsRed);
    h_ch_pt_0nXn->SetMarkerColor(cmsRed);
    h_ch_pt_0nXn->SetMarkerStyle(kOpenTriangleUp);

    h_ch_E_0n0n->SetLineColor(cmsViolet);
    h_ch_E_0n0n->SetMarkerColor(cmsViolet);
    h_ch_E_0n0n->SetMarkerStyle(kFullCircle);
    h_ch_pt_0n0n->SetLineColor(cmsViolet);
    h_ch_pt_0n0n->SetMarkerColor(cmsViolet);
    h_ch_pt_0n0n->SetMarkerStyle(kOpenCircle);

    h_ch_E_XnXn->SetLineColor(cmsBlue);
    h_ch_E_XnXn->SetMarkerColor(cmsBlue);
    h_ch_E_XnXn->SetMarkerStyle(kFullTriangleDown);
    h_ch_pt_XnXn->SetLineColor(cmsBlue);
    h_ch_pt_XnXn->SetMarkerColor(cmsBlue);
    h_ch_pt_XnXn->SetMarkerStyle(kOpenTriangleDown);

    h_ch_E_0n0n->GetXaxis()->SetTitle("E^{PF,ch} or p_{T}^{PF,ch} (GeV)");
    h_ch_E_0n0n->GetYaxis()->SetTitle("Normalized entries");
    h_ch_E_0n0n->GetYaxis()->SetRangeUser(1e-4, 10.);
    h_ch_E_0n0n->GetXaxis()->SetRangeUser(0., 70.);
    h_ch_E_0n0n->Draw();
    h_ch_E_XnXn->Draw("same");
    h_ch_pt_0n0n->Draw("same");
    h_ch_pt_XnXn->Draw("same");
    h_ch_E_0nXn->Draw("same");
    h_ch_pt_0nXn->Draw("same");
    c_kinematics_ch->cd(3)->SetLogy();

    TLegend *legend_ch = new TLegend(0.2, 0.65, 0.8, 0.85);
    legend_ch->SetBorderSize(0);
    legend_ch->SetNColumns(2);
    legend_ch->AddEntry(new TH1F(), "E^{PF,ch}", "");
    legend_ch->AddEntry(new TH1F(), "p_{T}^{PF,ch}", "");
    legend_ch->AddEntry(h_ch_E_0n0n, "0n0n", "pl");
    legend_ch->AddEntry(h_ch_pt_0n0n, "0n0n", "pl");
    legend_ch->AddEntry(h_ch_E_0nXn, "0nXn", "pl");
    legend_ch->AddEntry(h_ch_pt_0nXn, "0nXn", "pl");
    legend_ch->AddEntry(h_ch_E_XnXn, "XnXn", "pl");
    legend_ch->AddEntry(h_ch_pt_XnXn, "XnXn", "pl");
    legend_ch->Draw();

    c_kinematics_ch->cd(1);

    h_ch_eta_0nXn->SetLineColor(cmsRed);
    h_ch_eta_0nXn->SetMarkerColor(cmsRed);
    h_ch_eta_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_ch_eta_0n0n->SetLineColor(cmsViolet);
    h_ch_eta_0n0n->SetMarkerColor(cmsViolet);
    h_ch_eta_0n0n->SetMarkerStyle(kFullCircle);

    h_ch_eta_XnXn->SetLineColor(cmsBlue);
    h_ch_eta_XnXn->SetMarkerColor(cmsBlue);
    h_ch_eta_XnXn->SetMarkerStyle(kFullTriangleDown);

    h_ch_eta_0n0n->GetXaxis()->SetTitle("#eta^{PF,ch}");
    h_ch_eta_0n0n->GetYaxis()->SetTitle("Normalized entries");
    h_ch_eta_0n0n->GetYaxis()->SetRangeUser(0, 0.1);
    h_ch_eta_0n0n->GetXaxis()->SetRangeUser(-5., 5.);
    h_ch_eta_0n0n->Draw();
    h_ch_eta_XnXn->Draw("same");
    h_ch_eta_0nXn->Draw("same");

    TLegend *legend_ch_m = new TLegend(0.2, 0.7, 0.8, 0.85);
    legend_ch_m->SetBorderSize(0);
    legend_ch_m->SetFillStyle(0);
    legend_ch_m->AddEntry(h_ch_eta_0n0n, "0n0n", "pl");
    legend_ch_m->AddEntry(h_ch_eta_0nXn, "0nXn", "pl");
    legend_ch_m->AddEntry(h_ch_eta_XnXn, "XnXn", "pl");
    legend_ch_m->Draw();

    c_kinematics_ch->cd(2);

    h_ch_phi_0nXn->SetLineColor(cmsRed);
    h_ch_phi_0nXn->SetMarkerColor(cmsRed);
    h_ch_phi_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_ch_phi_0n0n->SetLineColor(cmsViolet);
    h_ch_phi_0n0n->SetMarkerColor(cmsViolet);
    h_ch_phi_0n0n->SetMarkerStyle(kFullCircle);

    h_ch_phi_XnXn->SetLineColor(cmsBlue);
    h_ch_phi_XnXn->SetMarkerColor(cmsBlue);
    h_ch_phi_XnXn->SetMarkerStyle(kFullTriangleDown);

    h_ch_phi_0n0n->GetXaxis()->SetTitle("#phi^{PF,ch} (radians)");
    h_ch_phi_0n0n->GetYaxis()->SetTitle("Normalized entries");
    h_ch_phi_0n0n->GetXaxis()->SetRangeUser(-3.14159, 3.14159);
    h_ch_phi_0n0n->GetYaxis()->SetRangeUser(0., 0.18);
    h_ch_phi_0n0n->Draw();
    h_ch_phi_XnXn->Draw("same");
    h_ch_phi_0nXn->Draw("same");

    TLegend *legend_ch_phi = (TLegend *) legend_ch_m->Clone("legend_ch_phi");
    legend_ch_phi->Draw();


    c_kinematics_ch->Print("plots/pf_distributions/0n0n_vs_0nXn_vs_XnXn_PFch_kinematics.pdf");

    // frg, brg 
    TCanvas *c_observables = new TCanvas("c_observables", "c_observables", 2400, 800);
    c_observables->Divide(3,1);

    c_observables->cd(2);

    h_frg_0nXn->SetLineColor(cmsRed);
    h_frg_0nXn->SetMarkerColor(cmsRed);
    h_frg_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_frg_0n0n->SetLineColor(cmsViolet);
    h_frg_0n0n->SetMarkerColor(cmsViolet);
    h_frg_0n0n->SetMarkerStyle(kFullCircle);

    h_frg_XnXn->SetLineColor(cmsBlue);
    h_frg_XnXn->SetMarkerColor(cmsBlue);
    h_frg_XnXn->SetMarkerStyle(kFullTriangleDown);

    h_frg_0n0n->GetXaxis()->SetTitle("FRG");
    h_frg_0n0n->GetYaxis()->SetTitle("Normalized entries");
    h_frg_0n0n->GetYaxis()->SetRangeUser(1e-5, 100.);
    h_frg_0n0n->GetXaxis()->SetRangeUser(0., 3.);
    h_frg_0n0n->Draw();
    h_frg_XnXn->Draw("same");
    h_frg_0nXn->Draw("same");
    
    TLegend *legend_frg = new TLegend(0.2, 0.7, 0.8, 0.85);
    legend_frg->SetBorderSize(0);
    legend_frg->SetFillStyle(0);
    legend_frg->AddEntry(h_frg_0n0n, "0n0n", "pl");
    legend_frg->AddEntry(h_frg_0nXn, "0nXn", "pl");
    legend_frg->AddEntry(h_frg_XnXn, "XnXn", "pl");
    legend_frg->Draw();

    c_observables->cd(2)->SetLogy();

    c_observables->cd(3);

    h_brg_0nXn->SetLineColor(cmsRed);
    h_brg_0nXn->SetMarkerColor(cmsRed);
    h_brg_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_brg_0n0n->SetLineColor(cmsViolet);
    h_brg_0n0n->SetMarkerColor(cmsViolet);
    h_brg_0n0n->SetMarkerStyle(kFullCircle);

    h_brg_XnXn->SetLineColor(cmsBlue);
    h_brg_XnXn->SetMarkerColor(cmsBlue);
    h_brg_XnXn->SetMarkerStyle(kFullTriangleDown);

    h_brg_0n0n->GetXaxis()->SetTitle("BRG");
    h_brg_0n0n->GetYaxis()->SetTitle("Normalized entries");
    h_brg_0n0n->GetYaxis()->SetRangeUser(0., 0.15);
    h_brg_0n0n->GetXaxis()->SetRangeUser(0., 5.);
    h_brg_0n0n->Draw();
    h_brg_XnXn->Draw("same");
    h_brg_0nXn->Draw("same");
    legend_frg->Draw();

    c_observables->cd(1);

    h_Nch_0nXn->SetLineColor(cmsRed);
    h_Nch_0nXn->SetMarkerColor(cmsRed);
    h_Nch_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_Nch_0n0n->SetLineColor(cmsViolet);
    h_Nch_0n0n->SetMarkerColor(cmsViolet);
    h_Nch_0n0n->SetMarkerStyle(kFullCircle);

    h_Nch_XnXn->SetLineColor(cmsBlue);
    h_Nch_XnXn->SetMarkerColor(cmsBlue);
    h_Nch_XnXn->SetMarkerStyle(kFullTriangleDown);

    h_Nch_0n0n->GetXaxis()->SetTitle("N_{ch}");
    h_Nch_0n0n->GetYaxis()->SetTitle("Normalized entries");
    h_Nch_0n0n->GetYaxis()->SetRangeUser(0., 0.15);
    h_Nch_0n0n->GetXaxis()->SetRangeUser(0., 100.);
    h_Nch_0n0n->Draw();
    h_Nch_XnXn->Draw("same");
    h_Nch_0nXn->Draw("same");
    legend_frg->Draw();

    c_observables->Print("plots/pf_distributions/0n0n_0nXn_XnXn_rapgap.pdf");
}