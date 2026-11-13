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
    // TString ylabel = "1/N dN/d" + xlabel;
    // h->Scale(1/h->Integral(),"width");
    TString ylabel = "Entries";
    
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

void draw_pthat()
{
    // Load histograms
    TFile *f_beamA_pthat10 = new TFile("histos/beamA_pthat10_pp26EtaBinsJEC_kinematics.root");
    TH2F *refpt_vs_pthat_beamA_pthat10 = (TH2F *) f_beamA_pthat10->Get("h_refpt_vs_pthat")->Clone("refpt_vs_pthat_beamA_pthat10");
    
    TFile *f_beamA_pthat20 = new TFile("histos/beamA_pthat20_pp26EtaBinsJEC_kinematics.root");
    TH2F *refpt_vs_pthat_beamA_pthat20 = (TH2F *) f_beamA_pthat20->Get("h_refpt_vs_pthat")->Clone("refpt_vs_pthat_beamA_pthat20");

    TFile *f_beamB_pthat10 = new TFile("histos/beamB_pthat10_pp26EtaBinsJEC_kinematics.root");
    TH2F *refpt_vs_pthat_beamB_pthat10 = (TH2F *) f_beamB_pthat10->Get("h_refpt_vs_pthat")->Clone("refpt_vs_pthat_beamB_pthat10");
    
    TFile *f_beamB_pthat20 = new TFile("histos/beamB_pthat20_pp26EtaBinsJEC_kinematics.root");
    TH2F *refpt_vs_pthat_beamB_pthat20 = (TH2F *) f_beamB_pthat20->Get("h_refpt_vs_pthat")->Clone("refpt_vs_pthat_beamB_pthat20");

    // Count events
    double n_beamA_pthat10_10to20 = refpt_vs_pthat_beamA_pthat10->Integral(
        refpt_vs_pthat_beamA_pthat10->GetXaxis()->FindBin(10), 
        refpt_vs_pthat_beamA_pthat10->GetXaxis()->FindBin(20)-1,
        1,
        refpt_vs_pthat_beamA_pthat10->GetYaxis()->GetNbins()+1
    );

    double n_beamA_pthat10_20toInf = refpt_vs_pthat_beamA_pthat10->Integral(
        refpt_vs_pthat_beamA_pthat10->GetXaxis()->FindBin(20), 
        refpt_vs_pthat_beamA_pthat10->GetXaxis()->GetNbins()+1,
        1,
        refpt_vs_pthat_beamA_pthat10->GetYaxis()->GetNbins()+1
    );

    double n_beamA_pthat20_20toInf = refpt_vs_pthat_beamA_pthat20->Integral(
        refpt_vs_pthat_beamA_pthat20->GetXaxis()->FindBin(20), 
        refpt_vs_pthat_beamA_pthat20->GetXaxis()->GetNbins()+1,
        1,
        refpt_vs_pthat_beamA_pthat20->GetYaxis()->GetNbins()+1
    );

    double n_beamA_10to20 = n_beamA_pthat10_10to20;
    double n_beamA_20toInf = n_beamA_pthat10_20toInf + n_beamA_pthat20_20toInf;

    std::cout << "Beam A" 
              << "\n\t10 < pthat < 20: " <<  n_beamA_10to20
              << "\n\t20 < pthat < #infty: " << n_beamA_20toInf
              << std::endl;

    double n_beamB_pthat10_10to20 = refpt_vs_pthat_beamB_pthat10->Integral(
        refpt_vs_pthat_beamB_pthat10->GetXaxis()->FindBin(10), 
        refpt_vs_pthat_beamB_pthat10->GetXaxis()->FindBin(20)-1,
        1,
        refpt_vs_pthat_beamB_pthat10->GetYaxis()->GetNbins()+1
    );

    double n_beamB_pthat10_20toInf = refpt_vs_pthat_beamB_pthat10->Integral(
        refpt_vs_pthat_beamB_pthat10->GetXaxis()->FindBin(20), 
        refpt_vs_pthat_beamB_pthat10->GetXaxis()->GetNbins()+1,
        1,
        refpt_vs_pthat_beamB_pthat10->GetYaxis()->GetNbins()+1
    );

    double n_beamB_pthat20_20toInf = refpt_vs_pthat_beamB_pthat20->Integral(
        refpt_vs_pthat_beamB_pthat20->GetXaxis()->FindBin(20), 
        refpt_vs_pthat_beamB_pthat20->GetXaxis()->GetNbins()+1,
        1,
        refpt_vs_pthat_beamB_pthat20->GetYaxis()->GetNbins()+1
    );

    double n_beamB_10to20 = n_beamB_pthat10_10to20;
    double n_beamB_20toInf = n_beamB_pthat10_20toInf + n_beamB_pthat20_20toInf;

    std::cout << "Beam B" 
              << "\n\t10 < pthat < 20: " <<  n_beamB_10to20
              << "\n\t20 < pthat < #infty: " << n_beamB_20toInf
              << std::endl;

    // Make projections
    TH1F *pthat_beamA_pthat10 = (TH1F *) refpt_vs_pthat_beamA_pthat10->ProjectionX("pthat_beamA_pthat10");
    TH1F *pthat_beamA_pthat20 = (TH1F *) refpt_vs_pthat_beamA_pthat20->ProjectionX("pthat_beamA_pthat20");
    TH1F *pthat_beamB_pthat10 = (TH1F *) refpt_vs_pthat_beamB_pthat10->ProjectionX("pthat_beamB_pthat10");
    TH1F *pthat_beamB_pthat20 = (TH1F *) refpt_vs_pthat_beamB_pthat20->ProjectionX("pthat_beamB_pthat20");
    TH1F *refpt_beamA_pthat10 = (TH1F *) refpt_vs_pthat_beamA_pthat10->ProjectionY("refpt_beamA_pthat10");
    TH1F *refpt_beamA_pthat20 = (TH1F *) refpt_vs_pthat_beamA_pthat20->ProjectionY("refpt_beamA_pthat20");
    TH1F *refpt_beamB_pthat10 = (TH1F *) refpt_vs_pthat_beamB_pthat10->ProjectionY("refpt_beamB_pthat10");
    TH1F *refpt_beamB_pthat20 = (TH1F *) refpt_vs_pthat_beamB_pthat20->ProjectionY("refpt_beamB_pthat20");

    // Draw pthat
    TCanvas *c_pthat = new TCanvas("c_pthat", "", 700, 600);
    c_pthat->SetLogy();
    formatCanvas(c_pthat);
    formatHisto(pthat_beamA_pthat10, "#hat{p_{T}} (GeV)", cmsBlue);
    formatHisto(pthat_beamA_pthat20, "#hat{p_{T}} (GeV)", cmsLightBlue);
    formatHisto(pthat_beamB_pthat10, "#hat{p_{T}} (GeV)", cmsOrange);
    formatHisto(pthat_beamB_pthat20, "#hat{p_{T}} (GeV)", cmsYellow);
    pthat_beamB_pthat10->SetLineStyle(2);
    pthat_beamB_pthat20->SetLineStyle(2);
    pthat_beamA_pthat10->Draw("hist");
    pthat_beamA_pthat20->Draw("hist same");
    pthat_beamB_pthat10->Draw("hist same");
    pthat_beamB_pthat20->Draw("hist same");
    drawHeader();

    TLegend *leg = new TLegend(0.4, 0.55, 0.85, 0.7);
    leg->SetTextSize(22);
    // leg->SetHeader("Leading jet p_{T}^{ref} > 5 GeV");
    leg->SetNColumns(2);
    leg->AddEntry(pthat_beamA_pthat10, "#hat{p_{T}}>10", "l");
    leg->AddEntry(pthat_beamB_pthat10, "#hat{p_{T}}>10", "l");
    leg->AddEntry(pthat_beamA_pthat20, "#hat{p_{T}}>20", "l");
    leg->AddEntry(pthat_beamB_pthat20, "#hat{p_{T}}>20", "l");
    leg->Draw();

    TLatex *latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(22);
    latex->DrawLatex(0.4, 0.8, "AK4, p_{T}^{ref,lead} > 5 GeV");
    latex->DrawLatex(0.4, 0.7, "PhotonBeam A     PhotonBeam B");

    // Draw refpt
    TCanvas *c_refpt = new TCanvas("c_refpt", "", 700, 600);
    c_refpt->SetLogy();
    formatCanvas(c_refpt);
    formatHisto(refpt_beamA_pthat10, "p_{T}^{ref}", cmsBlue);
    formatHisto(refpt_beamA_pthat20, "p_{T}^{ref}", cmsLightBlue);
    formatHisto(refpt_beamB_pthat10, "p_{T}^{ref}", cmsOrange);
    formatHisto(refpt_beamB_pthat20, "p_{T}^{ref}", cmsYellow);
    refpt_beamB_pthat10->SetLineStyle(2);
    refpt_beamB_pthat20->SetLineStyle(2);
    refpt_beamA_pthat10->GetXaxis()->SetTitle("Leading jet p_{T}^{ref} (GeV)");
    refpt_beamA_pthat10->Draw("hist");
    refpt_beamA_pthat20->Draw("hist same");
    refpt_beamB_pthat10->Draw("hist same");
    refpt_beamB_pthat20->Draw("hist same");
    drawHeader();
    leg->Draw();

    TLatex *latex2 = new TLatex();
    latex2->SetNDC();
    latex2->SetTextSize(22);
    latex2->DrawLatex(0.4, 0.8, "AK4, p_{T}^{ref,lead} > 5 GeV");
    latex2->DrawLatex(0.4, 0.7, "PhotonBeam A     PhotonBeam B");
}