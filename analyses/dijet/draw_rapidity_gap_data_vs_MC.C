#include "../../cms_palette.h"

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

void draw_rapidity_gap_data_vs_MC()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetLegendTextSize(24);
    gStyle->SetLabelSize(24, "XYZ");
    gStyle->SetTitleSize(28, "XYZ");

    TString suffix = "_oppHF_oppEC2_trkLim2p5_ptgr0p2_chOnly_jetID_jetVM"; // same suffix for all samples

    TFile *fin_data = new TFile("histos/hiforwardAll_2024rereco_pf_distribution"+suffix+".root"); // requires plot_PF_distribution_v2.C
    TH2F *h_PFJetDeta_vs_rapgap_b_data = (TH2F *) fin_data->Get("h_PFJetDeta_vs_rapgap_b_Etamax_tracker_wSwap")->Clone("h_PFJetDeta_vs_rapgap_b_data");

    TFile *fin_beamB = new TFile("histos/beamB_diffraction_pthat10_pf_distribution"+suffix+".root"); // requires plot_PF_distribution_v2.C
    // TFile *fin_beamB = new TFile("histos/beamA_qcd_pthat10_pf_distribution"+suffix+".root"); // requires plot_PF_distribution_v2.C
    // TFile *fin_beamB = new TFile("histos/beamA_diffractionSide2_pthat10_pf_distribution"+suffix+".root"); // requires plot_PF_distribution_v2.C
    TH2F *h_PFJetDeta_vs_rapgap_b_beamB = (TH2F *) fin_beamB->Get("h_PFJetDeta_vs_rapgap_b_Etamax_tracker_wSwap")->Clone("h_PFJetDeta_vs_rapgap_b_beamB");

    TFile *fin_beamA = new TFile("histos/beamA_diffraction_pthat10_pf_distribution"+suffix+".root"); // requires plot_PF_distribution_v2.C
    TH2F *h_PFJetDeta_vs_rapgap_b_beamA = (TH2F *) fin_beamA->Get("h_PFJetDeta_vs_rapgap_b_Etamax_tracker_wSwap")->Clone("h_PFJetDeta_vs_rapgap_b_beamA");

    // Make projections 
    TH1F *h_PFJetDeta_data = (TH1F*) h_PFJetDeta_vs_rapgap_b_data->ProjectionX("h_PFJetDeta_data", 0, h_PFJetDeta_vs_rapgap_b_data->GetNbinsY()+1);
    TH1F *h_rapgap_data = (TH1F*) h_PFJetDeta_vs_rapgap_b_data->ProjectionY("h_rapgap_data", 0, h_PFJetDeta_vs_rapgap_b_data->GetNbinsX()+1);
    TH1F *h_PFJetDeta_beamB = (TH1F*) h_PFJetDeta_vs_rapgap_b_beamB->ProjectionX("h_PFJetDeta_beamB", 0, h_PFJetDeta_vs_rapgap_b_beamB->GetNbinsY()+1);
    TH1F *h_rapgap_beamB = (TH1F*) h_PFJetDeta_vs_rapgap_b_beamB->ProjectionY("h_rapgap_beamB", 0, h_PFJetDeta_vs_rapgap_b_beamB->GetNbinsX()+1);
    TH1F *h_PFJetDeta_beamA = (TH1F*) h_PFJetDeta_vs_rapgap_b_beamA->ProjectionX("h_PFJetDeta_beamA", 0, h_PFJetDeta_vs_rapgap_b_beamA->GetNbinsY()+1);
    TH1F *h_rapgap_beamA = (TH1F*) h_PFJetDeta_vs_rapgap_b_beamA->ProjectionY("h_rapgap_beamA", 0, h_PFJetDeta_vs_rapgap_b_beamA->GetNbinsX()+1);

    // Format
    h_PFJetDeta_data->Scale(1/h_PFJetDeta_data->Integral());
    h_PFJetDeta_data->SetMarkerStyle(kFullCircle);
    h_PFJetDeta_data->SetMarkerColor(kBlack);
    h_PFJetDeta_data->SetLineColor(kBlack);

    h_rapgap_data->Scale(1/h_rapgap_data->Integral());
    h_rapgap_data->SetMarkerStyle(kFullCircle);
    h_rapgap_data->SetMarkerColor(kBlack);
    h_rapgap_data->SetLineColor(kBlack);

    h_PFJetDeta_beamB->Scale(1/h_PFJetDeta_beamB->Integral());
    h_PFJetDeta_beamB->SetLineColor(cmsBlue);
    h_PFJetDeta_beamB->SetLineWidth(2);

    h_rapgap_beamB->Scale(1/h_rapgap_beamB->Integral());
    h_rapgap_beamB->SetLineColor(cmsBlue);
    h_rapgap_beamB->SetLineWidth(2);

    h_PFJetDeta_beamA->Scale(1/h_PFJetDeta_beamA->Integral());
    h_PFJetDeta_beamA->SetLineColor(cmsOrange);
    h_PFJetDeta_beamA->SetLineWidth(2);

    h_rapgap_beamA->Scale(1/h_rapgap_beamA->Integral());
    h_rapgap_beamA->SetLineColor(cmsOrange);
    h_rapgap_beamA->SetLineWidth(2);

    // Make legend
    TLegend *leg = new TLegend(0.7, 0.65, 0.8, 0.8);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(h_PFJetDeta_data, "Data", "pe");
    leg->AddEntry(h_PFJetDeta_beamA, "MC (beamA)", "l");
    leg->AddEntry(h_PFJetDeta_beamB, "MC (beamB)", "l");

    // Draw
    TCanvas *c_PFJetDeta = new TCanvas("c_PFJetDeta", "eta(jet)-eta(trk) defining BRG", 800, 700);
    c_PFJetDeta->SetTopMargin(0.1);
    c_PFJetDeta->SetBottomMargin(0.15);
    c_PFJetDeta->SetLeftMargin(0.15);
    c_PFJetDeta->SetRightMargin(0.05);
    c_PFJetDeta->SetLogy();

    h_PFJetDeta_data->GetXaxis()->SetTitle("#Delta#eta[jet,PF]^{B}");
    h_PFJetDeta_data->GetXaxis()->SetRangeUser(-5, 5);
    h_PFJetDeta_data->GetYaxis()->SetTitle("Normalized entries per event");
    h_PFJetDeta_data->GetYaxis()->SetRangeUser(1e-4, 1.);

    h_PFJetDeta_data->Draw("E1");
    h_PFJetDeta_beamA->Draw("hist same");
    h_PFJetDeta_beamB->Draw("hist same");
    leg->Draw();
    draw_header();

    // c_PFJetDeta->Print("plots/data_vs_MC_PFJetDeta_b.pdf");

    TCanvas *c_rapgap = new TCanvas("c_rapgap", "BRG", 800, 700);
    c_rapgap->SetTopMargin(0.1);
    c_rapgap->SetBottomMargin(0.15);
    c_rapgap->SetLeftMargin(0.15);
    c_rapgap->SetRightMargin(0.05);

    h_rapgap_data->GetXaxis()->SetTitle("#Delta#eta^{B}");
    h_rapgap_data->GetXaxis()->SetRangeUser(0, 5);
    h_rapgap_data->GetYaxis()->SetTitle("Normalized entries per event");
    h_rapgap_data->GetYaxis()->SetRangeUser(0, 0.15);

    h_rapgap_data->Draw("E1");
    h_rapgap_beamA->Draw("hist same");
    h_rapgap_beamB->Draw("hist same");
    leg->Draw();
    draw_header();

    TLine *line = new TLine(1.2, 0., 1.2, 0.15);
    line->SetLineColor(kBlack);
    line->SetLineStyle(2);
    line->Draw();

    // c_rapgap->Print("plots/data_vs_MC_rapgap_b.pdf");
}