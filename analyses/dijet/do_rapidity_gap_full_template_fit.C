#include "../../cms_palette.h"

#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooFitResult.h"
#include "RooAbsData.h"
#include "RooGlobalFunc.h"
#include "RooMsgService.h"

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
//  Template fit of the *smaller* gap (y axis of the _sl histograms):
//      data = f * diffraction + (1 - f) * QCD
//  The larger gap (z axis) is only used for the cut  larger gap >= detaMin.
//  All distributions are normalized to unit area inside the fit range,
//  so f is the diffraction fraction (shape fraction).
//
//  Two minimizers:
//    "roofit" : RooFit chi2 fit (RooHistPdf + RooAddPdf), Minuit/Migrad.
//               Uses the data bin errors only.
//    "grid"   : custom chi2 scan of f on a regular grid in [0,1].
//               Uncertainty from chi2 < chi2_min + 1.
//               Optionally includes the MC template stat. errors.
//
// ------------------------------------------------------------------ //
struct FitConfig {
    TString method = "grid";         // "grid" or "roofit"
    int     nsteps = 1000;           // grid: number of steps in f in [0,1]
    bool    useTemplateErrors = true; // grid: include template stat. errors in the chi2
    double  xmin = 0.;               // fit range in delta eta
    double  xmax = 5.;
};

struct FitResult {
    double f = 0.;
    double ferr = 0.;
    double chi2 = 0.;
    int    ndf = 0;
    bool   ok = false;
    TGraph *gchi2 = nullptr;         // chi2 as a function of f (for the chi2 canvas)
    TString uid;                     // histogram name (+ cut tag), used in the chi2 file name
};

// bins of h covered by the fit range
void get_fit_bins(const TH1D *h, double xmin, double xmax, int &b1, int &b2)
{
    b1 = h->GetXaxis()->FindBin(xmin + 1e-6);
    b2 = h->GetXaxis()->FindBin(xmax - 1e-6);
}

// ------------------------------------------------------------------ //
//
//  Get the normalized 1D projection of the smaller gap (y axis) of a
//  3D histogram (x = dijet y, y = smaller gap, z = larger gap),
//  integrated over the y range.
//  If zMin > 0, only events with larger gap (z axis) >= zMin are kept
//  *before* projecting.
//  The projection is normalized to unit area inside the fit range.
//
// ------------------------------------------------------------------ //
bool get_smaller_gap_projection(TFile *fin, TString hname, TString tag,
                                bool useYRange, double yMin, double yMax,
                                double zMin, double fitXmin, double fitXmax,
                                TH1D *&h)
{
    TH3F *h3 = (TH3F *) fin->Get(hname);
    if (!h3) {
        std::cout << "ERROR: could not find " << hname << " in " << fin->GetName() << std::endl;
        return false;
    }

    if (useYRange) h3->GetXaxis()->SetRangeUser(yMin, yMax);
    if (zMin > 0.) h3->GetZaxis()->SetRangeUser(zMin, h3->GetZaxis()->GetXmax());

    TString cuttag = (zMin > 0.) ? Form("_zMin%g", zMin) : "";
    h = (TH1D *) h3->Project3D("y");
    h->SetName(hname+"_proj_"+tag+cuttag);

    // restore full range on the 3D histogram
    h3->GetXaxis()->SetRange(0, 0);
    h3->GetZaxis()->SetRange(0, 0);

    int b1, b2;
    get_fit_bins(h, fitXmin, fitXmax, b1, b2);
    double integral = h->Integral(b1, b2);
    if (integral <= 0.) {
        std::cout << "ERROR: empty projection " << h->GetName() << " in the fit range" << std::endl;
        return false;
    }
    h->Scale(1. / integral);
    h->SetTitle("");
    h->GetXaxis()->SetTitle("#Delta#eta");
    h->GetYaxis()->SetTitle("Normalized entries per event");
    h->GetXaxis()->SetRangeUser(0., 5.);
    return true;
}

// ------------------------------------------------------------------ //
//  Copy the fit-range bins of a histogram into a histogram with bins 1..N
//  (so the fit only sees the fit range).
// ------------------------------------------------------------------ //
TH1D *extract_fit_range(const TH1D *h, TString name, double xmin, double xmax)
{
    int b1, b2;
    get_fit_bins(h, xmin, xmax, b1, b2);
    int N = b2 - b1 + 1;
    TH1D *hc = new TH1D(name, name, N, 0., N);
    for (int b=b1; b<=b2; b++) {
        hc->SetBinContent(b-b1+1, h->GetBinContent(b));
        hc->SetBinError(b-b1+1, h->GetBinError(b));
    }
    return hc;
}

// ------------------------------------------------------------------ //
//  chi2 of  f*h1 + (1-f)*h2  with respect to hd
//  (bins with zero variance are skipped)
// ------------------------------------------------------------------ //
double compute_chi2(const TH1D *hd, const TH1D *h1, const TH1D *h2, double f,
                    bool useTemplateErrors, int &nused)
{
    double chi2 = 0.;
    nused = 0;
    for (int b=1; b<=hd->GetNbinsX(); b++) {
        double model = f * h1->GetBinContent(b) + (1. - f) * h2->GetBinContent(b);
        double var = std::pow(hd->GetBinError(b), 2);
        if (useTemplateErrors) {
            var += f*f * std::pow(h1->GetBinError(b), 2)
                 + (1.-f)*(1.-f) * std::pow(h2->GetBinError(b), 2);
        }
        if (var <= 0.) continue;
        chi2 += std::pow(hd->GetBinContent(b) - model, 2) / var;
        nused++;
    }
    return chi2;
}

// ------------------------------------------------------------------ //
//  Option 1: custom chi2 grid minimization
// ------------------------------------------------------------------ //
bool fit_grid(const TH1D *hd, const TH1D *h1, const TH1D *h2, const FitConfig &cfg,
              double &f, double &ferr)
{
    int n = std::max(cfg.nsteps, 10);
    std::vector<double> chi2s(n+1);
    int kmin = 0;
    int nused = 0;
    for (int k=0; k<=n; k++) {
        chi2s[k] = compute_chi2(hd, h1, h2, (double) k / n, cfg.useTemplateErrors, nused);
        if (chi2s[k] < chi2s[kmin]) kmin = k;
    }

    // uncertainty: range of f with chi2 <= chi2_min + 1
    int klo = kmin, khi = kmin;
    while (klo > 0 && chi2s[klo-1] <= chi2s[kmin] + 1.) klo--;
    while (khi < n && chi2s[khi+1] <= chi2s[kmin] + 1.) khi++;

    f = (double) kmin / n;
    ferr = std::max(0.5 * (double)(khi - klo) / n, 0.5 / n);
    if (kmin == 0 || kmin == n) {
        std::cout << "WARNING: grid minimum at the boundary f = " << f
                  << " (uncertainty is one-sided/limited by the [0,1] range)" << std::endl;
    }
    return true;
}

// ------------------------------------------------------------------ //
//  Option 2: RooFit chi2 fit with Minuit (data errors only)
// ------------------------------------------------------------------ //
bool fit_roofit(TH1D *hd, TH1D *h1, TH1D *h2, TString uid, double &f, double &ferr)
{
    using namespace RooFit;
    RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);

    int nb = hd->GetNbinsX();
    RooRealVar x(("x_"+uid).Data(), "x", 0., (double) nb);
    x.setBins(nb);

    RooDataHist dh_data(("dh_data_"+uid).Data(), "data",         RooArgList(x), Import(*hd));
    RooDataHist dh_1   (("dh_1_"+uid).Data(),    "diffraction",  RooArgList(x), Import(*h1));
    RooDataHist dh_2   (("dh_2_"+uid).Data(),    "qcd",          RooArgList(x), Import(*h2));

    RooHistPdf pdf_1(("pdf_1_"+uid).Data(), "diffraction", RooArgSet(x), dh_1, 0);
    RooHistPdf pdf_2(("pdf_2_"+uid).Data(), "qcd",         RooArgSet(x), dh_2, 0);

    RooRealVar frac(("frac_"+uid).Data(), "diffraction fraction", 0.5, 0., 1.);
    RooAddPdf model(("model_"+uid).Data(), "f*diffraction + (1-f)*qcd",
                    RooArgList(pdf_1, pdf_2), RooArgList(frac));

    RooFitResult *res = model.chi2FitTo(dh_data,
                                        DataError(RooAbsData::SumW2),
                                        Minimizer("Minuit", "Migrad"),
                                        Save(), PrintLevel(-1));
    if (!res) return false;
    bool ok = (res->status() == 0);
    if (!ok) std::cout << "WARNING: Minuit status = " << res->status() << " for " << uid << std::endl;

    f = frac.getVal();
    ferr = frac.getError();
    delete res;
    return ok;
}

// ------------------------------------------------------------------ //
//  Run the fit (data, diffraction template, QCD template)
//  and scan the chi2 as a function of f (same definition as the fit
//  for "grid"; data errors only for "roofit").
// ------------------------------------------------------------------ //
FitResult run_fit(const TH1D *hd, const TH1D *h1, const TH1D *h2, const FitConfig &cfg, TString uid)
{
    FitResult r;
    TH1D *cd = extract_fit_range(hd, "cd_"+uid, cfg.xmin, cfg.xmax);
    TH1D *c1 = extract_fit_range(h1, "c1_"+uid, cfg.xmin, cfg.xmax);
    TH1D *c2 = extract_fit_range(h2, "c2_"+uid, cfg.xmin, cfg.xmax);

    if (cfg.method == "roofit") r.ok = fit_roofit(cd, c1, c2, uid, r.f, r.ferr);
    else                        r.ok = fit_grid(cd, c1, c2, cfg, r.f, r.ferr);

    bool tmplErr = (cfg.method != "roofit") && cfg.useTemplateErrors;
    int nused = 0;
    r.chi2 = compute_chi2(cd, c1, c2, r.f, tmplErr, nused);
    r.ndf = nused - 1;

    // chi2 vs f
    int n = std::max(cfg.nsteps, 10);
    r.gchi2 = new TGraph(n+1);
    r.gchi2->SetName("gchi2_"+uid);
    for (int k=0; k<=n; k++) {
        double ff = (double) k / n;
        r.gchi2->SetPoint(k, ff, compute_chi2(cd, c1, c2, ff, tmplErr, nused));
    }

    delete cd;
    delete c1;
    delete c2;
    return r;
}

// ------------------------------------------------------------------ //
//
//  One canvas for one 3D histogram (_sl): data, scaled MC templates and
//  total fit of the smaller gap.
//  zMin > 0 additionally requires the larger gap (z axis) >= zMin.
//  Returns the fit result (with the chi2 vs f graph).
//
// ------------------------------------------------------------------ //
FitResult draw_template_fit_canvas(TFile *f_data, TFile *f_diff, TFile *f_qcd,
                                   TString hname, TString xlab, TString zlab,
                                   TString outtag, bool isData, const FitConfig &cfg,
                                   bool useYRange, double yMin, double yMax,
                                   double zMin = -1.)
{
    bool useZCut = (zMin > 0.);
    TString cuttag = useZCut ? Form("_detaMin%g", zMin) : "";
    TString uid = hname + cuttag;

    TH1D *hd = nullptr, *h1 = nullptr, *h2 = nullptr;
    if (!get_smaller_gap_projection(f_data, hname, "data", useYRange, yMin, yMax, zMin, cfg.xmin, cfg.xmax, hd)) return FitResult();
    if (!get_smaller_gap_projection(f_diff, hname, "diff", useYRange, yMin, yMax, zMin, cfg.xmin, cfg.xmax, h1)) return FitResult();
    if (!get_smaller_gap_projection(f_qcd,  hname, "qcd",  useYRange, yMin, yMax, zMin, cfg.xmin, cfg.xmax, h2)) return FitResult();

    // fit
    FitResult res = run_fit(hd, h1, h2, cfg, uid);
    res.uid = uid;
    std::cout << uid << " [" << cfg.method << "] " << xlab
              << ": f_diff = " << res.f << " +- " << res.ferr
              << ", chi2/ndf = " << res.chi2 << "/" << res.ndf
              << (res.ok ? "" : "  (FIT PROBLEM)") << std::endl;

    // fitted components
    TH1D *c1 = (TH1D *) h1->Clone("fitc1_"+uid);
    c1->Scale(res.f);
    TH1D *c2 = (TH1D *) h2->Clone("fitc2_"+uid);
    c2->Scale(1. - res.f);
    TH1D *csum = (TH1D *) h1->Clone("fitsum_"+uid);
    csum->Add(h1, h2, res.f, 1. - res.f);

    // 1.6: leave room for the text
    double hmax = std::max({hd->GetMaximum(), csum->GetMaximum(), c1->GetMaximum(), c2->GetMaximum()});
    hd->GetYaxis()->SetRangeUser(0., 1.6*hmax);
    hd->GetXaxis()->SetTitle(xlab);

    hd->SetLineColor(kBlack);
    hd->SetMarkerColor(kBlack);
    hd->SetMarkerStyle(kFullCircle);

    c1->SetLineColor(cmsBlue);
    c1->SetLineStyle(kDashed);
    c1->SetLineWidth(2);
    c2->SetLineColor(cmsRed);
    c2->SetLineStyle(kDashed);
    c2->SetLineWidth(2);
    csum->SetLineColor(kGreen+2);
    csum->SetLineWidth(2);

    TLegend *leg = new TLegend(0.6, 0.5, 0.93, 0.72);
    leg->AddEntry(hd, "Data", "pe");
    leg->AddEntry(csum, "Template fit", "l");
    leg->AddEntry(c1, "Diffraction (f)", "l");
    leg->AddEntry(c2, "QCD (1-f)", "l");

    // Draw
    TCanvas *c = new TCanvas("c_fit_"+uid, uid, 800, 700);
    c->SetTopMargin(0.1);
    c->SetBottomMargin(0.15);
    c->SetLeftMargin(0.15);
    c->SetRightMargin(0.05);

    hd->Draw("pe");
    c1->Draw("hist same");
    c2->Draw("hist same");
    csum->Draw("hist same");
    hd->Draw("pe same");
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
    double ytxt = 0.72;
    if (useZCut) {
        sel->DrawLatex(0.2, ytxt, Form("%s #geq %g", zlab.Data(), zMin));
        ytxt -= 0.04;
    }

    // fit result
    TString method = (cfg.method == "roofit") ? "RooFit (Minuit)" : "#chi^{2} grid";
    sel->DrawLatex(0.2, ytxt - 0.02, method);
    sel->DrawLatex(0.2, ytxt - 0.06, Form("f_{diff} = %.3f #pm %.3f", res.f, res.ferr));
    sel->DrawLatex(0.2, ytxt - 0.10, Form("#chi^{2}/ndf = %.1f/%d", res.chi2, res.ndf));

    c->Print("plots/rapidity_gap/"+outtag+"_"+hname+cuttag+"_"+cfg.method+"_full.pdf");
    return res;
}

// ------------------------------------------------------------------ //
//
//  One canvas per fit with the chi2 as a function of f.
//  Solid red line = best fit, dotted red = +-1 sigma,
//  dashed black = chi2_min + 1.
//
// ------------------------------------------------------------------ //
void draw_chi2_canvas(const std::vector<FitResult> &results, const std::vector<TString> &labels,
                      const FitConfig &cfg, TString outtag, bool isData)
{
    int n = results.size();

    for (int i=0; i<n; i++) {
        const FitResult &r = results[i];
        if (!r.gchi2) continue;
        TGraph *g = r.gchi2;

        TCanvas *c = new TCanvas("c_chi2_"+r.uid, "chi2 vs f "+r.uid, 800, 700);
        c->SetTopMargin(0.1);
        c->SetBottomMargin(0.15);
        c->SetLeftMargin(0.15);
        c->SetRightMargin(0.05);

        double chi2min = TMath::MinElement(g->GetN(), g->GetY());
        double ylo = std::max(0., chi2min - 3.);
        double yhi = chi2min + 40.;

        g->SetTitle("");
        g->SetMinimum(ylo);
        g->SetMaximum(yhi);
        g->GetXaxis()->SetLimits(0., 1.);
        g->GetXaxis()->SetTitle("f_{diff}");
        g->GetYaxis()->SetTitle("#chi^{2}");
        g->SetLineColor(kBlack);
        g->SetLineWidth(2);
        g->Draw("AL");

        // best fit and +- 1 sigma
        TLine *l_best = new TLine(r.f, ylo, r.f, yhi);
        l_best->SetLineColor(cmsRed);
        l_best->SetLineWidth(2);
        l_best->Draw();
        for (double fe : {r.f - r.ferr, r.f + r.ferr}) {
            TLine *l_err = new TLine(fe, ylo, fe, yhi);
            l_err->SetLineColor(cmsRed);
            l_err->SetLineStyle(kDotted);
            l_err->Draw();
        }
        TLine *l_min1 = new TLine(0., chi2min+1., 1., chi2min+1.);
        l_min1->SetLineStyle(kDashed);
        l_min1->Draw();

        if (isData) draw_header();
        else        draw_header_simulation();

        TLatex *txt = new TLatex();
        txt->SetNDC();
        txt->SetTextAlign(11);
        txt->SetTextSize(20);
        txt->DrawLatex(0.2, 0.82, labels[i]);
        txt->DrawLatex(0.2, 0.77, Form("f_{diff} = %.3f #pm %.3f", r.f, r.ferr));
        txt->DrawLatex(0.2, 0.72, Form("#chi^{2}_{min}/ndf = %.1f/%d", r.chi2, r.ndf));

        c->Print("plots/rapidity_gap/"+outtag+"_chi2_"+r.uid+"_"+cfg.method+"_full.pdf");
    }
}

// useYRange = false -> integrate over the full dijet y range
// useYRange = true  -> integrate over yMin < y < yMax
// detaMin           -> minimum larger gap for the additional canvases with a cut
// fitMethod         -> "grid" (custom chi2 scan) or "roofit" (RooFit + Minuit)
void do_rapidity_gap_full_template_fit(bool useYRange = true, double yMin = -1., double yMax = 1.,
                                       double detaMin = 2.,
                                       TString fitMethod = "grid",
                                       double fitXmin = 0.2, double fitXmax = 3.5)
{
    gStyle->SetOptStat(0);
    gStyle->SetPalette(kViridis);
    gStyle->SetLegendTextSize(24);
    gStyle->SetLabelSize(24, "XYZ");
    gStyle->SetTitleSize(28, "XYZ");

    if (fitMethod != "grid" && fitMethod != "roofit") {
        std::cout << "ERROR: fitMethod must be \"grid\" or \"roofit\"" << std::endl;
        return;
    }

    FitConfig cfg;
    cfg.method = fitMethod;
    cfg.xmin = fitXmin;
    cfg.xmax = fitXmax;
    // cfg.nsteps = 1000;             // grid resolution in f
    // cfg.useTemplateErrors = true;  // grid: include MC template stat. errors

    TString suffix_data = "_0n0n_noRG_jteta1p0";
    TString suffix_mc = "_noRG_jteta1p0";
    TString outtag = "templatefit"; // used in the output file names

    TString sample_data = "hiforwardAll_2024rereco";
    TString sample_diff = "beamA_diffraction_pthat10";
    TString sample_qcd  = "beamA_qcd_pthat10";

    TFile *f_data = new TFile("histos/"+sample_data+"_rapidity_gap_full"+suffix_data+".root"); // requires plot_rapgap_noise.C
    TFile *f_diff = new TFile("histos/"+sample_diff+"_rapidity_gap_full"+suffix_mc+".root");
    TFile *f_qcd  = new TFile("histos/"+sample_qcd+"_rapidity_gap_full"+suffix_mc+".root");

    bool isData = sample_data.Contains("hiforward");

    std::vector<FitResult> results;
    std::vector<TString> labels; // for the chi2 canvas

    // smaller gap (<), integrated over the larger gap (>)
    results.push_back(draw_template_fit_canvas(f_data, f_diff, f_qcd,
                             "h_y_vs_rapgap_sl", "#Delta#eta^{<}", "#Delta#eta^{>}",
                             outtag, isData, cfg, useYRange, yMin, yMax));
    labels.push_back("#Delta#eta^{<}");

    // second candidate smaller gap (<), integrated over the larger gap (>)
    results.push_back(draw_template_fit_canvas(f_data, f_diff, f_qcd,
                             "h_y_vs_rapgap2_sl", "#Delta#eta^{<}_{2}", "#Delta#eta^{>}_{2}",
                             outtag, isData, cfg, useYRange, yMin, yMax));
    labels.push_back("#Delta#eta^{<}_{2}");

    // same two, but requiring the larger gap (z axis) >= detaMin before projecting
    results.push_back(draw_template_fit_canvas(f_data, f_diff, f_qcd,
                             "h_y_vs_rapgap_sl", "#Delta#eta^{<}", "#Delta#eta^{>}",
                             outtag, isData, cfg, useYRange, yMin, yMax, detaMin));
    labels.push_back(Form("#Delta#eta^{<}, #Delta#eta^{>} #geq %g", detaMin));

    results.push_back(draw_template_fit_canvas(f_data, f_diff, f_qcd,
                             "h_y_vs_rapgap2_sl", "#Delta#eta^{<}_{2}", "#Delta#eta^{>}_{2}",
                             outtag, isData, cfg, useYRange, yMin, yMax, detaMin));
    labels.push_back(Form("#Delta#eta^{<}_{2}, #Delta#eta^{>}_{2} #geq %g", detaMin));

    // chi2 vs f for all the fits
    draw_chi2_canvas(results, labels, cfg, outtag, isData);
}