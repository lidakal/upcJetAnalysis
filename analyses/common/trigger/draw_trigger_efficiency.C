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
    gStyle->SetPaintTextFormat("0.2f");

    TString sample = "hiforwardAll_2024rereco";
    TFile *f = new TFile("histos/" + sample + "_pt_spectrum.root"); // Created by plot_pt_spectrum.C
    TH2F *h_trigger_jet8_vs_jet20 = (TH2F*)f->Get("h_trigger_jet8_vs_jet20");
    TH2F *h_trigger_jet12_vs_jet20 = (TH2F*)f->Get("h_trigger_jet12_vs_jet20");
    TH2F *h_trigger_jet16_vs_jet20 = (TH2F*)f->Get("h_trigger_jet16_vs_jet20");
    TH1F *h_lead_pt_jet8not20 = (TH1F*)f->Get("h_lead_pt_jet8not20");
    TH1F *h_lead_pt_jet8not16not20 = (TH1F*)f->Get("h_lead_pt_jet8not16not20");
    TH1F *h_lead_pt_jet8not12not16not20 = (TH1F*)f->Get("h_lead_pt_jet8not12not16not20");
    TH1F *h_lead_pt_jet12not16not20 = (TH1F*)f->Get("h_lead_pt_jet12not16not20");
    TH1F *h_lead_pt_jet16not20 = (TH1F*)f->Get("h_lead_pt_jet16not20");
    TH1F *h_lead_pt_jet20 = (TH1F*)f->Get("h_lead_pt_jet20");

    // Calculate PS
    double n_jet20 = h_trigger_jet8_vs_jet20->GetBinContent(1,2) + h_trigger_jet8_vs_jet20->GetBinContent(2,2);
    double n_jet8_jet20 = h_trigger_jet8_vs_jet20->GetBinContent(2,2);
    double PS8 = n_jet20 / n_jet8_jet20;
    std::cout << "Run-average Jet8 prescale factor (PS) = " << PS8 << std::endl;

    // double n_jet20 = h_trigger_jet12_vs_jet20->GetBinContent(1,2) + h_trigger_jet12_vs_jet20->GetBinContent(2,2);
    double n_jet12_jet20 = h_trigger_jet12_vs_jet20->GetBinContent(2,2);
    double PS12 = n_jet20 / n_jet12_jet20;
    std::cout << "Run-average Jet12 prescale factor (PS) = " << PS12 << std::endl;

    // double n_jet20 = h_trigger_jet16_vs_jet20->GetBinContent(1,2) + h_trigger_jet16_vs_jet20->GetBinContent(2,2);
    double n_jet16_jet20 = h_trigger_jet16_vs_jet20->GetBinContent(2,2);
    double PS16 = n_jet20 / n_jet16_jet20;
    std::cout << "Run-average Jet16 prescale factor (PS) = " << PS16 << std::endl;

    // Add
    TH1F *h_lead_pt_jet8_plus_jet20 = (TH1F*)h_lead_pt_jet20->Clone("h_lead_pt_jet8_plus_jet20");
    h_lead_pt_jet8_plus_jet20->Add(h_lead_pt_jet8not20, PS8); // scale by PS

    TH1F *h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20 = (TH1F*)h_lead_pt_jet20->Clone("h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20");
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20->Add(h_lead_pt_jet16not20, 1.); 
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20->Add(h_lead_pt_jet12not16not20, 1.); 
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20->Add(h_lead_pt_jet8not12not16not20, PS8); // scale by PS

    TH1F *h_lead_pt_jet12_plus_jet16_plus_jet20 = (TH1F*)h_lead_pt_jet20->Clone("h_lead_pt_jet12_plus_jet16_plus_jet20");
    h_lead_pt_jet12_plus_jet16_plus_jet20->Add(h_lead_pt_jet16not20, 1.); 
    h_lead_pt_jet12_plus_jet16_plus_jet20->Add(h_lead_pt_jet12not16not20, PS12); // scale by PS

    TH1F *h_lead_pt_jet16_plus_jet20 = (TH1F*)h_lead_pt_jet20->Clone("h_lead_pt_jet16_plus_jet20");
    h_lead_pt_jet16_plus_jet20->Add(h_lead_pt_jet16not20, PS16); // scale by PS

    TH1F *h_lead_pt_jet8_plus_jet16_plus_jet20 = (TH1F*)h_lead_pt_jet20->Clone("h_lead_pt_jet8_plus_jet16_plus_jet20");
    h_lead_pt_jet8_plus_jet16_plus_jet20->Add(h_lead_pt_jet16not20, 1.); 
    h_lead_pt_jet8_plus_jet16_plus_jet20->Add(h_lead_pt_jet8not12not16not20, PS8); // scale by PS

    // Calculate efficiency
    TH1F *h_efficiency_jet20 = (TH1F*)h_lead_pt_jet20->Clone("h_efficiency_jet20");
    h_efficiency_jet20->Divide(h_lead_pt_jet8_plus_jet20);
    h_efficiency_jet20->SetLineColor(cmsBlue);

    TH1F *h_efficiency_jet20_plus_jet16_plus_jet12 = (TH1F*)h_lead_pt_jet12_plus_jet16_plus_jet20->Clone("h_efficiency_jet20_plus_jet16_plus_jet12");
    h_efficiency_jet20_plus_jet16_plus_jet12->Divide(h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20);
    h_efficiency_jet20_plus_jet16_plus_jet12->SetLineColor(cmsRed);

    TH1F *h_efficiency_jet20_plus_jet16 = (TH1F*)h_lead_pt_jet16_plus_jet20->Clone("h_efficiency_jet20_plus_jet16");
    h_efficiency_jet20_plus_jet16->Divide(h_lead_pt_jet12_plus_jet16_plus_jet20);
    h_efficiency_jet20_plus_jet16->SetLineColor(cmsViolet);

    TH1F *h_efficiency_jet20_plus_jet16_v2 = (TH1F*)h_lead_pt_jet16_plus_jet20->Clone("h_efficiency_jet20_plus_jet16_v2");
    h_efficiency_jet20_plus_jet16_v2->Divide(h_lead_pt_jet8_plus_jet16_plus_jet20);
    h_efficiency_jet20_plus_jet16_v2->SetLineColor(cmsRed);

    for (auto h : {h_efficiency_jet20, h_efficiency_jet20_plus_jet16_plus_jet12, h_efficiency_jet20_plus_jet16, h_efficiency_jet20_plus_jet16_v2}) {
        h->SetLineWidth(2);
        h->SetMarkerColor(h->GetLineColor());
        h->GetXaxis()->SetTitle("p_{T}^{jet, lead} (GeV)");
        h->GetXaxis()->SetRangeUser(0., 200);
        h->GetYaxis()->SetTitle("Trigger efficiency");
        h->SetMinimum(0.4);
        h->SetMaximum(1.1);
        h->SetMarkerSize(600);
    }

    // Draw
    TCanvas *c_eff = new TCanvas("c_eff", "c_eff", 800, 700);
    c_eff->SetTopMargin(0.1);
    c_eff->SetBottomMargin(0.15);
    c_eff->SetLeftMargin(0.15);
    c_eff->SetRightMargin(0.05);
    // h_efficiency_jet20_v2->Draw("hist text");
    h_efficiency_jet20->Draw("hist text");
    // h_efficiency_jet20_plus_jet16_plus_jet12->Draw("hist same");
    h_efficiency_jet20_plus_jet16->Draw("hist text same");
    h_efficiency_jet20_plus_jet16_v2->Draw("hist text same");
    draw_header();

    TLine *line = new TLine(30., 0.4, 30., 1.1);
    line->SetLineStyle(2);
    line->SetLineColor(kBlack);
    line->Draw();

    TLegend *leg_eff = new TLegend(0.5, 0.3, 0.7, 0.4);
    leg_eff->SetBorderSize(0);
    leg_eff->SetMargin(0.15);
    leg_eff->AddEntry(h_efficiency_jet20, "Jet20", "l");
    leg_eff->AddEntry(h_efficiency_jet20_plus_jet16, "Jet20 + Jet16 (vs Jet12)", "l");
    leg_eff->AddEntry(h_efficiency_jet20_plus_jet16_v2, "Jet20 + Jet16 (vs Jet8)", "l");
    leg_eff->Draw();

    // Save
    c_eff->Print("plots/" + sample + "_trigger_efficiency.pdf");

    // debug
    TCanvas *c_debug = new TCanvas("c_debug", "c_debug", 800, 700);
    c_debug->SetTopMargin(0.1);
    c_debug->SetBottomMargin(0.15);
    c_debug->SetLeftMargin(0.15);
    c_debug->SetRightMargin(0.05);
    h_lead_pt_jet8_plus_jet16_plus_jet20->GetXaxis()->SetTitle("Leading Jet p_{T} (GeV)");
    h_lead_pt_jet8_plus_jet16_plus_jet20->GetXaxis()->SetRangeUser(0., 100);
    h_lead_pt_jet8_plus_jet16_plus_jet20->GetYaxis()->SetTitle("N_{events}");
    h_lead_pt_jet8_plus_jet16_plus_jet20->SetMinimum(1000);
    h_lead_pt_jet8_plus_jet16_plus_jet20->SetMaximum(2e7);
    h_lead_pt_jet8_plus_jet16_plus_jet20->SetLineColor(cmsBlue);
    h_lead_pt_jet8_plus_jet16_plus_jet20->Draw("hist");
    h_lead_pt_jet12_plus_jet16_plus_jet20->SetLineColor(cmsRed);
    h_lead_pt_jet12_plus_jet16_plus_jet20->Draw("hist same");
    c_debug->SetLogy();
    TLegend *leg_debug = new TLegend(0.5, 0.5, 0.9, 0.7);
    leg_debug->SetBorderSize(0);
    leg_debug->SetMargin(0.1);
    leg_debug->AddEntry(h_lead_pt_jet8_plus_jet16_plus_jet20, "Jet8 + Jet16 + Jet20", "l");
    leg_debug->AddEntry(h_lead_pt_jet12_plus_jet16_plus_jet20, "Jet12 + Jet16 + Jet20", "l");
    leg_debug->Draw();
    draw_header();
    c_debug->Print("plots/" + sample + "_debug.pdf");
}