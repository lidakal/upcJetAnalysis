#include "../../cms_palette.h"

void draw_PF_distribution_data_vs_MC_v2()
{
    // Plotting style

    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);

    // Load histograms

    TString suffix_data = "_0nXnOneSided_HFm_trkLim3p0";
    TString suffix_mc = "_oppHF_trkLim3p0";

    TFile *f_data = new TFile("histos/hiforwardAll_2024rereco_pf_distribution"+suffix_data+".root");
    std::cout << "DATA: Loaded " << f_data->GetName() << std::endl;
    TH3F *h_PF_data = (TH3F*)f_data->Get("h_PF")->Clone("h_PF_data");
    TH3F *h_PF_pt_data = (TH3F*)f_data->Get("h_PF_pt")->Clone("h_PF_pt_data");
    TH3F *h_PFch_data = (TH3F*)f_data->Get("h_PFch")->Clone("h_PFch_data");
    TH3F *h_PFch_pt_data = (TH3F*)f_data->Get("h_PFch_pt")->Clone("h_PFch_pt_data");
    TH3F *h_Nch_vs_rapgap_Etamax_tracker_data = (TH3F*)f_data->Get("h_Nch_vs_rapgap_fb_Etamax_tracker_wSwap")->Clone("h_Nch_vs_rapgap_Etamax_tracker_data");
    
    TFile *f_beamA_qcd = new TFile("histos/beamA_qcd_pthat10_pf_distribution"+suffix_mc+".root");
    std::cout << "BEAM A QCD: Loaded " << f_beamA_qcd->GetName() << std::endl;
    TH3F *h_PF_beamA_qcd = (TH3F*)f_beamA_qcd->Get("h_PF")->Clone("h_PF_beamA_qcd");
    TH3F *h_PF_pt_beamA_qcd = (TH3F*)f_beamA_qcd->Get("h_PF_pt")->Clone("h_PF_pt_beamA_qcd");
    TH3F *h_PFch_beamA_qcd = (TH3F*)f_beamA_qcd->Get("h_PFch")->Clone("h_PFch_beamA_qcd");
    TH3F *h_PFch_pt_beamA_qcd = (TH3F*)f_beamA_qcd->Get("h_PFch_pt")->Clone("h_PFch_pt_beamA_qcd");
    TH3F *h_Nch_vs_rapgap_Etamax_tracker_beamA_qcd = (TH3F*)f_beamA_qcd->Get("h_Nch_vs_rapgap_fb_Etamax_tracker_wSwap")->Clone("h_Nch_vs_rapgap_Etamax_tracker_beamA_qcd");

    TFile *f_beamA_diffraction = new TFile("histos/beamA_diffraction_pthat10_pf_distribution"+suffix_mc+".root");
    std::cout << "BEAM A DIFF1: Loaded " << f_beamA_diffraction->GetName() << std::endl;
    TH3F *h_PF_beamA_diffraction = (TH3F*)f_beamA_diffraction->Get("h_PF")->Clone("h_PF_beamA_diffraction");
    TH3F *h_PF_pt_beamA_diffraction = (TH3F*)f_beamA_diffraction->Get("h_PF_pt")->Clone("h_PF_pt_beamA_diffraction");
    TH3F *h_PFch_beamA_diffraction = (TH3F*)f_beamA_diffraction->Get("h_PFch")->Clone("h_PFch_beamA_diffraction");
    TH3F *h_PFch_pt_beamA_diffraction = (TH3F*)f_beamA_diffraction->Get("h_PFch_pt")->Clone("h_PFch_pt_beamA_diffraction");
    TH3F *h_Nch_vs_rapgap_Etamax_tracker_beamA_diffraction = (TH3F*)f_beamA_diffraction->Get("h_Nch_vs_rapgap_fb_Etamax_tracker_wSwap")->Clone("h_Nch_vs_rapgap_Etamax_tracker_beamA_diffraction");

    TFile *f_beamA_diffractionSide2 = new TFile("histos/beamA_diffractionSide2_pthat10_pf_distribution"+suffix_mc+".root");
    std::cout << "BEAM A DIFF2: Loaded " << f_beamA_diffractionSide2->GetName() << std::endl;
    TH3F *h_PF_beamA_diffractionSide2 = (TH3F*)f_beamA_diffractionSide2->Get("h_PF")->Clone("h_PF_beamA_diffractionSide2");
    TH3F *h_PF_pt_beamA_diffractionSide2 = (TH3F*)f_beamA_diffractionSide2->Get("h_PF_pt")->Clone("h_PF_pt_beamA_diffractionSide2");
    TH3F *h_PFch_beamA_diffractionSide2 = (TH3F*)f_beamA_diffractionSide2->Get("h_PFch")->Clone("h_PFch_beamA_diffractionSide2");
    TH3F *h_PFch_pt_beamA_diffractionSide2 = (TH3F*)f_beamA_diffractionSide2->Get("h_PFch_pt")->Clone("h_PFch_pt_beamA_diffractionSide2");
    TH3F *h_Nch_vs_rapgap_Etamax_tracker_beamA_diffractionSide2 = (TH3F*)f_beamA_diffractionSide2->Get("h_Nch_vs_rapgap_fb_Etamax_tracker_wSwap")->Clone("h_Nch_vs_rapgap_Etamax_tracker_beamA_diffractionSide2");

    TFile *f_beamB_diffraction = new TFile("histos/beamB_diffraction_pthat10_pf_distribution"+suffix_mc+".root");
    std::cout << "BEAM B: Loaded " << f_beamB_diffraction->GetName() << std::endl;
    TH3F *h_PF_beamB_diffraction = (TH3F*)f_beamB_diffraction->Get("h_PF")->Clone("h_PF_beamB_diffraction");
    TH3F *h_PF_pt_beamB_diffraction = (TH3F*)f_beamB_diffraction->Get("h_PF_pt")->Clone("h_PF_pt_beamB_diffraction");
    TH3F *h_PFch_beamB_diffraction = (TH3F*)f_beamB_diffraction->Get("h_PFch")->Clone("h_PFch_beamB_diffraction");
    TH3F *h_PFch_pt_beamB_diffraction = (TH3F*)f_beamB_diffraction->Get("h_PFch_pt")->Clone("h_PFch_pt_beamB_diffraction");
    TH3F *h_Nch_vs_rapgap_Etamax_tracker_beamB_diffraction = (TH3F*)f_beamB_diffraction->Get("h_Nch_vs_rapgap_fb_Etamax_tracker_wSwap")->Clone("h_Nch_vs_rapgap_Etamax_tracker_beamB_diffraction");


    // Projections

    TH1F *h_eta_data = (TH1F*)h_PF_data->ProjectionX("h_eta_data");
    TH1F *h_eta_beamA_qcd = (TH1F*)h_PF_beamA_qcd->ProjectionX("h_eta_beamA_qcd");
    TH1F *h_eta_beamA_diffraction = (TH1F*)h_PF_beamA_diffraction->ProjectionX("h_eta_beamA_diffraction");
    TH1F *h_eta_beamA_diffractionSide2 = (TH1F*)h_PF_beamA_diffractionSide2->ProjectionX("h_eta_beamA_diffractionSide2");
    TH1F *h_eta_beamB_diffraction = (TH1F*)h_PF_beamB_diffraction->ProjectionX("h_eta_beamB_diffraction");

    TH1F *h_phi_data = (TH1F*)h_PF_data->ProjectionY("h_phi_data");
    TH1F *h_phi_beamA_qcd = (TH1F*)h_PF_beamA_qcd->ProjectionY("h_phi_beamA_qcd");
    TH1F *h_phi_beamA_diffraction = (TH1F*)h_PF_beamA_diffraction->ProjectionY("h_phi_beamA_diffraction");
    TH1F *h_phi_beamA_diffractionSide2 = (TH1F*)h_PF_beamA_diffractionSide2->ProjectionY("h_phi_beamA_diffractionSide2");
    TH1F *h_phi_beamB_diffraction = (TH1F*)h_PF_beamB_diffraction->ProjectionY("h_phi_beamB_diffraction");

    TH1F *h_E_data = (TH1F*)h_PF_data->ProjectionZ("h_E_data");
    TH1F *h_E_beamA_qcd = (TH1F*)h_PF_beamA_qcd->ProjectionZ("h_E_beamA_qcd");
    TH1F *h_E_beamA_diffraction = (TH1F*)h_PF_beamA_diffraction->ProjectionZ("h_E_beamA_diffraction");
    TH1F *h_E_beamA_diffractionSide2 = (TH1F*)h_PF_beamA_diffractionSide2->ProjectionZ("h_E_beamA_diffractionSide2");
    TH1F *h_E_beamB_diffraction = (TH1F*)h_PF_beamB_diffraction->ProjectionZ("h_E_beamB_diffraction");

    TH1F *h_pt_data = (TH1F*)h_PF_pt_data->ProjectionZ("h_pt_data");
    TH1F *h_pt_beamA_qcd = (TH1F*)h_PF_pt_beamA_qcd->ProjectionZ("h_pt_beamA_qcd");
    TH1F *h_pt_beamA_diffraction = (TH1F*)h_PF_pt_beamA_diffraction->ProjectionZ("h_pt_beamA_diffraction");
    TH1F *h_pt_beamA_diffractionSide2 = (TH1F*)h_PF_pt_beamA_diffractionSide2->ProjectionZ("h_pt_beamA_diffractionSide2");
    TH1F *h_pt_beamB_diffraction = (TH1F*)h_PF_pt_beamB_diffraction->ProjectionZ("h_pt_beamB_diffraction");

    TH1F *h_ch_eta_data = (TH1F*)h_PFch_data->ProjectionX("h_ch_eta_data");
    TH1F *h_ch_eta_beamA_qcd = (TH1F*)h_PFch_beamA_qcd->ProjectionX("h_ch_eta_beamA_qcd");
    TH1F *h_ch_eta_beamA_diffraction = (TH1F*)h_PFch_beamA_diffraction->ProjectionX("h_ch_eta_beamA_diffraction");
    TH1F *h_ch_eta_beamA_diffractionSide2 = (TH1F*)h_PFch_beamA_diffractionSide2->ProjectionX("h_ch_eta_beamA_diffractionSide2");
    TH1F *h_ch_eta_beamB_diffraction = (TH1F*)h_PFch_beamB_diffraction->ProjectionX("h_ch_eta_beamB_diffraction");

    TH1F *h_ch_phi_data = (TH1F*)h_PFch_data->ProjectionY("h_ch_phi_data");
    TH1F *h_ch_phi_beamA_qcd = (TH1F*)h_PFch_beamA_qcd->ProjectionY("h_ch_phi_beamA_qcd");
    TH1F *h_ch_phi_beamA_diffraction = (TH1F*)h_PFch_beamA_diffraction->ProjectionY("h_ch_phi_beamA_diffraction");
    TH1F *h_ch_phi_beamA_diffractionSide2 = (TH1F*)h_PFch_beamA_diffractionSide2->ProjectionY("h_ch_phi_beamA_diffractionSide2");
    TH1F *h_ch_phi_beamB_diffraction = (TH1F*)h_PFch_beamB_diffraction->ProjectionY("h_ch_phi_beamB_diffraction");

    TH1F *h_ch_E_data = (TH1F*)h_PFch_data->ProjectionZ("h_ch_E_data");
    TH1F *h_ch_E_beamA_qcd = (TH1F*)h_PFch_beamA_qcd->ProjectionZ("h_ch_E_beamA_qcd");
    TH1F *h_ch_E_beamA_diffraction = (TH1F*)h_PFch_beamA_diffraction->ProjectionZ("h_ch_E_beamA_diffraction");
    TH1F *h_ch_E_beamA_diffractionSide2 = (TH1F*)h_PFch_beamA_diffractionSide2->ProjectionZ("h_ch_E_beamA_diffractionSide2");
    TH1F *h_ch_E_beamB_diffraction = (TH1F*)h_PFch_beamB_diffraction->ProjectionZ("h_ch_E_beamB_diffraction");

    TH1F *h_ch_pt_data = (TH1F*)h_PFch_pt_data->ProjectionZ("h_ch_pt_data");
    TH1F *h_ch_pt_beamA_qcd = (TH1F*)h_PFch_pt_beamA_qcd->ProjectionZ("h_ch_pt_beamA_qcd");
    TH1F *h_ch_pt_beamA_diffraction = (TH1F*)h_PFch_pt_beamA_diffraction->ProjectionZ("h_ch_pt_beamA_diffraction");
    TH1F *h_ch_pt_beamA_diffractionSide2 = (TH1F*)h_PFch_pt_beamA_diffractionSide2->ProjectionZ("h_ch_pt_beamA_diffractionSide2");
    TH1F *h_ch_pt_beamB_diffraction = (TH1F*)h_PFch_pt_beamB_diffraction->ProjectionZ("h_ch_pt_beamB_diffraction");

    TH1F *h_Nch_data = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_data->ProjectionX("h_Nch_data");
    TH1F *h_Nch_beamA_qcd = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_beamA_qcd->ProjectionX("h_Nch_beamA_qcd");
    TH1F *h_Nch_beamA_diffraction = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_beamA_diffraction->ProjectionX("h_Nch_beamA_diffraction");
    TH1F *h_Nch_beamA_diffractionSide2 = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_beamA_diffractionSide2->ProjectionX("h_Nch_beamA_diffractionSide2");
    TH1F *h_Nch_beamB_diffraction = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_beamB_diffraction->ProjectionX("h_Nch_beamB_diffraction");

    TH1F *h_frg_data = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_data->ProjectionY("h_frg_data");
    TH1F *h_frg_beamA_qcd = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_beamA_qcd->ProjectionY("h_frg_beamA_qcd");
    TH1F *h_frg_beamA_diffraction = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_beamA_diffraction->ProjectionY("h_frg_beamA_diffraction");
    TH1F *h_frg_beamA_diffractionSide2 = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_beamA_diffractionSide2->ProjectionY("h_frg_beamA_diffractionSide2");
    TH1F *h_frg_beamB_diffraction = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_beamB_diffraction->ProjectionY("h_frg_beamB_diffraction");

    TH1F *h_brg_data = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_data->ProjectionZ("h_brg_data");
    TH1F *h_brg_beamA_qcd = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_beamA_qcd->ProjectionZ("h_brg_beamA_qcd");
    TH1F *h_brg_beamA_diffraction = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_beamA_diffraction->ProjectionZ("h_brg_beamA_diffraction");
    TH1F *h_brg_beamA_diffractionSide2 = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_beamA_diffractionSide2->ProjectionZ("h_brg_beamA_diffractionSide2");
    TH1F *h_brg_beamB_diffraction = (TH1F*)h_Nch_vs_rapgap_Etamax_tracker_beamB_diffraction->ProjectionZ("h_brg_beamB_diffraction");

    // Preprocess

    // h_eta_beamA_diffraction->Add(h_eta_beamB_diffraction);
    // h_ch_eta_beamA_diffraction->Add(h_ch_eta_beamB_diffraction);

    for (auto h : { 
        h_eta_data, h_eta_beamA_qcd, h_eta_beamA_diffraction, h_eta_beamA_diffractionSide2, h_eta_beamB_diffraction,
        h_phi_data, h_phi_beamA_qcd, h_phi_beamA_diffraction, h_phi_beamA_diffractionSide2, h_phi_beamB_diffraction,

        h_ch_eta_data, h_ch_eta_beamA_qcd, h_ch_eta_beamA_diffraction, h_ch_eta_beamA_diffractionSide2, h_ch_eta_beamB_diffraction,
        h_ch_phi_data, h_ch_phi_beamA_qcd, h_ch_phi_beamA_diffraction, h_ch_phi_beamA_diffractionSide2, h_ch_phi_beamB_diffraction,
    }) {
        // h->Rebin(2);
        h->Scale(1.0 / h->Integral());
        h->GetXaxis()->SetTitleOffset(1.2);
    }

    for (auto h : { 
        h_E_data, h_E_beamA_qcd, h_E_beamA_diffraction, h_E_beamA_diffractionSide2, h_E_beamB_diffraction,
        h_pt_data, h_pt_beamA_qcd, h_pt_beamA_diffraction, h_pt_beamA_diffractionSide2, h_pt_beamB_diffraction,

        h_ch_E_data, h_ch_E_beamA_qcd, h_ch_E_beamA_diffraction, h_ch_E_beamA_diffractionSide2, h_ch_E_beamB_diffraction,
        h_ch_pt_data, h_ch_pt_beamA_qcd, h_ch_pt_beamA_diffraction, h_ch_pt_beamA_diffractionSide2, h_ch_pt_beamB_diffraction,
    }) {
        h->Rebin(2);
        h->Scale(1.0 / h->Integral());
        h->GetXaxis()->SetTitleOffset(1.2);
    }

    for (auto h : { 
        h_frg_data, h_frg_beamA_qcd, h_frg_beamA_diffraction, h_frg_beamA_diffractionSide2, h_frg_beamB_diffraction,
        h_brg_data,h_brg_beamA_qcd, h_brg_beamA_diffraction, h_brg_beamA_diffractionSide2, h_brg_beamB_diffraction,
    }) {
        // h->Rebin(2);
        h->Scale(1.0 / h->Integral());
        h->GetXaxis()->SetTitleOffset(1.2);
    }

    for (auto h : { 
        h_Nch_data, h_Nch_beamA_qcd, h_Nch_beamA_diffraction, h_Nch_beamA_diffractionSide2, h_Nch_beamB_diffraction,
    }) {
        h->Rebin(2);
        h->GetXaxis()->SetTitleOffset(1.2);
        h->Scale(1.0 / h->Integral());
    }
    
    // Draw eta, phi, E+pt
    TCanvas *c_kinematics = new TCanvas("c_kinematics", "c_kinematics", 2400, 800);
    c_kinematics->Divide(3,1);

    c_kinematics->cd(3);

    h_E_data->SetLineColor(kBlack);
    h_E_data->SetMarkerColor(kBlack);
    h_E_data->SetMarkerStyle(kFullCircle);
    h_pt_data->SetLineColor(kBlack);
    h_pt_data->SetMarkerColor(kBlack);
    h_pt_data->SetMarkerStyle(kOpenCircle);

    h_E_beamA_qcd->SetLineColor(cmsViolet);
    h_E_beamA_qcd->SetMarkerColor(cmsViolet);
    h_E_beamA_qcd->SetMarkerStyle(kFullDiamond);
    h_pt_beamA_qcd->SetLineColor(cmsViolet);
    h_pt_beamA_qcd->SetMarkerColor(cmsViolet);
    h_pt_beamA_qcd->SetMarkerStyle(kOpenDiamond);

    h_E_beamA_diffraction->SetLineColor(cmsBlue);
    h_E_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_E_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);
    h_pt_beamA_diffraction->SetLineColor(cmsBlue);
    h_pt_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_pt_beamA_diffraction->SetMarkerStyle(kOpenTriangleUp);

    h_E_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_E_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_E_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);
    h_pt_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_pt_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_pt_beamB_diffraction->SetMarkerStyle(kOpenTriangleDown);

    h_E_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_E_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_E_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);
    h_pt_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_pt_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_pt_beamA_diffractionSide2->SetMarkerStyle(kOpenSquare);

    h_E_beamA_qcd->GetXaxis()->SetTitle("E^{PF} or p_{T}^{PF} (GeV)");
    h_E_beamA_qcd->GetYaxis()->SetTitle("Normalized entries");
    h_E_beamA_qcd->GetYaxis()->SetRangeUser(1e-4, 10.);
    h_E_beamA_qcd->GetXaxis()->SetRangeUser(0., 70.);
    h_E_beamA_qcd->Draw();
    h_E_beamA_diffraction->Draw("same");
    // h_E_beamB_diffraction->Draw("same");
    h_E_beamA_diffractionSide2->Draw("same");
    h_pt_beamA_qcd->Draw("same");
    h_pt_beamA_diffraction->Draw("same");
    // h_pt_beamB_diffraction->Draw("same");
    h_pt_beamA_diffractionSide2->Draw("same");
    h_E_data->Draw("same");
    h_pt_data->Draw("same");
    c_kinematics->cd(3)->SetLogy();

    TLegend *legend = new TLegend(0.2, 0.65, 0.8, 0.85);
    legend->SetBorderSize(0);
    legend->SetNColumns(2);
    legend->AddEntry(new TH1F(), "E^{PF}", "");
    legend->AddEntry(new TH1F(), "p_{T}^{PF}", "");
    legend->AddEntry(h_E_data, "Data", "pl");
    legend->AddEntry(h_pt_data, "Data", "pl");
    legend->AddEntry(h_E_beamA_qcd, "non-diffr.", "pl");
    legend->AddEntry(h_pt_beamA_qcd, "non-diffr.", "pl");
    legend->AddEntry(h_E_beamA_diffraction, "diffr.", "pl");
    legend->AddEntry(h_pt_beamA_diffraction, "diffr.", "pl");
    // legend->AddEntry(h_E_beamB_diffraction, "BeamB, diffr.", "pl");
    // legend->AddEntry(h_pt_beamB_diffraction, "BeamB, diffr.", "pl");
    legend->AddEntry(h_E_beamA_diffractionSide2, "diffr. side 2", "pl");
    legend->AddEntry(h_pt_beamA_diffractionSide2, "diffr. side 2", "pl");
    legend->Draw();

    c_kinematics->cd(1);

    h_eta_data->SetLineColor(kBlack);
    h_eta_data->SetMarkerColor(kBlack);
    h_eta_data->SetMarkerStyle(kFullCircle);

    h_eta_beamA_qcd->SetLineColor(cmsViolet);
    h_eta_beamA_qcd->SetMarkerColor(cmsViolet);
    h_eta_beamA_qcd->SetMarkerStyle(kFullDiamond);

    h_eta_beamA_diffraction->SetLineColor(cmsBlue);
    h_eta_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_eta_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    h_eta_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_eta_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_eta_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);

    h_eta_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_eta_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_eta_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);


    h_eta_beamA_qcd->GetXaxis()->SetTitle("#eta^{PF}");
    h_eta_beamA_qcd->GetYaxis()->SetTitle("Normalized entries");
    h_eta_beamA_qcd->GetYaxis()->SetRangeUser(0, 0.06);
    // h_eta_beamA_qcd->GetYaxis()->SetRangeUser(1e-4, 10);
    h_eta_beamA_qcd->GetXaxis()->SetRangeUser(-5., 5.);
    h_eta_beamA_qcd->Draw();
    h_eta_beamA_diffraction->Draw("same");
    // h_eta_beamB_diffraction->Draw("same");
    h_eta_beamA_diffractionSide2->Draw("same");
    h_eta_data->Draw("same");
    // c_kinematics->cd(1)->SetLogy();

    TLegend *legend_m = new TLegend(0.2, 0.7, 0.8, 0.85);
    legend_m->SetBorderSize(0);
    legend_m->SetFillStyle(0);
    legend_m->AddEntry(h_eta_data, "Data", "pl");
    legend_m->AddEntry(h_eta_beamA_qcd, "non-diffr.", "pl");
    legend_m->AddEntry(h_eta_beamA_diffraction, "diffr.", "pl");
    // legend_m->AddEntry(h_eta_beamB_diffraction, "diffr.", "pl");
    legend_m->AddEntry(h_eta_beamA_diffractionSide2, "diffr. side 2", "pl");
    legend_m->Draw();

    c_kinematics->cd(2);

    h_phi_data->SetLineColor(kBlack);
    h_phi_data->SetMarkerColor(kBlack);
    h_phi_data->SetMarkerStyle(kFullCircle);

    h_phi_beamA_qcd->SetLineColor(cmsViolet);
    h_phi_beamA_qcd->SetMarkerColor(cmsViolet);
    h_phi_beamA_qcd->SetMarkerStyle(kFullDiamond);

    h_phi_beamA_diffraction->SetLineColor(cmsBlue);
    h_phi_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_phi_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    h_phi_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_phi_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_phi_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);

    h_phi_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_phi_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_phi_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    h_phi_beamA_qcd->GetXaxis()->SetTitle("#phi^{PF} (radians)");
    h_phi_beamA_qcd->GetYaxis()->SetTitle("Normalized entries");
    h_phi_beamA_qcd->GetXaxis()->SetRangeUser(-3.14159, 3.14159);
    h_phi_beamA_qcd->GetYaxis()->SetRangeUser(0., 0.18);
    h_phi_beamA_qcd->Draw();
    h_phi_beamA_diffraction->Draw("same");
    // h_phi_beamB_diffraction->Draw("same");
    h_phi_beamA_diffractionSide2->Draw("same");
    h_phi_data->Draw("same");

    TLegend *legend_phi = (TLegend *) legend_m->Clone("legend_phi");
    legend_phi->Draw();


    c_kinematics->Print("plots/pf_distributions/data_vs_MC_PF_kinematics"+suffix_data+".pdf");

    TCanvas *c_kinematics_ch = new TCanvas("c_kinematics_ch", "c_kinematics_ch", 2400, 800);
    c_kinematics_ch->Divide(3,1);

    c_kinematics_ch->cd(3);

    h_ch_E_data->SetLineColor(kBlack);
    h_ch_E_data->SetMarkerColor(kBlack);
    h_ch_E_data->SetMarkerStyle(kFullCircle);
    h_ch_pt_data->SetLineColor(kBlack);
    h_ch_pt_data->SetMarkerColor(kBlack);
    h_ch_pt_data->SetMarkerStyle(kOpenCircle);

    h_ch_E_beamA_qcd->SetLineColor(cmsViolet);
    h_ch_E_beamA_qcd->SetMarkerColor(cmsViolet);
    h_ch_E_beamA_qcd->SetMarkerStyle(kFullDiamond);
    h_ch_pt_beamA_qcd->SetLineColor(cmsViolet);
    h_ch_pt_beamA_qcd->SetMarkerColor(cmsViolet);
    h_ch_pt_beamA_qcd->SetMarkerStyle(kOpenDiamond);

    h_ch_E_beamA_diffraction->SetLineColor(cmsBlue);
    h_ch_E_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_ch_E_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);
    h_ch_pt_beamA_diffraction->SetLineColor(cmsBlue);
    h_ch_pt_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_ch_pt_beamA_diffraction->SetMarkerStyle(kOpenTriangleUp);

    h_ch_E_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_ch_E_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_ch_E_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);
    h_ch_pt_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_ch_pt_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_ch_pt_beamB_diffraction->SetMarkerStyle(kOpenTriangleDown);

    h_ch_E_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_ch_E_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_ch_E_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);
    h_ch_pt_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_ch_pt_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_ch_pt_beamA_diffractionSide2->SetMarkerStyle(kOpenSquare);

    h_ch_E_beamA_qcd->GetXaxis()->SetTitle("E^{PF,ch} or p_{T}^{PF,ch} (GeV)");
    h_ch_E_beamA_qcd->GetYaxis()->SetTitle("Normalized entries");
    h_ch_E_beamA_qcd->GetYaxis()->SetRangeUser(1e-4, 10.);
    h_ch_E_beamA_qcd->GetXaxis()->SetRangeUser(0., 70.);
    h_ch_E_beamA_qcd->Draw();
    h_ch_E_beamA_diffraction->Draw("same");
    // h_ch_E_beamB_diffraction->Draw("same");
    h_ch_E_beamA_diffractionSide2->Draw("same");
    h_ch_pt_beamA_qcd->Draw("same");
    h_ch_pt_beamA_diffraction->Draw("same");
    // h_ch_pt_beamB_diffraction->Draw("same");
    h_ch_pt_beamA_diffractionSide2->Draw("same");
    h_ch_E_data->Draw("same");
    h_ch_pt_data->Draw("same");
    c_kinematics_ch->cd(3)->SetLogy();

    TLegend *legend_ch = new TLegend(0.2, 0.65, 0.8, 0.85);
    legend_ch->SetBorderSize(0);
    legend_ch->SetNColumns(2);
    legend_ch->AddEntry(new TH1F(), "E^{PF,ch}", "");
    legend_ch->AddEntry(new TH1F(), "p_{T}^{PF,ch}", "");
    legend_ch->AddEntry(h_ch_E_data, "Data", "pl");
    legend_ch->AddEntry(h_ch_pt_data, "Data", "pl");
    legend_ch->AddEntry(h_ch_E_beamA_qcd, "non-diffr.", "pl");
    legend_ch->AddEntry(h_ch_pt_beamA_qcd, "non-diffr.", "pl");
    legend_ch->AddEntry(h_ch_E_beamA_diffraction, "diffr.", "pl");
    legend_ch->AddEntry(h_ch_pt_beamA_diffraction, "diffr.", "pl");
    // legend_ch->AddEntry(h_ch_E_beamB_diffraction, "BeamB, diffr.", "pl");
    // legend_ch->AddEntry(h_ch_pt_beamB_diffraction, "BeamB, diffr.", "pl");
    legend_ch->AddEntry(h_ch_E_beamA_diffractionSide2, "diffr. side 2", "pl");
    legend_ch->AddEntry(h_ch_pt_beamA_diffractionSide2, "diffr. side 2", "pl");
    legend_ch->Draw();

    c_kinematics_ch->cd(1);

    h_ch_eta_data->SetLineColor(kBlack);
    h_ch_eta_data->SetMarkerColor(kBlack);
    h_ch_eta_data->SetMarkerStyle(kFullCircle);

    h_ch_eta_beamA_qcd->SetLineColor(cmsViolet);
    h_ch_eta_beamA_qcd->SetMarkerColor(cmsViolet);
    h_ch_eta_beamA_qcd->SetMarkerStyle(kFullDiamond);

    h_ch_eta_beamA_diffraction->SetLineColor(cmsBlue);
    h_ch_eta_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_ch_eta_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    h_ch_eta_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_ch_eta_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_ch_eta_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);

    h_ch_eta_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_ch_eta_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_ch_eta_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);


    h_ch_eta_beamA_qcd->GetXaxis()->SetTitle("#eta^{PF,ch}");
    h_ch_eta_beamA_qcd->GetYaxis()->SetTitle("Normalized entries");
    h_ch_eta_beamA_qcd->GetYaxis()->SetRangeUser(0, 0.1);
    h_ch_eta_beamA_qcd->GetXaxis()->SetRangeUser(-5., 5.);
    h_ch_eta_beamA_qcd->Draw();
    h_ch_eta_beamA_diffraction->Draw("same");
    // h_ch_eta_beamB_diffraction->Draw("same");
    h_ch_eta_beamA_diffractionSide2->Draw("same");
    h_ch_eta_data->Draw("same");

    TLegend *legend_ch_m = new TLegend(0.2, 0.7, 0.8, 0.85);
    legend_ch_m->SetBorderSize(0);
    legend_ch_m->SetFillStyle(0);
    legend_ch_m->AddEntry(h_ch_eta_data, "Data", "pl");
    legend_ch_m->AddEntry(h_ch_eta_beamA_qcd, "non-diffr.", "pl");
    legend_ch_m->AddEntry(h_ch_eta_beamA_diffraction, "diffr.", "pl");
    // legend_ch_m->AddEntry(h_ch_eta_beamB_diffraction, "diffr.", "pl");
    legend_ch_m->AddEntry(h_ch_eta_beamA_diffractionSide2, "diffr. side 2", "pl");
    legend_ch_m->Draw();

    c_kinematics_ch->cd(2);

    h_ch_phi_data->SetLineColor(kBlack);
    h_ch_phi_data->SetMarkerColor(kBlack);
    h_ch_phi_data->SetMarkerStyle(kFullCircle);

    h_ch_phi_beamA_qcd->SetLineColor(cmsViolet);
    h_ch_phi_beamA_qcd->SetMarkerColor(cmsViolet);
    h_ch_phi_beamA_qcd->SetMarkerStyle(kFullDiamond);

    h_ch_phi_beamA_diffraction->SetLineColor(cmsBlue);
    h_ch_phi_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_ch_phi_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    h_ch_phi_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_ch_phi_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_ch_phi_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);

    h_ch_phi_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_ch_phi_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_ch_phi_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    h_ch_phi_beamA_qcd->GetXaxis()->SetTitle("#phi^{PF,ch} (radians)");
    h_ch_phi_beamA_qcd->GetYaxis()->SetTitle("Normalized entries");
    h_ch_phi_beamA_qcd->GetXaxis()->SetRangeUser(-3.14159, 3.14159);
    h_ch_phi_beamA_qcd->GetYaxis()->SetRangeUser(0., 0.18);
    h_ch_phi_beamA_qcd->Draw();
    h_ch_phi_beamA_diffraction->Draw("same");
    // h_ch_phi_beamB_diffraction->Draw("same");
    h_ch_phi_beamA_diffractionSide2->Draw("same");
    h_ch_phi_data->Draw("same");

    TLegend *legend_ch_phi = (TLegend *) legend_ch_m->Clone("legend_ch_phi");
    legend_ch_phi->Draw();


    c_kinematics_ch->Print("plots/pf_distributions/data_vs_MC_PFch_kinematics"+suffix_data+".pdf");

    // frg, brg 
    TCanvas *c_observables = new TCanvas("c_observables", "c_observables", 2400, 800);
    c_observables->Divide(3,1);

    c_observables->cd(2);

    h_frg_data->SetLineColor(kBlack);
    h_frg_data->SetMarkerColor(kBlack);
    h_frg_data->SetMarkerStyle(kFullCircle);

    h_frg_beamA_qcd->SetLineColor(cmsViolet);
    h_frg_beamA_qcd->SetMarkerColor(cmsViolet);
    h_frg_beamA_qcd->SetMarkerStyle(kFullDiamond);

    h_frg_beamA_diffraction->SetLineColor(cmsBlue);
    h_frg_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_frg_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    h_frg_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_frg_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_frg_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);

    h_frg_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_frg_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_frg_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    h_frg_beamA_qcd->GetXaxis()->SetTitle("FRG");
    h_frg_beamA_qcd->GetYaxis()->SetTitle("Normalized entries");
    h_frg_beamA_qcd->GetYaxis()->SetRangeUser(1e-5, 100.);
    h_frg_beamA_qcd->GetXaxis()->SetRangeUser(0., 3.);
    h_frg_beamA_qcd->Draw();
    h_frg_beamA_diffraction->Draw("same");
    // h_frg_beamB_diffraction->Draw("same");
    h_frg_beamA_diffractionSide2->Draw("same");
    h_frg_data->Draw("same");
    legend_m->Draw();
    c_observables->cd(2)->SetLogy();

    c_observables->cd(3);

    h_brg_data->SetLineColor(kBlack);
    h_brg_data->SetMarkerColor(kBlack);
    h_brg_data->SetMarkerStyle(kFullCircle);

    h_brg_beamA_qcd->SetLineColor(cmsViolet);
    h_brg_beamA_qcd->SetMarkerColor(cmsViolet);
    h_brg_beamA_qcd->SetMarkerStyle(kFullDiamond);

    h_brg_beamA_diffraction->SetLineColor(cmsBlue);
    h_brg_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_brg_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    h_brg_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_brg_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_brg_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);

    h_brg_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_brg_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_brg_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    h_brg_beamA_qcd->GetXaxis()->SetTitle("BRG");
    h_brg_beamA_qcd->GetYaxis()->SetTitle("Normalized entries");
    h_brg_beamA_qcd->GetYaxis()->SetRangeUser(0., 0.3);
    h_brg_beamA_qcd->GetXaxis()->SetRangeUser(0., 5.);
    h_brg_beamA_qcd->Draw();
    h_brg_beamA_diffraction->Draw("same");
    // h_brg_beamB_diffraction->Draw("same");
    h_brg_beamA_diffractionSide2->Draw("same");
    h_brg_data->Draw("same");
    legend_m->Draw();

    c_observables->cd(1);

    h_Nch_data->SetLineColor(kBlack);
    h_Nch_data->SetMarkerColor(kBlack);
    h_Nch_data->SetMarkerStyle(kFullCircle);

    h_Nch_beamA_qcd->SetLineColor(cmsViolet);
    h_Nch_beamA_qcd->SetMarkerColor(cmsViolet);
    h_Nch_beamA_qcd->SetMarkerStyle(kFullDiamond);

    h_Nch_beamA_diffraction->SetLineColor(cmsBlue);
    h_Nch_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_Nch_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    h_Nch_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_Nch_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_Nch_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);

    h_Nch_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_Nch_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_Nch_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    h_Nch_beamA_qcd->GetXaxis()->SetTitle("N_{ch}");
    h_Nch_beamA_qcd->GetYaxis()->SetTitle("Normalized entries");
    h_Nch_beamA_qcd->GetYaxis()->SetRangeUser(0., 0.15);
    h_Nch_beamA_qcd->GetXaxis()->SetRangeUser(0., 100.);
    h_Nch_beamA_qcd->Draw();
    h_Nch_beamA_diffraction->Draw("same");
    // h_Nch_beamB_diffraction->Draw("same");
    h_Nch_beamA_diffractionSide2->Draw("same");
    h_Nch_data->Draw("same");
    legend_m->Draw();

    c_observables->Print("plots/pf_distributions/data_vs_MC_rapgap"+suffix_data+".pdf");
}