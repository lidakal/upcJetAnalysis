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
    data->DrawLatex(0.95, 0.92, "2023 PbPb (5.36 TeV)");
}

void draw_header_simulation_A() 
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
    data->DrawLatex(0.95, 0.92, "PYTHIA8 (#gamma-Pb 5.36 TeV)");
}

void draw_header_simulation_B() 
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
    data->DrawLatex(0.95, 0.92, "PYTHIA8 (Pb-#gamma 5.36 TeV)");
}

void draw_rapidity()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);

    TString sample = "beamA_diffraction_pthat10";
    // TString sample = "hiforwardAll_2024rereco";

    // TString suffix = "";
    TString suffix_wSwap = "_oppHF_oppEC2_trkLim2p5_ptgr0p2_chOnly_jetID_jetVM_noAbsY";
    TString suffix_noSwap = "_oppHF_oppEC2_trkLim2p5_ptgr0p2_chOnly_jetID_jetVM_noSwap";

    TFile *f_wSwap = new TFile("histos/" + sample + "_dijet_kinematics" + suffix_wSwap + ".root"); // requires plot_dijet_kinematics.C
    TH1F *h_y_wSwap = (TH1F*)f_wSwap->Get("h_y")->Clone("h_y_wSwap");
    h_y_wSwap->SetLineColor(cmsBlue);
    h_y_wSwap->SetMarkerColor(cmsBlue);

    TFile *f_noSwap = new TFile("histos/" + sample + "_dijet_kinematics" + suffix_noSwap + ".root"); // requires plot_dijet_kinematics.C
    TH1F *h_y_noSwap = (TH1F*)f_noSwap->Get("h_y")->Clone("h_y_noSwap");
    h_y_noSwap->SetLineColor(cmsOrange);
    h_y_noSwap->SetMarkerColor(cmsOrange);

    // Draw
    TCanvas *c_rapidity = new TCanvas("c_rapidity", "x=dijet y", 800, 700);
    c_rapidity->SetTopMargin(0.1);
    c_rapidity->SetBottomMargin(0.15);
    c_rapidity->SetLeftMargin(0.15);
    c_rapidity->SetRightMargin(0.05);
    for (auto h : {h_y_wSwap, h_y_noSwap}) {
        h->Rebin(2);
        // h->Scale(1/h->Integral());
        h->GetXaxis()->SetTitle("Dijet y");
        h->GetXaxis()->SetTitleOffset(1.2);
        h->GetYaxis()->SetTitle("N_{events}");
        // h->GetYaxis()->SetRangeUser(0.,h->GetMaximum()*1.5);
        h->GetYaxis()->SetRangeUser(0.,800.);
        h->Draw("same");
    }
    TLegend *leg = new TLegend(0.2, 0.7, 0.5, 0.85);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(h_y_noSwap, "Original", "pl");
    leg->AddEntry(h_y_wSwap, "#eta^{jet}#rightarrow-#eta^{jet} when #Delta#eta^{+} > #Delta#eta^{-}", "pl");
    leg->Draw();
    if (sample.Contains("beamA")) draw_header_simulation_A();
    else if (sample.Contains("beamB")) draw_header_simulation_B();
    else draw_header();

    c_rapidity->Print("plots/"+sample+"_rapidity.pdf");
}
