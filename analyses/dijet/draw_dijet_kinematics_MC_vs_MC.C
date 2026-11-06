#include "../../cms_palette.h"

void draw_dijet_kinematics_MC_vs_MC()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);

    TString suffix_mc = "_oppHF";
    
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

    TFile *f_beamA_diffraction = new TFile("histos/beamA_diffraction_pthat10_dijet_kinematics"+suffix_mc+".root");
    std::cout << "BEAM A DIFF1: Loaded " << f_beamA_diffraction->GetName() << std::endl;
    TH1F *h_QT_beamA_diffraction = (TH1F*)f_beamA_diffraction->Get("h_QT")->Clone("h_QT_beamA_diffraction");
    TH1F *h_PT_beamA_diffraction = (TH1F*)f_beamA_diffraction->Get("h_PT")->Clone("h_PT_beamA_diffraction");
    TH1F *h_Minv_beamA_diffraction = (TH1F*)f_beamA_diffraction->Get("h_Minv")->Clone("h_Minv_beamA_diffraction");
    TH1F *h_y_beamA_diffraction = (TH1F*)f_beamA_diffraction->Get("h_y")->Clone("h_y_beamA_diffraction");
    TH1F *h_PHI_beamA_diffraction = (TH1F*)f_beamA_diffraction->Get("h_PHI")->Clone("h_PHI_beamA_diffraction");
    TH1F *h_PHI_signed_beamA_diffraction = (TH1F*)f_beamA_diffraction->Get("h_PHI_signed")->Clone("h_PHI_signed_beamA_diffraction");
    TH2F *h_cos2PHI_vs_QT_beamA_diffraction = (TH2F*)f_beamA_diffraction->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_beamA_diffraction");
    TH2F *h_cos4PHI_vs_QT_beamA_diffraction = (TH2F*)f_beamA_diffraction->Get("h_cos4PHI_vs_QT")->Clone("h_cos4PHI_vs_QT_beamA_diffraction");

    TFile *f_beamA_diffractionSide2 = new TFile("histos/beamA_diffractionSide2_pthat10_dijet_kinematics"+suffix_mc+".root");
    std::cout << "BEAM A DIFF2: Loaded " << f_beamA_diffractionSide2->GetName() << std::endl;
    TH1F *h_QT_beamA_diffractionSide2 = (TH1F*)f_beamA_diffractionSide2->Get("h_QT")->Clone("h_QT_beamA_diffractionSide2");
    TH1F *h_PT_beamA_diffractionSide2 = (TH1F*)f_beamA_diffractionSide2->Get("h_PT")->Clone("h_PT_beamA_diffractionSide2");
    TH1F *h_Minv_beamA_diffractionSide2 = (TH1F*)f_beamA_diffractionSide2->Get("h_Minv")->Clone("h_Minv_beamA_diffractionSide2");
    TH1F *h_y_beamA_diffractionSide2 = (TH1F*)f_beamA_diffractionSide2->Get("h_y")->Clone("h_y_beamA_diffractionSide2");
    TH1F *h_PHI_beamA_diffractionSide2 = (TH1F*)f_beamA_diffractionSide2->Get("h_PHI")->Clone("h_PHI_beamA_diffractionSide2");
    TH1F *h_PHI_signed_beamA_diffractionSide2 = (TH1F*)f_beamA_diffractionSide2->Get("h_PHI_signed")->Clone("h_PHI_signed_beamA_diffractionSide2");
    TH2F *h_cos2PHI_vs_QT_beamA_diffractionSide2 = (TH2F*)f_beamA_diffractionSide2->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_beamA_diffractionSide2");
    TH2F *h_cos4PHI_vs_QT_beamA_diffractionSide2 = (TH2F*)f_beamA_diffractionSide2->Get("h_cos4PHI_vs_QT")->Clone("h_cos4PHI_vs_QT_beamA_diffractionSide2");

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

    // QT, PT -> normalize
    for (auto h : { 
        h_QT_beamA_qcd, h_QT_beamA_diffraction, h_QT_beamA_diffractionSide2, h_QT_beamB_diffraction,
        h_PT_beamA_qcd, h_PT_beamA_diffraction, h_PT_beamA_diffractionSide2, h_PT_beamB_diffraction,
        h_Minv_beamA_qcd, h_Minv_beamA_diffraction, h_Minv_beamA_diffractionSide2, h_Minv_beamB_diffraction,
        h_y_beamA_qcd, h_y_beamA_diffraction, h_y_beamA_diffractionSide2, h_y_beamB_diffraction,
    }) {
        h->Rebin(2);
        h->Scale(1.0 / h->Integral(), "width");
    }

    // dN/dPHI -> normalize
    for (auto h : { h_PHI_signed_beamA_qcd, h_PHI_signed_beamA_diffraction, h_PHI_signed_beamA_diffractionSide2, h_PHI_signed_beamB_diffraction }) {
        h->RebinX(5);
        h->Scale(1.0 / h->Integral(), "width");
    }

    // cos2PHI, cos4PHI -> do not normalize, will take profile
    for (auto h : { h_cos2PHI_vs_QT_beamA_qcd, h_cos2PHI_vs_QT_beamA_diffraction, h_cos2PHI_vs_QT_beamA_diffractionSide2, h_cos2PHI_vs_QT_beamB_diffraction,
                    h_cos4PHI_vs_QT_beamA_qcd, h_cos4PHI_vs_QT_beamA_diffraction, h_cos4PHI_vs_QT_beamA_diffractionSide2, h_cos4PHI_vs_QT_beamB_diffraction }) {
        h->RebinX(5);
    }

    // Draw QT + PT, Minv, y
    TCanvas *c_kinematics = new TCanvas("c_kinematics", "c_kinematics", 2400, 800);
    c_kinematics->Divide(3,1);

    c_kinematics->cd(1);

    h_QT_beamA_qcd->SetLineColor(cmsViolet);
    h_QT_beamA_qcd->SetMarkerColor(cmsViolet);
    h_QT_beamA_qcd->SetMarkerStyle(kFullCircle);
    h_PT_beamA_qcd->SetLineColor(cmsViolet);
    h_PT_beamA_qcd->SetMarkerColor(cmsViolet);
    h_PT_beamA_qcd->SetMarkerStyle(kOpenCircle);

    h_QT_beamA_diffraction->SetLineColor(cmsBlue);
    h_QT_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_QT_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);
    h_PT_beamA_diffraction->SetLineColor(cmsBlue);
    h_PT_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_PT_beamA_diffraction->SetMarkerStyle(kOpenTriangleUp);

    h_QT_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_QT_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_QT_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);
    h_PT_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_PT_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_PT_beamB_diffraction->SetMarkerStyle(kOpenTriangleDown);

    h_QT_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_QT_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_QT_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);
    h_PT_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_PT_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_PT_beamA_diffractionSide2->SetMarkerStyle(kOpenSquare);

    h_QT_beamA_qcd->GetXaxis()->SetTitle("QT or PT (GeV)");
    h_QT_beamA_qcd->GetYaxis()->SetTitle("Normalized entries");
    h_QT_beamA_qcd->GetYaxis()->SetRangeUser(0., 0.18);
    h_QT_beamA_qcd->GetXaxis()->SetRangeUser(0., 60.);
    h_QT_beamA_qcd->Draw();
    h_QT_beamA_diffraction->Draw("same");
    // h_QT_beamB_diffraction->Draw("same");
    h_QT_beamA_diffractionSide2->Draw("same");
    h_PT_beamA_qcd->Draw("same");
    h_PT_beamA_diffraction->Draw("same");
    // h_PT_beamB_diffraction->Draw("same");
    h_PT_beamA_diffractionSide2->Draw("same");

    TLegend *legend = new TLegend(0.2, 0.65, 0.8, 0.85);
    legend->SetBorderSize(0);
    legend->SetNColumns(2);
    legend->AddEntry(new TH1F(), "QT", "");
    legend->AddEntry(new TH1F(), "PT", "");
    legend->AddEntry(h_QT_beamA_qcd, "non-diffr.", "pl");
    legend->AddEntry(h_PT_beamA_qcd, "non-diffr.", "pl");
    legend->AddEntry(h_QT_beamA_diffraction, "diffr.", "pl");
    legend->AddEntry(h_PT_beamA_diffraction, "diffr.", "pl");
    // legend->AddEntry(h_QT_beamB_diffraction, "BeamB, diffr.", "pl");
    // legend->AddEntry(h_PT_beamB_diffraction, "BeamB, diffr.", "pl");
    legend->AddEntry(h_QT_beamA_diffractionSide2, "diffr. side 2", "pl");
    legend->AddEntry(h_PT_beamA_diffractionSide2, "diffr. side 2", "pl");
    legend->Draw();

    c_kinematics->cd(2);

    h_Minv_beamA_qcd->SetLineColor(cmsViolet);
    h_Minv_beamA_qcd->SetMarkerColor(cmsViolet);
    h_Minv_beamA_qcd->SetMarkerStyle(kFullCircle);

    h_Minv_beamA_diffraction->SetLineColor(cmsBlue);
    h_Minv_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_Minv_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    h_Minv_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_Minv_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_Minv_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);

    h_Minv_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_Minv_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_Minv_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);


    h_Minv_beamA_qcd->GetXaxis()->SetTitle("Dijet M_{inv} (GeV)");
    h_Minv_beamA_qcd->GetYaxis()->SetTitle("Normalized entries");
    h_Minv_beamA_qcd->GetYaxis()->SetRangeUser(0, 0.06);
    h_Minv_beamA_qcd->GetXaxis()->SetRangeUser(40., 140.);
    h_Minv_beamA_qcd->Draw();
    h_Minv_beamA_diffraction->Draw("same");
    // h_Minv_beamB_diffraction->Draw("same");
    h_Minv_beamA_diffractionSide2->Draw("same");

    TLegend *legend_m = new TLegend(0.2, 0.7, 0.8, 0.85);
    legend_m->SetBorderSize(0);
    legend_m->SetFillStyle(0);
    legend_m->AddEntry(h_Minv_beamA_qcd, "non-diffr.", "pl");
    legend_m->AddEntry(h_Minv_beamA_diffraction, "diffr.", "pl");
    // legend_m->AddEntry(h_Minv_beamB_diffraction, "diffr.", "pl");
    legend_m->AddEntry(h_Minv_beamA_diffractionSide2, "diffr. side 2", "pl");
    legend_m->Draw();

    c_kinematics->cd(3);

    h_y_beamA_qcd->SetLineColor(cmsViolet);
    h_y_beamA_qcd->SetMarkerColor(cmsViolet);
    h_y_beamA_qcd->SetMarkerStyle(kFullCircle);

    h_y_beamA_diffraction->SetLineColor(cmsBlue);
    h_y_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_y_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    h_y_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_y_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_y_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);

    h_y_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_y_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_y_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    h_y_beamA_qcd->GetXaxis()->SetTitle("Dijet rapidity");
    h_y_beamA_qcd->GetYaxis()->SetTitle("Normalized entries");
    h_y_beamA_qcd->GetXaxis()->SetRangeUser(-3., 3.);
    h_y_beamA_qcd->GetYaxis()->SetRangeUser(0., 1.);
    h_y_beamA_qcd->Draw();
    h_y_beamA_diffraction->Draw("same");
    // h_y_beamB_diffraction->Draw("same");
    h_y_beamA_diffractionSide2->Draw("same");

    TLegend *legend_y = (TLegend *) legend_m->Clone("legend_y");
    legend_y->Draw();


    c_kinematics->Print("plots/dijet_kinematics/MC_vs_MC_dijet_kinematics.pdf");
    // c_kinematics->Print("plots/dijet_kinematics/beamA_qcd_vs_MC_dijet_kinematics.png");

    // dN/dPHI vs PHI, <cos(2PHI)> vs QT, <cos(4PHI)> vs QT
    TCanvas *c_observables = new TCanvas("c_observables", "c_observables", 2400, 800);
    c_observables->Divide(3,1);

    c_observables->cd(1);

    h_PHI_signed_beamA_qcd->SetLineColor(cmsViolet);
    h_PHI_signed_beamA_qcd->SetMarkerColor(cmsViolet);
    h_PHI_signed_beamA_qcd->SetMarkerStyle(kFullCircle);

    h_PHI_signed_beamA_diffraction->SetLineColor(cmsBlue);
    h_PHI_signed_beamA_diffraction->SetMarkerColor(cmsBlue);
    h_PHI_signed_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    h_PHI_signed_beamB_diffraction->SetLineColor(cmsLightBlue);
    h_PHI_signed_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    h_PHI_signed_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);

    h_PHI_signed_beamA_diffractionSide2->SetLineColor(cmsRed);
    h_PHI_signed_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    h_PHI_signed_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    h_PHI_signed_beamA_qcd->GetXaxis()->SetTitle("#Phi (radians)");
    h_PHI_signed_beamA_qcd->GetYaxis()->SetTitle("1/N_{events}dN/d#Phi");
    h_PHI_signed_beamA_qcd->GetYaxis()->SetRangeUser(0., 0.5);
    h_PHI_signed_beamA_qcd->Draw();
    h_PHI_signed_beamA_diffraction->Draw("same");
    // h_PHI_signed_beamB_diffraction->Draw("same");
    h_PHI_signed_beamA_diffractionSide2->Draw("same");
    legend_m->Draw();

    c_observables->cd(2);

    TProfile *p_cos2PHI_vs_QT_beamA_qcd = h_cos2PHI_vs_QT_beamA_qcd->ProfileX();
    p_cos2PHI_vs_QT_beamA_qcd->SetLineColor(cmsViolet);
    p_cos2PHI_vs_QT_beamA_qcd->SetMarkerColor(cmsViolet);
    p_cos2PHI_vs_QT_beamA_qcd->SetMarkerStyle(kFullCircle);

    TProfile *p_cos2PHI_vs_QT_beamA_diffraction = h_cos2PHI_vs_QT_beamA_diffraction->ProfileX();
    p_cos2PHI_vs_QT_beamA_diffraction->SetLineColor(cmsBlue);
    p_cos2PHI_vs_QT_beamA_diffraction->SetMarkerColor(cmsBlue);
    p_cos2PHI_vs_QT_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    TProfile *p_cos2PHI_vs_QT_beamB_diffraction = h_cos2PHI_vs_QT_beamB_diffraction->ProfileX();
    p_cos2PHI_vs_QT_beamB_diffraction->SetLineColor(cmsLightBlue);
    p_cos2PHI_vs_QT_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    p_cos2PHI_vs_QT_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);

    TProfile *p_cos2PHI_vs_QT_beamA_diffractionSide2 = h_cos2PHI_vs_QT_beamA_diffractionSide2->ProfileX();
    p_cos2PHI_vs_QT_beamA_diffractionSide2->SetLineColor(cmsRed);
    p_cos2PHI_vs_QT_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    p_cos2PHI_vs_QT_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    p_cos2PHI_vs_QT_beamA_qcd->GetXaxis()->SetTitle("QT (GeV)");
    p_cos2PHI_vs_QT_beamA_qcd->GetYaxis()->SetTitle("<cos(2#Phi)>");    
    p_cos2PHI_vs_QT_beamA_qcd->GetXaxis()->SetRangeUser(0., 40.);
    p_cos2PHI_vs_QT_beamA_qcd->GetYaxis()->SetRangeUser(-0.5, 1.5);
    p_cos2PHI_vs_QT_beamA_qcd->Draw();
    p_cos2PHI_vs_QT_beamA_diffraction->Draw("same");
    // p_cos2PHI_vs_QT_beamB_diffraction->Draw("same");
    p_cos2PHI_vs_QT_beamA_diffractionSide2->Draw("same");
    legend_m->Draw();

    c_observables->cd(3);

    TProfile *p_cos4PHI_vs_QT_beamA_qcd = h_cos4PHI_vs_QT_beamA_qcd->ProfileX();
    p_cos4PHI_vs_QT_beamA_qcd->SetLineColor(cmsViolet);
    p_cos4PHI_vs_QT_beamA_qcd->SetMarkerColor(cmsViolet);
    p_cos4PHI_vs_QT_beamA_qcd->SetMarkerStyle(kFullCircle);

    TProfile *p_cos4PHI_vs_QT_beamA_diffraction = h_cos4PHI_vs_QT_beamA_diffraction->ProfileX();
    p_cos4PHI_vs_QT_beamA_diffraction->SetLineColor(cmsBlue);
    p_cos4PHI_vs_QT_beamA_diffraction->SetMarkerColor(cmsBlue);
    p_cos4PHI_vs_QT_beamA_diffraction->SetMarkerStyle(kFullTriangleUp);

    TProfile *p_cos4PHI_vs_QT_beamB_diffraction = h_cos4PHI_vs_QT_beamB_diffraction->ProfileX();
    p_cos4PHI_vs_QT_beamB_diffraction->SetLineColor(cmsLightBlue);
    p_cos4PHI_vs_QT_beamB_diffraction->SetMarkerColor(cmsLightBlue);
    p_cos4PHI_vs_QT_beamB_diffraction->SetMarkerStyle(kFullTriangleDown);

    TProfile *p_cos4PHI_vs_QT_beamA_diffractionSide2 = h_cos4PHI_vs_QT_beamA_diffractionSide2->ProfileX();
    p_cos4PHI_vs_QT_beamA_diffractionSide2->SetLineColor(cmsRed);
    p_cos4PHI_vs_QT_beamA_diffractionSide2->SetMarkerColor(cmsRed);
    p_cos4PHI_vs_QT_beamA_diffractionSide2->SetMarkerStyle(kFullSquare);

    p_cos4PHI_vs_QT_beamA_qcd->GetXaxis()->SetTitle("QT (GeV)");
    p_cos4PHI_vs_QT_beamA_qcd->GetYaxis()->SetTitle("<cos(4#Phi)>");    
    p_cos4PHI_vs_QT_beamA_qcd->GetXaxis()->SetRangeUser(0., 40.);
    p_cos4PHI_vs_QT_beamA_qcd->GetYaxis()->SetRangeUser(-0.5, 1.5);
    p_cos4PHI_vs_QT_beamA_qcd->Draw();
    p_cos4PHI_vs_QT_beamA_diffraction->Draw("same");
    // p_cos4PHI_vs_QT_beamB_diffraction->Draw("same");
    p_cos4PHI_vs_QT_beamA_diffractionSide2->Draw("same");
    legend_m->Draw();

    c_observables->Print("plots/dijet_kinematics/MC_vs_MC_dijet_observables.pdf");
    // c_observables->Print("plots/dijet_kinematics/beamA_qcd_vs_MC_dijet_observables.png");

}