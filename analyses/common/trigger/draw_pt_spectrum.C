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

void draw_pt_spectrum()
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

    // Scale Jet8 spectrum by PS
    TH1F *h_lead_pt_jet8_scaled = (TH1F*)h_lead_pt_jet8->Clone("h_lead_pt_jet8_scaled");
    h_lead_pt_jet8_scaled->Scale(PS);

    // Stack
    h_lead_pt_jet8_scaled->SetFillColorAlpha(cmsBlue, 0.3);
    h_lead_pt_jet8_scaled->SetLineColor(cmsBlue);
    h_lead_pt_jet20->SetFillColorAlpha(cmsOrange, 0.3);
    h_lead_pt_jet20->SetLineColor(cmsOrange);
    h_lead_pt_jet8_scaled->SetFillStyle(1001); // Solid fill
    h_lead_pt_jet20->SetFillStyle(1001); // Solid fill

    THStack *hs = new THStack("hs", "Leading Jet p_{T} Spectrum");
    hs->Add(h_lead_pt_jet8_scaled);
    hs->Add(h_lead_pt_jet20);

    // Draw
    TCanvas *c_stack = new TCanvas("c_stack", "c_stack", 800, 700);
    c_stack->SetTopMargin(0.1);
    c_stack->SetBottomMargin(0.15);
    c_stack->SetLeftMargin(0.15);
    c_stack->SetRightMargin(0.05);
    c_stack->SetLogy();
    hs->Draw("hist");
    draw_header();

    // Format axes
    hs->GetXaxis()->SetTitle("p_{T}^{jet, lead} (GeV)");
    hs->GetXaxis()->SetRangeUser(0., 200);
    hs->GetYaxis()->SetTitle("N_{events}");
    hs->SetMinimum(1);
    hs->SetMaximum(1e8);

    // Legend
    TLegend *legend = new TLegend(0.4, 0.7, 0.9, 0.8);
    legend->SetBorderSize(0);
    legend->SetMargin(0.1);
    legend->AddEntry(h_lead_pt_jet8_scaled, "Jet8&&!Jet20 (scaled by PS)", "f");
    legend->AddEntry(h_lead_pt_jet20, "Jet20", "f");
    legend->Draw();

    // Save
    c_stack->Print("plots/" + sample + "_pt_spectrum.pdf");
}