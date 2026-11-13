#include "../cms_palette.h"

void formatCanvas(TCanvas *c)
{
    c->SetLeftMargin(0.15);
    c->SetRightMargin(0.05);
    c->SetBottomMargin(0.15);
    c->SetTopMargin(0.1);
}

void formatHisto(TH1F *h, TString xlabel, Int_t color)
{
    TString ylabel = "1/N dN/d" + xlabel;

    h->Scale(1/h->Integral(),"width");
    
    h->GetXaxis()->SetTitle(xlabel);
    h->GetYaxis()->SetTitle(ylabel);
    h->GetXaxis()->SetTitleSize(28);
    h->GetXaxis()->SetTitleOffset(1.2);
    h->GetXaxis()->SetLabelSize(22);
    h->GetYaxis()->SetTitleSize(28);
    h->GetYaxis()->SetTitleOffset(1.7);
    h->GetYaxis()->SetLabelSize(22);
    h->SetLineWidth(4);
    h->SetLineColor(color);
    h->SetMarkerColor(color);
}

void drawHeader()
{
    TLatex *latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(26);
    latex->DrawLatex(0.15, 0.92, "#bf{CMS} #it{Simulation}");
    latex->DrawLatex(0.48, 0.92, "PYTHIA8 GNucleus (5.36 TeV)");
}

void draw_from_jra()
{
    // Load histograms
    TFile *f_beamA_pthat5_ppJEC = new TFile("histos/beamA_pthat5_ppJEC_kinematics.root");
    TH1F *rawpt_beamA_pthat5_ppJEC = (TH1F *) f_beamA_pthat5_ppJEC->Get("h_rawpt")->Clone("rawpt_beamA_pthat5_ppJEC");
    TH1F *jteta_beamA_pthat5_ppJEC = (TH1F *) f_beamA_pthat5_ppJEC->Get("h_jteta")->Clone("jteta_beamA_pthat5_ppJEC");
    TH1F *jtphi_beamA_pthat5_ppJEC = (TH1F *) f_beamA_pthat5_ppJEC->Get("h_jtphi")->Clone("jtphi_beamA_pthat5_ppJEC");

    TFile *f_beamA_pthat10_ppJEC = new TFile("histos/beamA_pthat10_ppJEC_kinematics.root");
    TH1F *rawpt_beamA_pthat10_ppJEC = (TH1F *) f_beamA_pthat10_ppJEC->Get("h_rawpt")->Clone("rawpt_beamA_pthat10_ppJEC");
    TH1F *jteta_beamA_pthat10_ppJEC = (TH1F *) f_beamA_pthat10_ppJEC->Get("h_jteta")->Clone("jteta_beamA_pthat10_ppJEC");
    TH1F *jtphi_beamA_pthat10_ppJEC = (TH1F *) f_beamA_pthat10_ppJEC->Get("h_jtphi")->Clone("jtphi_beamA_pthat10_ppJEC");

    TFile *f_beamB_pthat10_ppJEC = new TFile("histos/beamB_pthat10_ppJEC_kinematics.root");
    TH1F *rawpt_beamB_pthat10_ppJEC = (TH1F *) f_beamB_pthat10_ppJEC->Get("h_rawpt")->Clone("rawpt_beamB_pthat10_ppJEC");
    TH1F *jteta_beamB_pthat10_ppJEC = (TH1F *) f_beamB_pthat10_ppJEC->Get("h_jteta")->Clone("jteta_beamB_pthat10_ppJEC");
    TH1F *jtphi_beamB_pthat10_ppJEC = (TH1F *) f_beamB_pthat10_ppJEC->Get("h_jtphi")->Clone("jtphi_beamB_pthat10_ppJEC");

    TFile *f_beamA_pthat0_ppJEC = new TFile("histos/beamA_pthat0_ppJEC_kinematics.root");
    TH1F *rawpt_beamA_pthat0_ppJEC = (TH1F *) f_beamA_pthat0_ppJEC->Get("h_rawpt")->Clone("rawpt_beamA_pthat0_ppJEC");
    TH1F *jteta_beamA_pthat0_ppJEC = (TH1F *) f_beamA_pthat0_ppJEC->Get("h_jteta")->Clone("jteta_beamA_pthat0_ppJEC");
    TH1F *jtphi_beamA_pthat0_ppJEC = (TH1F *) f_beamA_pthat0_ppJEC->Get("h_jtphi")->Clone("jtphi_beamA_pthat0_ppJEC");

    TFile *f_beamB_pthat0_ppJEC = new TFile("histos/beamB_pthat0_ppJEC_kinematics.root");
    TH1F *rawpt_beamB_pthat0_ppJEC = (TH1F *) f_beamB_pthat0_ppJEC->Get("h_rawpt")->Clone("rawpt_beamB_pthat0_ppJEC");
    TH1F *jteta_beamB_pthat0_ppJEC = (TH1F *) f_beamB_pthat0_ppJEC->Get("h_jteta")->Clone("jteta_beamB_pthat0_ppJEC");
    TH1F *jtphi_beamB_pthat0_ppJEC = (TH1F *) f_beamB_pthat0_ppJEC->Get("h_jtphi")->Clone("jtphi_beamB_pthat0_ppJEC");

    // Draw rawpt
    TCanvas *c_rawpt = new TCanvas("c_rawpt", "", 700, 600);
    formatCanvas(c_rawpt);

    formatHisto(rawpt_beamA_pthat5_ppJEC, "p_{T}^{jet,reco}", cmsBlue);
    formatHisto(rawpt_beamA_pthat0_ppJEC, "p_{T}^{jet,reco}", cmsLightBlue);
    formatHisto(rawpt_beamB_pthat0_ppJEC, "p_{T}^{jet,reco}", cmsOrange);
    formatHisto(rawpt_beamA_pthat10_ppJEC, "p_{T}^{jet,reco}", cmsViolet);
    formatHisto(rawpt_beamB_pthat10_ppJEC, "p_{T}^{jet,reco}", cmsRed);
    rawpt_beamB_pthat0_ppJEC->SetLineStyle(2);
    rawpt_beamB_pthat10_ppJEC->SetLineStyle(2);
    rawpt_beamA_pthat5_ppJEC->GetXaxis()->SetRangeUser(0., 50.);
    rawpt_beamA_pthat5_ppJEC->GetYaxis()->SetRangeUser(1e-4, 10.);
    rawpt_beamA_pthat5_ppJEC->Draw("hist");
    rawpt_beamA_pthat0_ppJEC->Draw("hist same");
    rawpt_beamB_pthat0_ppJEC->Draw("hist same");
    rawpt_beamA_pthat10_ppJEC->Draw("hist same");
    rawpt_beamB_pthat10_ppJEC->Draw("hist same");
    drawHeader();

    TLegend *leg = new TLegend(0.4, 0.6, 0.85, 0.85);
    leg->SetTextSize(26);
    leg->AddEntry(rawpt_beamA_pthat5_ppJEC, "PhotonBeamA pthat=5", "l");
    leg->AddEntry(rawpt_beamA_pthat0_ppJEC, "PhotonBeamA pthat=0", "l");
    leg->AddEntry(rawpt_beamB_pthat0_ppJEC, "PhotonBeamB pthat=0", "l");
    leg->AddEntry(rawpt_beamA_pthat10_ppJEC, "PhotonBeamA pthat=10", "l");
    leg->AddEntry(rawpt_beamB_pthat10_ppJEC, "PhotonBeamB pthat=10", "l");
    leg->Draw();

    c_rawpt->SetLogy();

    // Draw jteta
    TCanvas *c_jteta = new TCanvas("c_jteta", "", 700, 600);
    formatCanvas(c_jteta);
    formatHisto(jteta_beamA_pthat5_ppJEC, "#eta^{jet}", cmsBlue);
    formatHisto(jteta_beamA_pthat0_ppJEC, "#eta^{jet}", cmsLightBlue);
    formatHisto(jteta_beamB_pthat0_ppJEC, "#eta^{jet}", cmsOrange);
    formatHisto(jteta_beamA_pthat10_ppJEC, "#eta^{jet}", cmsViolet);
    formatHisto(jteta_beamB_pthat10_ppJEC, "#eta^{jet}", cmsRed);
    jteta_beamB_pthat0_ppJEC->SetLineStyle(2);
    jteta_beamB_pthat10_ppJEC->SetLineStyle(2);
    jteta_beamA_pthat5_ppJEC->GetYaxis()->SetRangeUser(0., 0.6);
    jteta_beamA_pthat5_ppJEC->Draw("hist");
    jteta_beamA_pthat0_ppJEC->Draw("hist same");
    jteta_beamB_pthat0_ppJEC->Draw("hist same");
    jteta_beamA_pthat10_ppJEC->Draw("hist same");
    jteta_beamB_pthat10_ppJEC->Draw("hist same");
    drawHeader();
    leg->Draw();

    // Draw jtphi
    TCanvas *c_jtphi = new TCanvas("c_jtphi", "", 700, 600);
    formatCanvas(c_jtphi);
    formatHisto(jtphi_beamA_pthat5_ppJEC, "#phi^{jet}", cmsBlue);
    formatHisto(jtphi_beamA_pthat0_ppJEC, "#phi^{jet}", cmsLightBlue);
    formatHisto(jtphi_beamB_pthat0_ppJEC, "#phi^{jet}", cmsOrange);
    formatHisto(jtphi_beamA_pthat10_ppJEC, "#phi^{jet}", cmsViolet);
    formatHisto(jtphi_beamB_pthat10_ppJEC, "#phi^{jet}", cmsRed);
    jtphi_beamB_pthat0_ppJEC->SetLineStyle(2);
    jtphi_beamB_pthat10_ppJEC->SetLineStyle(2);
    jtphi_beamA_pthat5_ppJEC->GetYaxis()->SetRangeUser(0., 0.4);
    jtphi_beamA_pthat5_ppJEC->Draw("hist");
    jtphi_beamA_pthat0_ppJEC->Draw("hist same");
    jtphi_beamB_pthat0_ppJEC->Draw("hist same");
    jtphi_beamA_pthat10_ppJEC->Draw("hist same");
    jtphi_beamB_pthat10_ppJEC->Draw("hist same");
    drawHeader();
    leg->Draw();
}