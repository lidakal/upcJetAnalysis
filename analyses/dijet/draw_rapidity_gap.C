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
    gStyle->SetLegendTextSize(24);
    gStyle->SetLabelSize(24, "XYZ");
    gStyle->SetTitleSize(28, "XYZ");

    // TString sample = "beamB_diffraction_pthat10";
    TString sample = "hiforwardAll_2024rereco";
    TFile *fin = new TFile("histos/"+sample+"_pf_distribution_tracker_bothHF.root"); // requires plot_PF_distribution*.C

    TH2F *h_rapgap_Emax = (TH2F *) fin->Get("h_rapgap_Emax");
    TH2F *h_rapgap_Etamax = (TH2F *) fin->Get("h_rapgap_Etamax");

    // Format
    for (auto h : {
        h_rapgap_Emax, h_rapgap_Etamax
    }) {
        // h->Scale(1/h->Integral());
        // h->GetZaxis()->SetRange(0., 1.);
        h->GetXaxis()->SetTitle("FRG");
        h->GetYaxis()->SetTitle("BRG");
        // h->GetZaxis()->SetTitle("Normalized entries (per event)");
        h->GetZaxis()->SetTitleOffset(1.7);
    }

    // Draw
    TCanvas *c_rapgap_Emax = new TCanvas("c_rapgap_Emax", "x=FRG, y=BRG, Emax", 800, 700);
    c_rapgap_Emax->SetTopMargin(0.1);
    c_rapgap_Emax->SetBottomMargin(0.15);
    c_rapgap_Emax->SetLeftMargin(0.15);
    c_rapgap_Emax->SetRightMargin(0.2);

    h_rapgap_Emax->Draw("colz");
    draw_header_simulation();

    c_rapgap_Emax->Print("plots/"+sample+"_rapgap_Emax.pdf");

    TCanvas *c_rapgap_Etamax = new TCanvas("c_rapgap_Etamax", "x=FRG, y=BRG, Etamax", 800, 700);
    c_rapgap_Etamax->SetTopMargin(0.1);
    c_rapgap_Etamax->SetBottomMargin(0.15);
    c_rapgap_Etamax->SetLeftMargin(0.15);
    c_rapgap_Etamax->SetRightMargin(0.2);

    h_rapgap_Etamax->Draw("colz");
    draw_header_simulation();

    c_rapgap_Etamax->Print("plots/"+sample+"_rapgap_Etamax.pdf");
}