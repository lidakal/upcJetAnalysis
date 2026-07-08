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

void draw_PF_in_HF_distribution()
{
    gStyle->SetLegendTextSize(24);
    gStyle->SetLabelSize(24, "XYZ");
    gStyle->SetTitleSize(28, "XYZ");

    TString sample = "hiforward0_2024rereco";
    TFile *fin = new TFile("histos/"+sample+"_pf_in_hf_distribution.root");
    TH3F *h_PF_HFp_Emax = (TH3F *) fin->Get("h_PF_HFp_Emax");
    TH3F *h_PF_HFm_Emax = (TH3F *) fin->Get("h_PF_HFm_Emax");

    // Make projections
    TH1F *h_PF_HFp_Emax_E = (TH1F *) h_PF_HFp_Emax->ProjectionZ("h_PF_HFp_Emax_E");
    TH1F *h_PF_HFm_Emax_E = (TH1F *) h_PF_HFm_Emax->ProjectionZ("h_PF_HFm_Emax_E");

    // Normalize
    for (auto h : {h_PF_HFp_Emax_E, h_PF_HFm_Emax_E}) {
        h->Scale(1/h->Integral());
    }

    // Format
    h_PF_HFp_Emax_E->SetLineColor(cmsOrange);
    h_PF_HFp_Emax_E->SetFillColorAlpha(cmsOrange, 0.5);
    h_PF_HFp_Emax_E->SetFillStyle(3004);

    h_PF_HFm_Emax_E->SetLineColor(cmsBlue);
    h_PF_HFm_Emax_E->SetFillColorAlpha(cmsBlue, 0.5);
    h_PF_HFm_Emax_E->SetFillStyle(3005);

    // Legend
    TLegend *leg_E = new TLegend(0.6, 0.7, 0.75, 0.85);
    leg_E->SetBorderSize(0);
    leg_E->SetFillStyle(0);
    leg_E->SetHeader("Empty bunch crossing");
    leg_E->AddEntry(h_PF_HFp_Emax_E, "HF+", "f");
    leg_E->AddEntry(h_PF_HFm_Emax_E, "HF-", "f");
    
    // Draw
    TCanvas *c_E = new TCanvas("c_E", "", 800, 700);
    c_E->SetTopMargin(0.1);
    c_E->SetBottomMargin(0.1);
    c_E->SetLeftMargin(0.15);
    c_E->SetRightMargin(0.05);
    
    h_PF_HFp_Emax_E->GetXaxis()->SetTitle("PF E^{max}");
    h_PF_HFp_Emax_E->GetYaxis()->SetTitle("Normalized distribution");
    h_PF_HFp_Emax_E->GetXaxis()->SetRangeUser(0.,20.);
    h_PF_HFp_Emax_E->GetYaxis()->SetRangeUser(1e-6, 1.);
    h_PF_HFp_Emax_E->Draw("hist");
    h_PF_HFm_Emax_E->Draw("hist same");
    c_E->SetLogy();
    leg_E->Draw();
    draw_header();

    c_E->Print("plots/"+sample+"_pf_in_hf_distribution.pdf");
    c_E->Print("plots/"+sample+"_pf_in_hf_distribution.png");

    // Cumulative distribution 
    TH1F *h_PF_HFp_Emax_Ecum = (TH1F *) h_PF_HFp_Emax_E->Clone("h_PF_HFp_Emax_Ecum");
    TH1F *h_PF_HFm_Emax_Ecum = (TH1F *) h_PF_HFm_Emax_E->Clone("h_PF_HFm_Emax_Ecum");
    for (Int_t ibin=0; ibin<h_PF_HFp_Emax_Ecum->GetNbinsX(); ibin++) {
        h_PF_HFp_Emax_Ecum->SetBinContent(ibin, h_PF_HFp_Emax_E->Integral(ibin, h_PF_HFp_Emax_E->GetNbinsX()+1));
        h_PF_HFm_Emax_Ecum->SetBinContent(ibin, h_PF_HFm_Emax_E->Integral(ibin, h_PF_HFm_Emax_E->GetNbinsX()+1));
    }

    // Draw
    TCanvas *c_Ecum = new TCanvas("c_Ecum", "", 800, 700);
    c_Ecum->SetTopMargin(0.1);
    c_Ecum->SetBottomMargin(0.1);
    c_Ecum->SetLeftMargin(0.15);
    c_Ecum->SetRightMargin(0.05);
    
    h_PF_HFp_Emax_Ecum->GetXaxis()->SetTitle("PF E^{max}");
    h_PF_HFp_Emax_Ecum->GetYaxis()->SetTitle("Cumulative distribution");
    h_PF_HFp_Emax_Ecum->GetXaxis()->SetRangeUser(0.,20.);
    h_PF_HFp_Emax_Ecum->GetYaxis()->SetRangeUser(1e-6, 5.);
    h_PF_HFp_Emax_Ecum->Draw("hist");
    h_PF_HFm_Emax_Ecum->Draw("hist same");
    c_Ecum->SetLogy();
    leg_E->Draw();
    draw_header();

    c_Ecum->Print("plots/"+sample+"_pf_in_hf_cumulative_distribution.pdf");
    c_Ecum->Print("plots/"+sample+"_pf_in_hf_cumulative_distribution.png");

}