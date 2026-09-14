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

void draw_jet_kinematics()
{
    gStyle->SetPalette(kViridis);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);
    gStyle->SetPaintTextFormat("0.2f");

    TString sample = "hiforwardAll_2024rereco";
    TString suffix = "_HLT_ZDC";
    TFile *f = new TFile("histos/" + sample + "_jet_kinematics" + suffix + ".root"); // Created by plot_jet_kinematics.C
    TH1F *h_nref = (TH1F *) f->Get("h_nref");
    TH3F *h_nref_pt_eta_lead = (TH3F *) f->Get("h_nref_pt_eta_lead");
    TH3F *h_nref_pt_eta_sub = (TH3F *) f->Get("h_nref_pt_eta_sub");
    TH3F *h_nref_pt_eta_third = (TH3F *) f->Get("h_nref_pt_eta_third");

    // Make projections 
    TH2F *h_nref_pt_lead = (TH2F *) h_nref_pt_eta_lead->Project3D("xy");
    TH2F *h_nref_pt_sub = (TH2F *) h_nref_pt_eta_sub->Project3D("xy");
    TH2F *h_nref_pt_third = (TH2F *) h_nref_pt_eta_third->Project3D("xy");

    TH1F *h_pt_lead = (TH1F *) h_nref_pt_eta_lead->Project3D("y");
    h_pt_lead->SetMarkerStyle(kFullCircle);
    h_pt_lead->SetMarkerColor(cmsBlue);
    h_pt_lead->SetLineColor(cmsBlue);
    h_pt_lead->RebinX(5);

    TH1F *h_pt_sub = (TH1F *) h_nref_pt_eta_sub->Project3D("y");
    h_pt_sub->SetMarkerStyle(kFullSquare);
    h_pt_sub->SetMarkerColor(cmsLightBlue);
    h_pt_sub->SetLineColor(cmsLightBlue);
    h_pt_sub->RebinX(5);
    
    TH1F *h_pt_third = (TH1F *) h_nref_pt_eta_third->Project3D("y");
    h_pt_third->SetMarkerStyle(kFullTriangleUp);
    h_pt_third->SetMarkerColor(cmsViolet);
    h_pt_third->SetLineColor(cmsViolet);
    h_pt_third->RebinX(5);

    // Draw
    TCanvas *c_nref = new TCanvas("c_nref", "x=nref", 800, 700);
    c_nref->SetTopMargin(0.1);
    c_nref->SetBottomMargin(0.15);
    c_nref->SetLeftMargin(0.15);
    c_nref->SetRightMargin(0.05);
    c_nref->SetLogy();
    h_nref->GetXaxis()->SetTitle("Number of jets in event");
    h_nref->GetYaxis()->SetTitle("Number of events");
    h_nref->Draw();
    draw_header();

    TCanvas *c_nref_pt_lead = new TCanvas("c_nref_pt_lead", "x=ptlead, y=nref", 800, 700);
    c_nref_pt_lead->SetTopMargin(0.1);
    c_nref_pt_lead->SetBottomMargin(0.15);
    c_nref_pt_lead->SetLeftMargin(0.15);
    c_nref_pt_lead->SetRightMargin(0.15);
    c_nref_pt_lead->SetLogz();
    h_nref_pt_lead->GetYaxis()->SetTitle("Number of jets in event");
    h_nref_pt_lead->GetXaxis()->SetTitle("p_{T}^{jet,lead}");
    h_nref_pt_lead->Draw("colz");
    draw_header();

    TCanvas *c_nref_pt_sub = new TCanvas("c_nref_pt_sub", "x=ptsub, y=nref", 800, 700);
    c_nref_pt_sub->SetTopMargin(0.1);
    c_nref_pt_sub->SetBottomMargin(0.15);
    c_nref_pt_sub->SetLeftMargin(0.15);
    c_nref_pt_sub->SetRightMargin(0.15);
    c_nref_pt_sub->SetLogz();
    h_nref_pt_sub->GetYaxis()->SetTitle("Number of jets in event");
    h_nref_pt_sub->GetXaxis()->SetTitle("p_{T}^{jet,sub}");
    h_nref_pt_sub->Draw("colz");
    draw_header();

    TCanvas *c_nref_pt_third = new TCanvas("c_nref_pt_third", "x=ptthird, y=nref", 800, 700);
    c_nref_pt_third->SetTopMargin(0.1);
    c_nref_pt_third->SetBottomMargin(0.15);
    c_nref_pt_third->SetLeftMargin(0.15);
    c_nref_pt_third->SetRightMargin(0.15);
    c_nref_pt_third->SetLogz();
    h_nref_pt_third->GetYaxis()->SetTitle("Number of jets in event");
    h_nref_pt_third->GetXaxis()->SetTitle("p_{T}^{jet,third}");
    h_nref_pt_third->Draw("colz");
    draw_header();

    TCanvas *c_pt = new TCanvas("c_pt", "x=pt", 800, 700);
    c_pt->SetTopMargin(0.1);
    c_pt->SetBottomMargin(0.15);
    c_pt->SetLeftMargin(0.15);
    c_pt->SetRightMargin(0.05);
    c_pt->SetLogy();
    h_pt_lead->GetXaxis()->SetTitle("p_{T}^{jet}");
    h_pt_lead->GetYaxis()->SetTitle("Number of events");
    h_pt_lead->Draw();
    h_pt_sub->Draw("same");
    h_pt_third->Draw("same");
    draw_header();

    TLegend *leg_pt = new TLegend(0.6, 0.7, 0.85, 0.85);
    leg_pt->SetBorderSize(0);
    leg_pt->SetFillStyle(0);
    leg_pt->AddEntry(h_pt_lead, "Leading jet", "pl");
    leg_pt->AddEntry(h_pt_sub, "Subleading jet", "pl");
    leg_pt->AddEntry(h_pt_third, "Third jet", "pl");
    leg_pt->Draw();


}