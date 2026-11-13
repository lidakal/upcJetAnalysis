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
    gStyle->SetLegendTextSize(20);

    TString sample = "hiforwardAll_2024rereco";
    TString suffix = "_jtpt";
    TFile *f = new TFile("histos/" + sample + "_pt_spectrum" + suffix + ".root"); // Created by plot_pt_spectrum.C

    TH2F *h_trigger_jet8_vs_jet28 = (TH2F*)f->Get("h_trigger_jet8_vs_jet28");
    TH2F *h_trigger_jet12_vs_jet28 = (TH2F*)f->Get("h_trigger_jet12_vs_jet28");
    TH2F *h_trigger_jet16_vs_jet28 = (TH2F*)f->Get("h_trigger_jet16_vs_jet28");
    TH2F *h_trigger_jet20_vs_jet28 = (TH2F*)f->Get("h_trigger_jet20_vs_jet28");
    TH2F *h_trigger_jet24_vs_jet28 = (TH2F*)f->Get("h_trigger_jet24_vs_jet28");

    TH1F *h_lead_pt_jet8 = (TH1F*)f->Get("h_lead_pt_jet8");
    TH1F *h_lead_pt_jet12 = (TH1F*)f->Get("h_lead_pt_jet12");
    TH1F *h_lead_pt_jet16 = (TH1F*)f->Get("h_lead_pt_jet16");
    TH1F *h_lead_pt_jet20 = (TH1F*)f->Get("h_lead_pt_jet20");
    TH1F *h_lead_pt_jet24 = (TH1F*)f->Get("h_lead_pt_jet24");
    TH1F *h_lead_pt_jet28 = (TH1F*)f->Get("h_lead_pt_jet28");

    TH1F *h_lead_pt_jet8not28 = (TH1F*)f->Get("h_lead_pt_jet8not28");

    TH1F *h_lead_pt_jet8not12not16not20not24not28 = (TH1F*)f->Get("h_lead_pt_jet8not12not16not20not24not28");
    TH1F *h_lead_pt_jet12not16not20not24not28 = (TH1F*)f->Get("h_lead_pt_jet12not16not20not24not28");
    TH1F *h_lead_pt_jet16not20not24not28 = (TH1F*)f->Get("h_lead_pt_jet16not20not24not28");
    TH1F *h_lead_pt_jet20not24not28 = (TH1F*)f->Get("h_lead_pt_jet20not24not28");
    TH1F *h_lead_pt_jet24not28 = (TH1F*)f->Get("h_lead_pt_jet24not28");

    TH1F *h_lead_pt_jet8not16not20not24not28 = (TH1F*)f->Get("h_lead_pt_jet8not16not20not24not28");
    
    // Draw spectra w/o weights
    TCanvas *c_pt = new TCanvas("c_pt", "c_pt", 800, 700);
    c_pt->SetTopMargin(0.1);
    c_pt->SetBottomMargin(0.15);
    c_pt->SetLeftMargin(0.15);
    c_pt->SetRightMargin(0.05);
    c_pt->SetLogy();
    TLegend *leg_pt = new TLegend(0.55, 0.55, 0.9, 0.8);
    leg_pt->SetBorderSize(0);
    leg_pt->SetMargin(0.1);
    std::vector<Int_t> colors = {cmsLightBlue, cmsBlue, cmsViolet, cmsYellow, cmsOrange, cmsRed};
    std::vector<TH1F*> histos = {
        h_lead_pt_jet8, h_lead_pt_jet12, h_lead_pt_jet16, 
        h_lead_pt_jet20, h_lead_pt_jet24, h_lead_pt_jet28,  
    };
    std::vector<TString> names = {
        "Jet8", "Jet12", "Jet16", 
        "Jet20", "Jet24", "Jet28", 
    };
    for (int i=0; i<names.size(); i++) {
        histos[i]->SetLineColor(colors[i]);
        histos[i]->SetLineWidth(2);
        histos[i]->GetXaxis()->SetTitle("Leading Jet p_{T} (GeV)");
        histos[i]->GetXaxis()->SetRangeUser(0., 100);
        histos[i]->GetYaxis()->SetTitle("N_{events}");
        histos[i]->SetMinimum(100);
        histos[i]->SetMaximum(1e8);
        histos[i]->Draw("hist same");
        leg_pt->AddEntry(histos[i], names[i], "l");
    }
    draw_header();
    leg_pt->Draw();

    c_pt->Print("plots/" + sample + "_lead_pt_spectrum" + suffix + ".pdf");

    // Draw spectra w/ weights

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

    // Scale spectrum by PS
    TH1F *h_lead_pt_jet8not28_scaled = (TH1F*)h_lead_pt_jet8not28->Clone("h_lead_pt_jet8not28_scaled");
    h_lead_pt_jet8not28_scaled->Scale(PS8);
    h_lead_pt_jet8not28_scaled->SetFillStyle(1001);
    h_lead_pt_jet8not28_scaled->SetFillColorAlpha(cmsBlue, 0.3);
    h_lead_pt_jet8not28_scaled->SetLineColor(cmsBlue);

    TH1F *h_lead_pt_jet8not16not20not24not28_scaled = (TH1F*)h_lead_pt_jet8not16not20not24not28->Clone("h_lead_pt_jet8not16not20not24not28_scaled");
    h_lead_pt_jet8not16not20not24not28_scaled->Scale(PS8);
    h_lead_pt_jet8not16not20not24not28_scaled->SetFillStyle(1001);
    h_lead_pt_jet8not16not20not24not28_scaled->SetFillColorAlpha(cmsBlue, 0.3);
    h_lead_pt_jet8not16not20not24not28_scaled->SetLineColor(cmsBlue);

    TH1F *h_lead_pt_jet16not20not24not28_scaled = (TH1F*)h_lead_pt_jet16not20not24not28->Clone("h_lead_pt_jet16not20not24not28_scaled");
    h_lead_pt_jet16not20not24not28_scaled->Scale(PS16);
    h_lead_pt_jet16not20not24not28_scaled->SetFillStyle(1001);
    h_lead_pt_jet16not20not24not28_scaled->SetFillColorAlpha(cmsBlue, 0.3);
    h_lead_pt_jet16not20not24not28_scaled->SetLineColor(cmsBlue);

    // Add upper threshold histograms
    TH1F *h_lead_pt_jet20_plus_jet24_plus_jet28 = (TH1F*) h_lead_pt_jet28->Clone("h_lead_pt_jet20_plus_jet24_plus_jet28");
    h_lead_pt_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet24not28);
    h_lead_pt_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet20not24not28);
    h_lead_pt_jet20_plus_jet24_plus_jet28->SetFillStyle(1001);
    h_lead_pt_jet20_plus_jet24_plus_jet28->SetFillColorAlpha(cmsOrange,0.3);
    h_lead_pt_jet20_plus_jet24_plus_jet28->SetLineColor(cmsOrange);

    TH1F *h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28 = (TH1F*) h_lead_pt_jet28->Clone("h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28");
    h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet24not28);
    h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet20not24not28);
    h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28->Add(h_lead_pt_jet16not20not24not28);
    h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28->SetFillStyle(1001);
    h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28->SetFillColorAlpha(cmsOrange,0.3);
    h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28->SetLineColor(cmsOrange);

    TH1F *h_lead_pt_jet28_copy = (TH1F*) h_lead_pt_jet28->Clone("h_lead_pt_jet28_copy");
    h_lead_pt_jet28_copy->SetFillStyle(1001);
    h_lead_pt_jet28_copy->SetFillColorAlpha(cmsOrange,0.3);
    h_lead_pt_jet28_copy->SetLineColor(cmsOrange);

    // Stack -- labeled by the lowest threshold trigger 
    THStack *hs_jet8not28 = new THStack("hs_jet8not28", "Leading Jet p_{T} Spectrum");
    hs_jet8not28->Add(h_lead_pt_jet8not28_scaled);
    hs_jet8not28->Add(h_lead_pt_jet28_copy);

    THStack *hs_jet8not16not20not24not28 = new THStack("hs_jet8not16not20not24not28", "Leading Jet p_{T} Spectrum");
    hs_jet8not16not20not24not28->Add(h_lead_pt_jet8not16not20not24not28_scaled);
    hs_jet8not16not20not24not28->Add(h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28);

    THStack *hs_jet16not20not24not28 = new THStack("hs_jet16not20not24not28", "Leading Jet p_{T} Spectrum");
    hs_jet16not20not24not28->Add(h_lead_pt_jet16not20not24not28_scaled);
    hs_jet16not20not24not28->Add(h_lead_pt_jet20_plus_jet24_plus_jet28);

    // Draw -- labeled by the lowest threshold trigger 
    TCanvas *c_jet8not28 = new TCanvas("c_jet8not28", "jet8not28", 800, 700);
    TCanvas *c_jet8not16not20not24not28 = new TCanvas("c_jet8not16not20not24not28", "jet8not16not20not24not28", 800, 700);
    TCanvas *c_jet16not20not24not28 = new TCanvas("c_jet16not20not24not28", "jet16not20not24not28", 800, 700);

    // Legends -- labeled by the lowest threshold trigger 
    TLegend *leg_jet8not28 = new TLegend(0.25, 0.75, 0.9, 0.85);
    leg_jet8not28->SetBorderSize(0);
    leg_jet8not28->SetMargin(0.1);
    leg_jet8not28->AddEntry(h_lead_pt_jet28_copy, "Jet28", "f");
    leg_jet8not28->AddEntry(h_lead_pt_jet8not28_scaled, "Jet8 && !Jet28 (scaled by PS)", "f");

    TLegend *leg_jet8not16not20not24not28 = new TLegend(0.25, 0.75, 0.9, 0.85);
    leg_jet8not16not20not24not28->SetBorderSize(0);
    leg_jet8not16not20not24not28->SetMargin(0.1);
    leg_jet8not16not20not24not28->AddEntry(h_lead_pt_jet16_plus_jet20_plus_jet24_plus_jet28, "Jet28 || Jet24 || Jet20 || Jet16", "f");
    leg_jet8not16not20not24not28->AddEntry(h_lead_pt_jet8not16not20not24not28_scaled, "Jet8 && !(Jet28 || Jet24 || Jet20 || Jet16) (scaled by PS)", "f");

    TLegend *leg_jet16not20not24not28 = new TLegend(0.25, 0.75, 0.9, 0.85);
    leg_jet16not20not24not28->SetBorderSize(0);
    leg_jet16not20not24not28->SetMargin(0.1);
    leg_jet16not20not24not28->AddEntry(h_lead_pt_jet20_plus_jet24_plus_jet28, "Jet28 || Jet24 || Jet20", "f");
    leg_jet16not20not24not28->AddEntry(h_lead_pt_jet16not20not24not28_scaled, "Jet16 && !(Jet28 || Jet24 || Jet20) (scaled by PS)", "f");

    std::vector<TCanvas*> canvases = {
        c_jet8not28, c_jet8not16not20not24not28, c_jet16not20not24not28
    };
    std::vector<THStack*> stacks = {
        hs_jet8not28, hs_jet8not16not20not24not28, hs_jet16not20not24not28
    };
    std::vector<TLegend*> legends = {
        leg_jet8not28, leg_jet8not16not20not24not28, leg_jet16not20not24not28
    };

    for (int i = 0; i < canvases.size(); ++i) {
        canvases[i]->SetTopMargin(0.1);
        canvases[i]->SetBottomMargin(0.15);
        canvases[i]->SetLeftMargin(0.15);
        canvases[i]->SetRightMargin(0.05);
        canvases[i]->SetLogy();

        canvases[i]->cd();
        stacks[i]->Draw("hist");
        draw_header();

        // Format axes
        stacks[i]->GetXaxis()->SetTitle("p_{T}^{jet, lead} (GeV)");
        stacks[i]->GetXaxis()->SetRangeUser(0., 100);
        stacks[i]->GetYaxis()->SetTitle("N_{events}");
        stacks[i]->SetMinimum(1);
        stacks[i]->SetMaximum(1e9);

        
        legends[i]->Draw();

        // Save
        canvases[i]->Print("plots/" + sample + "_" + canvases[i]->GetTitle() + "_lead_pt_spectrum" + suffix + ".pdf");
    }    
}