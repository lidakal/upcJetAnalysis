#include "../../cms_palette.h"

void draw_dijet_kinematics_0n0n_vs_0nXn_vs_XnXn()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);
    
    TFile *f_data_0n0n = new TFile("histos/hiforwardAll_2024rereco_dijet_kinematics_0n0n_oppHF.root");
    std::cout << "0n0n: Loaded " << f_data_0n0n->GetName() << std::endl;
    TH1F *h_QT_data_0n0n = (TH1F*)f_data_0n0n->Get("h_QT")->Clone("h_QT_data_0n0n");
    TH1F *h_PT_data_0n0n = (TH1F*)f_data_0n0n->Get("h_PT")->Clone("h_PT_data_0n0n");
    TH1F *h_Minv_data_0n0n = (TH1F*)f_data_0n0n->Get("h_Minv")->Clone("h_Minv_data_0n0n");
    TH1F *h_y_data_0n0n = (TH1F*)f_data_0n0n->Get("h_y")->Clone("h_y_data_0n0n");
    TH1F *h_deta_data_0n0n = (TH1F*)f_data_0n0n->Get("h_deta")->Clone("h_deta_data_0n0n");
    TH1F *h_dphi_data_0n0n = (TH1F*)f_data_0n0n->Get("h_dphi")->Clone("h_dphi_data_0n0n");
    TH1F *h_PHI_data_0n0n = (TH1F*)f_data_0n0n->Get("h_PHI")->Clone("h_PHI_data_0n0n");
    TH1F *h_PHI_signed_data_0n0n = (TH1F*)f_data_0n0n->Get("h_PHI_signed")->Clone("h_PHI_signed_data_0n0n");
    TH2F *h_cos2PHI_vs_QT_data_0n0n = (TH2F*)f_data_0n0n->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_data_0n0n");
    TH2F *h_cos4PHI_vs_QT_data_0n0n = (TH2F*)f_data_0n0n->Get("h_cos4PHI_vs_QT")->Clone("h_cos4PHI_vs_QT_data_0n0n");
    TH3F *h_cos2PHI_vs_QT_vs_x1_data_0n0n = (TH3F*)f_data_0n0n->Get("h_cos2PHI_vs_QT_vs_x1")->Clone("h_cos2PHI_vs_QT_vs_x1_data_0n0n");
    TH3F *h_cos2PHI_vs_QT_vs_x2_data_0n0n = (TH3F*)f_data_0n0n->Get("h_cos2PHI_vs_QT_vs_x2")->Clone("h_cos2PHI_vs_QT_vs_x2_data_0n0n");
    TH3F *h_cos4PHI_vs_QT_vs_x1_data_0n0n = (TH3F*)f_data_0n0n->Get("h_cos4PHI_vs_QT_vs_x1")->Clone("h_cos4PHI_vs_QT_vs_x1_data_0n0n");
    TH3F *h_cos4PHI_vs_QT_vs_x2_data_0n0n = (TH3F*)f_data_0n0n->Get("h_cos4PHI_vs_QT_vs_x2")->Clone("h_cos4PHI_vs_QT_vs_x2_data_0n0n");

    TFile *f_data_0nXn = new TFile("histos/hiforwardAll_2024rereco_dijet_kinematics_0nXnInclusive_HFmp.root");
    std::cout << "0nXn: Loaded " << f_data_0nXn->GetName() << std::endl;
    TH1F *h_QT_data_0nXn = (TH1F*)f_data_0nXn->Get("h_QT")->Clone("h_QT_data_0nXn");
    TH1F *h_PT_data_0nXn = (TH1F*)f_data_0nXn->Get("h_PT")->Clone("h_PT_data_0nXn");
    TH1F *h_Minv_data_0nXn = (TH1F*)f_data_0nXn->Get("h_Minv")->Clone("h_Minv_data_0nXn");
    TH1F *h_y_data_0nXn = (TH1F*)f_data_0nXn->Get("h_y")->Clone("h_y_data_0nXn");
    TH1F *h_deta_data_0nXn = (TH1F*)f_data_0nXn->Get("h_deta")->Clone("h_deta_data_0nXn");
    TH1F *h_dphi_data_0nXn = (TH1F*)f_data_0nXn->Get("h_dphi")->Clone("h_dphi_data_0nXn");
    TH1F *h_PHI_data_0nXn = (TH1F*)f_data_0nXn->Get("h_PHI")->Clone("h_PHI_data_0nXn");
    TH1F *h_PHI_signed_data_0nXn = (TH1F*)f_data_0nXn->Get("h_PHI_signed")->Clone("h_PHI_signed_data_0nXn");
    TH2F *h_cos2PHI_vs_QT_data_0nXn = (TH2F*)f_data_0nXn->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_data_0nXn");
    TH2F *h_cos4PHI_vs_QT_data_0nXn = (TH2F*)f_data_0nXn->Get("h_cos4PHI_vs_QT")->Clone("h_cos4PHI_vs_QT_data_0nXn");
    TH3F *h_cos2PHI_vs_QT_vs_x1_data_0nXn = (TH3F*)f_data_0nXn->Get("h_cos2PHI_vs_QT_vs_x1")->Clone("h_cos2PHI_vs_QT_vs_x1_data_0nXn");
    TH3F *h_cos2PHI_vs_QT_vs_x2_data_0nXn = (TH3F*)f_data_0nXn->Get("h_cos2PHI_vs_QT_vs_x2")->Clone("h_cos2PHI_vs_QT_vs_x2_data_0nXn");
    TH3F *h_cos4PHI_vs_QT_vs_x1_data_0nXn = (TH3F*)f_data_0nXn->Get("h_cos4PHI_vs_QT_vs_x1")->Clone("h_cos4PHI_vs_QT_vs_x1_data_0nXn");
    TH3F *h_cos4PHI_vs_QT_vs_x2_data_0nXn = (TH3F*)f_data_0nXn->Get("h_cos4PHI_vs_QT_vs_x2")->Clone("h_cos4PHI_vs_QT_vs_x2_data_0nXn");


    TFile *f_data_XnXn = new TFile("histos/hiforwardAll_2024rereco_dijet_kinematics_XnXn_oppHF.root");
    std::cout << "XnXn: Loaded " << f_data_XnXn->GetName() << std::endl;
    TH1F *h_QT_data_XnXn = (TH1F*)f_data_XnXn->Get("h_QT")->Clone("h_QT_data_XnXn");
    TH1F *h_PT_data_XnXn = (TH1F*)f_data_XnXn->Get("h_PT")->Clone("h_PT_data_XnXn");
    TH1F *h_Minv_data_XnXn = (TH1F*)f_data_XnXn->Get("h_Minv")->Clone("h_Minv_data_XnXn");
    TH1F *h_y_data_XnXn = (TH1F*)f_data_XnXn->Get("h_y")->Clone("h_y_data_XnXn");
    TH1F *h_deta_data_XnXn = (TH1F*)f_data_XnXn->Get("h_deta")->Clone("h_deta_data_XnXn");
    TH1F *h_dphi_data_XnXn = (TH1F*)f_data_XnXn->Get("h_dphi")->Clone("h_dphi_data_XnXn");
    TH1F *h_PHI_data_XnXn = (TH1F*)f_data_XnXn->Get("h_PHI")->Clone("h_PHI_data_XnXn");
    TH1F *h_PHI_signed_data_XnXn = (TH1F*)f_data_XnXn->Get("h_PHI_signed")->Clone("h_PHI_signed_data_XnXn");
    TH2F *h_cos2PHI_vs_QT_data_XnXn = (TH2F*)f_data_XnXn->Get("h_cos2PHI_vs_QT")->Clone("h_cos2PHI_vs_QT_data_XnXn");
    TH2F *h_cos4PHI_vs_QT_data_XnXn = (TH2F*)f_data_XnXn->Get("h_cos4PHI_vs_QT")->Clone("h_cos4PHI_vs_QT_data_XnXn");
    TH3F *h_cos2PHI_vs_QT_vs_x1_data_XnXn = (TH3F*)f_data_XnXn->Get("h_cos2PHI_vs_QT_vs_x1")->Clone("h_cos2PHI_vs_QT_vs_x1_data_XnXn");
    TH3F *h_cos2PHI_vs_QT_vs_x2_data_XnXn = (TH3F*)f_data_XnXn->Get("h_cos2PHI_vs_QT_vs_x2")->Clone("h_cos2PHI_vs_QT_vs_x2_data_XnXn");
    TH3F *h_cos4PHI_vs_QT_vs_x1_data_XnXn = (TH3F*)f_data_XnXn->Get("h_cos4PHI_vs_QT_vs_x1")->Clone("h_cos4PHI_vs_QT_vs_x1_data_XnXn");
    TH3F *h_cos4PHI_vs_QT_vs_x2_data_XnXn = (TH3F*)f_data_XnXn->Get("h_cos4PHI_vs_QT_vs_x2")->Clone("h_cos4PHI_vs_QT_vs_x2_data_XnXn");

    // Preprocess

    // x1, x2 -> take projections and normalize
    TH1F *h_x1_data_0n0n = (TH1F*)h_cos2PHI_vs_QT_vs_x1_data_0n0n->ProjectionY("h_x1_data_0n0n");
    TH1F *h_x2_data_0n0n = (TH1F*)h_cos2PHI_vs_QT_vs_x2_data_0n0n->ProjectionY("h_x2_data_0n0n");
    TH1F *h_x1_data_0nXn = (TH1F*)h_cos2PHI_vs_QT_vs_x1_data_0nXn->ProjectionY("h_x1_data_0nXn");
    TH1F *h_x2_data_0nXn = (TH1F*)h_cos2PHI_vs_QT_vs_x2_data_0nXn->ProjectionY("h_x2_data_0nXn");
    TH1F *h_x1_data_XnXn = (TH1F*)h_cos2PHI_vs_QT_vs_x1_data_XnXn->ProjectionY("h_x1_data_XnXn");
    TH1F *h_x2_data_XnXn = (TH1F*)h_cos2PHI_vs_QT_vs_x2_data_XnXn->ProjectionY("h_x2_data_XnXn");
    for (auto h : { h_x1_data_0n0n, h_x2_data_0n0n, h_x1_data_0nXn, h_x2_data_0nXn, h_x1_data_XnXn, h_x2_data_XnXn }) {
        h->Rebin(5);
        h->Scale(1.0 / h->Integral(), "width");
    }

    // QT, PT, deta, dphi -> normalize
    for (auto h : { 
        h_QT_data_0n0n, h_QT_data_XnXn, h_QT_data_0nXn, 
        h_PT_data_0n0n, h_PT_data_XnXn, h_PT_data_0nXn,
        h_Minv_data_0n0n, h_Minv_data_XnXn, h_Minv_data_0nXn, 
        h_y_data_0n0n, h_y_data_XnXn, h_y_data_0nXn,
        h_deta_data_0n0n, h_deta_data_0nXn, h_deta_data_XnXn,
        h_dphi_data_0n0n, h_dphi_data_0nXn, h_dphi_data_XnXn,
    }) {
        h->Rebin(2);
        h->Scale(1.0 / h->Integral(), "width");
    }

    // dN/dPHI -> normalize
    for (auto h : { h_PHI_signed_data_0n0n, h_PHI_signed_data_XnXn, h_PHI_signed_data_0nXn, }) {
        h->RebinX(5);
        h->Scale(1.0 / h->Integral(), "width");
    }

    // cos2PHI, cos4PHI -> do not normalize, will take profile
    for (auto h : { h_cos2PHI_vs_QT_data_0n0n, h_cos2PHI_vs_QT_data_XnXn, h_cos2PHI_vs_QT_data_0nXn, 
                    h_cos4PHI_vs_QT_data_0n0n, h_cos4PHI_vs_QT_data_XnXn, h_cos4PHI_vs_QT_data_0nXn, }) {
        h->RebinX(5);
    }

    // Dijet DeltaEta, DeltaPhi
    TCanvas *c_control = new TCanvas("c_control", "c_control", 1600, 800);
    c_control->Divide(2,1);

    c_control->cd(1);
    h_deta_data_0n0n->SetLineColor(cmsViolet);
    h_deta_data_0n0n->SetMarkerColor(cmsViolet);
    h_deta_data_0n0n->SetMarkerStyle(kFullCircle);

    h_deta_data_0nXn->SetLineColor(cmsRed);
    h_deta_data_0nXn->SetMarkerColor(cmsRed);
    h_deta_data_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_deta_data_XnXn->SetLineColor(cmsBlue);
    h_deta_data_XnXn->SetMarkerColor(cmsBlue);
    h_deta_data_XnXn->SetMarkerStyle(kFullTriangleDown);

    h_deta_data_0n0n->GetXaxis()->SetTitle("Dijet #Delta#eta");
    h_deta_data_0n0n->GetXaxis()->SetRangeUser(0, 5.);
    h_deta_data_0n0n->GetYaxis()->SetTitle("Normalized entries");
    h_deta_data_0n0n->GetYaxis()->SetRangeUser(0.,1.);
    h_deta_data_0n0n->Draw();
    h_deta_data_0nXn->Draw("same");
    h_deta_data_XnXn->Draw("same");

    TLegend *legend_control = new TLegend(0.4, 0.7, 0.6, 0.85);
    legend_control->SetBorderSize(0);
    legend_control->AddEntry(h_deta_data_0n0n, "0n0n", "pl");
    legend_control->AddEntry(h_deta_data_0nXn, "0nXn", "pl");
    legend_control->AddEntry(h_deta_data_XnXn, "XnXn", "pl");
    legend_control->Draw();

    c_control->cd(2);
    h_dphi_data_0n0n->SetLineColor(cmsViolet);
    h_dphi_data_0n0n->SetMarkerColor(cmsViolet);
    h_dphi_data_0n0n->SetMarkerStyle(kFullCircle);

    h_dphi_data_0nXn->SetLineColor(cmsRed);
    h_dphi_data_0nXn->SetMarkerColor(cmsRed);
    h_dphi_data_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_dphi_data_XnXn->SetLineColor(cmsBlue);
    h_dphi_data_XnXn->SetMarkerColor(cmsBlue);
    h_dphi_data_XnXn->SetMarkerStyle(kFullTriangleDown);

    h_dphi_data_0n0n->GetXaxis()->SetTitle("Dijet #Delta#phi");
    h_dphi_data_0n0n->GetXaxis()->SetRangeUser(0., 3.2);
    h_dphi_data_0n0n->GetYaxis()->SetTitle("Normalized entries");
    h_dphi_data_0n0n->Draw();
    h_dphi_data_0nXn->Draw("same");
    h_dphi_data_XnXn->Draw("same");
    c_control->cd(2)->SetLogy();

    legend_control->Draw();

    c_control->Print("plots/dijet_kinematics/0n0n_vs_0nXn_vs_XnXn_deta_dphi.pdf");

    // Draw QT + PT, Minv, y
    TCanvas *c_kinematics = new TCanvas("c_kinematics", "c_kinematics", 2400, 800);
    c_kinematics->Divide(3,1);

    c_kinematics->cd(1);

    h_QT_data_0n0n->SetLineColor(cmsViolet);
    h_QT_data_0n0n->SetMarkerColor(cmsViolet);
    h_QT_data_0n0n->SetMarkerStyle(kFullCircle);
    h_PT_data_0n0n->SetLineColor(cmsViolet);
    h_PT_data_0n0n->SetMarkerColor(cmsViolet);
    h_PT_data_0n0n->SetMarkerStyle(kOpenCircle);

    h_QT_data_0nXn->SetLineColor(cmsRed);
    h_QT_data_0nXn->SetMarkerColor(cmsRed);
    h_QT_data_0nXn->SetMarkerStyle(kFullTriangleUp);
    h_PT_data_0nXn->SetLineColor(cmsRed);
    h_PT_data_0nXn->SetMarkerColor(cmsRed);
    h_PT_data_0nXn->SetMarkerStyle(kOpenTriangleUp);

    h_QT_data_XnXn->SetLineColor(cmsBlue);
    h_QT_data_XnXn->SetMarkerColor(cmsBlue);
    h_QT_data_XnXn->SetMarkerStyle(kFullTriangleDown);
    h_PT_data_XnXn->SetLineColor(cmsBlue);
    h_PT_data_XnXn->SetMarkerColor(cmsBlue);
    h_PT_data_XnXn->SetMarkerStyle(kOpenTriangleDown);


    h_QT_data_0n0n->GetXaxis()->SetTitle("QT or PT (GeV)");
    h_QT_data_0n0n->GetYaxis()->SetTitle("Normalized entries");
    h_QT_data_0n0n->GetYaxis()->SetRangeUser(0., 0.18);
    h_QT_data_0n0n->GetXaxis()->SetRangeUser(0., 60.);
    h_QT_data_0n0n->Draw();
    h_QT_data_XnXn->Draw("same");
    h_PT_data_0n0n->Draw("same");
    h_PT_data_XnXn->Draw("same");
    h_PT_data_0nXn->Draw("same");

    TLegend *legend = new TLegend(0.2, 0.65, 0.8, 0.85);
    legend->SetBorderSize(0);
    legend->SetNColumns(2);
    legend->AddEntry(new TH1F(), "QT", "");
    legend->AddEntry(new TH1F(), "PT", "");
    legend->AddEntry(h_QT_data_0n0n, "0n0n", "pl");
    legend->AddEntry(h_PT_data_0n0n, "0n0n", "pl");
    legend->AddEntry(h_QT_data_0nXn, "0nXn", "pl");
    legend->AddEntry(h_PT_data_0nXn, "0nXn", "pl");
    legend->AddEntry(h_QT_data_XnXn, "XnXn", "pl");
    legend->AddEntry(h_PT_data_XnXn, "XnXn", "pl");
    legend->Draw();

    c_kinematics->cd(2);

    h_Minv_data_0n0n->SetLineColor(cmsViolet);
    h_Minv_data_0n0n->SetMarkerColor(cmsViolet);
    h_Minv_data_0n0n->SetMarkerStyle(kFullCircle);

    h_Minv_data_0nXn->SetLineColor(cmsRed);
    h_Minv_data_0nXn->SetMarkerColor(cmsRed);
    h_Minv_data_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_Minv_data_XnXn->SetLineColor(cmsBlue);
    h_Minv_data_XnXn->SetMarkerColor(cmsBlue);
    h_Minv_data_XnXn->SetMarkerStyle(kFullTriangleDown);

    h_Minv_data_0n0n->GetXaxis()->SetTitle("Dijet M_{inv} (GeV)");
    h_Minv_data_0n0n->GetYaxis()->SetTitle("Normalized entries");
    h_Minv_data_0n0n->GetYaxis()->SetRangeUser(0, 0.06);
    h_Minv_data_0n0n->GetXaxis()->SetRangeUser(40., 140.);
    h_Minv_data_0n0n->Draw();
    h_Minv_data_XnXn->Draw("same");
    h_Minv_data_0nXn->Draw("same");

    TLegend *legend_m = new TLegend(0.2, 0.7, 0.8, 0.85);
    legend_m->SetBorderSize(0);
    legend_m->SetFillStyle(0);
    legend_m->AddEntry(h_Minv_data_0n0n, "0n0n", "pl");
    legend_m->AddEntry(h_Minv_data_0nXn, "0nXn", "pl");
    legend_m->AddEntry(h_Minv_data_XnXn, "XnXn", "pl");
    legend_m->Draw();

    c_kinematics->cd(3);

    h_y_data_0n0n->SetLineColor(cmsViolet);
    h_y_data_0n0n->SetMarkerColor(cmsViolet);
    h_y_data_0n0n->SetMarkerStyle(kFullCircle);

    h_y_data_0nXn->SetLineColor(cmsRed);
    h_y_data_0nXn->SetMarkerColor(cmsRed);
    h_y_data_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_y_data_XnXn->SetLineColor(cmsBlue);
    h_y_data_XnXn->SetMarkerColor(cmsBlue);
    h_y_data_XnXn->SetMarkerStyle(kFullTriangleDown);

    h_y_data_0n0n->GetXaxis()->SetTitle("Dijet rapidity");
    h_y_data_0n0n->GetYaxis()->SetTitle("Normalized entries");
    h_y_data_0n0n->GetXaxis()->SetRangeUser(-3., 3.);
    h_y_data_0n0n->GetYaxis()->SetRangeUser(0., 1.);
    h_y_data_0n0n->Draw();
    h_y_data_XnXn->Draw("same");
    h_y_data_0nXn->Draw("same");

    TLegend *legend_y = (TLegend *) legend_m->Clone("legend_y");
    legend_y->Draw();


    c_kinematics->Print("plots/dijet_kinematics/0n0n_vs_0nXn_vs_XnXn_dijet_kinematics.pdf");

    // dN/dPHI vs PHI, <cos(2PHI)> vs QT, <cos(4PHI)> vs QT
    TCanvas *c_observables = new TCanvas("c_observables", "c_observables", 2400, 800);
    c_observables->Divide(3,1);

    c_observables->cd(1);

    h_PHI_signed_data_0n0n->SetLineColor(cmsViolet);
    h_PHI_signed_data_0n0n->SetMarkerColor(cmsViolet);
    h_PHI_signed_data_0n0n->SetMarkerStyle(kFullCircle);

    h_PHI_signed_data_0nXn->SetLineColor(cmsRed);
    h_PHI_signed_data_0nXn->SetMarkerColor(cmsRed);
    h_PHI_signed_data_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_PHI_signed_data_XnXn->SetLineColor(cmsBlue);
    h_PHI_signed_data_XnXn->SetMarkerColor(cmsBlue);
    h_PHI_signed_data_XnXn->SetMarkerStyle(kFullTriangleDown);

    h_PHI_signed_data_0n0n->GetXaxis()->SetTitle("#Phi (radians)");
    h_PHI_signed_data_0n0n->GetYaxis()->SetTitle("1/N_{events}dN/d#Phi");
    h_PHI_signed_data_0n0n->GetYaxis()->SetRangeUser(0., 0.5);
    h_PHI_signed_data_0n0n->Draw();
    h_PHI_signed_data_XnXn->Draw("same");
    h_PHI_signed_data_0nXn->Draw("same");
    legend_m->Draw();

    c_observables->cd(2);

    TProfile *p_cos2PHI_vs_QT_data_0n0n = h_cos2PHI_vs_QT_data_0n0n->ProfileX();
    p_cos2PHI_vs_QT_data_0n0n->SetLineColor(cmsViolet);
    p_cos2PHI_vs_QT_data_0n0n->SetMarkerColor(cmsViolet);
    p_cos2PHI_vs_QT_data_0n0n->SetMarkerStyle(kFullCircle);

    TProfile *p_cos2PHI_vs_QT_data_0nXn = h_cos2PHI_vs_QT_data_0nXn->ProfileX();
    p_cos2PHI_vs_QT_data_0nXn->SetLineColor(cmsRed);
    p_cos2PHI_vs_QT_data_0nXn->SetMarkerColor(cmsRed);
    p_cos2PHI_vs_QT_data_0nXn->SetMarkerStyle(kFullTriangleUp);

    TProfile *p_cos2PHI_vs_QT_data_XnXn = h_cos2PHI_vs_QT_data_XnXn->ProfileX();
    p_cos2PHI_vs_QT_data_XnXn->SetLineColor(cmsBlue);
    p_cos2PHI_vs_QT_data_XnXn->SetMarkerColor(cmsBlue);
    p_cos2PHI_vs_QT_data_XnXn->SetMarkerStyle(kFullTriangleDown);

    p_cos2PHI_vs_QT_data_0n0n->GetXaxis()->SetTitle("QT (GeV)");
    p_cos2PHI_vs_QT_data_0n0n->GetYaxis()->SetTitle("<cos(2#Phi)>");    
    p_cos2PHI_vs_QT_data_0n0n->GetXaxis()->SetRangeUser(0., 40.);
    p_cos2PHI_vs_QT_data_0n0n->GetYaxis()->SetRangeUser(-0.5, 1.5);
    p_cos2PHI_vs_QT_data_0n0n->Draw();
    p_cos2PHI_vs_QT_data_XnXn->Draw("same");
    p_cos2PHI_vs_QT_data_0nXn->Draw("same");
    legend_m->Draw();

    c_observables->cd(3);

    TProfile *p_cos4PHI_vs_QT_data_0n0n = h_cos4PHI_vs_QT_data_0n0n->ProfileX();
    p_cos4PHI_vs_QT_data_0n0n->SetLineColor(cmsViolet);
    p_cos4PHI_vs_QT_data_0n0n->SetMarkerColor(cmsViolet);
    p_cos4PHI_vs_QT_data_0n0n->SetMarkerStyle(kFullCircle);

    TProfile *p_cos4PHI_vs_QT_data_0nXn = h_cos4PHI_vs_QT_data_0nXn->ProfileX();
    p_cos4PHI_vs_QT_data_0nXn->SetLineColor(cmsRed);
    p_cos4PHI_vs_QT_data_0nXn->SetMarkerColor(cmsRed);
    p_cos4PHI_vs_QT_data_0nXn->SetMarkerStyle(kFullTriangleUp);

    TProfile *p_cos4PHI_vs_QT_data_XnXn = h_cos4PHI_vs_QT_data_XnXn->ProfileX();
    p_cos4PHI_vs_QT_data_XnXn->SetLineColor(cmsBlue);
    p_cos4PHI_vs_QT_data_XnXn->SetMarkerColor(cmsBlue);
    p_cos4PHI_vs_QT_data_XnXn->SetMarkerStyle(kFullTriangleDown);

    p_cos4PHI_vs_QT_data_0n0n->GetXaxis()->SetTitle("QT (GeV)");
    p_cos4PHI_vs_QT_data_0n0n->GetYaxis()->SetTitle("<cos(4#Phi)>");    
    p_cos4PHI_vs_QT_data_0n0n->GetXaxis()->SetRangeUser(0., 40.);
    p_cos4PHI_vs_QT_data_0n0n->GetYaxis()->SetRangeUser(-0.5, 1.5);
    p_cos4PHI_vs_QT_data_0n0n->Draw();
    p_cos4PHI_vs_QT_data_XnXn->Draw("same");
    p_cos4PHI_vs_QT_data_0nXn->Draw("same");
    legend_m->Draw();

    c_observables->Print("plots/dijet_kinematics/0n0n_vs_0nXn_vs_XnXn_dijet_observables.pdf");

    // x1, x2
    TCanvas *c_x1_x2 = new TCanvas("c_x1_x2", "c_x1_x2", 1600, 800);
    c_x1_x2->Divide(2,1);

    c_x1_x2->cd(1);
    h_x1_data_0n0n->SetLineColor(cmsViolet);
    h_x1_data_0n0n->SetMarkerColor(cmsViolet);
    h_x1_data_0n0n->SetMarkerStyle(kFullCircle);

    h_x1_data_0nXn->SetLineColor(cmsRed);
    h_x1_data_0nXn->SetMarkerColor(cmsRed);
    h_x1_data_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_x1_data_XnXn->SetLineColor(cmsBlue);
    h_x1_data_XnXn->SetMarkerColor(cmsBlue);
    h_x1_data_XnXn->SetMarkerStyle(kFullTriangleDown);

    h_x1_data_0n0n->GetXaxis()->SetTitle("x1 (x_{#gamma})");
    h_x1_data_0n0n->GetYaxis()->SetTitle("1/N #frac{dN}{dx_{1}}");
    h_x1_data_0n0n->GetYaxis()->SetRangeUser(0., 350.);
    h_x1_data_0n0n->Draw();
    h_x1_data_0nXn->Draw("same");
    h_x1_data_XnXn->Draw("same");
    c_x1_x2->cd(1)->SetLogx();

    TLegend *legend_x1_x2 = new TLegend(0.4, 0.7, 0.6, 0.85);
    legend_x1_x2->SetBorderSize(0);
    legend_x1_x2->AddEntry(h_x1_data_0n0n, "0n0n", "pl");
    legend_x1_x2->AddEntry(h_x1_data_0nXn, "0nXn", "pl");
    legend_x1_x2->AddEntry(h_x1_data_XnXn, "XnXn", "pl");
    legend_x1_x2->Draw();

    c_x1_x2->cd(2);
    h_x2_data_0n0n->SetLineColor(cmsViolet);
    h_x2_data_0n0n->SetMarkerColor(cmsViolet);
    h_x2_data_0n0n->SetMarkerStyle(kFullCircle);

    h_x2_data_0nXn->SetLineColor(cmsRed);
    h_x2_data_0nXn->SetMarkerColor(cmsRed);
    h_x2_data_0nXn->SetMarkerStyle(kFullTriangleUp);

    h_x2_data_XnXn->SetLineColor(cmsBlue);
    h_x2_data_XnXn->SetMarkerColor(cmsBlue);
    h_x2_data_XnXn->SetMarkerStyle(kFullTriangleDown);

    h_x2_data_0n0n->GetXaxis()->SetTitle("x2 (x_{P})");
    h_x2_data_0n0n->GetYaxis()->SetTitle("1/N #frac{dN}{dx_{2}}");
    h_x2_data_0n0n->GetYaxis()->SetRangeUser(0., 20);
    h_x2_data_0n0n->Draw();
    h_x2_data_0nXn->Draw("same");
    h_x2_data_XnXn->Draw("same");
    c_x1_x2->cd(2)->SetLogx();

    legend_x1_x2->Draw();

    c_x1_x2->Print("plots/dijet_kinematics/0n0n_vs_0nXn_vs_XnXn_x1_x2.pdf");
}