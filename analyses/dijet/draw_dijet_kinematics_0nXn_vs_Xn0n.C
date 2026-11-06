#include "../../cms_palette.h"

void draw_dijet_kinematics_0nXn_vs_Xn0n()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);
    
    TFile *f_data_0nXn = new TFile("histos/hiforwardAll_2024rereco_dijet_kinematics_0nXnOneSided_HFm.root");
    std::cout << "0nXn: Loaded " << f_data_0nXn->GetName() << std::endl;
    TH1F *h_QT_data_0nXn = (TH1F*)f_data_0nXn->Get("h_QT")->Clone("h_QT_data_0nXn");
    TH1F *h_PT_data_0nXn = (TH1F*)f_data_0nXn->Get("h_PT")->Clone("h_PT_data_0nXn");
    TH1F *h_Minv_data_0nXn = (TH1F*)f_data_0nXn->Get("h_Minv")->Clone("h_Minv_data_0nXn");
    TH1F *h_y_data_0nXn = (TH1F*)f_data_0nXn->Get("h_y")->Clone("h_y_data_0nXn");
    TH1F *h_PHI_data_0nXn = (TH1F*)f_data_0nXn->Get("h_PHI")->Clone("h_PHI_data_0nXn");
    TH1F *h_PHI_signed_data_0nXn = (TH1F*)f_data_0nXn->Get("h_PHI_signed")->Clone("h_PHI_signed_data_0nXn");
    TH2F *h_cos2PHI_vs_QT_data_0nXn = (TH2F*)f_data_0nXn->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_data_0nXn");
    TH2F *h_cos4PHI_vs_QT_data_0nXn = (TH2F*)f_data_0nXn->Get("h_cos4PHI_vs_QT")->Clone("h_cos4PHI_vs_QT_data_0nXn");

    TFile *f_data_Xn0n = new TFile("histos/hiforwardAll_2024rereco_dijet_kinematics_Xn0nOneSided_HFp.root");
    std::cout << "Xn0n: Loaded " << f_data_Xn0n->GetName() << std::endl;
    TH1F *h_QT_data_Xn0n = (TH1F*)f_data_Xn0n->Get("h_QT")->Clone("h_QT_data_Xn0n");
    TH1F *h_PT_data_Xn0n = (TH1F*)f_data_Xn0n->Get("h_PT")->Clone("h_PT_data_Xn0n");
    TH1F *h_Minv_data_Xn0n = (TH1F*)f_data_Xn0n->Get("h_Minv")->Clone("h_Minv_data_Xn0n");
    TH1F *h_y_data_Xn0n = (TH1F*)f_data_Xn0n->Get("h_y")->Clone("h_y_data_Xn0n");
    TH1F *h_PHI_data_Xn0n = (TH1F*)f_data_Xn0n->Get("h_PHI")->Clone("h_PHI_data_Xn0n");
    TH1F *h_PHI_signed_data_Xn0n = (TH1F*)f_data_Xn0n->Get("h_PHI_signed")->Clone("h_PHI_signed_data_Xn0n");
    TH2F *h_cos2PHI_vs_QT_data_Xn0n = (TH2F*)f_data_Xn0n->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_data_Xn0n");
    TH2F *h_cos4PHI_vs_QT_data_Xn0n = (TH2F*)f_data_Xn0n->Get("h_cos4PHI_vs_QT")->Clone("h_cos4PHI_vs_QT_data_Xn0n");

    // Preprocess

    // QT, PT -> normalize
    for (auto h : { 
        h_QT_data_Xn0n, h_QT_data_0nXn, 
        h_PT_data_Xn0n, h_PT_data_0nXn,
        h_Minv_data_Xn0n, h_Minv_data_0nXn, 
        h_y_data_Xn0n, h_y_data_0nXn,
    }) {
        h->Rebin(2);
        h->Scale(1.0 / h->Integral(), "width");
    }

    // dN/dPHI -> normalize
    for (auto h : { h_PHI_signed_data_Xn0n, h_PHI_signed_data_0nXn, }) {
        h->RebinX(5);
        h->Scale(1.0 / h->Integral(), "width");
    }

    // cos2PHI, cos4PHI -> do not normalize, will take profile
    for (auto h : { h_cos2PHI_vs_QT_data_Xn0n, h_cos2PHI_vs_QT_data_0nXn, 
                    h_cos4PHI_vs_QT_data_Xn0n, h_cos4PHI_vs_QT_data_0nXn, }) {
        h->RebinX(5);
    }

    // Draw QT + PT, Minv, y
    TCanvas *c_kinematics = new TCanvas("c_kinematics", "c_kinematics", 2400, 800);
    c_kinematics->Divide(3,1);

    c_kinematics->cd(1);

    h_QT_data_0nXn->SetLineColor(cmsRed);
    h_QT_data_0nXn->SetMarkerColor(cmsRed);
    h_QT_data_0nXn->SetMarkerStyle(kFullTriangleUp);
    h_PT_data_0nXn->SetLineColor(cmsRed);
    h_PT_data_0nXn->SetMarkerColor(cmsRed);
    h_PT_data_0nXn->SetMarkerStyle(kOpenTriangleUp);

    h_QT_data_Xn0n->SetLineColor(cmsBlue);
    h_QT_data_Xn0n->SetMarkerColor(cmsBlue);
    h_QT_data_Xn0n->SetMarkerStyle(kFullTriangleDown);
    h_PT_data_Xn0n->SetLineColor(cmsBlue);
    h_PT_data_Xn0n->SetMarkerColor(cmsBlue);
    h_PT_data_Xn0n->SetMarkerStyle(kOpenTriangleDown);


    h_QT_data_0nXn->GetXaxis()->SetTitle("QT or PT (GeV)");
    h_QT_data_0nXn->GetYaxis()->SetTitle("Normalized entries");
    h_QT_data_0nXn->GetYaxis()->SetRangeUser(0., 0.18);
    h_QT_data_0nXn->GetXaxis()->SetRangeUser(0., 60.);
    h_QT_data_0nXn->Draw();
    h_QT_data_Xn0n->Draw("same");
    h_PT_data_Xn0n->Draw("same");
    h_PT_data_0nXn->Draw("same");

    TLegend *legend = new TLegend(0.2, 0.65, 0.8, 0.85);
    legend->SetBorderSize(0);
    legend->SetNColumns(2);
    legend->AddEntry(new TH1F(), "QT", "");
    legend->AddEntry(new TH1F(), "PT", "");
    legend->AddEntry(h_QT_data_0nXn, "0nXn", "pl");
    legend->AddEntry(h_PT_data_0nXn, "0nXn", "pl");
    legend->AddEntry(h_QT_data_Xn0n, "Xn0n", "pl");
    legend->AddEntry(h_PT_data_Xn0n, "Xn0n", "pl");
    legend->Draw();

    c_kinematics->cd(2);

    h_Minv_data_0nXn->SetLineColor(cmsRed);
    h_Minv_data_0nXn->SetMarkerColor(cmsRed);
    h_Minv_data_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_Minv_data_Xn0n->SetLineColor(cmsBlue);
    h_Minv_data_Xn0n->SetMarkerColor(cmsBlue);
    h_Minv_data_Xn0n->SetMarkerStyle(kFullTriangleDown);

    h_Minv_data_0nXn->GetXaxis()->SetTitle("Dijet M_{inv} (GeV)");
    h_Minv_data_0nXn->GetYaxis()->SetTitle("Normalized entries");
    h_Minv_data_0nXn->GetYaxis()->SetRangeUser(0, 0.06);
    h_Minv_data_0nXn->GetXaxis()->SetRangeUser(40., 140.);
    h_Minv_data_0nXn->Draw();
    h_Minv_data_Xn0n->Draw("same");

    TLegend *legend_m = new TLegend(0.2, 0.7, 0.8, 0.85);
    legend_m->SetBorderSize(0);
    legend_m->SetFillStyle(0);
    legend_m->AddEntry(h_Minv_data_0nXn, "0nXn", "pl");
    legend_m->AddEntry(h_Minv_data_Xn0n, "Xn0n", "pl");
    legend_m->Draw();

    c_kinematics->cd(3);

    h_y_data_0nXn->SetLineColor(cmsRed);
    h_y_data_0nXn->SetMarkerColor(cmsRed);
    h_y_data_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_y_data_Xn0n->SetLineColor(cmsBlue);
    h_y_data_Xn0n->SetMarkerColor(cmsBlue);
    h_y_data_Xn0n->SetMarkerStyle(kFullTriangleDown);

    h_y_data_0nXn->GetXaxis()->SetTitle("Dijet rapidity");
    h_y_data_0nXn->GetYaxis()->SetTitle("Normalized entries");
    h_y_data_0nXn->GetXaxis()->SetRangeUser(-3., 3.);
    h_y_data_0nXn->GetYaxis()->SetRangeUser(0., 1.);
    h_y_data_0nXn->Draw();
    h_y_data_Xn0n->Draw("same");

    TLegend *legend_y = (TLegend *) legend_m->Clone("legend_y");
    legend_y->Draw();

    c_kinematics->Print("plots/dijet_kinematics/0nXn_vs_Xn0n_dijet_kinematics.pdf");

    // dN/dPHI vs PHI, <cos(2PHI)> vs QT, <cos(4PHI)> vs QT
    TCanvas *c_observables = new TCanvas("c_observables", "c_observables", 2400, 800);
    c_observables->Divide(3,1);

    c_observables->cd(1);

    h_PHI_signed_data_0nXn->SetLineColor(cmsRed);
    h_PHI_signed_data_0nXn->SetMarkerColor(cmsRed);
    h_PHI_signed_data_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_PHI_signed_data_Xn0n->SetLineColor(cmsBlue);
    h_PHI_signed_data_Xn0n->SetMarkerColor(cmsBlue);
    h_PHI_signed_data_Xn0n->SetMarkerStyle(kFullTriangleDown);

    h_PHI_signed_data_0nXn->GetXaxis()->SetTitle("#Phi (radians)");
    h_PHI_signed_data_0nXn->GetYaxis()->SetTitle("1/N_{events}dN/d#Phi");
    h_PHI_signed_data_0nXn->GetYaxis()->SetRangeUser(0., 0.5);
    h_PHI_signed_data_0nXn->Draw();
    h_PHI_signed_data_Xn0n->Draw("same");
    legend_m->Draw();

    c_observables->cd(2);

    TProfile *p_cos2PHI_vs_QT_data_0nXn = h_cos2PHI_vs_QT_data_0nXn->ProfileX();
    p_cos2PHI_vs_QT_data_0nXn->SetLineColor(cmsRed);
    p_cos2PHI_vs_QT_data_0nXn->SetMarkerColor(cmsRed);
    p_cos2PHI_vs_QT_data_0nXn->SetMarkerStyle(kFullTriangleUp);

    TProfile *p_cos2PHI_vs_QT_data_Xn0n = h_cos2PHI_vs_QT_data_Xn0n->ProfileX();
    p_cos2PHI_vs_QT_data_Xn0n->SetLineColor(cmsBlue);
    p_cos2PHI_vs_QT_data_Xn0n->SetMarkerColor(cmsBlue);
    p_cos2PHI_vs_QT_data_Xn0n->SetMarkerStyle(kFullTriangleDown);

    p_cos2PHI_vs_QT_data_0nXn->GetXaxis()->SetTitle("QT (GeV)");
    p_cos2PHI_vs_QT_data_0nXn->GetYaxis()->SetTitle("<cos(2#Phi)>");    
    p_cos2PHI_vs_QT_data_0nXn->GetXaxis()->SetRangeUser(0., 40.);
    p_cos2PHI_vs_QT_data_0nXn->GetYaxis()->SetRangeUser(-0.5, 1.5);
    p_cos2PHI_vs_QT_data_0nXn->Draw();
    p_cos2PHI_vs_QT_data_Xn0n->Draw("same");
    legend_m->Draw();

    c_observables->cd(3);

    TProfile *p_cos4PHI_vs_QT_data_0nXn = h_cos4PHI_vs_QT_data_0nXn->ProfileX();
    p_cos4PHI_vs_QT_data_0nXn->SetLineColor(cmsRed);
    p_cos4PHI_vs_QT_data_0nXn->SetMarkerColor(cmsRed);
    p_cos4PHI_vs_QT_data_0nXn->SetMarkerStyle(kFullTriangleUp);

    TProfile *p_cos4PHI_vs_QT_data_Xn0n = h_cos4PHI_vs_QT_data_Xn0n->ProfileX();
    p_cos4PHI_vs_QT_data_Xn0n->SetLineColor(cmsBlue);
    p_cos4PHI_vs_QT_data_Xn0n->SetMarkerColor(cmsBlue);
    p_cos4PHI_vs_QT_data_Xn0n->SetMarkerStyle(kFullTriangleDown);

    p_cos4PHI_vs_QT_data_0nXn->GetXaxis()->SetTitle("QT (GeV)");
    p_cos4PHI_vs_QT_data_0nXn->GetYaxis()->SetTitle("<cos(4#Phi)>");    
    p_cos4PHI_vs_QT_data_0nXn->GetXaxis()->SetRangeUser(0., 40.);
    p_cos4PHI_vs_QT_data_0nXn->GetYaxis()->SetRangeUser(-0.5, 1.5);
    p_cos4PHI_vs_QT_data_0nXn->Draw();
    p_cos4PHI_vs_QT_data_Xn0n->Draw("same");
    p_cos4PHI_vs_QT_data_0nXn->Draw("same");
    legend_m->Draw();

    c_observables->Print("plots/dijet_kinematics/0nXn_vs_Xn0n_dijet_observables.pdf");
}