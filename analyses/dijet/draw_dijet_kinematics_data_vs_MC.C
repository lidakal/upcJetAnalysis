#include "../../cms_palette.h"

void draw_dijet_kinematics_data_vs_MC()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);

    // TString suffix = "_oppHF_oppEC2_trkLim2p5_ptgr0p2_chOnly_jetID_jetVM";
    TString suffix = "_0n0n_bothHF";
    TString suffix_mc = "_bothHF";
    
    TFile *f_data = new TFile("histos/hiforwardAll_2024rereco_dijet_kinematics"+suffix+".root");
    std::cout << "DATA: Loaded " << f_data->GetName() << std::endl;
    TH1F *h_QT_data = (TH1F*)f_data->Get("h_QT")->Clone("h_QT_data");
    TH1F *h_PT_data = (TH1F*)f_data->Get("h_PT")->Clone("h_PT_data");
    TH1F *h_Minv_data = (TH1F*)f_data->Get("h_Minv")->Clone("h_Minv_data");
    TH1F *h_y_data = (TH1F*)f_data->Get("h_y")->Clone("h_y_data");
    TH1F *h_PHI_data = (TH1F*)f_data->Get("h_PHI")->Clone("h_PHI_data");
    TH1F *h_PHI_signed_data = (TH1F*)f_data->Get("h_PHI_signed")->Clone("h_PHI_signed_data");
    TH2F *h_cos2PHI_vs_QT_data = (TH2F*)f_data->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_data");
    TH2F *h_cos4PHI_vs_QT_data = (TH2F*)f_data->Get("h_cos4PHI_vs_QT")->Clone("h_cos4PHI_vs_QT_data");

    TFile *f_beamA_diffraction = new TFile("histos/beamA_diffraction_pthat10_dijet_kinematics"+suffix_mc+".root");
    std::cout << "BEAM A DIFFRACTION: Loaded " << f_beamA_diffraction->GetName() << std::endl;
    TH1F *h_QT_beamA_diffraction = (TH1F*)f_beamA_diffraction->Get("h_QT")->Clone("h_QT_beamA_diffraction");
    TH1F *h_PT_beamA_diffraction = (TH1F*)f_beamA_diffraction->Get("h_PT")->Clone("h_PT_beamA_diffraction");
    TH1F *h_Minv_beamA_diffraction = (TH1F*)f_beamA_diffraction->Get("h_Minv")->Clone("h_Minv_beamA_diffraction");
    TH1F *h_y_beamA_diffraction = (TH1F*)f_beamA_diffraction->Get("h_y")->Clone("h_y_beamA_diffraction");
    TH1F *h_PHI_beamA_diffraction = (TH1F*)f_beamA_diffraction->Get("h_PHI")->Clone("h_PHI_beamA_diffraction");
    TH1F *h_PHI_signed_beamA_diffraction = (TH1F*)f_beamA_diffraction->Get("h_PHI_signed")->Clone("h_PHI_signed_beamA_diffraction");
    TH2F *h_cos2PHI_vs_QT_beamA_diffraction = (TH2F*)f_beamA_diffraction->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_beamA_diffraction");
    TH2F *h_cos4PHI_vs_QT_beamA_diffraction = (TH2F*)f_beamA_diffraction->Get("h_cos4PHI_vs_QT")->Clone("h_cos4PHI_vs_QT_beamA_diffraction");

    TFile *f_beamA_diffractionSide2 = new TFile("histos/beamA_diffractionSide2_pthat10_dijet_kinematics"+suffix_mc+".root");
    std::cout << "BEAM A DIFFRACTIONSIDE2: Loaded " << f_beamA_diffractionSide2->GetName() << std::endl;
    TH1F *h_QT_beamA_diffractionSide2 = (TH1F*)f_beamA_diffractionSide2->Get("h_QT")->Clone("h_QT_beamA_diffractionSide2");
    TH1F *h_PT_beamA_diffractionSide2 = (TH1F*)f_beamA_diffractionSide2->Get("h_PT")->Clone("h_PT_beamA_diffractionSide2");
    TH1F *h_Minv_beamA_diffractionSide2 = (TH1F*)f_beamA_diffractionSide2->Get("h_Minv")->Clone("h_Minv_beamA_diffractionSide2");
    TH1F *h_y_beamA_diffractionSide2 = (TH1F*)f_beamA_diffractionSide2->Get("h_y")->Clone("h_y_beamA_diffractionSide2");
    TH1F *h_PHI_beamA_diffractionSide2 = (TH1F*)f_beamA_diffractionSide2->Get("h_PHI")->Clone("h_PHI_beamA_diffractionSide2");
    TH1F *h_PHI_signed_beamA_diffractionSide2 = (TH1F*)f_beamA_diffractionSide2->Get("h_PHI_signed")->Clone("h_PHI_signed_beamA_diffractionSide2");
    TH2F *h_cos2PHI_vs_QT_beamA_diffractionSide2 = (TH2F*)f_beamA_diffractionSide2->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_beamA_diffractionSide2");
    TH2F *h_cos4PHI_vs_QT_beamA_diffractionSide2 = (TH2F*)f_beamA_diffractionSide2->Get("h_cos4PHI_vs_QT")->Clone("h_cos4PHI_vs_QT_beamA_diffractionSide2");

    TFile *f_beamA_qcd = new TFile("histos/beamA_qcd_pthat10_dijet_kinematics"+suffix_mc+".root");
    std::cout << "BEAM A QCD: Loaded " << f_beamA_qcd->GetName() << std::endl;
    TH1F *h_QT_beamA_qcd = (TH1F*)f_beamA_qcd->Get("h_QT")->Clone("h_QT_beamA_qcd");
    TH1F *h_PT_beamA_qcd = (TH1F*)f_beamA_qcd->Get("h_PT")->Clone("h_PT_beamA_qcd");
    TH1F *h_Minv_beamA_qcd = (TH1F*)f_beamA_qcd->Get("h_Minv")->Clone("h_Minv_beamA_qcd");
    TH1F *h_y_beamA_qcd = (TH1F*)f_beamA_qcd->Get("h_y")->Clone("h_y_beamA_qcd");
    TH1F *h_PHI_beamA_qcd = (TH1F*)f_beamA_qcd->Get("h_PHI")->Clone("h_PHI_beamA_qcd");
    TH1F *h_PHI_signed_beamA_qcd = (TH1F*)f_beamA_qcd->Get("h_PHI_signed")->Clone("h_PHI_signed_beamA_qcd");
    TH2F *h_cos2PHI_vs_QT_beamA_qcd = (TH2F*)f_beamA_qcd->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_beamA_qcd");
    TH2F *h_cos4PHI_vs_QT_beamA_qcd = (TH2F*)f_beamA_qcd->Get("h_cos4PHI_vs_QT")->Clone("h_cos4PHI_vs_QT_beamA_qcd");

    TFile *f_beamB_diffraction = new TFile("histos/beamB_diffraction_pthat10_dijet_kinematics"+suffix_mc+".root");
    std::cout << "BEAM B: Loaded " << f_beamB_diffraction->GetName() << std::endl;
    TH1F *h_QT_beamB_diffraction = (TH1F*)f_beamB_diffraction->Get("h_QT")->Clone("h_QT_beamB_diffraction");
    TH1F *h_PT_beamB_diffraction = (TH1F*)f_beamB_diffraction->Get("h_PT")->Clone("h_PT_beamB_diffraction");
    TH1F *h_Minv_beamB_diffraction = (TH1F*)f_beamB_diffraction->Get("h_Minv")->Clone("h_Minv_beamB_diffraction");
    TH1F *h_y_beamB_diffraction = (TH1F*)f_beamB_diffraction->Get("h_y")->Clone("h_y_beamB_diffraction");
    TH1F *h_PHI_beamB_diffraction = (TH1F*)f_beamB_diffraction->Get("h_PHI")->Clone("h_PHI_beamB_diffraction");
    TH1F *h_PHI_signed_beamB_diffraction = (TH1F*)f_beamB_diffraction->Get("h_PHI_signed")->Clone("h_PHI_signed_beamB_diffraction");
    TH2F *h_cos2PHI_vs_QT_beamB_diffraction = (TH2F*)f_beamB_diffraction->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_beamB_diffraction");
    TH2F *h_cos4PHI_vs_QT_beamB_diffraction = (TH2F*)f_beamB_diffraction->Get("h_cos4PHI_vs_QT")->Clone("h_cos4PHI_vs_QT_beamB_diffraction");

    // Preprocess
    for (auto h : { 
        h_QT_data, h_QT_beamA_diffraction, h_QT_beamA_diffractionSide2, h_QT_beamA_qcd, h_QT_beamB_diffraction,
        h_PT_data, h_PT_beamA_diffraction, h_PT_beamA_diffractionSide2, h_PT_beamA_qcd, h_PT_beamB_diffraction,
        h_Minv_data, h_Minv_beamA_diffraction, h_Minv_beamA_diffractionSide2, h_Minv_beamA_qcd, h_Minv_beamB_diffraction,
        h_y_data, h_y_beamA_diffraction, h_y_beamA_diffractionSide2, h_y_beamA_qcd, h_y_beamB_diffraction,
    }) {
        h->Rebin(2);
        h->Scale(1./h->Integral(),"width");
    }

    for (auto h : { h_PHI_signed_data, h_PHI_signed_beamA_diffraction, h_PHI_signed_beamA_diffractionSide2, h_PHI_signed_beamA_qcd, h_PHI_signed_beamB_diffraction }) {
        h->RebinX(5);
        h->Scale(1./h->Integral(),"width");
    }

    for (auto h : { h_cos2PHI_vs_QT_data, h_cos2PHI_vs_QT_beamA_diffraction, h_cos2PHI_vs_QT_beamA_diffractionSide2, h_cos2PHI_vs_QT_beamA_qcd, h_cos2PHI_vs_QT_beamB_diffraction,
                    h_cos4PHI_vs_QT_data, h_cos4PHI_vs_QT_beamA_diffraction, h_cos4PHI_vs_QT_beamA_diffractionSide2, h_cos4PHI_vs_QT_beamA_qcd, h_cos4PHI_vs_QT_beamB_diffraction }) {
        h->RebinX(5);
    }

    // QT + PT, Minv, y
    TCanvas *c_kinematics = new TCanvas("c_kinematics", "c_kinematics", 2400, 800);
    c_kinematics->Divide(3,1);

    c_kinematics->cd(1);

    h_QT_data->SetLineColor(kBlack);
    h_QT_data->SetMarkerColor(kBlack);
    h_QT_data->SetMarkerStyle(kFullCircle);
    h_QT_data->GetXaxis()->SetTitle("QT or PT (GeV)");
    h_QT_data->GetYaxis()->SetTitle("Normalized entries");
    h_QT_data->GetYaxis()->SetRangeUser(0., 0.2);
    h_QT_data->GetXaxis()->SetRangeUser(0., 60.);

    h_QT_beamA_diffraction->SetLineColor(cmsBlue);
    h_QT_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_QT_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    h_QT_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_QT_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_QT_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    h_QT_beamA_qcd->SetLineColor(cmsViolet);
    h_QT_beamA_qcd->SetMarkerColor(cmsViolet);
    h_QT_beamA_qcd->SetMarkerStyle(kFullDiamond);

    h_PT_data->SetLineColor(kBlack);
    h_PT_data->SetMarkerColor(kBlack);
    h_PT_data->SetMarkerStyle(kOpenCircle);

    h_PT_beamA_diffraction->SetLineColor(cmsBlue);
    h_PT_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_PT_beamA_diffraction->SetMarkerStyle(kOpenTriangleUp);

    h_PT_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_PT_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_PT_beamA_diffractionSide2->SetMarkerStyle(kOpenSquare);

    h_PT_beamA_qcd->SetLineColor(cmsViolet);
    h_PT_beamA_qcd->SetMarkerColor(cmsViolet);
    h_PT_beamA_qcd->SetMarkerStyle(kOpenDiamond);

    h_QT_data->Draw();
    h_QT_beamA_diffraction->Draw("same");
    h_QT_beamA_diffractionSide2->Draw("same");
    h_QT_beamA_qcd->Draw("same");
    h_QT_data->Draw("same");
    h_PT_data->Draw("same");
    h_PT_beamA_diffraction->Draw("same");
    h_PT_beamA_diffractionSide2->Draw("same");
    h_PT_beamA_qcd->Draw("same");
    h_PT_data->Draw("same");
    

    TLegend *legend = new TLegend(0.2, 0.6, 0.8, 0.85);
    legend->SetBorderSize(0);
    legend->SetNColumns(2);
    legend->AddEntry(new TH1F(), "QT", "");
    legend->AddEntry(new TH1F(), "PT", "");
    legend->AddEntry(h_QT_data, "Data", "pl");
    legend->AddEntry(h_PT_data, "Data", "pl");
    legend->AddEntry(h_QT_beamA_qcd, "non-diffr.", "pl");
    legend->AddEntry(h_PT_beamA_qcd, "non-diffr.", "pl");
    legend->AddEntry(h_QT_beamA_diffraction, "diffr.", "pl");
    legend->AddEntry(h_PT_beamA_diffraction, "diffr.", "pl");
    legend->AddEntry(h_QT_beamA_diffractionSide2, "diffr. side 2", "pl");
    legend->AddEntry(h_PT_beamA_diffractionSide2, "diffr. side 2", "pl");
    legend->Draw();

    c_kinematics->cd(2);

    h_Minv_data->SetLineColor(kBlack);
    h_Minv_data->SetMarkerColor(kBlack);
    h_Minv_data->SetMarkerStyle(kFullCircle);
    h_Minv_data->GetXaxis()->SetTitle("Minv (GeV)");
    h_Minv_data->GetYaxis()->SetTitle("Normalized entries");
    h_Minv_data->GetYaxis()->SetRangeUser(0., 0.05);
    h_Minv_data->GetXaxis()->SetRangeUser(0., 200.);

    h_Minv_beamA_diffraction->SetLineColor(cmsBlue);
    h_Minv_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_Minv_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    h_Minv_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_Minv_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_Minv_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    h_Minv_beamA_qcd->SetLineColor(cmsViolet);
    h_Minv_beamA_qcd->SetMarkerColor(cmsViolet);
    h_Minv_beamA_qcd->SetMarkerStyle(kFullDiamond);

    TLegend *legend_m = new TLegend(0.5, 0.6, 0.85, 0.85);
    legend_m->SetBorderSize(0);
    legend_m->AddEntry(h_Minv_data, "Data", "pl");
    legend_m->AddEntry(h_Minv_beamA_qcd, "non-diffr.", "pl");
    legend_m->AddEntry(h_Minv_beamA_diffraction, "diffr.", "pl");
    legend_m->AddEntry(h_Minv_beamA_diffractionSide2, "diffr. side 2", "pl");

    h_Minv_data->Draw();
    h_Minv_beamA_diffraction->Draw("same");
    h_Minv_beamA_diffractionSide2->Draw("same");
    h_Minv_beamA_qcd->Draw("same");
    h_Minv_data->Draw("same");
    legend_m->Draw();

    c_kinematics->cd(3);
   
    h_y_data->SetLineColor(kBlack);
    h_y_data->SetMarkerColor(kBlack);
    h_y_data->SetMarkerStyle(kFullCircle);
    h_y_data->GetXaxis()->SetTitle("Dijet y");
    h_y_data->GetYaxis()->SetTitle("Normalized entries");
    h_y_data->GetYaxis()->SetRangeUser(0., 1.2);
    h_y_data->GetXaxis()->SetRangeUser(-2.5, 2.5);

    h_y_beamA_diffraction->SetLineColor(cmsBlue);
    h_y_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_y_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    h_y_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_y_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_y_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    h_y_beamA_qcd->SetLineColor(cmsViolet);
    h_y_beamA_qcd->SetMarkerColor(cmsViolet);
    h_y_beamA_qcd->SetMarkerStyle(kFullDiamond);

    TLegend *legend_y = new TLegend(0.2, 0.5, 0.5, 0.85);
    legend_y->SetBorderSize(0);
    legend_y->AddEntry(h_y_data, "Data", "pl");
    legend_y->AddEntry(h_y_beamA_qcd, "non-diffr.", "pl");
    legend_y->AddEntry(h_y_beamA_diffraction, "diffr.", "pl");
    legend_y->AddEntry(h_y_beamA_diffractionSide2, "diffr. side 2", "pl");

    h_y_data->Draw();
    h_y_beamA_diffraction->Draw("same");
    h_y_beamA_diffractionSide2->Draw("same");
    h_y_beamA_qcd->Draw("same");
    h_y_data->Draw("same");
    legend_y->Draw();

    c_kinematics->Print("plots/dijet_kinematics/data_vs_MC_dijet_kinematics"+suffix+".pdf");

    // dN/dPHI vs PHI, <cos(2PHI)> vs QT, <cos(4PHI)> vs QT
    TCanvas *c_observables = new TCanvas("c_observables", "c_observables", 2400, 800);
    c_observables->Divide(3,1);

    c_observables->cd(1);

    h_PHI_signed_data->SetLineColor(kBlack);
    h_PHI_signed_data->SetMarkerColor(kBlack);
    h_PHI_signed_data->SetMarkerStyle(kFullCircle);
    h_PHI_signed_data->GetXaxis()->SetTitle("#Phi (radians)");
    h_PHI_signed_data->GetYaxis()->SetTitle("Normalized entries");
    h_PHI_signed_data->GetYaxis()->SetRangeUser(0., 0.6);
    h_PHI_signed_data->GetXaxis()->SetRangeUser(-3.2, 3.2);

    h_PHI_signed_beamA_diffraction->SetLineColor(cmsBlue);
    h_PHI_signed_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_PHI_signed_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    h_PHI_signed_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_PHI_signed_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_PHI_signed_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    h_PHI_signed_beamA_qcd->SetLineColor(cmsViolet);
    h_PHI_signed_beamA_qcd->SetMarkerColor(cmsViolet);
    h_PHI_signed_beamA_qcd->SetMarkerStyle(kFullDiamond);

    TLegend *legend_PHI = new TLegend(0.5, 0.6, 0.85, 0.85);
    legend_PHI->SetBorderSize(0);
    legend_PHI->AddEntry(h_PHI_signed_data, "Data", "pl");
    legend_PHI->AddEntry(h_PHI_signed_beamA_qcd, "non-diffr.", "pl");
    legend_PHI->AddEntry(h_PHI_signed_beamA_diffraction, "diffr.", "pl");
    legend_PHI->AddEntry(h_PHI_signed_beamA_diffractionSide2, "diffr. side 2", "pl");

    h_PHI_signed_data->Draw();
    h_PHI_signed_beamA_diffraction->Draw("same");
    h_PHI_signed_beamA_diffractionSide2->Draw("same");
    h_PHI_signed_beamA_qcd->Draw("same");
    h_PHI_signed_data->Draw("same");
    legend_PHI->Draw();

    c_observables->cd(2);

    TProfile *p_cos2PHI_vs_QT_data = h_cos2PHI_vs_QT_data->ProfileX();
    p_cos2PHI_vs_QT_data->SetLineColor(kBlack);
    p_cos2PHI_vs_QT_data->SetMarkerColor(kBlack);
    p_cos2PHI_vs_QT_data->SetMarkerStyle(kFullCircle);
    p_cos2PHI_vs_QT_data->GetXaxis()->SetTitle("QT");
    p_cos2PHI_vs_QT_data->GetYaxis()->SetTitle("<cos(2#Phi)>");
    p_cos2PHI_vs_QT_data->GetYaxis()->SetRangeUser(-1., 2.);
    p_cos2PHI_vs_QT_data->GetXaxis()->SetRangeUser(0., 40.);

    TProfile *p_cos2PHI_vs_QT_beamA_diffraction = h_cos2PHI_vs_QT_beamA_diffraction->ProfileX();
    p_cos2PHI_vs_QT_beamA_diffraction->SetLineColor(cmsBlue);
    p_cos2PHI_vs_QT_beamA_diffraction->SetMarkerColor(cmsBlue);
    p_cos2PHI_vs_QT_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    TProfile *p_cos2PHI_vs_QT_beamA_diffractionSide2 = h_cos2PHI_vs_QT_beamA_diffractionSide2->ProfileX();
    p_cos2PHI_vs_QT_beamA_diffractionSide2->SetLineColor(cmsRed);
    p_cos2PHI_vs_QT_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    p_cos2PHI_vs_QT_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    TProfile *p_cos2PHI_vs_QT_beamA_qcd = h_cos2PHI_vs_QT_beamA_qcd->ProfileX();
    p_cos2PHI_vs_QT_beamA_qcd->SetLineColor(cmsViolet);
    p_cos2PHI_vs_QT_beamA_qcd->SetMarkerColor(cmsViolet);
    p_cos2PHI_vs_QT_beamA_qcd->SetMarkerStyle(kDiamond);

    p_cos2PHI_vs_QT_data->Draw();
    p_cos2PHI_vs_QT_beamA_diffraction->Draw("same");
    p_cos2PHI_vs_QT_beamA_diffractionSide2->Draw("same");
    p_cos2PHI_vs_QT_beamA_qcd->Draw("same");
    p_cos2PHI_vs_QT_data->Draw("same");
    legend_PHI->Draw();

    c_observables->cd(3);

    TProfile *p_cos4PHI_vs_QT_data = h_cos4PHI_vs_QT_data->ProfileX();
    p_cos4PHI_vs_QT_data->SetLineColor(kBlack);
    p_cos4PHI_vs_QT_data->SetMarkerColor(kBlack);
    p_cos4PHI_vs_QT_data->SetMarkerStyle(kFullCircle);
    p_cos4PHI_vs_QT_data->GetXaxis()->SetTitle("QT");
    p_cos4PHI_vs_QT_data->GetYaxis()->SetTitle("<cos(2#Phi)>");
    p_cos4PHI_vs_QT_data->GetYaxis()->SetRangeUser(-1., 2.);
    p_cos4PHI_vs_QT_data->GetXaxis()->SetRangeUser(0., 40.);

    TProfile *p_cos4PHI_vs_QT_beamA_diffraction = h_cos4PHI_vs_QT_beamA_diffraction->ProfileX();
    p_cos4PHI_vs_QT_beamA_diffraction->SetLineColor(cmsBlue);
    p_cos4PHI_vs_QT_beamA_diffraction->SetMarkerColor(cmsBlue);
    p_cos4PHI_vs_QT_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    TProfile *p_cos4PHI_vs_QT_beamA_diffractionSide2 = h_cos4PHI_vs_QT_beamA_diffractionSide2->ProfileX();
    p_cos4PHI_vs_QT_beamA_diffractionSide2->SetLineColor(cmsRed);
    p_cos4PHI_vs_QT_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    p_cos4PHI_vs_QT_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    TProfile *p_cos4PHI_vs_QT_beamA_qcd = h_cos4PHI_vs_QT_beamA_qcd->ProfileX();
    p_cos4PHI_vs_QT_beamA_qcd->SetLineColor(cmsViolet);
    p_cos4PHI_vs_QT_beamA_qcd->SetMarkerColor(cmsViolet);
    p_cos4PHI_vs_QT_beamA_qcd->SetMarkerStyle(kDiamond);

    p_cos4PHI_vs_QT_data->Draw();
    p_cos4PHI_vs_QT_beamA_diffraction->Draw("same");
    p_cos4PHI_vs_QT_beamA_diffractionSide2->Draw("same");
    p_cos4PHI_vs_QT_beamA_qcd->Draw("same");
    p_cos4PHI_vs_QT_data->Draw("same");
    legend_PHI->Draw();

    c_observables->Print("plots/dijet_kinematics/data_vs_MC_dijet_observables"+suffix+".pdf");

}