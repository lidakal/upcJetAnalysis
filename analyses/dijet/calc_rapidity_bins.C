#include "../../cms_palette.h"

// ------------------------------------------------------------------ //
//
//  Find merged bins of h_y with (approximately) equal statistics.
//
//  Consecutive bins of the original histogram are merged into nBins
//  groups. The k-th internal boundary is put on the original bin edge
//  where the cumulative content is closest to k/nBins of the total
//  (inside the range [yMin, yMax]), so the groups are as equal as the
//  original binning allows.
//
//  Returns the list of bin edges (nBins+1 values, or fewer if the
//  original binning is too coarse to make nBins distinct groups).
//
// ------------------------------------------------------------------ //
std::vector<double> find_equal_stat_edges(TH1 *h, int nBins, double yMin, double yMax)
{
    TAxis *ax = h->GetXaxis();
    int b1 = ax->FindBin(yMin + 1e-6);
    int b2 = ax->FindBin(yMax - 1e-6);
    int nOrig = b2 - b1 + 1;

    if (nBins < 1) {
        std::cout << "ERROR: nBins must be >= 1" << std::endl;
        return {};
    }
    if (nBins > nOrig) {
        std::cout << "WARNING: nBins=" << nBins << " > number of original bins in range (" << nOrig
                  << "), using " << nOrig << std::endl;
        nBins = nOrig;
    }

    // cumulative[j] = content of bins b1 .. b1+j-1  (cumulative[0] = 0)
    std::vector<double> cumulative(nOrig+1, 0.);
    for (int j=0; j<nOrig; j++) cumulative[j+1] = cumulative[j] + h->GetBinContent(b1+j);
    double total = cumulative[nOrig];
    if (total <= 0.) {
        std::cout << "ERROR: histogram is empty in the range [" << yMin << ", " << yMax << "]" << std::endl;
        return {};
    }

    // boundary index j means the edge between original bins b1+j-1 and b1+j
    std::vector<int> cuts = {0};
    for (int k=1; k<nBins; k++) {
        double target = total * k / nBins;
        int best = -1;
        double bestDiff = 1e300;
        // must leave at least one original bin for each remaining merged bin
        int jmin = cuts.back() + 1;
        int jmax = nOrig - (nBins - k);
        for (int j=jmin; j<=jmax; j++) {
            double diff = std::abs(cumulative[j] - target);
            if (diff < bestDiff) { bestDiff = diff; best = j; }
        }
        cuts.push_back(best);
    }
    cuts.push_back(nOrig);

    std::vector<double> edges;
    for (int j : cuts) edges.push_back(ax->GetBinLowEdge(b1+j));
    edges.back() = ax->GetBinUpEdge(b2);
    return edges;
}

// nBins      -> final number of merged bins (tunable)
// yMin, yMax -> range of the h_y histogram to use (default: whole histogram)
void calc_rapidity_bins(int nBins = 6, double yMin = -999., double yMax = 999.)
{
    gStyle->SetOptStat(0);
    gStyle->SetTitleSize(32, "XYZ");
    gStyle->SetLabelSize(28, "XYZ");
    gStyle->SetLegendTextSize(28);

    // TString sample = "beamA_qcd_pthat10";
    TString sample = "hiforwardAll_2024rereco";

    TString suffix = "_0n0n_oppHF_SingleJet8";

    TFile *f = new TFile("histos/" + sample + "_dijet_kinematics" + suffix + ".root");
    TH1F *h_y = (TH1F*)f->Get("h_y");
    if (!h_y) {
        std::cout << "ERROR: could not find h_y in " << f->GetName() << std::endl;
        return;
    }

    // Preprocess (optional: rebin the original histogram first, as in draw_dijet_kinematics)
    // h_y->Rebin(2);

    // restrict to the histogram range
    yMin = std::max(yMin, h_y->GetXaxis()->GetXmin());
    yMax = std::min(yMax, h_y->GetXaxis()->GetXmax());

    // Find the edges
    std::vector<double> edges = find_equal_stat_edges(h_y, nBins, yMin, yMax);
    if (edges.size() < 2) return;
    int nMerged = edges.size() - 1;

    // Print
    double total = h_y->Integral(h_y->GetXaxis()->FindBin(yMin + 1e-6), h_y->GetXaxis()->FindBin(yMax - 1e-6));
    std::cout << "\nh_y from " << f->GetName() << "\n"
              << "Range [" << yMin << ", " << yMax << "], total entries = " << total
              << ", target per bin = " << total / nMerged << "\n" << std::endl;

    std::cout << "Bin\tlow edge\thigh edge\tentries\tfraction\tdeviation from target" << std::endl;
    std::vector<double> contents(nMerged);
    for (int i=0; i<nMerged; i++) {
        int blo = h_y->GetXaxis()->FindBin(edges[i] + 1e-6);
        int bhi = h_y->GetXaxis()->FindBin(edges[i+1] - 1e-6);
        contents[i] = h_y->Integral(blo, bhi);
        std::cout << i+1 << "\t" << edges[i] << "\t\t" << edges[i+1] << "\t\t"
                  << contents[i] << "\t" << contents[i] / total << "\t"
                  << Form("%+.1f%%", 100. * (contents[i] / (total / nMerged) - 1.))
                  << std::endl;
    }

    // Bin edges as a C++ array, ready to copy
    std::cout << "\ndouble y_bins[" << edges.size() << "] = {";
    for (size_t i=0; i<edges.size(); i++) std::cout << (i ? ", " : "") << edges[i];
    std::cout << "};\n" << std::endl;

    // Draw: original h_y with the merged-bin edges, and the merged histogram
    TCanvas *c = new TCanvas("c_equal_stat", "c_equal_stat", 1600, 800);
    c->Divide(2,1);

    c->cd(1);
    h_y->SetLineColor(cmsBlue);
    h_y->SetMarkerColor(cmsBlue);
    h_y->GetXaxis()->SetTitle("Dijet rapidity");
    h_y->GetYaxis()->SetTitle("N_{events}");
    h_y->GetXaxis()->SetRangeUser(yMin, yMax);
    h_y->SetMaximum(1.2 * h_y->GetMaximum());
    h_y->Draw();
    for (size_t i=0; i<edges.size(); i++) {
        TLine *l = new TLine(edges[i], 0., edges[i], h_y->GetMaximum());
        l->SetLineColor(cmsRed);
        l->SetLineStyle(kDashed);
        l->Draw();
    }

    c->cd(2);
    TH1D *h_merged = new TH1D("h_y_equal_stat", "", nMerged, edges.data());
    for (int i=0; i<nMerged; i++) {
        h_merged->SetBinContent(i+1, contents[i]);
        h_merged->SetBinError(i+1, std::sqrt(contents[i]));
    }
    h_merged->SetLineColor(cmsRed);
    h_merged->SetMarkerColor(cmsRed);
    h_merged->GetXaxis()->SetTitle("Dijet rapidity");
    h_merged->GetYaxis()->SetTitle("N_{events}");
    h_merged->SetMinimum(0.);
    h_merged->SetMaximum(1.5 * h_merged->GetMaximum());
    h_merged->Draw("pe");

    c->Print("plots/dijet_kinematics/" + sample + "_h_y_equal_stat_bins.pdf");
}