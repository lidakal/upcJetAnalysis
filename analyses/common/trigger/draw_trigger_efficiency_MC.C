#include "../../../cms_palette.h"

void draw_header() 
{
    TLatex *cms = new TLatex();
    cms->SetNDC();
    cms->SetTextAlign(11);
    cms->SetTextSize(28);
    cms->DrawLatex(0.15, 0.92, "#bf{CMS} #it{Simulation Internal}");

    TLatex *data = new TLatex();
    data->SetNDC();
    data->SetTextAlign(31);
    data->SetTextSize(28);
    data->DrawLatex(0.95, 0.92, "PYTHIA8 (PbPb 5.36 TeV)");
}

void draw_trigger_efficiency_MC()
{
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);
    gStyle->SetPaintTextFormat("0.2f");

    TString sample = "beamB_diffraction_pthat10";
    // TFile *f = new TFile("histos/" + sample + "_pt_spectrum_mc.root"); // Created by plot_pt_spectrum_MC.C
    TFile *f = new TFile("pt_spectrum_mc.root"); // Created by plot_pt_spectrum_MC.C
    TH2F *h_lead_pt_Jet8 = (TH2F*) f->Get("h_lead_pt_Jet8");
    TH2F *h_lead_pt_Jet12 = (TH2F*) f->Get("h_lead_pt_Jet12");
    TH2F *h_lead_pt_Jet16 = (TH2F*) f->Get("h_lead_pt_Jet16");
    TH2F *h_lead_pt_Jet20 = (TH2F*) f->Get("h_lead_pt_Jet20");

    // Create efficiency graphs
    TH1F *h_den_Jet8 = (TH1F*) h_lead_pt_Jet8->ProjectionX("h_den_Jet8", 1, 2);
    TH1F *h_eff_Jet8 = (TH1F*) h_lead_pt_Jet8->ProjectionX("h_eff_Jet8", 2, 2);
    h_eff_Jet8->Divide(h_den_Jet8);
    h_eff_Jet8->SetLineColor(cmsBlue);

    TH1F *h_den_Jet12 = (TH1F*) h_lead_pt_Jet12->ProjectionX("h_den_Jet12", 1, 2);
    TH1F *h_eff_Jet12 = (TH1F*) h_lead_pt_Jet12->ProjectionX("h_eff_Jet12", 2, 2);
    h_eff_Jet12->Divide(h_den_Jet12);
    h_eff_Jet12->SetLineColor(cmsViolet);

    TH1F *h_den_Jet16 = (TH1F*) h_lead_pt_Jet16->ProjectionX("h_den_Jet16", 1, 2);
    TH1F *h_eff_Jet16 = (TH1F*) h_lead_pt_Jet16->ProjectionX("h_eff_Jet16", 2, 2);
    h_eff_Jet16->Divide(h_den_Jet16);
    h_eff_Jet16->SetLineColor(cmsOrange);

    TH1F *h_den_Jet20 = (TH1F*) h_lead_pt_Jet20->ProjectionX("h_den_Jet20", 1, 2);
    TH1F *h_eff_Jet20 = (TH1F*) h_lead_pt_Jet20->ProjectionX("h_eff_Jet20", 2, 2);
    h_eff_Jet20->Divide(h_den_Jet20);
    h_eff_Jet20->SetLineColor(cmsRed);

    for (auto h : {h_eff_Jet8, h_eff_Jet12, h_eff_Jet16, h_eff_Jet20}) {
        h->SetLineWidth(2);
        h->SetMarkerColor(h->GetLineColor());
        h->GetXaxis()->SetTitle("p_{T}^{jet, lead} (GeV)");
        h->GetXaxis()->SetRangeUser(0., 100);
        h->GetYaxis()->SetTitle("Trigger efficiency");
        h->SetMinimum(0.);
        h->SetMaximum(1.1);
        h->SetMarkerSize(600);
    }

    TCanvas *c_eff = new TCanvas("c_eff", "c_eff", 800, 700);
    c_eff->SetTopMargin(0.1);
    c_eff->SetBottomMargin(0.15);
    c_eff->SetLeftMargin(0.15);
    c_eff->SetRightMargin(0.05);

    h_eff_Jet8->Draw("hist text same");
    h_eff_Jet12->Draw("hist text same");
    h_eff_Jet16->Draw("hist text same");
    h_eff_Jet20->Draw("hist text same");
    draw_header();

    TLegend *leg_eff = new TLegend(0.5, 0.2, 0.7, 0.5);
    leg_eff->SetBorderSize(0);
    leg_eff->SetMargin(0.15);
    leg_eff->SetHeader("NotMBAND AND");
    leg_eff->AddEntry(h_eff_Jet8, "Jet8", "l");
    leg_eff->AddEntry(h_eff_Jet12, "Jet12", "l");
    leg_eff->AddEntry(h_eff_Jet16, "Jet16", "l");
    leg_eff->AddEntry(h_eff_Jet20, "Jet20", "l");
    leg_eff->Draw();

    c_eff->Print("plots/" + sample + "_trigger_efficiency_MC.pdf");
}
