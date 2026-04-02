#include "../cms_palette.h"

void drawHeader()
{
    TLatex *latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(26);
    latex->DrawLatex(0.15, 0.92, "#bf{CMS} #it{Simulation}");
    latex->DrawLatex(0.48, 0.92, "PYTHIA8 GNucleus (5.36 TeV)");
}

void formatCanvas(TCanvas *c)
{
    c->SetLeftMargin(0.15);
    c->SetRightMargin(0.05);
    c->SetBottomMargin(0.15);
    c->SetTopMargin(0.1);
}

void draw_jes_distribution()
{
    gStyle->SetTitleSize(28, "XYZ");
    gStyle->SetLabelSize(24, "XYZ");
    gStyle->SetLegendTextSize(24);

    TString suffix = "ppJEC";
    TFile *fin = new TFile("histos/beamAPlusB_pthat0_"+suffix+"_kinematics.root");
    TH3F *h_jes_vs_refpt_vs_jteta = (TH3F *) fin->Get("h_jes_vs_refpt_vs_jteta"); // no JEC

    // Select eta range
    double etamin = -5.1, etamax = +5.1;
    int zmin = h_jes_vs_refpt_vs_jteta->GetZaxis()->FindBin(etamin);
    int zmax = h_jes_vs_refpt_vs_jteta->GetZaxis()->FindBin(etamax);
    double realetamin = h_jes_vs_refpt_vs_jteta->GetZaxis()->GetBinLowEdge(zmin);
    double realetamax = h_jes_vs_refpt_vs_jteta->GetZaxis()->GetBinUpEdge(zmax);
    std::cout << "\nSelecting eta range " << etamin << " to " << etamax << std::endl;
    std::cout << "Which corresponds to bins " << zmin << " to " << zmax << std::endl;
    std::cout << "Which corresponds to actual eta range " << realetamin << " to " << realetamax << std::endl;

    // Make projections
    TH1F *jes_0_5 = (TH1F *) h_jes_vs_refpt_vs_jteta->ProjectionY("jes_0_5", 
        h_jes_vs_refpt_vs_jteta->GetXaxis()->FindBin(0.), h_jes_vs_refpt_vs_jteta->GetXaxis()->FindBin(5.), zmin, zmax);
    TH1F *jes_5_6 = (TH1F *) h_jes_vs_refpt_vs_jteta->ProjectionY("jes_5_6", 
        h_jes_vs_refpt_vs_jteta->GetXaxis()->FindBin(5.), h_jes_vs_refpt_vs_jteta->GetXaxis()->FindBin(6.), zmin, zmax);
    TH1F *jes_6_7 = (TH1F *) h_jes_vs_refpt_vs_jteta->ProjectionY("jes_6_7", 
        h_jes_vs_refpt_vs_jteta->GetXaxis()->FindBin(6.), h_jes_vs_refpt_vs_jteta->GetXaxis()->FindBin(7.), zmin, zmax);
    TH1F *jes_7_8 = (TH1F *) h_jes_vs_refpt_vs_jteta->ProjectionY("jes_7_8", 
        h_jes_vs_refpt_vs_jteta->GetXaxis()->FindBin(7.), h_jes_vs_refpt_vs_jteta->GetXaxis()->FindBin(8.), zmin, zmax);
    TH1F *jes_8_9 = (TH1F *) h_jes_vs_refpt_vs_jteta->ProjectionY("jes_8_9", 
        h_jes_vs_refpt_vs_jteta->GetXaxis()->FindBin(8.), h_jes_vs_refpt_vs_jteta->GetXaxis()->FindBin(9.), zmin, zmax);
    TH1F *jes_9_10 = (TH1F *) h_jes_vs_refpt_vs_jteta->ProjectionY("jes_9_10", 
        h_jes_vs_refpt_vs_jteta->GetXaxis()->FindBin(9.), h_jes_vs_refpt_vs_jteta->GetXaxis()->FindBin(10.), zmin, zmax);

    // Format histos
    std::vector<TH1F*> histos = {jes_0_5, jes_5_6, jes_6_7, jes_7_8, jes_8_9, jes_9_10};
    std::vector<int> colors = {cmsBlue, cmsViolet, cmsRed, cmsOrange, cmsYellow, cmsLightOlive};
    for (size_t i = 0; i < histos.size(); ++i) {
        histos[i]->Scale(1. / histos[i]->Integral(), "width");
        histos[i]->SetLineColor(colors[i]);
        histos[i]->SetLineWidth(3);
    }

    jes_0_5->GetXaxis()->SetTitle("p_{T}^{raw} / p_{T}^{gen}");
    jes_0_5->GetXaxis()->SetTitleOffset(1.2);
    jes_0_5->GetYaxis()->SetTitle("1/N dN/d(p_{T}^{raw} / p_{T}^{gen})");
    jes_0_5->GetYaxis()->SetRangeUser(0., 2.);

    // Build legend
    TLegend *legend = new TLegend(0.55, 0.4, 0.85, 0.85);
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetHeader(Form("AK4, %0.3f < #eta^{jet} < %0.3f", realetamin, realetamax));
    legend->AddEntry(jes_0_5, "0 < p_{T}^{gen} < 5 GeV", "l");
    legend->AddEntry(jes_5_6, "5 < p_{T}^{gen} < 6 GeV", "l");
    legend->AddEntry(jes_6_7, "6 < p_{T}^{gen} < 7 GeV", "l");
    legend->AddEntry(jes_7_8, "7 < p_{T}^{gen} < 8 GeV", "l");
    legend->AddEntry(jes_8_9, "8 < p_{T}^{gen} < 9 GeV", "l");
    legend->AddEntry(jes_9_10, "9 < p_{T}^{gen} < 10 GeV", "l");


    // Draw
    TCanvas *c_jes = new TCanvas("c_jes", "", 700, 600);
    formatCanvas(c_jes);
    jes_0_5->Draw("hist");
    jes_5_6->Draw("hist same");
    jes_6_7->Draw("hist same");
    jes_7_8->Draw("hist same");
    jes_8_9->Draw("hist same");
    jes_9_10->Draw("hist same");
    drawHeader();
    legend->Draw();

    // TLatex *info = new TLatex();
    // info->SetNDC();
    // info->SetTextSize(24);
    // info->DrawLatex(0.15, 0.85, Form("%0.1f < |#eta| < %0.1f", etamin, etamax));
    // info->DrawLatex(0.15, 0.80, Form("%0.1f < p_{T}^{ref} < %0.1f GeV", ptmin, ptmax));

}
