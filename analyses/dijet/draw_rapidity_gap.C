#include "../../cms_palette.h"

void draw_header() 
{
    TLatex *cms = new TLatex();
    cms->SetNDC();
    cms->SetTextAlign(11);
    cms->SetTextSize(24);
    cms->DrawLatex(0.15, 0.92, "#bf{CMS} #it{Internal}");

    TLatex *data = new TLatex();
    data->SetNDC();
    data->SetTextAlign(31);
    data->SetTextSize(24);
    data->DrawLatex(0.8, 0.92, "2023 PbPb (5.36 TeV)");
}

void draw_header_simulation() 
{
    TLatex *cms = new TLatex();
    cms->SetNDC();
    cms->SetTextAlign(11);
    cms->SetTextSize(24);
    cms->DrawLatex(0.15, 0.92, "#bf{CMS} #it{Internal Simulation}");

    TLatex *data = new TLatex();
    data->SetNDC();
    data->SetTextAlign(31);
    data->SetTextSize(24);
    data->DrawLatex(0.8, 0.92, "PYTHIA8 (Pb-#gamma 5.36 TeV)");
}

void draw_rapidity_gap()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetLegendTextSize(24);
    gStyle->SetLabelSize(24, "XYZ");
    gStyle->SetTitleSize(28, "XYZ");

    TString sample = "beamB_diffraction_pthat10";
    // TString sample = "hiforwardAll_2024rereco";
    TString suffix = "_oppHF_oppEC2_trkLim2p5_ptgr0p2_chOnly_jetID_jetVM";
    TFile *fin = new TFile("histos/"+sample+"_pf_distribution"+suffix+".root"); // requires plot_PF_distribution*.C

    TH2F *h_rapgap_Emax_tracker = (TH2F *) fin->Get("h_rapgap_fb_Emax_tracker");
    TH2F *h_rapgap_Etamax_tracker = (TH2F *) fin->Get("h_rapgap_fb_Etamax_tracker");
    TH3F *h_Nch_vs_rapgap_Etamax_tracker_wSwap = (TH3F *) fin->Get("h_Nch_vs_rapgap_fb_Etamax_tracker_wSwap");
    h_Nch_vs_rapgap_Etamax_tracker_wSwap->GetXaxis()->SetRange(0, h_Nch_vs_rapgap_Etamax_tracker_wSwap->GetNbinsX()+1);
    TH2F *h_rapgap_Etamax_tracker_wSwap = (TH2F *) h_Nch_vs_rapgap_Etamax_tracker_wSwap->Project3D("zy");

    // Format
    for (auto h : {
        h_rapgap_Emax_tracker, h_rapgap_Etamax_tracker, h_rapgap_Etamax_tracker_wSwap
    }) {
        h->Scale(1/h->Integral());
        h->GetZaxis()->SetRangeUser(0., 0.05);
        h->GetXaxis()->SetTitle("#Delta#eta^{+}");
        h->GetYaxis()->SetTitle("#Delta#eta^{-}");
        h->GetZaxis()->SetTitle("Normalized entries per event");
        h->GetZaxis()->SetTitleOffset(1.7);
        h->GetXaxis()->SetRangeUser(0., 5.);
        h->GetYaxis()->SetRangeUser(0., 5.);
    }

    // Draw
    TCanvas *c_rapgap_Emax = new TCanvas("c_rapgap_Emax", "x=FRG, y=BRG, Emax", 800, 700);
    c_rapgap_Emax->SetTopMargin(0.1);
    c_rapgap_Emax->SetBottomMargin(0.15);
    c_rapgap_Emax->SetLeftMargin(0.15);
    c_rapgap_Emax->SetRightMargin(0.2);

    h_rapgap_Emax_tracker->Draw("colz");
    if (sample.Contains("hiforward")) draw_header();
    else draw_header_simulation();

    c_rapgap_Emax->Print("plots/"+sample+"_rapgap_Emax.pdf");

    TCanvas *c_rapgap_Etamax = new TCanvas("c_rapgap_Etamax", "x=FRG, y=BRG, Etamax", 800, 700);
    c_rapgap_Etamax->SetTopMargin(0.1);
    c_rapgap_Etamax->SetBottomMargin(0.15);
    c_rapgap_Etamax->SetLeftMargin(0.15);
    c_rapgap_Etamax->SetRightMargin(0.2);

    h_rapgap_Etamax_tracker->Draw("colz");
    if (sample.Contains("hiforward")) draw_header();
    else draw_header_simulation();

    c_rapgap_Etamax->Print("plots/"+sample+"_rapgap_Etamax.pdf");
    
    TCanvas *c_rapgap_Etamax_wSwap = new TCanvas("c_rapgap_Etamax_wSwap", "x=FRG, y=BRG, Etamax", 800, 700);
    c_rapgap_Etamax_wSwap->SetTopMargin(0.1);
    c_rapgap_Etamax_wSwap->SetBottomMargin(0.15);
    c_rapgap_Etamax_wSwap->SetLeftMargin(0.15);
    c_rapgap_Etamax_wSwap->SetRightMargin(0.2);

    h_rapgap_Etamax_tracker_wSwap->GetXaxis()->SetTitle("#Delta#eta^{F}");
    h_rapgap_Etamax_tracker_wSwap->GetYaxis()->SetTitle("#Delta#eta^{B}");
    h_rapgap_Etamax_tracker_wSwap->Draw("colz");
    if (sample.Contains("hiforward")) draw_header();
    else draw_header_simulation();

    c_rapgap_Etamax_wSwap->Print("plots/"+sample+"_rapgap_Etamax_wSwap.pdf");
}