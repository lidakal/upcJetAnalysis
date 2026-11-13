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
    // TString sample = "beamA_diffraction_pthat10";
    TString suffix = "_jtpt";
    TFile *f = new TFile("histos/" + sample + "_pt_spectrum" + suffix + ".root"); // Created by plot_pt_spectrum.C

    TH2F *h_trigger_jet8_vs_jet28 = (TH2F*)f->Get("h_trigger_jet8_vs_jet28");
    TH2F *h_trigger_jet12_vs_jet28 = (TH2F*)f->Get("h_trigger_jet12_vs_jet28");
    TH2F *h_trigger_jet16_vs_jet28 = (TH2F*)f->Get("h_trigger_jet16_vs_jet28");
    TH2F *h_trigger_jet20_vs_jet28 = (TH2F*)f->Get("h_trigger_jet20_vs_jet28");
    TH2F *h_trigger_jet24_vs_jet28 = (TH2F*)f->Get("h_trigger_jet24_vs_jet28");

    TH1F *h_lead_pt_jet8 = (TH1F*)f->Get("h_lead_pt_jet8");
    TH1F *h_lead_pt_jet12 = (TH1F*)f->Get("h_lead_pt_jet12");

    TH1F *h_lead_pt_jet8not28 = (TH1F*)f->Get("h_lead_pt_jet8not28");

    TH1F *h_lead_pt_jet8not12not16not20not24not28 = (TH1F*)f->Get("h_lead_pt_jet8not12not16not20not24not28");
    TH1F *h_lead_pt_jet12not16not20not24not28 = (TH1F*)f->Get("h_lead_pt_jet12not16not20not24not28");
    TH1F *h_lead_pt_jet16not20not24not28 = (TH1F*)f->Get("h_lead_pt_jet16not20not24not28");
    TH1F *h_lead_pt_jet20not24not28 = (TH1F*)f->Get("h_lead_pt_jet20not24not28");
    TH1F *h_lead_pt_jet24not28 = (TH1F*)f->Get("h_lead_pt_jet24not28");
    TH1F *h_lead_pt_jet28 = (TH1F*)f->Get("h_lead_pt_jet28");

    TH1F *h_lead_pt_jet8not16not20not24not28 = (TH1F*)f->Get("h_lead_pt_jet8not16not20not24not28");
    // Calculate PS
    double n_jet28 = h_trigger_jet8_vs_jet28->GetBinContent(1,2) + h_trigger_jet8_vs_jet28->GetBinContent(2,2);
    double n_jet8_jet28 = h_trigger_jet8_vs_jet28->GetBinContent(2,2);
    double PS8 = n_jet28 / n_jet8_jet28;
    std::cout << "Run-average Jet8 prescale factor (PS) = " << PS8 << std::endl;

    double n_jet12_jet28 = h_trigger_jet12_vs_jet28->GetBinContent(2,2);
    double PS12 = n_jet28 / n_jet12_jet28;
    std::cout << "Run-average Jet12 prescale factor (PS) = " << PS12 << std::endl;

    double n_jet16_jet28 = h_trigger_jet16_vs_jet28->GetBinContent(2,2);
    double PS16 = n_jet28 / n_jet16_jet28;
    std::cout << "Run-average Jet16 prescale factor (PS) = " << PS16 << std::endl;

    double n_jet20_jet28 = h_trigger_jet20_vs_jet28->GetBinContent(2,2);
    double PS20 = n_jet28 / n_jet20_jet28;
    std::cout << "Run-average Jet20 prescale factor (PS) = " << PS20 << std::endl;

    double n_jet24_jet28 = h_trigger_jet24_vs_jet28->GetBinContent(2,2);
    double PS24 = n_jet28 / n_jet24_jet28;
    std::cout << "Run-average Jet24 prescale factor (PS) = " << PS24 << std::endl;

    // Add
    TH1F *h_lead_pt_jet8_plus_jet28 = (TH1F*) h_lead_pt_jet28->Clone("h_lead_pt_jet8_plus_jet28");
    h_lead_pt_jet8_plus_jet28->Add(h_lead_pt_jet8not28, PS8); // scale by PS

    TH1F *h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28 = (TH1F*) h_lead_pt_jet28->Clone("h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28");
    h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet24not28, 1.);
    h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet20not24not28, 1.);
    h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet16not20not24not28, PS16); // scale by PS

    TH1F *h_lead_pt_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28 = (TH1F*) h_lead_pt_jet28->Clone("h_lead_pt_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28");
    h_lead_pt_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet24not28, 1.); 
    h_lead_pt_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet20not24not28, 1.); 
    h_lead_pt_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet16not20not24not28, 1.); 
    h_lead_pt_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet12not16not20not24not28, PS12); // scale by PS

    TH1F *h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28 = (TH1F*) h_lead_pt_jet28->Clone("h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28");
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet24not28, 1.); 
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet20not24not28, 1.); 
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet16not20not24not28, 1.); 
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet12not16not20not24not28, 1.); 
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet8not12not16not20not24not28, PS8); // scale by PS

    TH1F *h_lead_pt_jet8_plus_jet16_plus_jet20_plus_jet24_plus_jet28 = (TH1F*) h_lead_pt_jet28->Clone("h_lead_pt_jet8_plus_jet16_plus_jet20_plus_jet24_plus_jet28");
    h_lead_pt_jet8_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet24not28, 1.); 
    h_lead_pt_jet8_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet20not24not28, 1.); 
    h_lead_pt_jet8_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet16not20not24not28, 1.); 
    h_lead_pt_jet8_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet8not16not20not24not28, PS8); // scale by PS

    // Calculate efficiency
    TH1F *h_efficiency_jet28 = (TH1F*) h_lead_pt_jet28->Clone("h_efficiency_jet28");
    h_efficiency_jet28->Divide(h_lead_pt_jet8_plus_jet28);
    h_efficiency_jet28->SetLineColor(cmsBlue);

    TH1F *h_efficiency_jet16_plus_jet20_plus_jet24_plus_jet28 = (TH1F*) h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28->Clone("h_efficiency_jet16_plus_jet20_plus_jet24_plus_jet28");
    h_efficiency_jet16_plus_jet20_plus_jet24_plus_jet28->Divide(h_lead_pt_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28); // TODO: Change to 8+16+...
    h_efficiency_jet16_plus_jet20_plus_jet24_plus_jet28->SetLineColor(cmsRed);

    TH1F *h_efficiency_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28 = (TH1F*) h_lead_pt_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Clone("h_efficiency_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28");
    h_efficiency_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Divide(h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28);
    h_efficiency_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->SetLineColor(cmsViolet);

    // Draw
    TCanvas *c_eff = new TCanvas("c_eff", "c_eff", 800, 700);
    c_eff->SetTopMargin(0.1);
    c_eff->SetBottomMargin(0.15);
    c_eff->SetLeftMargin(0.15);
    c_eff->SetRightMargin(0.05);
    for (auto h : {
        // h_efficiency_jet28, 
        h_efficiency_jet16_plus_jet20_plus_jet24_plus_jet28, 
        // h_efficiency_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28
    }) {
        h->SetLineWidth(2);
        h->SetMarkerColor(h->GetLineColor());
        h->GetXaxis()->SetTitle("p_{T}^{jet, lead} (GeV)");
        h->GetXaxis()->SetRangeUser(0., 100);
        h->GetYaxis()->SetTitle("Trigger efficiency");
        h->SetMinimum(0.4);
        h->SetMaximum(1.1);
        h->SetMarkerSize(600);
        h->Draw("hist text same");
    }
    draw_header();

    TLine *line = new TLine(30., 0.4, 30., 1.1);
    line->SetLineStyle(2);
    line->SetLineColor(kBlack);
    line->Draw();

    TLegend *leg_eff = new TLegend(0.45, 0.3, 0.7, 0.4);
    leg_eff->SetBorderSize(0);
    leg_eff->SetMargin(0.15);
    leg_eff->SetHeader("NotMB AND");
    // leg_eff->AddEntry(h_efficiency_jet28, "Jet28", "l");
    leg_eff->AddEntry(h_efficiency_jet16_plus_jet20_plus_jet24_plus_jet28, "Jet28 + Jet24 + Jet20 + Jet16", "l");
    // leg_eff->AddEntry(h_efficiency_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28, "Jet28 + Jet24 + Jet20 + Jet16 + Jet12", "l");
    leg_eff->Draw();

    // Save
    c_eff->Print("plots/" + sample + "_trigger_efficiency" + suffix + ".pdf");

    // debug
    TCanvas *c_debug = new TCanvas("c_debug", "c_debug", 800, 700);
    c_debug->SetTopMargin(0.1);
    c_debug->SetBottomMargin(0.15);
    c_debug->SetLeftMargin(0.15);
    c_debug->SetRightMargin(0.05);
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->GetXaxis()->SetTitle("Leading Jet p_{T} (GeV)");
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->GetXaxis()->SetRangeUser(0., 100);
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->GetYaxis()->SetTitle("N_{events}");
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->SetMinimum(1000);
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->SetMaximum(2e7);
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->SetLineColor(cmsBlue);
    h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Draw("hist");
    h_lead_pt_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->SetLineColor(cmsRed);
    h_lead_pt_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28->Draw("hist same");
    h_lead_pt_jet8->SetLineColorAlpha(cmsBlue,0.5);
    h_lead_pt_jet8->SetLineStyle(kDashed);
    h_lead_pt_jet8->Draw("hist same");
    h_lead_pt_jet12->SetLineColorAlpha(cmsRed,0.5);
    h_lead_pt_jet12->SetLineStyle(kDashed);
    h_lead_pt_jet12->Draw("hist same");
    c_debug->SetLogy();
    TLegend *leg_debug = new TLegend(0.5, 0.5, 0.9, 0.7);
    leg_debug->SetBorderSize(0);
    leg_debug->SetMargin(0.1);
    leg_debug->AddEntry(h_lead_pt_jet8_plus_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28, "Jet8 + Jet12 + Jet16 + Jet20 + Jet24 + Jet28", "l");
    leg_debug->AddEntry(h_lead_pt_jet12_plus_jet16_plus_jet20_plus_jet24_plus_jet28, "Jet12 + Jet16 + Jet20 + Jet24 + Jet28", "l");
    leg_debug->AddEntry(h_lead_pt_jet8, "Jet8", "l");
    leg_debug->AddEntry(h_lead_pt_jet12, "Jet12", "l");
    leg_debug->Draw();
    draw_header();
    c_debug->Print("plots/" + sample + "_debug.pdf");
}