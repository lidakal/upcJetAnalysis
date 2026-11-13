#include "../../../cms_palette.h"

void draw_header() 
{
    TLatex *cms = new TLatex();
    cms->SetNDC();
    cms->SetTextAlign(11);
    cms->SetTextSize(28);
    cms->DrawLatex(0.15, 0.92, "#bf{CMS} #it{Internal}");

    TLatex *data = new TLatex();
    data->SetNDC();
    data->SetTextAlign(31);
    data->SetTextSize(28);
    data->DrawLatex(0.95, 0.92, "2023 PbPb (5.36 TeV)");
}

void draw_jet_kinematics_data_vs_MC()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);
    gStyle->SetPaintTextFormat("0.2f");

    TString suffix = "_HLT_ZDC_dijet";

    TFile *fin_data = new TFile("histos/hiforwardAll_2024rereco_jet_kinematics" + suffix + ".root"); // Created by plot_jet_kinematics.C
    TH1F *h_nref_data = (TH1F *) fin_data->Get("h_nref")->Clone("h_nref_data");
    TH3F *h_nref_pt_eta_lead_data = (TH3F *) fin_data->Get("h_nref_pt_eta_lead")->Clone("h_nref_pt_eta_lead_data");
    TH3F *h_nref_pt_eta_sub_data = (TH3F *) fin_data->Get("h_nref_pt_eta_sub")->Clone("h_nref_pt_eta_sub_data");
    TH3F *h_nref_pt_eta_third_data = (TH3F *) fin_data->Get("h_nref_pt_eta_third")->Clone("h_nref_pt_eta_third_data");

    TFile *fin_beamA = new TFile("histos/beamA_diffraction_pthat10_jet_kinematics" + suffix + ".root"); // Created by plot_jet_kinematics.C
    TH1F *h_nref_beamA = (TH1F *) fin_beamA->Get("h_nref")->Clone("h_nref_beamA");
    TH3F *h_nref_pt_eta_lead_beamA = (TH3F *) fin_beamA->Get("h_nref_pt_eta_lead")->Clone("h_nref_pt_eta_lead_beamA");
    TH3F *h_nref_pt_eta_sub_beamA = (TH3F *) fin_beamA->Get("h_nref_pt_eta_sub")->Clone("h_nref_pt_eta_sub_beamA");
    TH3F *h_nref_pt_eta_third_beamA = (TH3F *) fin_beamA->Get("h_nref_pt_eta_third")->Clone("h_nref_pt_eta_third_beamA");

    TFile *fin_beamB = new TFile("histos/beamB_diffraction_pthat10_jet_kinematics" + suffix + ".root"); // Created by plot_jet_kinematics.C
    TH1F *h_nref_beamB = (TH1F *) fin_beamB->Get("h_nref")->Clone("h_nref_beamB");
    TH3F *h_nref_pt_eta_lead_beamB = (TH3F *) fin_beamB->Get("h_nref_pt_eta_lead")->Clone("h_nref_pt_eta_lead_beamB");
    TH3F *h_nref_pt_eta_sub_beamB = (TH3F *) fin_beamB->Get("h_nref_pt_eta_sub")->Clone("h_nref_pt_eta_sub_beamB");
    TH3F *h_nref_pt_eta_third_beamB = (TH3F *) fin_beamB->Get("h_nref_pt_eta_third")->Clone("h_nref_pt_eta_third_beamB");

    // Make projections
    TH1F *h_pt_lead_data = (TH1F *) h_nref_pt_eta_lead_data->Project3D("y");
    h_pt_lead_data->SetMarkerStyle(kFullCircle);
    h_pt_lead_data->SetMarkerColor(cmsBlue);
    h_pt_lead_data->SetLineColor(cmsBlue);
    h_pt_lead_data->RebinX(5);

    TH1F *h_pt_lead_beamB = (TH1F *) h_nref_pt_eta_lead_beamB->Project3D("y");
    h_pt_lead_beamB->SetLineColorAlpha(cmsBlue,0.5);
    h_pt_lead_beamB->SetLineStyle(2);
    h_pt_lead_beamB->SetLineWidth(2);
    h_pt_lead_beamB->RebinX(5);
    h_pt_lead_beamB->Scale(h_pt_lead_data->Integral()/h_pt_lead_beamB->Integral());

    TH1F *h_pt_sub_data = (TH1F *) h_nref_pt_eta_sub_data->Project3D("y");
    h_pt_sub_data->SetMarkerStyle(kFullSquare);
    h_pt_sub_data->SetMarkerColor(cmsOrange);
    h_pt_sub_data->SetLineColor(cmsOrange);
    h_pt_sub_data->RebinX(5);

    TH1F *h_pt_sub_beamB = (TH1F *) h_nref_pt_eta_sub_beamB->Project3D("y");
    h_pt_sub_beamB->SetLineColorAlpha(cmsOrange,0.5);
    h_pt_sub_beamB->SetLineStyle(2);
    h_pt_sub_beamB->SetLineWidth(2);
    h_pt_sub_beamB->RebinX(5);
    h_pt_sub_beamB->Scale(h_pt_sub_data->Integral()/h_pt_sub_beamB->Integral());

    TH1F *h_pt_third_data = (TH1F *) h_nref_pt_eta_third_data->Project3D("y");
    h_pt_third_data->SetMarkerStyle(kFullTriangleUp);
    h_pt_third_data->SetMarkerColor(cmsViolet);
    h_pt_third_data->SetLineColor(cmsViolet);
    h_pt_third_data->RebinX(5);

    TH1F *h_pt_third_beamB = (TH1F *) h_nref_pt_eta_third_beamB->Project3D("y");
    h_pt_third_beamB->SetLineColorAlpha(cmsViolet,0.5);
    h_pt_third_beamB->SetLineStyle(2);
    h_pt_third_beamB->SetLineWidth(2);
    h_pt_third_beamB->RebinX(5);
    h_pt_third_beamB->Scale(h_pt_third_data->Integral()/h_pt_third_beamB->Integral(h_pt_third_beamB->GetXaxis()->FindBin(10.),h_pt_third_beamB->GetNbinsX()));

    // Draw
    TCanvas *c_pt = new TCanvas("c_pt", "x=pt", 800, 700);
    c_pt->SetTopMargin(0.1);
    c_pt->SetBottomMargin(0.15);
    c_pt->SetLeftMargin(0.15);
    c_pt->SetRightMargin(0.05);
    c_pt->SetLogy();
    h_pt_lead_beamB->GetXaxis()->SetTitle("p_{T}^{jet} (GeV)");
    h_pt_lead_beamB->GetXaxis()->SetTitleOffset(1.2);
    h_pt_lead_beamB->GetYaxis()->SetTitle("Number of events");
    h_pt_lead_beamB->GetYaxis()->SetRangeUser(1, 1e4);
    h_pt_lead_beamB->Draw("same hist");
    h_pt_sub_beamB->Draw("same hist");
    h_pt_lead_data->Draw("same");
    h_pt_sub_data->Draw("same");
    draw_header();

    TLegend *leg_pt = new TLegend(0.5, 0.7, 0.85, 0.85);
    leg_pt->SetBorderSize(0);
    leg_pt->SetFillStyle(0);
    leg_pt->SetNColumns(2);
    leg_pt->AddEntry(new TH1F(), "Leading", "");
    leg_pt->AddEntry(new TH1F(), "Subleading", "");    
    leg_pt->AddEntry(h_pt_lead_data, "Data", "pl");
    leg_pt->AddEntry(h_pt_sub_data, "Data", "pl");
    leg_pt->AddEntry(h_pt_lead_beamB, "MC", "l");
    leg_pt->AddEntry(h_pt_sub_beamB, "MC", "l");
    leg_pt->Draw();

    c_pt->Print("plots/data_vs_MC_pt"+suffix+".pdf");

    TCanvas *c_pt_third = new TCanvas("c_pt_third", "x=pt", 800, 700);
    c_pt_third->SetTopMargin(0.1);
    c_pt_third->SetBottomMargin(0.15);
    c_pt_third->SetLeftMargin(0.15);
    c_pt_third->SetRightMargin(0.05);
    c_pt_third->SetLogy();
    h_pt_third_beamB->GetXaxis()->SetTitle("Third jet p_{T} (GeV)");
    h_pt_third_beamB->GetXaxis()->SetTitleOffset(1.2);
    h_pt_third_beamB->GetYaxis()->SetTitle("Number of events");
    h_pt_third_beamB->GetYaxis()->SetRangeUser(1, 1e3);
    h_pt_third_beamB->Draw("same hist");
    h_pt_third_data->Draw("same");
    draw_header();

    TLegend *leg_pt_third = new TLegend(0.5, 0.7, 0.85, 0.85);
    leg_pt_third->SetBorderSize(0);
    leg_pt_third->SetFillStyle(0);
    leg_pt_third->AddEntry(h_pt_third_data, "Data", "pl");
    leg_pt_third->AddEntry(h_pt_third_beamB, "MC", "l");
    leg_pt_third->Draw();

    c_pt_third->Print("plots/data_vs_MC_pt_third"+suffix+".pdf");
}