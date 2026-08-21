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
    gStyle->SetLegendTextSize(22);

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
    TH1F *h_lead_pt_jet16 = (TH1F*)f->Get("h_lead_pt_jet16");
    TH1F *h_lead_pt_jet12 = (TH1F*)f->Get("h_lead_pt_jet12");
    TH1F *h_lead_pt_jet8 = (TH1F*)f->Get("h_lead_pt_jet8");
    
    // Draw spectra w/o weights
    h_lead_pt_jet8->SetLineColor(cmsBlue);
    h_lead_pt_jet12->SetLineColor(cmsViolet);
    h_lead_pt_jet16->SetLineColor(cmsOrange);
    h_lead_pt_jet20->SetLineColor(cmsRed);

    h_lead_pt_jet8->SetLineWidth(3);
    h_lead_pt_jet12->SetLineWidth(3);
    h_lead_pt_jet16->SetLineWidth(3);
    h_lead_pt_jet20->SetLineWidth(3);

    h_lead_pt_jet8->GetXaxis()->SetTitle("Leading Jet p_{T} (GeV)");
    h_lead_pt_jet8->GetXaxis()->SetRangeUser(0., 100);
    h_lead_pt_jet8->GetYaxis()->SetTitle("N_{events}");
    h_lead_pt_jet8->SetMinimum(100);
    h_lead_pt_jet8->SetMaximum(2e7);

    TCanvas *c_pt = new TCanvas("c_pt", "c_pt", 800, 700);
    c_pt->SetTopMargin(0.1);
    c_pt->SetBottomMargin(0.15);
    c_pt->SetLeftMargin(0.15);
    c_pt->SetRightMargin(0.05);
    c_pt->SetLogy();
    h_lead_pt_jet8->Draw("hist");
    h_lead_pt_jet12->Draw("hist same");
    h_lead_pt_jet16->Draw("hist same");
    h_lead_pt_jet20->Draw("hist same");
    draw_header();

    TLegend *leg_pt = new TLegend(0.6, 0.6, 0.9, 0.8);
    leg_pt->SetBorderSize(0);
    leg_pt->SetMargin(0.1);
    leg_pt->AddEntry(h_lead_pt_jet8, "Jet8", "l");
    leg_pt->AddEntry(h_lead_pt_jet12, "Jet12", "l");
    leg_pt->AddEntry(h_lead_pt_jet16, "Jet16", "l");
    leg_pt->AddEntry(h_lead_pt_jet20, "Jet20", "l");
    leg_pt->Draw();

    c_pt->Print("plots/" + sample + "_lead_pt_spectrum.pdf");

    // Draw spectra w/ weights

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

    // Scale spectrum by PS
    TH1F *h_lead_pt_jet8not20_scaled = (TH1F*)h_lead_pt_jet8not20->Clone("h_lead_pt_jet8not20_scaled");
    h_lead_pt_jet8not20_scaled->Scale(PS8);

    TH1F *h_lead_pt_jet8not16not20_scaled = (TH1F*)h_lead_pt_jet8not16not20->Clone("h_lead_pt_jet8not16not20_scaled");
    h_lead_pt_jet8not16not20_scaled->Scale(PS8);

    TH1F *h_lead_pt_jet8not12not16not20_scaled = (TH1F*)h_lead_pt_jet8not12not16not20->Clone("h_lead_pt_jet8not12not16not20_scaled");
    h_lead_pt_jet8not12not16not20_scaled->Scale(PS8);

    TH1F *h_lead_pt_jet12not16not20_scaled = (TH1F*)h_lead_pt_jet12not16not20->Clone("h_lead_pt_jet12not16not20_scaled");
    h_lead_pt_jet12not16not20_scaled->Scale(PS12);

    TH1F *h_lead_pt_jet16not20_scaled = (TH1F*)h_lead_pt_jet16not20->Clone("h_lead_pt_jet16not20_scaled");
    h_lead_pt_jet16not20_scaled->Scale(PS16);

    // Stack -- labeled by the lowest threshold trigger 
    h_lead_pt_jet8not20_scaled->SetFillColorAlpha(cmsBlue, 0.3);
    h_lead_pt_jet8not20_scaled->SetLineColor(cmsBlue);
    h_lead_pt_jet20->SetFillColorAlpha(cmsRed, 0.3);
    h_lead_pt_jet20->SetLineColor(cmsRed);
    h_lead_pt_jet8not20_scaled->SetFillStyle(1001); // Solid fill
    h_lead_pt_jet20->SetFillStyle(1001); // Solid fill
    h_lead_pt_jet20->SetLineWidth(1);

    THStack *hs_jet8not20 = new THStack("hs_jet8not20", "Leading Jet p_{T} Spectrum");
    hs_jet8not20->Add(h_lead_pt_jet8not20_scaled);
    hs_jet8not20->Add(h_lead_pt_jet20);

    h_lead_pt_jet8not12not16not20_scaled->SetFillColorAlpha(cmsBlue, 0.3);
    h_lead_pt_jet8not12not16not20_scaled->SetLineColor(cmsBlue);
    h_lead_pt_jet8not12not16not20_scaled->SetFillStyle(1001); // Solid fill

    h_lead_pt_jet12not16not20_scaled->SetFillColorAlpha(cmsViolet, 0.3);
    h_lead_pt_jet12not16not20_scaled->SetLineColor(cmsViolet);
    h_lead_pt_jet12not16not20_scaled->SetFillStyle(1001); // Solid fill
    
    h_lead_pt_jet12not16not20->SetFillColorAlpha(cmsViolet, 0.3);
    h_lead_pt_jet12not16not20->SetLineColor(cmsViolet);
    h_lead_pt_jet12not16not20->SetFillStyle(1001); // Solid fill

    h_lead_pt_jet16not20->SetFillColorAlpha(cmsOrange, 0.3);
    h_lead_pt_jet16not20->SetLineColor(cmsOrange);
    h_lead_pt_jet16not20->SetFillStyle(1001); // Solid fill

    h_lead_pt_jet16not20_scaled->SetFillColorAlpha(cmsOrange, 0.3);
    h_lead_pt_jet16not20_scaled->SetLineColor(cmsOrange);
    h_lead_pt_jet16not20_scaled->SetFillStyle(1001); // Solid fill

    THStack *hs_jet8not12not16not20 = new THStack("hs_jet8not12not16not20", "Leading Jet p_{T} Spectrum");
    hs_jet8not12not16not20->Add(h_lead_pt_jet8not12not16not20_scaled);
    hs_jet8not12not16not20->Add(h_lead_pt_jet12not16not20);
    hs_jet8not12not16not20->Add(h_lead_pt_jet16not20);
    hs_jet8not12not16not20->Add(h_lead_pt_jet20);

    THStack *hs_jet12not16not20 = new THStack("hs_jet12not16not20", "Leading Jet p_{T} Spectrum");
    hs_jet12not16not20->Add(h_lead_pt_jet12not16not20_scaled);
    hs_jet12not16not20->Add(h_lead_pt_jet16not20);
    hs_jet12not16not20->Add(h_lead_pt_jet20);

    THStack *hs_jet16not20 = new THStack("hs_jet16not20", "Leading Jet p_{T} Spectrum");
    hs_jet16not20->Add(h_lead_pt_jet16not20_scaled);
    hs_jet16not20->Add(h_lead_pt_jet20);

    h_lead_pt_jet8not16not20_scaled->SetFillColorAlpha(cmsBlue, 0.3);
    h_lead_pt_jet8not16not20_scaled->SetLineColor(cmsBlue);
    h_lead_pt_jet8not16not20_scaled->SetFillStyle(1001); // Solid fill

    THStack *hs_jet8not16not20 = new THStack("hs_jet8not16not20", "Leading Jet p_{T} Spectrum");
    hs_jet8not16not20->Add(h_lead_pt_jet8not16not20_scaled);
    hs_jet8not16not20->Add(h_lead_pt_jet16not20);
    hs_jet8not16not20->Add(h_lead_pt_jet20);

    // Draw -- labeled by the lowest threshold trigger 
    TCanvas *c_jet8not20 = new TCanvas("c_jet8not20", "jet8not20", 800, 700);
    TCanvas *c_jet8not16not20 = new TCanvas("c_jet8not16not20", "jet8not16not20", 800, 700);
    TCanvas *c_jet8not12not16not20 = new TCanvas("c_jet8not12not16not20", "jet8not12not16not20", 800, 700);
    TCanvas *c_jet12not16not20 = new TCanvas("c_jet12not16not20", "jet12not16not20", 800, 700);
    TCanvas *c_jet16not20 = new TCanvas("c_jet16not20", "jet16not20", 800, 700);

    // Legends
    TLegend *leg_jet8not20 = new TLegend(0.3, 0.65, 0.9, 0.85);
    leg_jet8not20->SetBorderSize(0);
    leg_jet8not20->SetMargin(0.1);
    leg_jet8not20->AddEntry(h_lead_pt_jet20, "Jet20", "f");
    leg_jet8not20->AddEntry(h_lead_pt_jet8not20_scaled, "Jet8&&!Jet20 (scaled by PS)", "f");

    TLegend *leg_jet8not16not20 = new TLegend(0.3, 0.65, 0.9, 0.85);
    leg_jet8not16not20->SetBorderSize(0);
    leg_jet8not16not20->SetMargin(0.1);
    leg_jet8not16not20->AddEntry(h_lead_pt_jet20, "Jet20", "f");
    leg_jet8not16not20->AddEntry(h_lead_pt_jet16not20, "Jet16 && !Jet20", "f");
    leg_jet8not16not20->AddEntry(h_lead_pt_jet8not16not20_scaled, "Jet8 && !Jet16 && !Jet20 (scaled by PS)", "f");

    TLegend *leg_jet8not12not16not20 = new TLegend(0.3, 0.65, 0.9, 0.85);
    leg_jet8not12not16not20->SetBorderSize(0);
    leg_jet8not12not16not20->SetMargin(0.1);
    leg_jet8not12not16not20->AddEntry(h_lead_pt_jet20, "Jet20", "f");
    leg_jet8not12not16not20->AddEntry(h_lead_pt_jet16not20, "Jet16 && !Jet20", "f");
    leg_jet8not12not16not20->AddEntry(h_lead_pt_jet12not16not20, "Jet12 && !Jet20", "f");
    leg_jet8not12not16not20->AddEntry(h_lead_pt_jet8not12not16not20_scaled, "Jet8 && !Jet12 && !Jet16 && !Jet20 (scaled by PS)", "f");

    TLegend *leg_jet12not16not20 = new TLegend(0.3, 0.65, 0.9, 0.85);
    leg_jet12not16not20->SetBorderSize(0);
    leg_jet12not16not20->SetMargin(0.1);
    leg_jet12not16not20->AddEntry(h_lead_pt_jet20, "Jet20", "f");
    leg_jet12not16not20->AddEntry(h_lead_pt_jet16not20, "Jet16 && !Jet20", "f");
    leg_jet12not16not20->AddEntry(h_lead_pt_jet12not16not20_scaled, "Jet12 && !Jet16 && !Jet20 (scaled by PS)", "f");

    TLegend *leg_jet16not20 = new TLegend(0.3, 0.65, 0.9, 0.85);
    leg_jet16not20->SetBorderSize(0);
    leg_jet16not20->SetMargin(0.1);
    leg_jet16not20->AddEntry(h_lead_pt_jet20, "Jet20", "f");
    leg_jet16not20->AddEntry(h_lead_pt_jet16not20_scaled, "Jet16 && !Jet20 (scaled by PS)", "f");

    std::vector<TCanvas*> canvases = {c_jet8not20, c_jet8not16not20, c_jet8not12not16not20, c_jet12not16not20, c_jet16not20};
    std::vector<THStack*> stacks = {hs_jet8not20, hs_jet8not16not20, hs_jet8not12not16not20, hs_jet12not16not20, hs_jet16not20};
    std::vector<TLegend*> legends = {leg_jet8not20, leg_jet8not16not20, leg_jet8not12not16not20, leg_jet12not16not20, leg_jet16not20};

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
        stacks[i]->GetXaxis()->SetRangeUser(0., 200);
        stacks[i]->GetYaxis()->SetTitle("N_{events}");
        stacks[i]->SetMinimum(1);
        stacks[i]->SetMaximum(1e8);

        
        legends[i]->Draw();

        // Save
        canvases[i]->Print("plots/" + sample + "_" + canvases[i]->GetTitle() + "_lead_pt_spectrum.pdf");
    }    
}