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

void draw_trigger_efficiency()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);

    TString sample = "hiforwardAll_2024rereco";
    TFile *f = new TFile("histos/" + sample + "_pt_spectrum.root"); // Created by plot_pt_spectrum.C
    TH2F *h_trigger = (TH2F*)f->Get("h_trigger");
    TH1F *h_lead_pt_jet8 = (TH1F*)f->Get("h_lead_pt_jet8");
    TH1F *h_lead_pt_jet20 = (TH1F*)f->Get("h_lead_pt_jet20");

    // Calculate PS
    double n_jet20 = h_trigger->GetBinContent(2,1) + h_trigger->GetBinContent(2,2);
    double n_jet8_jet20 = h_trigger->GetBinContent(2,2);
    double PS = n_jet20 / n_jet8_jet20;
    std::cout << "Run-average Jet8 prescale factor (PS) = " << PS << std::endl;

    // Add
    TH1F *h_lead_pt_jet8_plus_jet20 = (TH1F*)h_lead_pt_jet20->Clone("h_lead_pt_jet8_plus_jet20");
    h_lead_pt_jet8_plus_jet20->Add(h_lead_pt_jet8, PS); // scale by PS

    // Calculate efficiency
    TH1F *h_efficiency = (TH1F*)h_lead_pt_jet20->Clone("h_efficiency");
    h_efficiency->Divide(h_lead_pt_jet8_plus_jet20);

    // Draw
    TCanvas *c_eff = new TCanvas("c_eff", "c_eff", 800, 700);
    c_eff->SetTopMargin(0.1);
    c_eff->SetBottomMargin(0.15);
    c_eff->SetLeftMargin(0.15);
    c_eff->SetRightMargin(0.05);
    h_efficiency->Draw("hist");
    draw_header();

    // Format axes
    h_efficiency->GetXaxis()->SetTitle("p_{T}^{jet, lead} (GeV)");
    h_efficiency->GetXaxis()->SetRangeUser(0., 200);
    h_efficiency->GetYaxis()->SetTitle("Trigger efficiency");
    h_efficiency->SetMinimum(0);
    h_efficiency->SetMaximum(1.1);

    // Save
    c_eff->Print("plots/" + sample + "_trigger_efficiency.pdf");
}