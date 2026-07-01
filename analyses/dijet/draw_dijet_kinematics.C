#include "../../cms_palette.h"

void draw_dijet_kinematics()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);

    TString sample = "beamA_diffraction_pthat10";

    TFile *f = new TFile("histos/" + sample + "_dijet_kinematics.root");
    TH1F *h_QT = (TH1F*)f->Get("h_QT");
    TH1F *h_PT = (TH1F*)f->Get("h_PT");
    TH1F *h_Minv = (TH1F*)f->Get("h_Minv");
    TH1F *h_y = (TH1F*)f->Get("h_y");
    TH1F *h_PHI = (TH1F*)f->Get("h_PHI");
    TH1F *h_PHI_signed = (TH1F*)f->Get("h_PHI_signed");
    TH2F *h_cos2PHI_vs_QT = (TH2F*)f->Get("h_cos2PHI_vs_QT");

    // QT + PT, Minv, y
    TCanvas *c_kinematics = new TCanvas("c_kinematics", "c_kinematics", 2400, 800);
    c_kinematics->Divide(3,1);

    c_kinematics->cd(1);
    h_QT->SetLineColor(cmsBlue);
    h_QT->GetXaxis()->SetTitle("QT or PT (GeV)");
    h_QT->GetYaxis()->SetTitle("N_{events}");
    double ymax = std::max(h_QT->GetMaximum(), h_PT->GetMaximum());
    h_QT->SetMaximum(1.2 * ymax);
    h_QT->Draw();
    h_PT->SetLineColor(cmsRed);
    h_PT->Draw("same");
    TLegend *legend = new TLegend(0.6, 0.7, 0.8, 0.8);
    legend->SetBorderSize(0);
    legend->AddEntry(h_QT, "QT", "l");
    legend->AddEntry(h_PT, "PT", "l");
    legend->Draw();

    c_kinematics->cd(2);
    h_Minv->SetLineColor(cmsBlue);
    h_Minv->GetXaxis()->SetTitle("Dijet M_{inv} (GeV)");
    h_Minv->GetYaxis()->SetTitle("N_{events}");
    h_Minv->Draw();

    c_kinematics->cd(3);
    h_y->SetLineColor(cmsBlue);
    h_y->GetXaxis()->SetTitle("Dijet rapidity");
    h_y->GetYaxis()->SetTitle("N_{events}");
    h_y->Draw();

    c_kinematics->Print("plots/" + sample + "_dijet_kinematics.pdf");
    c_kinematics->Print("plots/" + sample + "_dijet_kinematics.png");

    // dN/dPHI vs PHI, <cos(2PHI)> vs QT
    TCanvas *c_observables = new TCanvas("c_observables", "c_observables", 2400, 800);
    c_observables->Divide(2,1);

    c_observables->cd(1);
    h_PHI_signed->Scale(1.0 / h_PHI_signed->Integral(), "width"); 
    h_PHI_signed->SetLineColor(cmsBlue);
    h_PHI_signed->SetMarkerColor(cmsBlue);
    h_PHI_signed->GetXaxis()->SetTitle("#Phi (radians)");
    h_PHI_signed->GetYaxis()->SetTitle("1/N_{events}dN/d#Phi");
    h_PHI_signed->Draw();

    c_observables->cd(2);
    h_cos2PHI_vs_QT->GetXaxis()->SetTitle("QT (GeV)");
    h_cos2PHI_vs_QT->GetYaxis()->SetTitle("cos(2#Phi)");
    h_cos2PHI_vs_QT->Draw("COLZ");

    c_observables->cd(3);
    TProfile *p_cos2PHI_vs_QT = h_cos2PHI_vs_QT->ProfileX();
    p_cos2PHI_vs_QT->SetLineColor(cmsBlue);
    p_cos2PHI_vs_QT->SetMarkerColor(cmsBlue);
    p_cos2PHI_vs_QT->GetXaxis()->SetTitle("QT (GeV)");
    p_cos2PHI_vs_QT->GetYaxis()->SetTitle("<cos(2#Phi)>");
    p_cos2PHI_vs_QT->Draw();

    c_observables->Print("plots/" + sample + "_dijet_observables.pdf");
    c_observables->Print("plots/" + sample + "_dijet_observables.png");
}