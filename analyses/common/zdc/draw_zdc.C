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

void draw_zdc()
{
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);
    
    TString sample = "";
    // TFile *fin = new TFile("histos/"+sample+"_zdc.root");
    TFile *fin = new TFile("zdc.root");
    TH2F *h_Esum = (TH2F *) fin->Get("h_Esum"); 

    // Make projections
    h_Esum->GetXaxis()->SetRange(0, h_Esum->GetNbinsX()+1);
    h_Esum->GetYaxis()->SetRange(0, h_Esum->GetNbinsY()+1);
    TH1F *h_sumPlus = (TH1F *) h_Esum->ProjectionX();
    h_sumPlus->SetLineColor(cmsBlue);
    TH1F *h_sumMinus = (TH1F *) h_Esum->ProjectionY();
    h_sumMinus->SetLineColor(cmsOrange);

    // Format
    double ymin = 10., ymax = std::max(h_sumPlus->GetMaximum(), h_sumMinus->GetMaximum())*10;
    for (auto h : {h_sumPlus, h_sumMinus}) {
        // h->SetLineWidth(2);
        h->SetMarkerColor(h->GetLineColor());
        h->GetXaxis()->SetTitle("Offline energy sum (GeV)");
        // h->GetXaxis()->SetRangeUser(0., 200);
        h->GetYaxis()->SetTitle("Number of events");
        h->SetMinimum(ymin);
        h->SetMaximum(ymax);
        // h->SetMarkerSize(600);
        h->Rebin(10);
    }

    // Make legend
    TLegend *leg = new TLegend(0.6, 0.6, 0.8, 0.8);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(h_sumPlus, "ZDC+", "pl");
    leg->AddEntry(h_sumMinus, "ZDC-", "pl");

    // Draw
    TCanvas *c_Esum = new TCanvas("c_Esum", "c_Esum", 800, 700);
    c_Esum->SetTopMargin(0.1);
    c_Esum->SetBottomMargin(0.15);
    c_Esum->SetLeftMargin(0.15);
    c_Esum->SetRightMargin(0.05);
    c_Esum->SetLogy();

    h_sumPlus->Draw();
    h_sumMinus->Draw("same");
    leg->Draw();

    TLine *line_sumPlus = new TLine(1100., ymin, 1100., ymax);
    line_sumPlus->SetLineColorAlpha(h_sumPlus->GetLineColor(), 0.5);
    line_sumPlus->SetLineStyle(2);
    line_sumPlus->SetLineWidth(2);
    line_sumPlus->Draw();

    TLine *line_sumMinus = new TLine(1000., ymin, 1000., ymax);
    line_sumMinus->SetLineColorAlpha(h_sumMinus->GetLineColor(), 0.5);
    line_sumMinus->SetLineStyle(2);
    line_sumMinus->SetLineWidth(2);
    line_sumMinus->Draw();

    draw_header();

    c_Esum->Print("plots/"+sample+"_zdc2.pdf");
    
}