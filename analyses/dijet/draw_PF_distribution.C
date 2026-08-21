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

void draw_PF_distribution()
{
    gStyle->SetLegendTextSize(24);
    gStyle->SetLabelSize(24, "XYZ");
    gStyle->SetTitleSize(28, "XYZ");

    // TString sample = "beamB_diffraction_pthat10";
    TString sample = "hiforwardAll_2024rereco";
    TFile *fin = new TFile("histos/"+sample+"_pf_distribution.root"); // requires plot_PF_distribution.C
    
    TH3F *h_PF = (TH3F *) fin->Get("h_PF");
    TH3F *h_PF_forward = (TH3F *) fin->Get("h_PF_forward");
    TH3F *h_PF_backward = (TH3F *) fin->Get("h_PF_backward");

    TH3F *h_PF_forward_Emax = (TH3F *) fin->Get("h_PF_forward_Emax");
    TH3F *h_PF_backward_Emax = (TH3F *) fin->Get("h_PF_backward_Emax");

    TH3F *h_PF_forward_Etamax = (TH3F *) fin->Get("h_PF_forward_Etamax");
    TH3F *h_PF_backward_Etamax = (TH3F *) fin->Get("h_PF_backward_Etamax");
    
    // Make eta projections

    TH1F *h_PF_eta = (TH1F *) h_PF->ProjectionX("h_PF_eta");
    TH1F *h_PF_forward_eta = (TH1F *) h_PF_forward->ProjectionX("h_PF_forward_eta");
    TH1F *h_PF_backward_eta = (TH1F *) h_PF_backward->ProjectionX("h_PF_backward_eta");

    TH1F *h_PF_forward_Emax_eta = (TH1F *) h_PF_forward_Emax->ProjectionX("h_PF_forward_Emax_eta");
    TH1F *h_PF_backward_Emax_eta = (TH1F *) h_PF_backward_Emax->ProjectionX("h_PF_backward_Emax_eta");

    TH1F *h_PF_forward_Etamax_eta = (TH1F *) h_PF_forward_Etamax->ProjectionX("h_PF_forward_Etamax_eta");
    TH1F *h_PF_backward_Etamax_eta = (TH1F *) h_PF_backward_Etamax->ProjectionX("h_PF_backward_Etamax_eta");

    // Make phi projections

    TH1F *h_PF_phi = (TH1F *) h_PF->ProjectionY("h_PF_phi");
    TH1F *h_PF_forward_phi = (TH1F *) h_PF_forward->ProjectionY("h_PF_forward_phi");
    TH1F *h_PF_backward_phi = (TH1F *) h_PF_backward->ProjectionY("h_PF_backward_phi");

    TH1F *h_PF_forward_Emax_phi = (TH1F *) h_PF_forward_Emax->ProjectionY("h_PF_forward_Emax_phi");
    TH1F *h_PF_backward_Emax_phi = (TH1F *) h_PF_backward_Emax->ProjectionY("h_PF_backward_Emax_phi");

    TH1F *h_PF_forward_Etamax_phi = (TH1F *) h_PF_forward_Etamax->ProjectionY("h_PF_forward_Etamax_phi");
    TH1F *h_PF_backward_Etamax_phi = (TH1F *) h_PF_backward_Etamax->ProjectionY("h_PF_backward_Etamax_phi");

    // Make E projections

    TH1F *h_PF_E = (TH1F *) h_PF->ProjectionZ("h_PF_E");
    TH1F *h_PF_forward_E = (TH1F *) h_PF_forward->ProjectionZ("h_PF_forward_E");
    TH1F *h_PF_backward_E = (TH1F *) h_PF_backward->ProjectionZ("h_PF_backward_E");

    TH1F *h_PF_forward_Emax_E = (TH1F *) h_PF_forward_Emax->ProjectionZ("h_PF_forward_Emax_E");
    TH1F *h_PF_backward_Emax_E = (TH1F *) h_PF_backward_Emax->ProjectionZ("h_PF_backward_Emax_E");

    TH1F *h_PF_forward_Etamax_E = (TH1F *) h_PF_forward_Etamax->ProjectionZ("h_PF_forward_Etamax_E");
    TH1F *h_PF_backward_Etamax_E = (TH1F *) h_PF_backward_Etamax->ProjectionZ("h_PF_backward_Etamax_E");

    // Normalize

    for (auto h : {
        h_PF_eta, 
        h_PF_forward_eta, h_PF_backward_eta,
        h_PF_forward_Emax_eta, h_PF_backward_Emax_eta,
        h_PF_forward_Etamax_eta, h_PF_backward_Etamax_eta,
        h_PF_E, 
        h_PF_forward_E, h_PF_backward_E,
        h_PF_forward_Emax_E, h_PF_backward_Emax_E,
        h_PF_forward_Etamax_E, h_PF_backward_Etamax_E,
    }) {
        h->Rebin(2);
    }

    for (auto h : {
        h_PF_eta, 
        h_PF_forward_eta, h_PF_backward_eta,
        h_PF_forward_Emax_eta, h_PF_backward_Emax_eta,
        h_PF_forward_Etamax_eta, h_PF_backward_Etamax_eta,
        h_PF_phi, 
        h_PF_forward_phi, h_PF_backward_phi,
        h_PF_forward_Emax_phi, h_PF_backward_Emax_phi,
        h_PF_forward_Etamax_phi, h_PF_backward_Etamax_phi,
        h_PF_E, 
        h_PF_forward_E, h_PF_backward_E,
        h_PF_forward_Emax_E, h_PF_backward_Emax_E,
        h_PF_forward_Etamax_E, h_PF_backward_Etamax_E,
    }) {
        h->Scale(1/h->Integral());
        h->SetLineWidth(2);
    }

    // Format 
    for (auto h : {
        h_PF_eta, h_PF_phi, h_PF_E,
    }) {
        h->SetLineColor(kBlack);
    }

    for (auto h : {
        h_PF_forward_eta,
        h_PF_forward_Emax_eta,
        h_PF_forward_Etamax_eta,
        h_PF_forward_phi,
        h_PF_forward_Emax_phi,
        h_PF_forward_Etamax_phi,
        h_PF_forward_E,
        h_PF_forward_Emax_E,
        h_PF_forward_Etamax_E,
    }) {
        h->SetLineColor(cmsBlue);
    }

    for (auto h : {
        h_PF_backward_eta,
        h_PF_backward_Emax_eta,
        h_PF_backward_Etamax_eta,
        h_PF_backward_phi,
        h_PF_backward_Emax_phi,
        h_PF_backward_Etamax_phi,
        h_PF_backward_E,
        h_PF_backward_Emax_E,
        h_PF_backward_Etamax_E,
    }) {
        h->SetLineColor(cmsOrange);
    }

    // Legend
    TLegend *leg_eta = new TLegend(0.2, 0.7, 0.6, 0.85);
    leg_eta->SetBorderSize(0);
    leg_eta->SetFillStyle(0);
    leg_eta->AddEntry(h_PF_eta, "All PF", "l");
    leg_eta->AddEntry(h_PF_forward_eta, "Forward PF (out of dijet)", "l");
    leg_eta->AddEntry(h_PF_backward_eta, "Backward PF (out of dijet)", "l");
    
    // Draw
    TCanvas *c_pf = new TCanvas("c_pf", "", 2400, 800);
    // c_pf->SetTopMargin(0.1);
    // c_pf->SetBottomMargin(0.1);
    // c_pf->SetLeftMargin(0.15);
    // c_pf->SetRightMargin(0.05);
    c_pf->Divide(3,1);

    c_pf->cd(1);
    h_PF_eta->GetXaxis()->SetTitle("#eta^{PF}");
    h_PF_eta->GetYaxis()->SetTitle("Normalized distribution (per PF cand.)");
    h_PF_eta->GetXaxis()->SetTitleOffset(1.2);
    h_PF_eta->GetYaxis()->SetRangeUser(0., 0.25);
    h_PF_eta->Draw("hist same");
    h_PF_forward_eta->Draw("hist same");
    h_PF_backward_eta->Draw("hist same");
    leg_eta->Draw();

    c_pf->cd(2);
    h_PF_phi->GetXaxis()->SetTitle("#phi^{PF}");
    h_PF_phi->GetYaxis()->SetTitle("Normalized distribution (per PF cand.)");
    h_PF_phi->GetXaxis()->SetTitleOffset(1.2);
    h_PF_phi->GetYaxis()->SetRangeUser(0., 0.2);
    h_PF_phi->Draw("hist same");
    h_PF_forward_phi->Draw("hist same");
    h_PF_backward_phi->Draw("hist same");

    c_pf->cd(3);
    h_PF_E->GetXaxis()->SetTitle("E^{PF} (GeV)");
    h_PF_E->GetYaxis()->SetTitle("Normalized distribution (per PF cand.)");
    h_PF_E->GetXaxis()->SetTitleOffset(1.2);
    h_PF_E->GetYaxis()->SetRangeUser(0., 0.45);
    h_PF_E->Draw("hist");
    h_PF_forward_E->Draw("hist same");
    h_PF_backward_E->Draw("hist same");

    c_pf->Print("plots/"+sample+"_pf_distribution.pdf");
    c_pf->Print("plots/"+sample+"_pf_distribution.png");

    TCanvas *c_pf_max = new TCanvas("c_pf_max", "", 2400, 800);
    // c_pf_max->SetTopMargin(0.1);
    // c_pf_max->SetBottomMargin(0.1);
    // c_pf_max->SetLeftMargin(0.15);
    // c_pf_max->SetRightMargin(0.05);
    c_pf_max->Divide(3,1);

    c_pf_max->cd(1);

    h_PF_forward_Etamax_eta->SetLineStyle(2);
    h_PF_backward_Etamax_eta->SetLineStyle(2);

    TLegend *leg_max_eta = new TLegend(0.2, 0.65, 0.6, 0.85);
    leg_max_eta->SetBorderSize(0);
    leg_max_eta->SetFillStyle(0);
    leg_max_eta->SetHeader("PF candidate (outside of jet)");
    leg_max_eta->AddEntry(h_PF_forward_Emax_eta, "Forward (Emax)", "l");
    leg_max_eta->AddEntry(h_PF_backward_Emax_eta, "Backward (Emax)", "l");
    leg_max_eta->AddEntry(h_PF_forward_Etamax_eta, "Forward (Etamax)", "l");
    leg_max_eta->AddEntry(h_PF_backward_Etamax_eta, "Backward (Etamax)", "l");

    
    h_PF_forward_Emax_eta->GetXaxis()->SetTitle("#eta^{PF}");
    h_PF_forward_Emax_eta->GetYaxis()->SetTitle("Normalized distribution (per event)");
    h_PF_forward_Emax_eta->GetXaxis()->SetTitleOffset(1.2);
    // h_PF_forward_Emax_eta->GetXaxis()->SetRangeUser(0.,20.);
    h_PF_forward_Emax_eta->GetYaxis()->SetRangeUser(0., 0.25);
    h_PF_forward_Emax_eta->Draw("hist");
    h_PF_backward_Emax_eta->Draw("hist same");
    h_PF_forward_Etamax_eta->Draw("hist same");
    h_PF_backward_Etamax_eta->Draw("hist same");
    leg_max_eta->Draw();

    c_pf_max->cd(2);

    h_PF_forward_Etamax_phi->SetLineStyle(2);
    h_PF_backward_Etamax_phi->SetLineStyle(2);
    
    h_PF_forward_Emax_phi->GetXaxis()->SetTitle("#phi^{PF}");
    h_PF_forward_Emax_phi->GetYaxis()->SetTitle("Normalized distribution (per event)");
    h_PF_forward_Emax_phi->GetXaxis()->SetTitleOffset(1.2);
    // h_PF_forward_Emax_phi->GetXaxis()->SetRangeUser(0.,20.);
    h_PF_forward_Emax_phi->GetYaxis()->SetRangeUser(0., 0.2);
    h_PF_forward_Emax_phi->Draw("hist");
    h_PF_backward_Emax_phi->Draw("hist same");
    h_PF_forward_Etamax_phi->Draw("hist same");
    h_PF_backward_Etamax_phi->Draw("hist same");

    c_pf_max->cd(3);

    h_PF_forward_Etamax_E->SetLineStyle(2);
    h_PF_backward_Etamax_E->SetLineStyle(2);
    
    h_PF_forward_Emax_E->GetXaxis()->SetTitle("E^{PF} (GeV)");
    h_PF_forward_Emax_E->GetYaxis()->SetTitle("Normalized distribution (per event)");
    h_PF_forward_Emax_E->GetXaxis()->SetTitleOffset(1.2);
    // h_PF_forward_Emax_E->GetXaxis()->SetRangeUser(0.,20.);
    h_PF_forward_Emax_E->GetYaxis()->SetRangeUser(0., 0.45);
    h_PF_forward_Emax_E->Draw("hist");
    h_PF_backward_Emax_E->Draw("hist same");
    h_PF_forward_Etamax_E->Draw("hist same");
    h_PF_backward_Etamax_E->Draw("hist same");

    c_pf_max->Print("plots/"+sample+"_pf_max_distribution.pdf");
    c_pf_max->Print("plots/"+sample+"_pf_max_distribution.png");
}