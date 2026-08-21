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

void draw_PF_distribution_data_vs_MC()
{
    gStyle->SetLegendTextSize(24);
    gStyle->SetLabelSize(24, "XYZ");
    gStyle->SetTitleSize(28, "XYZ");

    // Load histograms

    TFile *fin_data = new TFile("histos/hiforwardAll_2024rereco_pf_distribution.root"); // requires plot_PF_distribution.C
    
    TH3F *h_PF_data = (TH3F *) fin_data->Get("h_PF")->Clone("h_PF_data");
    TH3F *h_PF_forward_data = (TH3F *) fin_data->Get("h_PF_forward")->Clone("h_PF_forward_data");
    TH3F *h_PF_backward_data = (TH3F *) fin_data->Get("h_PF_backward")->Clone("h_PF_backward_data");

    TH3F *h_PF_forward_Emax_data = (TH3F *) fin_data->Get("h_PF_forward_Emax")->Clone("h_PF_forward_Emax_data");
    TH3F *h_PF_backward_Emax_data = (TH3F *) fin_data->Get("h_PF_backward_Emax")->Clone("h_PF_backward_Emax_data");

    TH3F *h_PF_forward_Etamax_data = (TH3F *) fin_data->Get("h_PF_forward_Etamax")->Clone("h_PF_forward_Etamax_data");
    TH3F *h_PF_backward_Etamax_data = (TH3F *) fin_data->Get("h_PF_backward_Etamax")->Clone("h_PF_backward_Etamax_data");

    TFile *fin_beamB = new TFile("histos/beamB_diffraction_pthat10_pf_distribution.root"); // requires plot_PF_distribution.C
    
    TH3F *h_PF_beamB = (TH3F *) fin_beamB->Get("h_PF")->Clone("h_PF_beamB");
    TH3F *h_PF_forward_beamB = (TH3F *) fin_beamB->Get("h_PF_forward")->Clone("h_PF_forward_beamB");
    TH3F *h_PF_backward_beamB = (TH3F *) fin_beamB->Get("h_PF_backward")->Clone("h_PF_backward_beamB");

    TH3F *h_PF_forward_Emax_beamB = (TH3F *) fin_beamB->Get("h_PF_forward_Emax")->Clone("h_PF_forward_Emax_beamB");
    TH3F *h_PF_backward_Emax_beamB = (TH3F *) fin_beamB->Get("h_PF_backward_Emax")->Clone("h_PF_backward_Emax_beamB");

    TH3F *h_PF_forward_Etamax_beamB = (TH3F *) fin_beamB->Get("h_PF_forward_Etamax")->Clone("h_PF_forward_Etamax_beamB");
    TH3F *h_PF_backward_Etamax_beamB = (TH3F *) fin_beamB->Get("h_PF_backward_Etamax")->Clone("h_PF_backward_Etamax_beamB");

    // Make eta projections

    TH1F *h_PF_data_eta = (TH1F *) h_PF_data->ProjectionX("h_PF_data_eta");
    TH1F *h_PF_forward_data_eta = (TH1F *) h_PF_forward_data->ProjectionX("h_PF_forward_data_eta");
    TH1F *h_PF_backward_data_eta = (TH1F *) h_PF_backward_data->ProjectionX("h_PF_backward_data_eta");

    TH1F *h_PF_forward_Emax_data_eta = (TH1F *) h_PF_forward_Emax_data->ProjectionX("h_PF_forward_Emax_data_eta");
    TH1F *h_PF_backward_Emax_data_eta = (TH1F *) h_PF_backward_Emax_data->ProjectionX("h_PF_backward_Emax_data_eta");

    TH1F *h_PF_forward_Etamax_data_eta = (TH1F *) h_PF_forward_Etamax_data->ProjectionX("h_PF_forward_Etamax_data_eta");
    TH1F *h_PF_backward_Etamax_data_eta = (TH1F *) h_PF_backward_Etamax_data->ProjectionX("h_PF_backward_Etamax_data_eta");

    TH1F *h_PF_beamB_eta = (TH1F *) h_PF_beamB->ProjectionX("h_PF_beamB_eta");
    TH1F *h_PF_forward_beamB_eta = (TH1F *) h_PF_forward_beamB->ProjectionX("h_PF_forward_beamB_eta");
    TH1F *h_PF_backward_beamB_eta = (TH1F *) h_PF_backward_beamB->ProjectionX("h_PF_backward_beamB_eta");

    TH1F *h_PF_forward_Emax_beamB_eta = (TH1F *) h_PF_forward_Emax_beamB->ProjectionX("h_PF_forward_Emax_beamB_eta");
    TH1F *h_PF_backward_Emax_beamB_eta = (TH1F *) h_PF_backward_Emax_beamB->ProjectionX("h_PF_backward_Emax_beamB_eta");

    TH1F *h_PF_forward_Etamax_beamB_eta = (TH1F *) h_PF_forward_Etamax_beamB->ProjectionX("h_PF_forward_Etamax_beamB_eta");
    TH1F *h_PF_backward_Etamax_beamB_eta = (TH1F *) h_PF_backward_Etamax_beamB->ProjectionX("h_PF_backward_Etamax_beamB_eta");

    // Make phi projections

    TH1F *h_PF_data_phi = (TH1F *) h_PF_data->ProjectionY("h_PF_data_phi");
    TH1F *h_PF_forward_data_phi = (TH1F *) h_PF_forward_data->ProjectionY("h_PF_forward_data_phi");
    TH1F *h_PF_backward_data_phi = (TH1F *) h_PF_backward_data->ProjectionY("h_PF_backward_data_phi");

    TH1F *h_PF_forward_Emax_data_phi = (TH1F *) h_PF_forward_Emax_data->ProjectionY("h_PF_forward_Emax_data_phi");
    TH1F *h_PF_backward_Emax_data_phi = (TH1F *) h_PF_backward_Emax_data->ProjectionY("h_PF_backward_Emax_data_phi");

    TH1F *h_PF_forward_Etamax_data_phi = (TH1F *) h_PF_forward_Etamax_data->ProjectionY("h_PF_forward_Etamax_data_phi");
    TH1F *h_PF_backward_Etamax_data_phi = (TH1F *) h_PF_backward_Etamax_data->ProjectionY("h_PF_backward_Etamax_data_phi");

    TH1F *h_PF_beamB_phi = (TH1F *) h_PF_beamB->ProjectionY("h_PF_beamB_phi");
    TH1F *h_PF_forward_beamB_phi = (TH1F *) h_PF_forward_beamB->ProjectionY("h_PF_forward_beamB_phi");
    TH1F *h_PF_backward_beamB_phi = (TH1F *) h_PF_backward_beamB->ProjectionY("h_PF_backward_beamB_phi");

    TH1F *h_PF_forward_Emax_beamB_phi = (TH1F *) h_PF_forward_Emax_beamB->ProjectionY("h_PF_forward_Emax_beamB_phi");
    TH1F *h_PF_backward_Emax_beamB_phi = (TH1F *) h_PF_backward_Emax_beamB->ProjectionY("h_PF_backward_Emax_beamB_phi");

    TH1F *h_PF_forward_Etamax_beamB_phi = (TH1F *) h_PF_forward_Etamax_beamB->ProjectionY("h_PF_forward_Etamax_beamB_phi");
    TH1F *h_PF_backward_Etamax_beamB_phi = (TH1F *) h_PF_backward_Etamax_beamB->ProjectionY("h_PF_backward_Etamax_beamB_phi");

    // Make E projections

    TH1F *h_PF_data_E = (TH1F *) h_PF_data->ProjectionZ("h_PF_data_E");
    TH1F *h_PF_forward_data_E = (TH1F *) h_PF_forward_data->ProjectionZ("h_PF_forward_data_E");
    TH1F *h_PF_backward_data_E = (TH1F *) h_PF_backward_data->ProjectionZ("h_PF_backward_data_E");

    TH1F *h_PF_forward_Emax_data_E = (TH1F *) h_PF_forward_Emax_data->ProjectionZ("h_PF_forward_Emax_data_E");
    TH1F *h_PF_backward_Emax_data_E = (TH1F *) h_PF_backward_Emax_data->ProjectionZ("h_PF_backward_Emax_data_E");

    TH1F *h_PF_forward_Etamax_data_E = (TH1F *) h_PF_forward_Etamax_data->ProjectionZ("h_PF_forward_Etamax_data_E");
    TH1F *h_PF_backward_Etamax_data_E = (TH1F *) h_PF_backward_Etamax_data->ProjectionZ("h_PF_backward_Etamax_data_E");

    TH1F *h_PF_beamB_E = (TH1F *) h_PF_beamB->ProjectionZ("h_PF_beamB_E");
    TH1F *h_PF_forward_beamB_E = (TH1F *) h_PF_forward_beamB->ProjectionZ("h_PF_forward_beamB_E");
    TH1F *h_PF_backward_beamB_E = (TH1F *) h_PF_backward_beamB->ProjectionZ("h_PF_backward_beamB_E");

    TH1F *h_PF_forward_Emax_beamB_E = (TH1F *) h_PF_forward_Emax_beamB->ProjectionZ("h_PF_forward_Emax_beamB_E");
    TH1F *h_PF_backward_Emax_beamB_E = (TH1F *) h_PF_backward_Emax_beamB->ProjectionZ("h_PF_backward_Emax_beamB_E");

    TH1F *h_PF_forward_Etamax_beamB_E = (TH1F *) h_PF_forward_Etamax_beamB->ProjectionZ("h_PF_forward_Etamax_beamB_E");
    TH1F *h_PF_backward_Etamax_beamB_E = (TH1F *) h_PF_backward_Etamax_beamB->ProjectionZ("h_PF_backward_Etamax_beamB_E");

    // Normalize

    for (auto h : {
        h_PF_data_eta, 
        h_PF_forward_data_eta, h_PF_backward_data_eta,
        h_PF_forward_Emax_data_eta, h_PF_backward_Emax_data_eta,
        h_PF_forward_Etamax_data_eta, h_PF_backward_Etamax_data_eta,
        h_PF_data_E, 
        h_PF_forward_data_E, h_PF_backward_data_E,
        h_PF_forward_Emax_data_E, h_PF_backward_Emax_data_E,
        h_PF_forward_Etamax_data_E, h_PF_backward_Etamax_data_E,
        h_PF_beamB_eta, 
        h_PF_forward_beamB_eta, h_PF_backward_beamB_eta,
        h_PF_forward_Emax_beamB_eta, h_PF_backward_Emax_beamB_eta,
        h_PF_forward_Etamax_beamB_eta, h_PF_backward_Etamax_beamB_eta,
        h_PF_beamB_E, 
        h_PF_forward_beamB_E, h_PF_backward_beamB_E,
        h_PF_forward_Emax_beamB_E, h_PF_backward_Emax_beamB_E,
        h_PF_forward_Etamax_beamB_E, h_PF_backward_Etamax_beamB_E,
    }) {
        h->Rebin(2);
    }

    for (auto h : {
        h_PF_data_eta, 
        h_PF_forward_data_eta, h_PF_backward_data_eta,
        h_PF_forward_Emax_data_eta, h_PF_backward_Emax_data_eta,
        h_PF_forward_Etamax_data_eta, h_PF_backward_Etamax_data_eta,
        h_PF_data_phi, 
        h_PF_forward_data_phi, h_PF_backward_data_phi,
        h_PF_forward_Emax_data_phi, h_PF_backward_Emax_data_phi,
        h_PF_forward_Etamax_data_phi, h_PF_backward_Etamax_data_phi,
        h_PF_data_E, 
        h_PF_forward_data_E, h_PF_backward_data_E,
        h_PF_forward_Emax_data_E, h_PF_backward_Emax_data_E,
        h_PF_forward_Etamax_data_E, h_PF_backward_Etamax_data_E,
        h_PF_beamB_eta, 
        h_PF_forward_beamB_eta, h_PF_backward_beamB_eta,
        h_PF_forward_Emax_beamB_eta, h_PF_backward_Emax_beamB_eta,
        h_PF_forward_Etamax_beamB_eta, h_PF_backward_Etamax_beamB_eta,
        h_PF_beamB_phi, 
        h_PF_forward_beamB_phi, h_PF_backward_beamB_phi,
        h_PF_forward_Emax_beamB_phi, h_PF_backward_Emax_beamB_phi,
        h_PF_forward_Etamax_beamB_phi, h_PF_backward_Etamax_beamB_phi,
        h_PF_beamB_E, 
        h_PF_forward_beamB_E, h_PF_backward_beamB_E,
        h_PF_forward_Emax_beamB_E, h_PF_backward_Emax_beamB_E,
        h_PF_forward_Etamax_beamB_E, h_PF_backward_Etamax_beamB_E,
    }) {
        h->Scale(1/h->Integral());
        h->SetLineWidth(2);
    }

    // Format 
    for (auto h : {
        h_PF_data_eta,
        h_PF_data_phi,
        h_PF_data_E,
        h_PF_beamB_eta,
        h_PF_beamB_phi,
        h_PF_beamB_E,
    }) {
        h->SetMarkerColor(kBlack);
        h->SetLineColor(kBlack);
    }

    for (auto h : {
        h_PF_forward_data_eta,
        h_PF_forward_Emax_data_eta,
        h_PF_forward_Etamax_data_eta,
        h_PF_forward_data_phi,
        h_PF_forward_Emax_data_phi,
        h_PF_forward_Etamax_data_phi,
        h_PF_forward_data_E,
        h_PF_forward_Emax_data_E,
        h_PF_forward_Etamax_data_E,
        h_PF_forward_beamB_eta,
        h_PF_forward_Emax_beamB_eta,
        h_PF_forward_Etamax_beamB_eta,
        h_PF_forward_beamB_phi,
        h_PF_forward_Emax_beamB_phi,
        h_PF_forward_Etamax_beamB_phi,
        h_PF_forward_beamB_E,
        h_PF_forward_Emax_beamB_E,
        h_PF_forward_Etamax_beamB_E,
    }) {
        h->SetMarkerColor(cmsBlue);
        h->SetLineColor(cmsBlue);
    }

    for (auto h : {
        h_PF_backward_data_eta,
        h_PF_backward_Emax_data_eta,
        h_PF_backward_Etamax_data_eta,
        h_PF_backward_data_phi,
        h_PF_backward_Emax_data_phi,
        h_PF_backward_Etamax_data_phi,
        h_PF_backward_data_E,
        h_PF_backward_Emax_data_E,
        h_PF_backward_Etamax_data_E,
        h_PF_backward_beamB_eta,
        h_PF_backward_Emax_beamB_eta,
        h_PF_backward_Etamax_beamB_eta,
        h_PF_backward_beamB_phi,
        h_PF_backward_Emax_beamB_phi,
        h_PF_backward_Etamax_beamB_phi,
        h_PF_backward_beamB_E,
        h_PF_backward_Emax_beamB_E,
        h_PF_backward_Etamax_beamB_E,
    }) {
        h->SetMarkerColor(cmsOrange);
        h->SetLineColor(cmsOrange);
    }

    // Legend
    TLegend *leg_eta = new TLegend(0.2, 0.7, 0.6, 0.85);
    leg_eta->SetBorderSize(0);
    leg_eta->SetFillStyle(0);
    leg_eta->SetNColumns(2);
    leg_eta->AddEntry(new TH1F(), "Data", "");
    leg_eta->AddEntry(new TH1F(), "MC", "");
    leg_eta->AddEntry(h_PF_forward_data_eta, "Forward", "p");
    leg_eta->AddEntry(h_PF_forward_beamB_eta, "Forward", "l");
    leg_eta->AddEntry(h_PF_backward_data_eta, "Backward", "p");
    leg_eta->AddEntry(h_PF_backward_beamB_eta, "Backward", "l");
    
    // Draw
    TCanvas *c_pf = new TCanvas("c_pf", "", 2400, 800);
    // c_pf->SetTopMargin(0.1);
    // c_pf->SetBottomMargin(0.1);
    // c_pf->SetLeftMargin(0.15);
    // c_pf->SetRightMargin(0.05);
    c_pf->Divide(3,1);

    c_pf->cd(1);
    h_PF_forward_data_eta->GetXaxis()->SetTitle("#eta^{PF}");
    h_PF_forward_data_eta->GetYaxis()->SetTitle("Normalized distribution (per PF cand.)");
    h_PF_forward_data_eta->GetXaxis()->SetTitleOffset(1.2);
    h_PF_forward_data_eta->GetYaxis()->SetRangeUser(0., 0.25);
    h_PF_forward_data_eta->Draw("same");
    h_PF_backward_data_eta->Draw("same");
    h_PF_forward_beamB_eta->Draw("hist same");
    h_PF_backward_beamB_eta->Draw("hist same");
    leg_eta->Draw();

    c_pf->cd(2);
    h_PF_forward_data_phi->GetXaxis()->SetTitle("#phi^{PF}");
    h_PF_forward_data_phi->GetYaxis()->SetTitle("Normalized distribution (per PF cand.)");
    h_PF_forward_data_phi->GetXaxis()->SetTitleOffset(1.2);
    h_PF_forward_data_phi->GetYaxis()->SetRangeUser(0., 0.2);
    h_PF_forward_data_phi->Draw("same");
    h_PF_backward_data_phi->Draw("same");
    h_PF_forward_beamB_phi->Draw("hist same");
    h_PF_backward_beamB_phi->Draw("hist same");
    leg_eta->Draw();

    c_pf->cd(3);
    h_PF_forward_data_E->GetXaxis()->SetTitle("E^{PF} (GeV)");
    h_PF_forward_data_E->GetYaxis()->SetTitle("Normalized distribution (per PF cand.)");
    h_PF_forward_data_E->GetXaxis()->SetTitleOffset(1.2);
    h_PF_forward_data_E->GetYaxis()->SetRangeUser(0., 0.45);
    h_PF_forward_data_E->Draw("same");
    h_PF_backward_data_E->Draw("same");
    h_PF_forward_beamB_E->Draw("hist same");
    h_PF_backward_beamB_E->Draw("hist same");
    leg_eta->Draw();

    c_pf->Print("plots/data_vs_MC_pf_distribution.pdf");
    c_pf->Print("plots/data_vs_MC_pf_distribution.png");

    TCanvas *c_pf_Emax = new TCanvas("c_pf_Emax", "", 2400, 800);
    // c_pf_Emax->SetTopMargin(0.1);
    // c_pf_Emax->SetBottomMargin(0.1);
    // c_pf_Emax->SetLeftMargin(0.15);
    // c_pf_Emax->SetRightMargin(0.05);
    c_pf_Emax->Divide(3,1);

    c_pf_Emax->cd(1);    
    h_PF_forward_Emax_data_eta->GetXaxis()->SetTitle("#eta^{PF}");
    h_PF_forward_Emax_data_eta->GetYaxis()->SetTitle("Normalized distribution (per event)");
    h_PF_forward_Emax_data_eta->GetXaxis()->SetTitleOffset(1.2);
    h_PF_forward_Emax_data_eta->GetYaxis()->SetRangeUser(0., 0.25);
    h_PF_forward_Emax_data_eta->Draw("same");
    h_PF_backward_Emax_data_eta->Draw("same");
    h_PF_forward_Emax_beamB_eta->Draw("hist same");
    h_PF_backward_Emax_beamB_eta->Draw("hist same");
    leg_eta->Draw();

    c_pf_Emax->cd(2);
    h_PF_forward_Emax_data_phi->GetXaxis()->SetTitle("#phi^{PF}");
    h_PF_forward_Emax_data_phi->GetYaxis()->SetTitle("Normalized distribution (per event)");
    h_PF_forward_Emax_data_phi->GetXaxis()->SetTitleOffset(1.2);
    h_PF_forward_Emax_data_phi->GetYaxis()->SetRangeUser(0., 0.2);
    h_PF_forward_Emax_data_phi->Draw("same");
    h_PF_backward_Emax_data_phi->Draw("same");
    h_PF_forward_Emax_beamB_phi->Draw("hist same");
    h_PF_backward_Emax_beamB_phi->Draw("hist same");
    leg_eta->Draw();

    c_pf_Emax->cd(3);
    h_PF_forward_Emax_data_E->GetXaxis()->SetTitle("E^{PF} (GeV)");
    h_PF_forward_Emax_data_E->GetYaxis()->SetTitle("Normalized distribution (per event)");
    h_PF_forward_Emax_data_E->GetXaxis()->SetTitleOffset(1.2);
    h_PF_forward_Emax_data_E->GetYaxis()->SetRangeUser(0., 0.45);
    h_PF_forward_Emax_data_E->Draw("same");
    h_PF_backward_Emax_data_E->Draw("same");
    h_PF_forward_Emax_beamB_E->Draw("hist same");
    h_PF_backward_Emax_beamB_E->Draw("hist same");
    leg_eta->Draw();

    c_pf_Emax->Print("plots/data_vs_MC_pf_Emax_distribution.pdf");
    c_pf_Emax->Print("plots/data_vs_MC_pf_Emax_distribution.png");

    TCanvas *c_pf_Etamax = new TCanvas("c_pf_Etamax", "", 2400, 800);
    // c_pf_Etamax->SetTopMargin(0.1);
    // c_pf_Etamax->SetBottomMargin(0.1);
    // c_pf_Etamax->SetLeftMargin(0.15);
    // c_pf_Etamax->SetRightMargin(0.05);
    c_pf_Etamax->Divide(3,1);

    c_pf_Etamax->cd(1);    
    h_PF_forward_Etamax_data_eta->GetXaxis()->SetTitle("#eta^{PF}");
    h_PF_forward_Etamax_data_eta->GetYaxis()->SetTitle("Normalized distribution (per event)");
    h_PF_forward_Etamax_data_eta->GetXaxis()->SetTitleOffset(1.2);
    h_PF_forward_Etamax_data_eta->GetYaxis()->SetRangeUser(0., 0.25);
    h_PF_forward_Etamax_data_eta->Draw("same");
    h_PF_backward_Etamax_data_eta->Draw("same");
    h_PF_forward_Etamax_beamB_eta->Draw("hist same");
    h_PF_backward_Etamax_beamB_eta->Draw("hist same");
    leg_eta->Draw();

    c_pf_Etamax->cd(2);
    h_PF_forward_Etamax_data_phi->GetXaxis()->SetTitle("#phi^{PF}");
    h_PF_forward_Etamax_data_phi->GetYaxis()->SetTitle("Normalized distribution (per event)");
    h_PF_forward_Etamax_data_phi->GetXaxis()->SetTitleOffset(1.2);
    h_PF_forward_Etamax_data_phi->GetYaxis()->SetRangeUser(0., 0.2);
    h_PF_forward_Etamax_data_phi->Draw("same");
    h_PF_backward_Etamax_data_phi->Draw("same");
    h_PF_forward_Etamax_beamB_phi->Draw("hist same");
    h_PF_backward_Etamax_beamB_phi->Draw("hist same");
    leg_eta->Draw();

    c_pf_Etamax->cd(3);
    h_PF_forward_Etamax_data_E->GetXaxis()->SetTitle("E^{PF} (GeV)");
    h_PF_forward_Etamax_data_E->GetYaxis()->SetTitle("Normalized distribution (per event)");
    h_PF_forward_Etamax_data_E->GetXaxis()->SetTitleOffset(1.2);
    h_PF_forward_Etamax_data_E->GetYaxis()->SetRangeUser(0., 0.45);
    h_PF_forward_Etamax_data_E->Draw("same");
    h_PF_backward_Etamax_data_E->Draw("same");
    h_PF_forward_Etamax_beamB_E->Draw("hist same");
    h_PF_backward_Etamax_beamB_E->Draw("hist same");
    leg_eta->Draw();

    c_pf_Etamax->Print("plots/data_vs_MC_pf_Etamax_distribution.pdf");
    c_pf_Etamax->Print("plots/data_vs_MC_pf_Etamax_distribution.png");
}