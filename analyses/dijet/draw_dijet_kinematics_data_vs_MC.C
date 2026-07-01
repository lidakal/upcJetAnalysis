#include "../../cms_palette.h"

void draw_dijet_kinematics_data_vs_MC()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);

    TFile *f_data = new TFile("histos/merged_hiforward1to4_dijet_kinematics.root");
    TH1F *h_QT_data = (TH1F*)f_data->Get("h_QT")->Clone("h_QT_data");
    TH1F *h_PT_data = (TH1F*)f_data->Get("h_PT")->Clone("h_PT_data");
    TH1F *h_Minv_data = (TH1F*)f_data->Get("h_Minv")->Clone("h_Minv_data");
    TH1F *h_y_data = (TH1F*)f_data->Get("h_y")->Clone("h_y_data");
    TH1F *h_PHI_data = (TH1F*)f_data->Get("h_PHI")->Clone("h_PHI_data");
    // TH1F *h_PHI_signed_data = (TH1F*)f_data->Get("h_PHI_signed")->Clone("h_PHI_signed_data");
    TH2F *h_cos2PHI_vs_QT_data = (TH2F*)f_data->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_data");

    TFile *f_beamA = new TFile("histos/beamA_diffraction_pthat10_dijet_kinematics.root");
    TH1F *h_QT_beamA = (TH1F*)f_beamA->Get("h_QT")->Clone("h_QT_beamA");
    TH1F *h_PT_beamA = (TH1F*)f_beamA->Get("h_PT")->Clone("h_PT_beamA");
    TH1F *h_Minv_beamA = (TH1F*)f_beamA->Get("h_Minv")->Clone("h_Minv_beamA");
    TH1F *h_y_beamA = (TH1F*)f_beamA->Get("h_y")->Clone("h_y_beamA");
    TH1F *h_PHI_beamA = (TH1F*)f_beamA->Get("h_PHI")->Clone("h_PHI_beamA");
    // TH1F *h_PHI_signed_beamA = (TH1F*)f_beamA->Get("h_PHI_signed")->Clone("h_PHI_signed_beamA");
    TH2F *h_cos2PHI_vs_QT_beamA = (TH2F*)f_beamA->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_beamA");

    TFile *f_beamB = new TFile("histos/beamB_diffraction_pthat10_dijet_kinematics.root");
    TH1F *h_QT_beamB = (TH1F*)f_beamB->Get("h_QT")->Clone("h_QT_beamB");
    TH1F *h_PT_beamB = (TH1F*)f_beamB->Get("h_PT")->Clone("h_PT_beamB");
    TH1F *h_Minv_beamB = (TH1F*)f_beamB->Get("h_Minv")->Clone("h_Minv_beamB");
    TH1F *h_y_beamB = (TH1F*)f_beamB->Get("h_y")->Clone("h_y_beamB");
    TH1F *h_PHI_beamB = (TH1F*)f_beamB->Get("h_PHI")->Clone("h_PHI_beamB");
    // TH1F *h_PHI_signed_beamB = (TH1F*)f_beamB->Get("h_PHI_signed")->Clone("h_PHI_signed_beamB");
    TH2F *h_cos2PHI_vs_QT_beamB = (TH2F*)f_beamB->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_beamB");

    // QT + PT, Minv, y
    TCanvas *c_kinematics = new TCanvas("c_kinematics", "c_kinematics", 2400, 800);
    c_kinematics->Divide(3,1);

    c_kinematics->cd(1);
    h_QT_data->Scale(1.0 / h_QT_data->Integral(), "width");
    h_QT_data->SetLineColor(cmsViolet);
    h_QT_data->SetMarkerColor(cmsViolet);
    h_QT_data->SetMarkerStyle(20);
    h_QT_data->GetXaxis()->SetTitle("QT or PT (GeV)");
    h_QT_data->GetYaxis()->SetTitle("Normalized entries");
    h_QT_beamA->Scale(1.0 / h_QT_beamA->Integral(), "width");
    h_QT_beamA->SetLineColor(cmsBlue);
    h_QT_beamB->Scale(1.0 / h_QT_beamB->Integral(), "width");
    h_QT_beamB->SetLineColor(cmsLightBlue);
    // double ymax = std::max(h_QT_data->GetMaximum(), h_PT_data->GetMaximum());
    // h_QT_data->SetMaximum(1.2 * ymax);
    h_QT_data->SetMaximum(0.16);
    h_QT_data->Draw();
    h_QT_beamA->Draw("same hist");
    h_QT_beamB->Draw("same hist");
    h_PT_data->Scale(1.0 / h_PT_data->Integral(), "width");
    h_PT_data->SetLineColor(cmsRed);
    h_PT_data->SetMarkerColor(cmsRed);
    h_PT_data->SetMarkerStyle(22);
    h_PT_beamA->Scale(1.0 / h_PT_beamA->Integral(), "width");
    h_PT_beamA->SetLineColor(cmsOrange);
    h_PT_beamB->Scale(1.0 / h_PT_beamB->Integral(), "width");
    h_PT_beamB->SetLineColor(cmsYellow);
    h_PT_data->Draw("same");
    h_PT_beamA->Draw("same hist");
    h_PT_beamB->Draw("same hist");
    TLegend *legend = new TLegend(0.2, 0.65, 0.8, 0.85);
    legend->SetBorderSize(0);
    legend->SetNColumns(2);
    legend->AddEntry(new TH1F(), "QT", "");
    legend->AddEntry(new TH1F(), "PT", "");
    legend->AddEntry(h_QT_data, "Data", "pl");
    legend->AddEntry(h_PT_data, "Data", "pl");
    legend->AddEntry(h_QT_beamA, "MC (beamA)", "l");
    legend->AddEntry(h_PT_beamA, "MC (beamA)", "l");
    legend->AddEntry(h_QT_beamB, "MC (beamB)", "l");
    legend->AddEntry(h_PT_beamB, "MC (beamB)", "l");
    // legend->SetTextSize(0.03);
    legend->Draw();

    c_kinematics->cd(2);
    h_Minv_data->Scale(1.0 / h_Minv_data->Integral(), "width");
    h_Minv_data->SetMaximum(0.05);
    h_Minv_data->SetLineColor(cmsViolet);
    h_Minv_data->SetMarkerColor(cmsViolet);
    h_Minv_data->SetMarkerStyle(20);
    h_Minv_beamA->Scale(1.0 / h_Minv_beamA->Integral(), "width");
    h_Minv_beamA->SetLineColor(cmsBlue);
    h_Minv_beamB->Scale(1.0 / h_Minv_beamB->Integral(), "width");
    h_Minv_beamB->SetLineColor(cmsLightBlue);
    h_Minv_data->GetXaxis()->SetTitle("Dijet M_{inv} (GeV)");
    h_Minv_data->GetYaxis()->SetTitle("Normalized entries");
    h_Minv_data->Draw();
    h_Minv_beamA->Draw("same hist");
    h_Minv_beamB->Draw("same hist");
    TLegend *legend_m = new TLegend(0.2, 0.7, 0.8, 0.85);
    legend_m->SetBorderSize(0);
    legend_m->AddEntry(h_Minv_data, "Data", "pl");
    legend_m->AddEntry(h_Minv_beamA, "MC (beamA)", "l");
    legend_m->AddEntry(h_Minv_beamB, "MC (beamB)", "l");
    legend_m->Draw();

    c_kinematics->cd(3);
    h_y_data->Scale(1.0 / h_y_data->Integral(), "width");
    h_y_data->SetMaximum(1.2);
    h_y_data->SetLineColor(cmsViolet);
    h_y_data->SetMarkerColor(cmsViolet);
    h_y_data->SetMarkerStyle(20);
    h_y_beamA->Scale(1.0 / h_y_beamA->Integral(), "width");
    h_y_beamA->SetLineColor(cmsBlue);
    h_y_beamB->Scale(1.0 / h_y_beamB->Integral(), "width");
    h_y_beamB->SetLineColor(cmsLightBlue);
    h_y_data->GetXaxis()->SetTitle("Dijet rapidity");
    h_y_data->GetYaxis()->SetTitle("Normalized entries");
    h_y_data->Draw();
    h_y_beamA->Draw("same hist");
    h_y_beamB->Draw("same hist");
    legend_m->Draw();

    c_kinematics->Print("plots/data_vs_MC_dijet_kinematics.pdf");
    c_kinematics->Print("plots/data_vs_MC_dijet_kinematics.png");

    // dN/dPHI vs PHI, <cos(2PHI)> vs QT
    // TCanvas *c_observables = new TCanvas("c_observables", "c_observables", 2400, 800);
    // c_observables->Divide(2,1);

    // c_observables->cd(1);
    // h_PHI_signed_data->Scale(1.0 / h_PHI_signed_data->Integral(), "width"); 
    // h_PHI_signed_data->SetLineColor(cmsBlue);
    // h_PHI_signed_data->SetMarkerColor(cmsBlue);
    // h_PHI_signed_data->GetXaxis()->SetTitle("#Phi (radians)");
    // h_PHI_signed_data->GetYaxis()->SetTitle("1/N_{events}dN/d#Phi");
    // h_PHI_signed_data->Draw();

    // c_observables->cd(2);
    // h_cos2PHI_vs_QT_data->GetXaxis()->SetTitle("QT (GeV)");
    // h_cos2PHI_vs_QT_data->GetYaxis()->SetTitle("cos(2#Phi)");
    // h_cos2PHI_vs_QT_data->Draw("COLZ");

    // c_observables->cd(3);
    // TProfile *p_cos2PHI_vs_QT_data = h_cos2PHI_vs_QT_data->ProfileX();
    // p_cos2PHI_vs_QT_data->SetLineColor(cmsBlue);
    // p_cos2PHI_vs_QT_data->SetMarkerColor(cmsBlue);
    // p_cos2PHI_vs_QT_data->GetXaxis()->SetTitle("QT (GeV)");
    // p_cos2PHI_vs_QT_data->GetYaxis()->SetTitle("<cos(2#Phi)>");
    // p_cos2PHI_vs_QT_data->Draw();

    // c_observables->Print("plots/" + sample + "_dijet_observables.pdf");
    // c_observables->Print("plots/" + sample + "_dijet_observables.png");
}