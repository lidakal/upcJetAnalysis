// do_template_fit.C
// Usage:
//    root -l -b -q do_template_fit.C                  // uses default histogram "h_y"
//    root -l -b -q 'do_template_fit("h_pt")'          // any other histogram name
//
// Loads data + three template files, reads the histogram `histName` from each,
// renames the clones per file, and performs an extended binned template fit
// with RooFit:
//     data(obs) = nA * templateA(obs) + nB * templateB(obs) + nC * templateC(obs)
//
// Everything downstream of `histName` (RooFit variable, titles, output file)
// is generic, so reusing the macro only requires changing the histogram name.

#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TString.h"

#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooFit.h"

#include <iostream>

using namespace RooFit;

// ---------------------------------------------------------------- files
const char *fnData = "histos/hiforwardAll_2024rereco_pf_distribution_0nXnOneSided_HFm_trkLim3p0.root";
const char *fnA    = "histos/beamA_diffraction_pthat10_pf_distribution_oppHF_trkLim3p0.root";
const char *fnB    = "histos/beamA_diffractionSide2_pthat10_pf_distribution_oppHF_trkLim3p0.root";
const char *fnC    = "histos/beamA_qcd_pthat10_pf_distribution_oppHF_trkLim3p0.root";

// const char *fnData = "histos/hiforwardAll_2024rereco_dijet_kinematics_0nXnOneSided_HFm.root";
// const char *fnA    = "histos/beamA_diffraction_pthat10_dijet_kinematics_oppHF.root";
// const char *fnB    = "histos/beamA_diffractionSide2_pthat10_dijet_kinematics_oppHF.root";
// const char *fnC    = "histos/beamA_qcd_pthat10_dijet_kinematics_oppHF.root";

// ------------------------------------------------------------------ ranges
// const double xmin = -1.; // dijet y
// const double xmax = 2.5; // dijet y
const double xmin = 0.; // brg
const double xmax = 5.; // brg
// const double xmin = 0.005; // x2
// const double xmax = 0.15; // x2

// ------------------------------------------------------------------ titles
const char *xTitle = "BRG"; // brg
// const char *xTitle = "x_{2}"; // x2

// --------------------------------------------------------------------------
// Result container: fractions and their errors, in the order of the templates
// --------------------------------------------------------------------------
struct FitOutput {
   std::vector<double> frac;
   std::vector<double> err;
   RooFitResult *res = nullptr;
};

// --------------------------------------------------------------------------
// Open a file, fetch the histogram, clone it under a new name, detach it.
// --------------------------------------------------------------------------
static TH1 *loadHist1D(const char *fileName, TFile *&f, const char *histName, const char *newName)
{
   f = TFile::Open(fileName, "READ");
   if (!f || f->IsZombie()) {
      std::cerr << "ERROR: cannot open file " << fileName << std::endl;
      return nullptr;
   }
   TH1 *h = dynamic_cast<TH1 *>(f->Get(histName));
   if (!h) {
      std::cerr << "ERROR: histogram " << histName << " not found in " << fileName << std::endl;
      return nullptr;
   }
   TH1 *hc = (TH1 *)h->Clone(newName);
   hc->SetTitle(newName);
   hc->SetDirectory(nullptr); // survives closing the file
   return hc;
}

static TH3 *loadHist3D(const char *fileName, TFile *&f, const char *histName, const char *newName)
{
   f = TFile::Open(fileName, "READ");
   if (!f || f->IsZombie()) {
      std::cerr << "ERROR: cannot open file " << fileName << std::endl;
      return nullptr;
   }
   TH3 *h = dynamic_cast<TH3 *>(f->Get(histName));
   if (!h) {
      std::cerr << "ERROR: histogram " << histName << " not found in " << fileName << std::endl;
      return nullptr;
   }
   TH3 *hc = (TH3 *)h->Clone(newName);
   hc->SetTitle(newName);
   hc->SetDirectory(nullptr); // survives closing the file
   return hc;
}

static bool sameBinning(TH1 *a, TH1 *b)
{
   return a->GetNbinsX() == b->GetNbinsX() &&
          a->GetXaxis()->GetXmin() == b->GetXaxis()->GetXmin() &&
          a->GetXaxis()->GetXmax() == b->GetXaxis()->GetXmax();
}

// --------------------------------------------------------------------------
// Plot all templates, each normalised to unit area, on its own canvas
// --------------------------------------------------------------------------
void plotTemplates(const char *histName, const std::vector<TH1 *> &hT,
                   const std::vector<TString> &names)
{
   const int n = hT.size();
   const int colors[4] = {kBlue, kGreen + 2, kMagenta, kOrange + 7};

   TCanvas *c = new TCanvas(Form("c_templates_%s_%d", histName, n), "Templates (unit area)", 700, 600);
   TLegend *leg = new TLegend(0.2, 0.72, 0.5, 0.89);
   leg->SetBorderSize(0);

   std::vector<TH1 *> hn;
   double ymax = 0.;
   for (int i = 0; i < n; ++i) {
      TH1 *h = (TH1 *)hT[i]->Clone(Form("%s_norm%d_%d", histName, n, i));
      h->SetDirectory(nullptr);
      const double integral = h->Integral();
      if (integral > 0) h->Scale(1. / integral);
      h->SetStats(0);
      h->SetLineColor(colors[i % 4]);
      h->SetLineWidth(2);
      if (h->GetMaximum() > ymax) ymax = h->GetMaximum();
      leg->AddEntry(h, names[i], "l");
      h->GetXaxis()->SetRangeUser(xmin,xmax);
      hn.push_back(h);
   }

   hn[0]->SetTitle(Form("Templates for %s (unit area);%s;Normalised entries / bin", xTitle, xTitle));
   hn[0]->SetMaximum(1.5 * ymax);
   hn[0]->SetMinimum(0.);
   hn[0]->Draw("HIST");
   for (int i = 1; i < n; ++i) hn[i]->Draw("HIST SAME");
   leg->Draw();
   // c->SetLogx();

   c->SaveAs(Form("templates_%s_%d.png", histName, n));
}

// --------------------------------------------------------------------------
// Generic template fit for N templates (N >= 2).
//   tag      : short label used to make RooFit object / canvas names unique
//   histName : name of the histogram being fitted (titles, output file)
// --------------------------------------------------------------------------
FitOutput runTemplateFit(const char *tag, const char *histName, TH1 *h_data,
                         const std::vector<TH1 *> &hT, const std::vector<TString> &names)
{
   FitOutput out;
   const int n = hT.size();
   if (n < 2 || (int)names.size() != n) {
      std::cerr << "runTemplateFit: need at least 2 templates and one name per template." << std::endl;
      return out;
   }

   // ----- observable (generic name "obs", title from the x-axis title) ------
   const char *obsTitle = strlen(h_data->GetXaxis()->GetTitle()) ? h_data->GetXaxis()->GetTitle() : histName;
   RooRealVar *obs = new RooRealVar(Form("obs_%s", tag), obsTitle, xmin, xmax);

   RooDataHist *dh_data = new RooDataHist(Form("dh_data_%s", tag), "data", RooArgList(*obs), h_data);

   // ----- template PDFs ----------------------------------------------------
   RooArgList pdfList;
   std::vector<RooHistPdf *> pdfs;
   for (int i = 0; i < n; ++i) {
      RooDataHist *dh = new RooDataHist(Form("dh_%s_%d", tag, i), names[i], RooArgList(*obs), hT[i]);
      RooHistPdf *pdf = new RooHistPdf(Form("pdf_%s_%d", tag, i), names[i], RooArgSet(*obs), *dh);
      pdfs.push_back(pdf);
      pdfList.add(*pdf);
   }

   // ----- fractions: N-1 free, the last one is 1 - sum(others) ------------
   RooArgList coefList;
   std::vector<RooRealVar *> fr;
   TString formula = "1.0";
   for (int i = 0; i < n - 1; ++i) {
      RooRealVar *f = new RooRealVar(Form("f_%s_%d", tag, i), Form("fraction %s", names[i].Data()),
                                     1. / n, 0., 1.);
      if (i==0) {
         f->setVal(0.08);
         f->setError(0.001);
      }
      if (i==1) {
         f->setVal(0.005);
         f->setError(0.001);
      }
      fr.push_back(f);
      coefList.add(*f);
      formula += Form(" - @%d", i);
   }
   RooFormulaVar *fLast = new RooFormulaVar(Form("f_%s_last", tag),
                                            Form("fraction %s", names[n - 1].Data()), formula, coefList);

   RooAddPdf *model = new RooAddPdf(Form("model_%s", tag), "template sum", pdfList, coefList);

   // ----- fit (non-extended: only shapes / fractions) ---------------------
   RooFitResult *res = model->fitTo(*dh_data, 
      Minimizer("Minuit2","migrad"), Strategy(2), Hesse(2),
      SumW2Error(true), Save(true), PrintLevel(1), Verbose(true));
   out.res = res;

      // ---- Fit status check ----
   bool fitOK = true;

   // MIGRAD status: 0 = converged
   if (res->status() != 0) {
      std::cerr << "FIT WARNING: status = " << res->status() << " (expected 0)" << std::endl;
      fitOK = false;
   }
   // Covariance quality: 3 = full, accurate matrix
   if (res->covQual() != 3) {
      std::cerr << "FIT WARNING: covQual = " << res->covQual() << " (expected 3)" << std::endl;
      fitOK = false;
   }
   // Estimated distance to minimum: should be tiny
   if (res->edm() > 1e-3) {
      std::cerr << "FIT WARNING: EDM = " << res->edm() << " (large)" << std::endl;
      fitOK = false;
   }
   // Invalid likelihood evaluations (the NaN problem you saw)
   if (res->numInvalidNLL() > 0) {
      std::cerr << "FIT NOTE: " << res->numInvalidNLL()
                << " invalid NLL evaluations during minimisation" << std::endl;
   }
   // Parameters stuck at their limits
   const RooArgList &pars = res->floatParsFinal();
   for (int i = 0; i < pars.getSize(); ++i) {
      RooRealVar *p = dynamic_cast<RooRealVar *>(pars.at(i));
      if (!p) continue;
      const double range = p->getMax() - p->getMin();
      if (p->getVal() - p->getMin() < 1e-3 * range || p->getMax() - p->getVal() < 1e-3 * range) {
         std::cerr << "FIT NOTE: " << p->GetName() << " = " << p->getVal()
                   << " is at its limit [" << p->getMin() << ", " << p->getMax() << "]" << std::endl;
      }
   }
   std::cout << "\n\n" << std::endl;
   std::cout << (fitOK ? "FIT OK" : "FIT NOT OK") << " (status " << res->status()
             << ", covQual " << res->covQual() << ", EDM " << res->edm()
             << ", minNLL " << res->minNll() << ")" << std::endl;

   std::cout << "\n\n" << std::endl;
   RooFitResult *res2 = model->fitTo(*dh_data, SumW2Error(true), Save(true),
                                     Strategy(2), PrintLevel(-1));
   std::cout << "refit: status " << res2->status() << ", covQual " << res2->covQual()
             << ", EDM " << res2->edm() << ", minNll " << res2->minNll() << std::endl;
   for (int i = 0; i < n - 1; ++i) {
      std::cout << Form("  f%d: first fit %.4f +/- %.4f | refit %.4f +/- %.4f\n", i,
                        res->floatParsFinal().at(i) ? ((RooRealVar *)res->floatParsFinal().at(i))->getVal() : 0.,
                        ((RooRealVar *)res->floatParsFinal().at(i))->getError(),
                        fr[i]->getVal(), fr[i]->getError());
   }

   for (int i = 0; i < n - 1; ++i) {
      out.frac.push_back(fr[i]->getVal());
      out.err.push_back(fr[i]->getError());
   }
   out.frac.push_back(fLast->getVal());
   out.err.push_back(fLast->getPropagatedError(*res)); // includes correlations

      // ---- TEST: force fractions AFTER the fit results have been stored ----
   // const std::vector<double> forced = {0.08, 0.005};   // N-1 values: fA, fB (C = 1 - fA - fB)
   // if (!forced.empty()) {
   //    for (int i = 0; i < n - 1 && i < (int)forced.size(); ++i) {
   //       fr[i]->setVal(forced[i]);
   //       fr[i]->setError(0.);
   //       out.frac[i] = forced[i];
   //       out.err[i]  = 0.;
   //    }
   //    out.frac[n - 1] = fLast->getVal(); // recomputed from the forced values
   //    out.err[n - 1]  = 0.;
   //    std::cout << ">>> FRACTIONS FORCED, not the fit result <<<" << std::endl;
   // }

   std::cout << "\n===== Template fit (" << n << " templates) on " << histName << " =====\n";
   res->Print("v");
   double sum = 0.;
   for (int i = 0; i < n; ++i) {
      std::cout << Form("f%s = %.2f +/- %.2f %%\n", names[i].Data(), 100. * out.frac[i], 100. * out.err[i]);
      sum += out.frac[i];
   }
   std::cout << Form("sum = %.2f %%   (data integral = %.1f)\n", 100. * sum, h_data->Integral());
   std::cout << "=====================================================\n";

   // ----- plot -------------------------------------------------------------
   const int colors[4] = {kBlue, kGreen + 2, kMagenta, kOrange + 7};

   TCanvas *c = new TCanvas(Form("c_fit_%s_%s", tag, histName), Form("Template fit (%d templates)", n), 800, 800);
   TPad *pad1 = new TPad(Form("pad1_%s", tag), "pad1", 0, 0.3, 1, 1);
   TPad *pad2 = new TPad(Form("pad2_%s", tag), "pad2", 0, 0.0, 1, 0.3);
   pad1->SetBottomMargin(0.02);
   pad2->SetTopMargin(0.03);
   pad2->SetBottomMargin(0.3);
   pad1->Draw();
   pad2->Draw();

   RooPlot *frame = obs->frame(Title(Form("Template fit to %s (%d templates)", histName, n)));
   dh_data->plotOn(frame, Name("data"));
   model->plotOn(frame, Name("total"), LineColor(kRed));
   for (int i = 0; i < n; ++i) {
      model->plotOn(frame, Name(Form("comp%d", i)), Components(*pdfs[i]),
                    LineColor(colors[i % 4]), LineStyle(kDashed));
   }

   // Explicit y-range: guards against a bad auto-range hiding data and curves
   frame->SetMinimum(0.);
   frame->SetMaximum(1.5 * h_data->GetMaximum());

   pad1->cd();
   frame->GetXaxis()->SetLabelSize(0);
   frame->GetXaxis()->SetTitleSize(0);
   frame->Draw();
   // pad1->SetLogx();

   TLegend *leg = new TLegend(0.2, 0.62, 0.5, 0.89);
   leg->SetBorderSize(0);
   leg->AddEntry(frame->findObject("data"), "Data", "lep");
   leg->AddEntry(frame->findObject("total"), "Total fit", "l");
   for (int i = 0; i < n; ++i) {
      leg->AddEntry(frame->findObject(Form("comp%d", i)),
                    Form("%s: %.1f #pm %.1f %%", names[i].Data(), 100. * out.frac[i], 100. * out.err[i]), "l");
   }
   leg->Draw();

   // Pull distribution
   RooPlot *pullFrame = obs->frame(Title(""));
   pullFrame->addPlotable(frame->pullHist("data", "total"), "P");
   pullFrame->GetYaxis()->SetTitle("Pull");
   // pullFrame->GetYaxis()->SetNdivisions(505);
   // pullFrame->GetYaxis()->SetTitleSize(0.1);
   // pullFrame->GetYaxis()->SetTitleOffset(0.4);
   // pullFrame->GetYaxis()->SetLabelSize(0.09);
   // pullFrame->GetXaxis()->SetTitleSize(0.12);
   // pullFrame->GetXaxis()->SetLabelSize(0.10);
   pullFrame->GetXaxis()->SetTitle(xTitle);
   pad2->cd();
   pullFrame->Draw();
   // pad2->SetLogx();

   c->Modified();
   c->Update();
   c->SaveAs(Form("template_fit_%s_%dtemplates.png", histName, n));

   return out;
}

// --------------------------------------------------------------------------
// Two-template fit:  data = fA * A + (1 - fA) * B
// --------------------------------------------------------------------------
FitOutput fitTwoTemplates(const char *histName, TH1 *h_data, TH1 *hA, TH1 *hB, const std::vector<TString> &names)
{
   return runTemplateFit("2T", histName, h_data, {hA, hB}, names);
}

// --------------------------------------------------------------------------
// Three-template fit:  data = fA * A + fB * B + (1 - fA - fB) * C
// --------------------------------------------------------------------------
FitOutput fitThreeTemplates(const char *histName, TH1 *h_data, TH1 *hA, TH1 *hB, TH1 *hC, const std::vector<TString> &names)
{
   return runTemplateFit("3T", histName, h_data, {hA, hB, hC}, names);
}

// --------------------------------------------------------------------------
// Main macro: load files, read histName from each, call the chosen fit.
//   nTemplates = 2 -> A + B        nTemplates = 3 -> A + B + C
// --------------------------------------------------------------------------
// histanames: h_y, h_Nch_vs_rapgap_fb_Etamax_tracker_wSwap, h_cos2PHI_vs_QT_vs_x2
void do_template_fit(const char *histName = "h_Nch_vs_rapgap_fb_Etamax_tracker_wSwap", int nTemplates = 2)
{
   TFile *f_data = nullptr, *f_A = nullptr, *f_B = nullptr, *f_C = nullptr;

   TH1 *h_data = nullptr, *h_templateA = nullptr, *h_templateB = nullptr, *h_templateC = nullptr;
   TH3 *h_data3D = nullptr, *h_templateA3D = nullptr, *h_templateB3D = nullptr, *h_templateC3D = nullptr;

   // h_data      = loadHist1D(fnData, f_data, histName, Form("%s_data", histName));
   // h_templateA = loadHist1D(fnA, f_A, histName, Form("%s_templateA", histName));
   // h_templateB = loadHist1D(fnB, f_B, histName, Form("%s_templateB", histName));
   // h_templateC = loadHist1D(fnC, f_C, histName, Form("%s_templateC", histName));

   h_data3D      = dynamic_cast<TH3 *>(loadHist3D(fnData, f_data, histName, Form("%s_data", histName)));
   h_templateA3D = dynamic_cast<TH3 *>(loadHist3D(fnA, f_A, histName, Form("%s_templateA", histName)));
   h_templateB3D = dynamic_cast<TH3 *>(loadHist3D(fnB, f_B, histName, Form("%s_templateB", histName)));
   h_templateC3D = dynamic_cast<TH3 *>(loadHist3D(fnC, f_C, histName, Form("%s_templateC", histName)));

   if (h_data3D)      h_data      = h_data3D->Project3D("z");
   if (h_templateA3D) h_templateA = h_templateA3D->Project3D("z");
   if (h_templateB3D) h_templateB = h_templateB3D->Project3D("z");
   if (h_templateC3D) h_templateC = h_templateC3D->Project3D("z");


   for (auto h : {h_data, h_templateA, h_templateB, h_templateC}) {
      if (h) {
        h->Rebin(2);
      }
   }

   if (!h_data || !h_templateA || !h_templateB || (nTemplates == 3 && !h_templateC)) {
      std::cerr << "Aborting: could not load all histograms." << std::endl;
      return;
   }

   if (!sameBinning(h_data, h_templateA) || !sameBinning(h_data, h_templateB) ||
       (nTemplates == 3 && !sameBinning(h_data, h_templateC))) {
      std::cerr << "WARNING: binning of templates differs from data. "
                   "RooHistPdf will interpolate/rebin, check your inputs." << std::endl;
   }

   if (nTemplates == 2) {
      // const std::vector<TString> &names = {"diffr.", "diffr. (side 2)"};
      // plotTemplates(histName, {h_templateA, h_templateB}, names);
      // fitTwoTemplates(histName, h_data, h_templateA, h_templateB, names);

      const std::vector<TString> &names = {"diffr.", "non-diffr."};
      plotTemplates(histName, {h_templateA, h_templateC}, names);
      fitTwoTemplates(histName, h_data, h_templateA, h_templateC, names);
   } else {
      const std::vector<TString> &names = {"diffr.", "diffr. (side 2)", "non-diffr."};
      plotTemplates(histName, {h_templateA, h_templateB, h_templateC}, names);
      fitThreeTemplates(histName, h_data, h_templateA, h_templateB, h_templateC, names);
   }

   // Close input files (histograms were detached, so they remain valid)
//    for (TFile *f : {f_data, f_A, f_B, f_C}) {
//       if (f) f->Close();
//    }
}