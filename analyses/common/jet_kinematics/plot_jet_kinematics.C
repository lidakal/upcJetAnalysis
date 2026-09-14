#include "../tree.h"
#include "../bins.h"
void plot_jet_kinematics(TString fin="", TString fout="jet_kinematics.root") 
{
    std::cout << "Input file: " << fin << std::endl;
    std::cout << "Output file: " << fout << std::endl;

    tree t;
    if (fin != "") {
        t.Add(fin);
    } else {
        t.Add("/u/user/lidakal/SE_UserHome/HIForward0/crab_HiForward0_HIRun2023A-16Jan2024-v1_ZDCjson_wCCfilter/260629_023836/0000/HiForestMiniAOD_*.root");
        // t.Add("/u/user/lidakal/SE_UserHome/GNucleus-Diffraction-PhotonBeamA_Pthat10_5p36TeV/crab_GNucleus-Diffraction-PhotonBeamA_Pthat10_5p36TeV-forest_v2/260806_034151/0000/HiForestMiniAOD_*.root");
    }
    t.Init();

    TH1F *h_nref = new TH1F("h_nref", "x=nref", nnref_bins, nref_bins);
    TH3F *h_nref_pt1_pt2 = new TH3F("h_nref_pt1_pt2", "x=nref, y=pt1, z=pt2", nnref_bins, nref_bins, npt_bins, pt_bins, npt_bins, pt_bins);
    TH3F *h_nref_eta1_eta2 = new TH3F("h_nref_eta1_eta2", "x=nref, y=eta1, z=eta2", nnref_bins, nref_bins, neta_bins_s, eta_bins_s, neta_bins_s, eta_bins_s);
    TH3F *h_nref_pt_eta_lead = new TH3F("h_nref_pt_eta_lead", "x=nref, y=pt, z=eta (1st jet)", nnref_bins, nref_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);
    TH3F *h_nref_pt_eta_sub = new TH3F("h_nref_pt_eta_sub", "x=nref, y=pt, z=eta (2nd jet)", nnref_bins, nref_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);
    TH3F *h_nref_pt_eta_third = new TH3F("h_nref_pt_eta_third", "x=nref, y=pt, z=eta (3rd jet)", nnref_bins, nref_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);

    for (Long64_t ient=0; ient<t.GetEntries(); ient++) {
        if (ient % 100000 == 0) 
            std::cout << "Processing entry " << ient << "/" << t.GetEntries() << std::endl;

        // if (ient < 100000) continue;
        // if (ient > 10000) break;

        t.GetEntry(ient); 

        // hlt, zdc, dijet, add. activity, rapidity gap selections
        if (!t.passFilter(ient, true, true, true, false, false)) continue;
        double weight = t.weight;
        
        h_nref->Fill(t.nref, weight);

        if  (t.nref<1) continue;

        h_nref_pt_eta_lead->Fill(t.nref, t.jtpt[0], t.jteta[0], weight);

        if (t.nref<2) continue;

        h_nref_pt_eta_sub->Fill(t.nref, t.jtpt[1], t.jteta[1], weight);
        h_nref_pt1_pt2->Fill(t.nref, t.jtpt[0], t.jtpt[1], weight);
        h_nref_eta1_eta2->Fill(t.nref, t.jteta[0], t.jteta[1], weight);

        if (t.nref<3) continue;

        h_nref_pt_eta_third->Fill(t.nref, t.jtpt[2], t.jteta[2], weight);
    }

    TFile *f = new TFile(fout, "recreate");
    for (auto h : {
        h_nref
    }) {
        h->Write();
    }
    for (auto h : {
        h_nref_pt1_pt2, h_nref_eta1_eta2,
        h_nref_pt_eta_lead,
        h_nref_pt_eta_sub,
        h_nref_pt_eta_third
    }) {
        h->Write();
    }
    f->Close();
    delete f;
}