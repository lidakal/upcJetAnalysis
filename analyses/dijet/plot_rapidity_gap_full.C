#include "../common/tree.h"
#include "../common/bins.h"

// ----------------------- //
//
//  Detector geometry (signed eta regions)
//  HF-  : [-5.0, -3.0)    HF+  : [ 3.0, 5.0]
//  EC2- : [-3.0, -2.5)    EC2+ : [ 2.5, 3.0)
//  EC1- : [-2.5, -1.3)    EC1+ : [ 1.3, 2.5)
//  BB-  : [-1.3,  0.0)    BB+  : [ 0.0, 1.3)
//
//  Rapidity gaps (measured towards the detector edge at |eta| = 5)
//  All PF candidates in the detector are considered (no jet-based
//  etaMin/etaMax). A candidate counts only if its energy passes the
//  noise threshold of the region it falls in.
//
//  rapgap_right = 5 - eta(rightmost PF candidate passing threshold)
//  rapgap_left  = 5 + eta(leftmost  PF candidate passing threshold)
//  If no candidate passes on a side, that gap is the full 5 units.
//
// ----------------------- //

// Noise thresholds [GeV]
const double Ethr_HFp  = 9.5;
const double Ethr_HFm  = 9.;
const double Ethr_EC2p = 3.5;
const double Ethr_EC2m = 3.5;
const double Ethr_EC1p = 2.;   // placeholder -- to be filled in
const double Ethr_EC1m = 1.5;   // placeholder -- to be filled in
const double Ethr_BBp  = 3.;   // placeholder -- to be filled in
const double Ethr_BBm  = 3.;   // placeholder -- to be filled in

// Noise threshold on the PF candidate energy as a function of (signed) eta.
double pfEThreshold(double eta)
{
    if (eta >= 3.0)  return Ethr_HFp;    // HF+  [3.0, 5.0]
    if (eta >= 2.5)  return Ethr_EC2p;   // EC2+ [2.5, 3.0)
    if (eta >= 1.3)  return Ethr_EC1p;   // EC1+ [1.3, 2.5)
    if (eta >= 0.0)  return Ethr_BBp;    // BB+  [0.0, 1.3)
    if (eta >= -1.3) return Ethr_BBm;    // BB-  [-1.3, 0.0)
    if (eta >= -2.5) return Ethr_EC1m;   // EC1- [-2.5, -1.3)
    if (eta >= -3.0) return Ethr_EC2m;   // EC2- [-3.0, -2.5)
    return Ethr_HFm;                     // HF-  [-5.0, -3.0)
}

void plot_rapidity_gap_full(TString fin="", TString fout="rapgap_full.root")
{
    std::cout << "Input file: " << fin << std::endl;
    std::cout << "Output file: " << fout << std::endl;

    tree t;
    if (fin != "") {
        t.Add(fin);
    } else {
        fin = "/u/user/lidakal/SE_UserHome/GNucleus-Diffraction-PhotonBeamA_Pthat10_5p36TeV_v2/crab_GNucleus-Diffraction-PhotonBeamA_Pthat10_5p36TeV_v2-forest_v2/260908_062207/0000/HiForestMiniAOD_1*.root";
        t.Add(fin);
    }
    t.Init();

    // x = dijet y, y = right rapgap, z = left rapgap
    TH3F *h_y_vs_rapgap_rl = new TH3F("h_y_vs_rapgap_rl",
        "x=y, y=deta_right, z=deta_left",
        neta_bins_s, eta_bins_s, ndeta_bins, deta_bins, ndeta_bins, deta_bins);

    // x = dijet y, y = smaller rapgap, z = larger rapgap
    TH3F *h_y_vs_rapgap_sl = new TH3F("h_y_vs_rapgap_sl",
        "x=y, y=deta_smaller, z=deta_larger",
        neta_bins_s, eta_bins_s, ndeta_bins, deta_bins, ndeta_bins, deta_bins);

    // same, but using the *second* rightmost / leftmost candidates
    // x = dijet y, y = right rapgap (2nd), z = left rapgap (2nd)
    TH3F *h_y_vs_rapgap2_rl = new TH3F("h_y_vs_rapgap2_rl",
        "x=y, y=deta_right_2nd, z=deta_left_2nd",
        neta_bins_s, eta_bins_s, ndeta_bins, deta_bins, ndeta_bins, deta_bins);

    // x = dijet y, y = smaller rapgap (2nd), z = larger rapgap (2nd)
    TH3F *h_y_vs_rapgap2_sl = new TH3F("h_y_vs_rapgap2_sl",
        "x=y, y=deta_smaller_2nd, z=deta_larger_2nd",
        neta_bins_s, eta_bins_s, ndeta_bins, deta_bins, ndeta_bins, deta_bins);

    const double etaEdge = 5.0;

    TLorentzVector jet1, jet2;
    for (Long64_t ient=0; ient<t.GetEntries(); ient++) {
        if (ient % 100000 == 0)
            std::cout << "Processing entry " << ient << "/" << t.GetEntries() << std::endl;

        t.GetEntry(ient);

        // hlt, zdc, dijet, add. activity, rapidity gap selections
        if (!t.passFilter(ient, true, true, true, true, false)) continue;
        double weight = t.weight;

        // dijet rapidity
        jet1.SetPtEtaPhiM(t.jtpt[0], t.jteta[0], t.jtphi[0], t.jtm[0]);
        jet2.SetPtEtaPhiM(t.jtpt[1], t.jteta[1], t.jtphi[1], t.jtm[1]);
        double dijetY = (jet1+jet2).Rapidity();

        // rightmost / leftmost PF candidates above the noise threshold
        int imax_right = -1;  // largest eta
        int imax_left  = -1;  // smallest eta
        int imax_right2 = -1; // second largest eta
        int imax_left2  = -1; // second smallest eta

        for (int i=0; i<t.nPF; i++) {
            double pfEta = t.pfEta->at(i);
            double pfE   = t.pfE->at(i);

            // noise cut (region-dependent, signed eta)
            if (pfE < pfEThreshold(pfEta)) continue;

            // right: keep top two largest eta
            if (imax_right < 0 || pfEta > t.pfEta->at(imax_right)) {
                imax_right2 = imax_right;
                imax_right  = i;
            } else if (imax_right2 < 0 || pfEta > t.pfEta->at(imax_right2)) {
                imax_right2 = i;
            }

            // left: keep top two smallest eta
            if (imax_left < 0 || pfEta < t.pfEta->at(imax_left)) {
                imax_left2 = imax_left;
                imax_left  = i;
            } else if (imax_left2 < 0 || pfEta < t.pfEta->at(imax_left2)) {
                imax_left2 = i;
            }
        }

        // rapidity gaps (full range if nothing passes the threshold)
        double deta_right = etaEdge;
        if (imax_right >= 0) deta_right = etaEdge - t.pfEta->at(imax_right);
        double deta_left = etaEdge;
        if (imax_left >= 0) deta_left = etaEdge + t.pfEta->at(imax_left);

        h_y_vs_rapgap_rl->Fill(dijetY, deta_right, deta_left, weight);

        double deta_smaller = std::min(deta_right, deta_left);
        double deta_larger  = std::max(deta_right, deta_left);
        h_y_vs_rapgap_sl->Fill(dijetY, deta_smaller, deta_larger, weight);

        // gaps from the second rightmost / leftmost candidates
        double deta_right2 = etaEdge;
        if (imax_right2 >= 0) deta_right2 = etaEdge - t.pfEta->at(imax_right2);
        double deta_left2 = etaEdge;
        if (imax_left2 >= 0) deta_left2 = etaEdge + t.pfEta->at(imax_left2);

        h_y_vs_rapgap2_rl->Fill(dijetY, deta_right2, deta_left2, weight);

        double deta_smaller2 = std::min(deta_right2, deta_left2);
        double deta_larger2  = std::max(deta_right2, deta_left2);
        h_y_vs_rapgap2_sl->Fill(dijetY, deta_smaller2, deta_larger2, weight);
    }

    t.EntryCount();

    TFile *f = new TFile(fout, "recreate");
    h_y_vs_rapgap_rl->Write();
    h_y_vs_rapgap_sl->Write();
    h_y_vs_rapgap2_rl->Write();
    h_y_vs_rapgap2_sl->Write();
    f->Close();
}