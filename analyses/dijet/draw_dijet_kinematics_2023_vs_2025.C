#include "../../cms_palette.h"

void draw_dijet_kinematics_2023_vs_2025()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);

    TString suffix = "_0n0n_oppHF";
    
    TFile *f_2023 = new TFile("histos/hiforwardAll_2024rereco_dijet_kinematics"+suffix+".root");
    std::cout << "2023: Loaded " << f_2023->GetName() << std::endl;
    TH1F *h_QT_2023 = (TH1F*)f_2023->Get("h_QT")->Clone("h_QT_2023");
    TH1F *h_PT_2023 = (TH1F*)f_2023->Get("h_PT")->Clone("h_PT_2023");
    TH1F *h_Minv_2023 = (TH1F*)f_2023->Get("h_Minv")->Clone("h_Minv_2023");
    TH1F *h_y_2023 = (TH1F*)f_2023->Get("h_y")->Clone("h_y_2023");
    TH1F *h_deta_2023 = (TH1F*)f_2023->Get("h_deta")->Clone("h_deta_2023");
    TH1F *h_dphi_2023 = (TH1F*)f_2023->Get("h_dphi")->Clone("h_dphi_2023");
    TH1F *h_PHI_2023 = (TH1F*)f_2023->Get("h_PHI")->Clone("h_PHI_2023");
    TH1F *h_PHI_signed_2023 = (TH1F*)f_2023->Get("h_PHI_signed")->Clone("h_PHI_signed_2023");
    TH2F *h_cos2PHI_vs_QT_2023 = (TH2F*)f_2023->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_2023");
    TH2F *h_cos4PHI_vs_QT_2023 = (TH2F*)f_2023->Get("h_cos4PHI_vs_QT")->Clone("h_cos4PHI_vs_QT_2023");

    TFile *f_2025 = new TFile("histos/hiforward0to4_2025_dijet_kinematics"+suffix+".root");
    std::cout << "2025: Loaded " << f_2025->GetName() << std::endl;
    TH1F *h_QT_2025 = (TH1F*)f_2025->Get("h_QT")->Clone("h_QT_2025");
    TH1F *h_PT_2025 = (TH1F*)f_2025->Get("h_PT")->Clone("h_PT_2025");
    TH1F *h_Minv_2025 = (TH1F*)f_2025->Get("h_Minv")->Clone("h_Minv_2025");
    TH1F *h_y_2025 = (TH1F*)f_2025->Get("h_y")->Clone("h_y_2025");
    TH1F *h_deta_2025 = (TH1F*)f_2025->Get("h_deta")->Clone("h_deta_2025");
    TH1F *h_dphi_2025 = (TH1F*)f_2025->Get("h_dphi")->Clone("h_dphi_2025");
    TH1F *h_PHI_2025 = (TH1F*)f_2025->Get("h_PHI")->Clone("h_PHI_2025");
    TH1F *h_PHI_signed_2025 = (TH1F*)f_2025->Get("h_PHI_signed")->Clone("h_PHI_signed_2025");
    TH2F *h_cos2PHI_vs_QT_2025 = (TH2F*)f_2025->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_2025");
    TH2F *h_cos4PHI_vs_QT_2025 = (TH2F*)f_2025->Get("h_cos4PHI_vs_QT")->Clone("h_cos4PHI_vs_QT_2025");

    // Preprocess
    for (auto h : { 
        h_QT_2023, h_QT_2025,
        h_PT_2023, h_PT_2025,
        h_Minv_2023, h_Minv_2025,
        h_y_2023, h_y_2025,
        h_deta_2023, h_deta_2025,
        h_dphi_2023, h_dphi_2025,
    }) {
        h->Rebin(2);
    }

    for (auto h : { h_PHI_signed_2023, h_PHI_signed_2025 }) {
        h->RebinX(5);
    }

    for (auto h : { h_cos2PHI_vs_QT_2023, h_cos2PHI_vs_QT_2025,
                    h_cos4PHI_vs_QT_2023, h_cos4PHI_vs_QT_2025 }) {
        h->RebinX(5);
    }

    // Dijet DeltaEta, DeltaPhi
    TCanvas *c_control = new TCanvas("c_control", "c_control", 1600, 800);
    c_control->Divide(2,1);

    c_control->cd(1);
    h_deta_2023->Scale(1.0 / h_deta_2023->Integral(), "width");
    h_deta_2023->SetLineColor(cmsViolet);
    h_deta_2023->SetMarkerColor(cmsViolet);
    h_deta_2023->SetMarkerStyle(kFullCircle);
    h_deta_2025->Scale(1.0 / h_deta_2025->Integral(), "width");
    h_deta_2025->SetLineColor(cmsBlue);
    h_deta_2025->SetMarkerColor(cmsBlue);
    h_deta_2025->SetMarkerStyle(kFullTriangleUp);

    h_deta_2023->GetXaxis()->SetTitle("Dijet #Delta#eta");
    h_deta_2023->GetYaxis()->SetTitle("Normalized entries");
    h_deta_2023->Draw();
    h_deta_2025->Draw("same");

    TLegend *legend_control = new TLegend(0.2, 0.7, 0.8, 0.85);
    legend_control->SetBorderSize(0);
    legend_control->AddEntry(h_deta_2023, "2023", "pl");
    legend_control->AddEntry(h_deta_2025, "2025", "pl");
    legend_control->Draw();

    c_control->cd(2);
    h_dphi_2023->Scale(1.0 / h_dphi_2023->Integral(), "width");
    h_dphi_2023->SetLineColor(cmsViolet);
    h_dphi_2023->SetMarkerColor(cmsViolet);
    h_dphi_2023->SetMarkerStyle(kFullCircle);
    h_dphi_2025->Scale(1.0 / h_dphi_2025->Integral(), "width");
    h_dphi_2025->SetLineColor(cmsBlue);
    h_dphi_2025->SetMarkerColor(cmsBlue);
    h_dphi_2025->SetMarkerStyle(kFullTriangleUp);

    h_dphi_2023->GetXaxis()->SetTitle("Dijet #Delta#phi");
    h_dphi_2023->GetYaxis()->SetTitle("Normalized entries");
    h_dphi_2023->Draw();
    h_dphi_2025->Draw("same");

    legend_control->Draw();

    // QT + PT, Minv, y
    TCanvas *c_kinematics = new TCanvas("c_kinematics", "c_kinematics", 2400, 800);
    c_kinematics->Divide(3,1);

    c_kinematics->cd(1);
    h_QT_2023->Scale(1.0 / h_QT_2023->Integral(), "width");
    h_QT_2023->SetLineColor(cmsViolet);
    h_QT_2023->SetMarkerColor(cmsViolet);
    h_QT_2023->SetMarkerStyle(kFullCircle);
    h_QT_2023->GetXaxis()->SetTitle("QT or PT (GeV)");
    h_QT_2023->GetYaxis()->SetTitle("Normalized entries");
    h_QT_2025->Scale(1.0 / h_QT_2025->Integral(), "width");
    h_QT_2025->SetLineColor(cmsBlue);
    h_QT_2025->SetMarkerColor(cmsBlue);
    h_QT_2025->SetMarkerStyle(kFullTriangleUp);
    h_QT_2023->SetMaximum(0.16);
    h_QT_2023->Draw();
    h_QT_2025->Draw("same");
    h_PT_2023->Scale(1.0 / h_PT_2023->Integral(), "width");
    h_PT_2023->SetLineColor(cmsRed);
    h_PT_2023->SetMarkerColor(cmsRed);
    h_PT_2023->SetMarkerStyle(kOpenCircle);
    h_PT_2025->Scale(1.0 / h_PT_2025->Integral(), "width");
    h_PT_2025->SetLineColor(cmsOrange);
    h_PT_2025->SetMarkerColor(cmsOrange);
    h_PT_2025->SetMarkerStyle(kOpenTriangleUp);
    h_PT_2023->Draw("same");
    h_PT_2025->Draw("same");  

    TLegend *legend = new TLegend(0.2, 0.65, 0.8, 0.85);
    legend->SetBorderSize(0);
    legend->SetNColumns(2);
    legend->AddEntry(new TH1F(), "QT", "");
    legend->AddEntry(new TH1F(), "PT", "");
    legend->AddEntry(h_QT_2023, "2023", "pl");
    legend->AddEntry(h_PT_2023, "2023", "pl");
    legend->AddEntry(h_QT_2025, "2025", "pl");
    legend->AddEntry(h_PT_2025, "2025", "pl");
    legend->Draw();

    c_kinematics->cd(2);
    h_Minv_2023->Scale(1.0 / h_Minv_2023->Integral(), "width");
    h_Minv_2023->SetMaximum(0.05);
    h_Minv_2023->SetMinimum(0.);
    h_Minv_2023->SetLineColor(cmsViolet);
    h_Minv_2023->SetMarkerColor(cmsViolet);
    h_Minv_2023->SetMarkerStyle(kFullCircle);
    h_Minv_2025->Scale(1.0 / h_Minv_2025->Integral(), "width");
    h_Minv_2025->SetLineColor(cmsBlue);
    h_Minv_2025->SetMarkerColor(cmsBlue);
    h_Minv_2025->SetMarkerStyle(kFullTriangleUp);
    h_Minv_2023->GetXaxis()->SetTitle("Dijet M_{inv} (GeV)");
    h_Minv_2023->GetYaxis()->SetTitle("Normalized entries");
    h_Minv_2023->Draw();
    h_Minv_2025->Draw("same");
    TLegend *legend_m = new TLegend(0.2, 0.7, 0.8, 0.85);
    legend_m->SetBorderSize(0);
    legend_m->AddEntry(h_Minv_2023, "2023", "pl");
    legend_m->AddEntry(h_Minv_2025, "2025", "pl");
    legend_m->Draw();

    c_kinematics->cd(3);
    h_y_2023->Scale(1.0 / h_y_2023->Integral(), "width");
    h_y_2023->SetMaximum(1.2);
    h_y_2023->SetLineColor(cmsViolet);
    h_y_2023->SetMarkerColor(cmsViolet);
    h_y_2023->SetMarkerStyle(kFullCircle);
    h_y_2025->Scale(1.0 / h_y_2025->Integral(), "width");
    h_y_2025->SetLineColor(cmsBlue);
    h_y_2025->SetMarkerColor(cmsBlue);
    h_y_2025->SetMarkerStyle(kFullTriangleUp);
    h_y_2023->GetXaxis()->SetTitle("Dijet rapidity");
    h_y_2023->GetYaxis()->SetTitle("Normalized entries");
    h_y_2023->Draw();
    h_y_2025->Draw("same");
    TLegend *legend_y = (TLegend *) legend_m->Clone("legend_y");
    legend_y->Draw();

    // c_kinematics->Print("plots/dijet_kinematics/data_2023_vs_2025_dijet_kinematics.pdf");

    // dN/dPHI vs PHI, <cos(2PHI)> vs QT, <cos(4PHI)> vs QT
    TCanvas *c_observables = new TCanvas("c_observables", "c_observables", 2400, 800);
    c_observables->Divide(3,1);

    c_observables->cd(1);
    h_PHI_signed_2023->Scale(1.0 / h_PHI_signed_2023->Integral(), "width"); 
    h_PHI_signed_2023->SetMaximum(0.6);
    h_PHI_signed_2023->SetMinimum(0.);
    h_PHI_signed_2023->SetLineColor(cmsViolet);
    h_PHI_signed_2023->SetMarkerColor(cmsViolet);
    h_PHI_signed_2023->SetMarkerStyle(kFullCircle);
    h_PHI_signed_2023->GetXaxis()->SetTitle("#Phi (radians)");
    h_PHI_signed_2023->GetYaxis()->SetTitle("1/N_{events}dN/d#Phi");
    h_PHI_signed_2025->Scale(1.0 / h_PHI_signed_2025->Integral(), "width");
    h_PHI_signed_2025->SetLineColor(cmsBlue);
    h_PHI_signed_2025->SetMarkerColor(cmsBlue);
    h_PHI_signed_2025->SetMarkerStyle(kFullTriangleUp);
    h_PHI_signed_2023->Draw();
    h_PHI_signed_2025->Draw("same");
    legend_m->Draw();

    c_observables->cd(2);
    TProfile *p_cos2PHI_vs_QT_2023 = h_cos2PHI_vs_QT_2023->ProfileX();
    p_cos2PHI_vs_QT_2023->SetMaximum(2.);
    p_cos2PHI_vs_QT_2023->SetMinimum(-1.);
    p_cos2PHI_vs_QT_2023->GetXaxis()->SetRangeUser(0., 40.);
    p_cos2PHI_vs_QT_2023->SetLineColor(cmsViolet);
    p_cos2PHI_vs_QT_2023->SetMarkerColor(cmsViolet);
    p_cos2PHI_vs_QT_2023->SetMarkerStyle(kFullCircle);
    p_cos2PHI_vs_QT_2023->GetXaxis()->SetTitle("QT (GeV)");
    p_cos2PHI_vs_QT_2023->GetYaxis()->SetTitle("<cos(2#Phi)>");
    TProfile *p_cos2PHI_vs_QT_2025 = h_cos2PHI_vs_QT_2025->ProfileX();
    p_cos2PHI_vs_QT_2025->SetLineColor(cmsBlue);
    p_cos2PHI_vs_QT_2025->SetMarkerColor(cmsBlue);
    p_cos2PHI_vs_QT_2025->SetMarkerStyle(kFullTriangleUp);
    p_cos2PHI_vs_QT_2023->Draw();
    p_cos2PHI_vs_QT_2025->Draw("same");
    legend_m->Draw();

    c_observables->cd(3);
    TProfile *p_cos4PHI_vs_QT_2023 = h_cos4PHI_vs_QT_2023->ProfileX();
    p_cos4PHI_vs_QT_2023->SetMaximum(2.);
    p_cos4PHI_vs_QT_2023->SetMinimum(-1.);
    p_cos4PHI_vs_QT_2023->GetXaxis()->SetRangeUser(0., 40.);
    p_cos4PHI_vs_QT_2023->SetLineColor(cmsViolet);
    p_cos4PHI_vs_QT_2023->SetMarkerColor(cmsViolet);
    p_cos4PHI_vs_QT_2023->SetMarkerStyle(kFullCircle);
    p_cos4PHI_vs_QT_2023->GetXaxis()->SetTitle("QT (GeV)");
    p_cos4PHI_vs_QT_2023->GetYaxis()->SetTitle("<cos(4#Phi)>");
    TProfile *p_cos4PHI_vs_QT_2025 = h_cos4PHI_vs_QT_2025->ProfileX();
    p_cos4PHI_vs_QT_2025->SetLineColor(cmsBlue);
    p_cos4PHI_vs_QT_2025->SetMarkerColor(cmsBlue);
    p_cos4PHI_vs_QT_2025->SetMarkerStyle(kFullTriangleUp);
    p_cos4PHI_vs_QT_2023->Draw();
    p_cos4PHI_vs_QT_2025->Draw("same");
    legend_m->Draw();

    // c_observables->Print("plots/dijet_kinematics/data_2023_vs_2025_dijet_observables.pdf");

}