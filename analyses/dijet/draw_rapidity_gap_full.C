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
    data->DrawLatex(0.8, 0.92, "2023 PbPb (5.36 TeV)");
}

void draw_header_simulation() 
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
    data->DrawLatex(0.8, 0.92, "PYTHIA8 (Pb-#gamma 5.36 TeV)");
}

// ------------------------------------------------------------------ //
//
//  One canvas for one 3D histogram (x = dijet y, y = gap 1, z = gap 2):
//    left pad  : 2D map of (gap 1, gap 2), integrated over the chosen y range
//    right pad : 1D projections of gap 1 and gap 2
//
// ------------------------------------------------------------------ //
void draw_gap_canvas(TFile *fin, TString hname, TString xlab, TString ylab,
                     TString sample, TString suffix,
                     bool useYRange, double yMin, double yMax)
{
    TH3F *h3 = (TH3F *) fin->Get(hname);
    if (!h3) {
        std::cout << "ERROR: could not find " << hname << " in " << fin->GetName() << std::endl;
        return;
    }

    // dijet y range to integrate over
    if (useYRange) h3->GetXaxis()->SetRangeUser(yMin, yMax);

    // Project3D("zy"): x axis of the result = y axis of h3, y axis of the result = z axis of h3
    TH2D *h2  = (TH2D *) h3->Project3D("zy");
    TH1D *h_x = (TH1D *) h3->Project3D("y");
    TH1D *h_y = (TH1D *) h3->Project3D("z");
    h2->SetName(hname+"_2d");
    h_x->SetName(hname+"_projx");
    h_y->SetName(hname+"_projy");

    // restore full range on the 3D histogram
    h3->GetXaxis()->SetRange(0, 0);

    // Format
    h2->Scale(1. / h2->Integral());
    h2->SetTitle("");
    h2->GetXaxis()->SetTitle(xlab);
    h2->GetYaxis()->SetTitle(ylab);
    h2->GetZaxis()->SetTitle("Normalized entries per event");
    h2->GetZaxis()->SetTitleOffset(1.7);
    h2->GetZaxis()->SetRangeUser(0., 0.1);
    h2->GetXaxis()->SetRangeUser(0., 5.);
    h2->GetYaxis()->SetRangeUser(0., 5.);

    for (auto h : {h_x, h_y}) {
        h->Scale(1. / h->Integral());
        h->SetTitle("");
        h->GetXaxis()->SetTitle("#Delta#eta");
        h->GetYaxis()->SetTitle("Normalized entries per event");
        h->GetXaxis()->SetRangeUser(0., 5.);
    }
    double hmax = 1.3 * std::max(h_x->GetMaximum(), h_y->GetMaximum());
    h_x->GetYaxis()->SetRangeUser(0., hmax);
    h_y->GetYaxis()->SetRangeUser(0., hmax);

    h_x->SetLineColor(cmsBlue);
    h_x->SetMarkerColor(cmsBlue);
    h_x->SetMarkerStyle(kFullCircle);

    h_y->SetLineColor(cmsBlue);
    h_y->SetMarkerColor(cmsBlue);
    h_y->SetMarkerStyle(kOpenCircle);

    TLegend *leg = new TLegend(0.2, 0.5, 0.4, 0.65);
    leg->AddEntry(h_x, xlab, "pl");
    leg->AddEntry(h_y, ylab, "pl");

    // Draw
    TCanvas *c = new TCanvas("c_"+hname, hname, 1400, 700);
    c->Divide(2, 1);

    c->cd(1);
    c->cd(1)->SetTopMargin(0.1);
    c->cd(1)->SetBottomMargin(0.15);
    c->cd(1)->SetLeftMargin(0.15);
    c->cd(1)->SetRightMargin(0.2);

    h2->Draw("colz");
    if (sample.Contains("hiforward")) draw_header();
    else draw_header_simulation();

    c->cd(2);
    c->cd(2)->SetTopMargin(0.1);
    c->cd(2)->SetBottomMargin(0.15);
    c->cd(2)->SetLeftMargin(0.15);
    c->cd(2)->SetRightMargin(0.05);

    h_x->Draw("pe");
    h_y->Draw("pe same");
    leg->Draw();
    if (sample.Contains("hiforward")) draw_header();
    else draw_header_simulation();

    // event selection
    TLatex *sel = new TLatex();
    sel->SetNDC();
    sel->SetTextAlign(11);
    sel->SetTextSize(20);
    sel->DrawLatex(0.2, 0.8, "Events with AK4 dijets, p_{T,1} > 30 GeV, p_{T,2} > 20 GeV");
    if (useYRange) sel->DrawLatex(0.2, 0.76, Form("%.1f < y_{jj} < %.1f", yMin, yMax));
    else           sel->DrawLatex(0.2, 0.76, "all y_{jj}");    

    c->Print("plots/rapidity_gap/"+sample+suffix+"_"+hname+"_full.pdf");
}

// useYRange = false -> integrate over the full dijet y range
// useYRange = true  -> integrate over yMin < y < yMax
void draw_rapidity_gap_full(bool useYRange = true, double yMin = -1., double yMax = 1.)
{
    gStyle->SetOptStat(0);
    gStyle->SetPalette(kViridis);
    gStyle->SetLegendTextSize(24);
    gStyle->SetLabelSize(24, "XYZ");
    gStyle->SetTitleSize(28, "XYZ");

    // TString sample = "beamA_qcd_pthat10";
    TString sample = "hiforwardAll_2024rereco";
    TString suffix = "_noRG_jteta1p0";
    TFile *fin = new TFile("histos/"+sample+"_rapidity_gap_full"+suffix+".root"); // requires plot_rapgap_noise.C

    // rightmost (+) / leftmost (-) candidates gap
    draw_gap_canvas(fin, "h_y_vs_rapgap_rl",
                    "#Delta#eta^{+}", "#Delta#eta^{-}",
                    sample, suffix, useYRange, yMin, yMax);

    // second rightmost (+) / leftmost (-) candidates gap
    draw_gap_canvas(fin, "h_y_vs_rapgap2_rl",
                    "#Delta#eta^{+}_{2}", "#Delta#eta^{-}_{2}",
                    sample, suffix, useYRange, yMin, yMax);

    // smaller (<) / larger (>) gap
    draw_gap_canvas(fin, "h_y_vs_rapgap_sl",
                    "#Delta#eta^{<}", "#Delta#eta^{>}",
                    sample, suffix, useYRange, yMin, yMax);

    // second candidate smaller (<) / larger (>) gap
    draw_gap_canvas(fin, "h_y_vs_rapgap2_sl",
                    "#Delta#eta^{<}_{2}", "#Delta#eta^{>}_{2}",
                    sample, suffix, useYRange, yMin, yMax);
}