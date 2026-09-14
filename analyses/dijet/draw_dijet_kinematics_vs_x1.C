#include "../../cms_palette.h"

void draw_dijet_kinematics_vs_x1()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);

    // TString sample = "beamB_diffraction_pthat10";
    TString sample = "hiforwardAll_2024rereco";

    // TString suffix = "";
    TString suffix = "_oppHF_oppEC2_trkLim2p5_ptgr0p2_chOnly_jetID_jetVM";

    TFile *f = new TFile("histos/" + sample + "_dijet_kinematics" + suffix + ".root");
    TH1F *h_QT = (TH1F*)f->Get("h_QT");
    TH1F *h_PT = (TH1F*)f->Get("h_PT");
    TH1F *h_Minv = (TH1F*)f->Get("h_Minv");
    TH1F *h_y = (TH1F*)f->Get("h_y");
    TH1F *h_PHI = (TH1F*)f->Get("h_PHI");
    TH1F *h_PHI_signed = (TH1F*)f->Get("h_PHI_signed");
    TH2F *h_cos2PHI_vs_QT = (TH2F*)f->Get("h_cos2PHI_vs_QT");
    TH3F *h_cos2PHI_vs_QT_vs_x1 = (TH3F*)f->Get("h_cos2PHI_vs_QT_vs_x1");

    // Preprocess
    for (auto h : { h_QT, h_PT, h_Minv, h_y }) {
        h->Rebin(2);
    }

    for (auto h : { h_PHI, h_PHI_signed }) {
        h->RebinX(5);
    }

    for (auto h : { h_cos2PHI_vs_QT }) {
        h->RebinX(2);
        h->RebinY(2);
    }

    for (auto h : { h_cos2PHI_vs_QT_vs_x1 }) {
        h->RebinX(2); 
        // h->RebinY(5); 
        h->RebinZ(5);
    }

    // QT + PT, Minv, y
    TCanvas *c_kinematics = new TCanvas("c_kinematics", "c_kinematics", 2400, 800);
    c_kinematics->Divide(3,1);

    c_kinematics->cd(1);
    h_QT->SetLineColor(cmsBlue);
    h_QT->SetMarkerColor(cmsBlue);
    h_QT->GetXaxis()->SetTitle("QT or PT (GeV)");
    h_QT->GetYaxis()->SetTitle("N_{events}");
    double ymax = std::max(h_QT->GetMaximum(), h_PT->GetMaximum());
    h_QT->SetMaximum(1.2 * ymax);
    h_QT->Draw();
    h_PT->SetLineColor(cmsRed);
    h_PT->SetMarkerColor(cmsRed);
    h_PT->Draw("same");
    TLegend *leg_kin = new TLegend(0.6, 0.7, 0.8, 0.8);
    leg_kin->SetBorderSize(0);
    leg_kin->AddEntry(h_QT, "QT", "l");
    leg_kin->AddEntry(h_PT, "PT", "l");
    leg_kin->Draw();

    c_kinematics->cd(2);
    h_Minv->SetLineColor(cmsBlue);
    h_Minv->SetMarkerColor(cmsBlue);
    h_Minv->GetXaxis()->SetTitle("Dijet M_{inv} (GeV)");
    h_Minv->GetYaxis()->SetTitle("N_{events}");
    h_Minv->Draw();

    c_kinematics->cd(3);
    h_y->SetLineColor(cmsBlue);
    h_y->SetMarkerColor(cmsBlue);
    h_y->GetXaxis()->SetTitle("Dijet rapidity");
    h_y->GetYaxis()->SetTitle("N_{events}");
    h_y->Draw();

    c_kinematics->Print("plots/" + sample + "_dijet_kinematics.pdf");
    c_kinematics->Print("plots/" + sample + "_dijet_kinematics.png");

    // dN/dPHI vs PHI, <cos(2PHI)> vs QT
    TCanvas *c_observables = new TCanvas("c_observables", "c_observables", 2400, 800);
    c_observables->Divide(3,1);

    c_observables->cd(1);
    h_PHI_signed->Scale(1.0 / h_PHI_signed->Integral(), "width"); 
    h_PHI_signed->SetLineColor(cmsBlue);
    h_PHI_signed->SetMarkerColor(cmsBlue);
    h_PHI_signed->GetXaxis()->SetTitle("#Phi (radians)");
    h_PHI_signed->GetYaxis()->SetTitle("1/N_{events}dN/d#Phi");
    h_PHI_signed->Draw();

    // c_observables->cd(2);
    // h_cos2PHI_vs_QT->GetXaxis()->SetTitle("QT (GeV)");
    // h_cos2PHI_vs_QT->GetYaxis()->SetTitle("cos(2#Phi)");
    // h_cos2PHI_vs_QT->Draw("COLZ");

    c_observables->cd(2);
    TProfile *p_cos2PHI_vs_QT = h_cos2PHI_vs_QT->ProfileX();
    p_cos2PHI_vs_QT->SetLineColor(kBlack);
    p_cos2PHI_vs_QT->SetMarkerColor(kBlack);
    p_cos2PHI_vs_QT->GetXaxis()->SetTitle("QT (GeV)");
    p_cos2PHI_vs_QT->GetYaxis()->SetTitle("<cos(2#Phi)>");
    p_cos2PHI_vs_QT->GetXaxis()->SetRangeUser(0, 30);
    p_cos2PHI_vs_QT->GetYaxis()->SetRangeUser(-1, 2);
    p_cos2PHI_vs_QT->SetLineWidth(2);
    p_cos2PHI_vs_QT->Draw("hist");

    TLegend *leg_observables_x1 = new TLegend(0.2, 0.65, 0.8, 0.85);
    leg_observables_x1->SetBorderSize(0);
    leg_observables_x1->SetNColumns(2);
    std::vector<double> x1_bins = {0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 1.0};
    for (int i = 0; i < x1_bins.size() - 1; ++i) {
        // if (i>0) break;
        Int_t color = cms_palette[i];
        // if (i<2) continue;

        double x1_min = x1_bins[i];
        double x1_max = x1_bins[i + 1];
        h_cos2PHI_vs_QT_vs_x1->GetXaxis()->SetRange(h_cos2PHI_vs_QT_vs_x1->GetXaxis()->FindBin(x1_min), h_cos2PHI_vs_QT_vs_x1->GetXaxis()->FindBin(x1_max)-1);
        TH2D *h_cos2PHI_vs_QT_in_x1_bin = (TH2D*) h_cos2PHI_vs_QT_vs_x1->Project3D(Form("h_cos2PHI_vs_QT_in_x1_bin_%d_zx", i));
        if (h_cos2PHI_vs_QT_in_x1_bin->GetEntries() < 50) continue;
        TProfile *p_cos2PHI_vs_QT_in_x1_bin = h_cos2PHI_vs_QT_in_x1_bin->ProfileX(Form("p_cos2PHI_vs_QT_in_x1_bin_%d", i));
        p_cos2PHI_vs_QT_in_x1_bin->SetLineColor(color);
        p_cos2PHI_vs_QT_in_x1_bin->SetLineWidth(1);
        leg_observables_x1->AddEntry(p_cos2PHI_vs_QT_in_x1_bin, Form("%.2f < x1 < %.2f", x1_min, x1_max), "l");
        p_cos2PHI_vs_QT_in_x1_bin->Draw("hist same");

        h_cos2PHI_vs_QT_vs_x1->GetXaxis()->SetRange(1, h_cos2PHI_vs_QT_vs_x1->GetNbinsX()); // reset
    }

    p_cos2PHI_vs_QT->Draw("hist same");
    leg_observables_x1->AddEntry(p_cos2PHI_vs_QT, "0 < x1 < 1", "l");
    leg_observables_x1->Draw();

    c_observables->cd(3);
    c_observables->cd(3)->SetLogx();
    TH2D *h_cos2PHI_vs_x1 = (TH2D*) h_cos2PHI_vs_QT_vs_x1->Project3D("h_cos2PHI_vs_x1_zy");
    TProfile *p_cos2PHI_vs_x1 = h_cos2PHI_vs_x1->ProfileX("p_cos2PHI_vs_x1");
    p_cos2PHI_vs_x1->SetLineColor(kBlack);
    p_cos2PHI_vs_x1->SetMarkerColor(kBlack);
    p_cos2PHI_vs_x1->GetXaxis()->SetTitle("x_{1}");
    p_cos2PHI_vs_x1->GetYaxis()->SetTitle("<cos(2#Phi)>");
    // p_cos2PHI_vs_x1->GetXaxis()->SetRangeUser(-2.5, 2.5);
    p_cos2PHI_vs_x1->GetYaxis()->SetRangeUser(-1, 2);
    p_cos2PHI_vs_x1->SetLineWidth(2);
    p_cos2PHI_vs_x1->Draw("hist");

    TLegend *leg_observables_qt = new TLegend(0.2, 0.65, 0.8, 0.85);
    leg_observables_qt->SetBorderSize(0);
    leg_observables_qt->SetNColumns(2);
    std::vector<double> qt_bins = {0, 5, 10, 15, 20, 25, 30};
    for (int i = 0; i < qt_bins.size() - 1; ++i) {
        // if (i>0) break;
        Int_t color = cms_palette[i];

        double qt_min = qt_bins[i];
        double qt_max = qt_bins[i + 1];
        h_cos2PHI_vs_QT_vs_x1->GetXaxis()->SetRange(h_cos2PHI_vs_QT_vs_x1->GetXaxis()->FindBin(qt_min), h_cos2PHI_vs_QT_vs_x1->GetXaxis()->FindBin(qt_max)-1);
        TH2D *h_cos2PHI_vs_x1_in_QT_bin = (TH2D*) h_cos2PHI_vs_QT_vs_x1->Project3D(Form("h_cos2PHI_vs_x1_in_QT_bin_%d_zy", i));
        TProfile *p_cos2PHI_vs_x1_in_QT_bin = h_cos2PHI_vs_x1_in_QT_bin->ProfileX(Form("p_cos2PHI_vs_x1_in_QT_bin_%d", i));
        p_cos2PHI_vs_x1_in_QT_bin->SetLineColor(color);
        // p_cos2PHI_vs_x1_in_QT_bin->RebinX(2);
        leg_observables_qt->AddEntry(p_cos2PHI_vs_x1_in_QT_bin, Form("%.0f < QT < %.0f", qt_min, qt_max), "l");

        p_cos2PHI_vs_x1_in_QT_bin->Draw("hist same");

        h_cos2PHI_vs_QT_vs_x1->GetXaxis()->SetRange(1, h_cos2PHI_vs_QT_vs_x1->GetNbinsX()); // reset
    }
    leg_observables_qt->AddEntry(p_cos2PHI_vs_x1, "0 < QT < 30 GeV", "l");
    p_cos2PHI_vs_x1->Draw("hist same");
    leg_observables_qt->Draw();

    c_observables->Print("plots/" + sample + "_dijet_observables_vs_x1.pdf");
    c_observables->Print("plots/" + sample + "_dijet_observables_vs_x1.png");


}