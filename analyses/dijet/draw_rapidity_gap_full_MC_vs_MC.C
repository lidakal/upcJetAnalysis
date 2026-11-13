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
//  Get the two normalized 1D gap projections of a 3D histogram
//  (x = dijet y, y = gap 1, z = gap 2), integrated over the y range.
//  If zMin > 0, only events with gap 2 (z axis) >= zMin are kept
//  *before* projecting (for the _sl histograms, z = larger gap).
//
// ------------------------------------------------------------------ //
bool get_gap_projections(TFile *fin, TString hname, TString tag,
                         bool useYRange, double yMin, double yMax,
                         double zMin,
                         TH1D *&h_x, TH1D *&h_y)
{
    TH3F *h3 = (TH3F *) fin->Get(hname);
    if (!h3) {
        std::cout << "ERROR: could not find " << hname << " in " << fin->GetName() << std::endl;
        return false;
    }

    if (useYRange) h3->GetXaxis()->SetRangeUser(yMin, yMax);
    if (zMin > 0.) h3->GetZaxis()->SetRangeUser(zMin, h3->GetZaxis()->GetXmax());

    TString cuttag = (zMin > 0.) ? Form("_zMin%g", zMin) : "";
    h_x = (TH1D *) h3->Project3D("y");
    h_y = (TH1D *) h3->Project3D("z");
    h_x->SetName(hname+"_projx_"+tag+cuttag);
    h_y->SetName(hname+"_projy_"+tag+cuttag);

    // restore full range on the 3D histogram
    h3->GetXaxis()->SetRange(0, 0);
    h3->GetZaxis()->SetRange(0, 0);

    for (auto h : {h_x, h_y}) {
        h->Scale(1. / h->Integral());
        h->SetTitle("");
        h->GetXaxis()->SetTitle("#Delta#eta");
        h->GetYaxis()->SetTitle("Normalized entries per event");
        h->GetXaxis()->SetRangeUser(0., 5.);
    }
    return true;
}

// ------------------------------------------------------------------ //
//
//  One canvas for one 3D histogram: 1D projections of both gaps,
//  overlaid for all samples.
//  zMin > 0 additionally requires gap 2 (z axis) >= zMin.
//
// ------------------------------------------------------------------ //
void draw_gap_comparison_canvas(std::vector<TFile *> &fins,
                                std::vector<TString> &tags,
                                std::vector<TString> &labels,
                                std::vector<int> &colors,
                                std::vector<int> &markers_x,
                                std::vector<int> &markers_y,
                                TString hname, TString xlab, TString ylab,
                                TString outtag, bool isData,
                                bool useYRange, double yMin, double yMax,
                                double zMin = -1.)
{
    bool useZCut = (zMin > 0.);
    TString cuttag = useZCut ? Form("_detaMin%g", zMin) : "";

    int ns = fins.size();
    std::vector<TH1D *> hx(ns, nullptr), hy(ns, nullptr);

    double hmax = 0.;
    for (int i=0; i<ns; i++) {
        if (!get_gap_projections(fins[i], hname, tags[i], useYRange, yMin, yMax, zMin, hx[i], hy[i])) return;
        hmax = std::max({hmax, hx[i]->GetMaximum(), hy[i]->GetMaximum()});

        hx[i]->SetLineColor(colors[i]);
        hx[i]->SetMarkerColor(colors[i]);
        hx[i]->SetMarkerStyle(markers_x[i]);

        hy[i]->SetLineColor(colors[i]);
        hy[i]->SetMarkerColor(colors[i]);
        hy[i]->SetMarkerStyle(markers_y[i]);
    }
    for (int i=0; i<ns; i++) {
        hx[i]->GetYaxis()->SetRangeUser(0., 1.3*hmax);
        hy[i]->GetYaxis()->SetRangeUser(0., 1.3*hmax);
    }

    // legend: one column per sample; sample name, then gap 1, then gap 2
    // (shifted down when there is an extra cut line of text)
    double legShift = useZCut ? 0.06 : 0.;
    TLegend *leg = new TLegend(0.2, 0.5-legShift, 0.2+0.15*ns, 0.72-legShift);
    leg->SetNColumns(ns);
    for (int i=0; i<ns; i++) leg->AddEntry(new TH1F(), labels[i], "");
    for (int i=0; i<ns; i++) leg->AddEntry(hx[i], xlab, "pl");
    for (int i=0; i<ns; i++) leg->AddEntry(hy[i], ylab, "pl");

    // Draw
    TCanvas *c = new TCanvas("c_comp_"+hname+cuttag, hname+cuttag, 800, 700);
    c->SetTopMargin(0.1);
    c->SetBottomMargin(0.15);
    c->SetLeftMargin(0.15);
    c->SetRightMargin(0.05);

    bool first = true;
    for (int i=0; i<ns; i++) {
        hx[i]->Draw(first ? "pe" : "pe same");
        first = false;
        hy[i]->Draw("pe same");
    }
    leg->Draw();
    if (isData) draw_header();
    else        draw_header_simulation();

    // event selection
    TLatex *sel = new TLatex();
    sel->SetNDC();
    sel->SetTextAlign(11);
    sel->SetTextSize(20);
    sel->DrawLatex(0.2, 0.8, "Events with AK4 dijets, p_{T,1} > 30 GeV, p_{T,2} > 20 GeV");
    if (useYRange) sel->DrawLatex(0.2, 0.76, Form("%.1f < y_{jj} < %.1f", yMin, yMax));
    else           sel->DrawLatex(0.2, 0.76, "all y_{jj}");
    // gap 2 is the one cut on: the larger gap for the _sl histograms
    if (useZCut)   sel->DrawLatex(0.2, 0.72, Form("%s #geq %g", ylab.Data(), zMin));

    c->Print("plots/rapidity_gap/"+outtag+"_"+hname+cuttag+"_full.pdf");
}

// useYRange = false -> integrate over the full dijet y range
// useYRange = true  -> integrate over yMin < y < yMax
// detaMin           -> minimum larger gap for the additional _sl canvases
void draw_rapidity_gap_full_MC_vs_MC(bool useYRange = true, double yMin = -1., double yMax = 1.,
                                     double detaMin = 2.)
{
    gStyle->SetOptStat(0);
    gStyle->SetPalette(kViridis);
    gStyle->SetLegendTextSize(24);
    gStyle->SetLabelSize(24, "XYZ");
    gStyle->SetTitleSize(28, "XYZ");

    TString suffix_data = "_0n0n_noRG_jteta1p0";
    TString suffix_mc = "_noRG_jteta1p0";
    TString outtag = "data_vs_MC"; // used in the output file names

    // samples to compare (add more entries to each list to add a sample)
    std::vector<TString> samples = {
        "hiforwardAll_2024rereco",
        "beamA_diffraction_pthat10",
        "beamA_qcd_pthat10",
    };
    std::vector<TString> labels = {"0n0n Data", "Diffraction", "QCD"};
    std::vector<int> colors = {kBlack, cmsBlue, cmsRed};
    std::vector<int> markers_x = {kFullCircle, kFullTriangleUp, kFullSquare}; // first gap
    std::vector<int> markers_y = {kOpenCircle, kOpenTriangleUp, kOpenSquare}; // second gap

    bool isData = false;
    std::vector<TFile *> fins;
    for (auto &s : samples) {
        if (s.Contains("hiforward")) isData = true;
        TString suffix = (s.Contains("hiforward")) ? suffix_data : suffix_mc;
        fins.push_back(new TFile("histos/"+s+"_rapidity_gap_full"+suffix+".root")); // requires plot_rapgap_noise.C
    }

    // rightmost (+) / leftmost (-) candidates gap
    // draw_gap_comparison_canvas(fins, samples, labels, colors, markers_x, markers_y,
    //                            "h_y_vs_rapgap_rl", "#Delta#eta^{+}", "#Delta#eta^{-}",
    //                            outtag, isData, useYRange, yMin, yMax);

    // // second rightmost (+) / leftmost (-) candidates gap
    // draw_gap_comparison_canvas(fins, samples, labels, colors, markers_x, markers_y,
    //                            "h_y_vs_rapgap2_rl", "#Delta#eta^{+}_{2}", "#Delta#eta^{-}_{2}",
    //                            outtag, isData, useYRange, yMin, yMax);

    // smaller (<) / larger (>) gap
    draw_gap_comparison_canvas(fins, samples, labels, colors, markers_x, markers_y,
                               "h_y_vs_rapgap_sl", "#Delta#eta^{<}", "#Delta#eta^{>}",
                               outtag, isData, useYRange, yMin, yMax);

    // second candidate smaller (<) / larger (>) gap
    draw_gap_comparison_canvas(fins, samples, labels, colors, markers_x, markers_y,
                               "h_y_vs_rapgap2_sl", "#Delta#eta^{<}_{2}", "#Delta#eta^{>}_{2}",
                               outtag, isData, useYRange, yMin, yMax);

    // same two, but requiring the larger gap (z axis) >= detaMin before projecting
    draw_gap_comparison_canvas(fins, samples, labels, colors, markers_x, markers_y,
                               "h_y_vs_rapgap_sl", "#Delta#eta^{<}", "#Delta#eta^{>}",
                               outtag, isData, useYRange, yMin, yMax, detaMin);

    draw_gap_comparison_canvas(fins, samples, labels, colors, markers_x, markers_y,
                               "h_y_vs_rapgap2_sl", "#Delta#eta^{<}_{2}", "#Delta#eta^{>}_{2}",
                               outtag, isData, useYRange, yMin, yMax, detaMin);
}