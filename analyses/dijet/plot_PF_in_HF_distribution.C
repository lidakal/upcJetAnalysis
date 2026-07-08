#include "../common/tree.h"
#include "../common/bins.h"

// ----------------------- //
//
//  Detector geometry
//  HF  : 3.0 < |eta| < 5.2 
//  EC2 : 2.5 < |eta| < 3.0
//  EC1 : 1.3 < |eta| < 2.5
//  BB  : 0.0 < |eta| < 1.3
//
// ----------------------- //

// ----------------------- //
//
//  Event geometry
//  Forward = photon-going 
//  Backward = nucleus-going
//  Dijet is expected on the backward side (0 < |eta| < 2.5)
//  Rapidity gap is expected on the forward side
//
// ----------------------- //

void plot_PF_in_HF_distribution(TString fin="", TString fout="pf_in_hf_distribution.root")
{
    std::cout << "Input file: " << fin << std::endl;
    std::cout << "Output file: " << fout << std::endl;

    tree t;
    if (fin != "") {
        t.Add(fin);
    } else {
        // t.Add("/u/user/lidakal/SE_UserHome/GNucleus-Diffraction-PhotonBeamA_Pthat10_5p36TeV/crab_GNucleus-Diffraction-PhotonBeamA_Pthat10_5p36TeV-forest/260630_071353/0000/HiForestMiniAOD_*.root");
        // t.Add("/u/user/lidakal/SE_UserHome/HIForward0/crab_HiForward0_HIRun2023A-PromptReco-v2_ZDCjson_noCCfilter/260624_111153/0000/HiForestMiniAOD_*.root");
        // t.Add("/u/user/lidakal/SE_UserHome/GNucleus-Diffraction-PhotonBeamA_Pthat10_5p36TeV/crab_GNucleus-Diffraction-PhotonBeamA_Pthat10_5p36TeV-forest/260630_071353/0000/HiForestMiniAOD_6*.root");
        // t.Add("/u/user/lidakal/SE_UserHome/GNucleus-Diffraction-PhotonBeamB_Pthat10_5p36TeV/crab_GNucleus-Diffraction-PhotonBeamB_Pthat10_5p36TeV-forest/260701_005201/0000/HiForestMiniAOD_*.root");
        // t.Add("/u/user/lidakal/SE_UserHome/HIForward0/crab_HiForward0_HIRun2023A-16Jan2024-v1_ZDCjson_wCCfilter/260629_023836/0000/HiForestMiniAOD_*.root");
        t.Add("/u/user/lidakal/SE_UserHome/HIEmptyBX/crab_HiEmptyBX_HIRun2023A-16Jan2024-v1_ZDCjson/260706_131125/0000/HiForestMiniAOD_*.root");
    }
    t.Init();

    // one entry per event (PF with Emax in forward/backward (excl. jet const.))
    TH3F *h_PF_HFp_Emax = new TH3F("h_PF_HFp_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_HFm_Emax = new TH3F("h_PF_HFm_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);

    for (Long64_t ient=0; ient<t.GetEntries(); ient++) {
        if (ient % 100000 == 0) 
            std::cout << "Processing entry " << ient << "/" << t.GetEntries() << std::endl;

        // if (ient < 100000) continue;
        // if (ient > 200000) break;

        t.GetEntry(ient); 
        if (!t.passFilter(ient, true, true, true, true, false)) continue;

        // index of PF candidate
        int imaxE_HFp = -1;
        int imaxE_HFm = -1;

        for (int i=0; i<t.nPF; i++) {
            double maxE_HFp = (imaxE_HFp >= 0) ? t.pfE->at(imaxE_HFp) : 0;
            double maxE_HFm = (imaxE_HFm >= 0) ? t.pfE->at(imaxE_HFm) : 0;

            if ((t.pfEta->at(i) > +3.0) && (t.pfE->at(i) > maxE_HFp)) imaxE_HFp = i;
            if ((t.pfEta->at(i) < -3.0) && (t.pfE->at(i) > maxE_HFm)) imaxE_HFm = i;
        }

        if (imaxE_HFp >=0) h_PF_HFp_Emax->Fill(t.pfEta->at(imaxE_HFp), t.pfPhi->at(imaxE_HFp), t.pfE->at(imaxE_HFp), t.weight);
        else h_PF_HFp_Emax->Fill(0.,0.,0.,0.);
        if (imaxE_HFm >=0) h_PF_HFm_Emax->Fill(t.pfEta->at(imaxE_HFm), t.pfPhi->at(imaxE_HFm), t.pfE->at(imaxE_HFm), t.weight);
        else h_PF_HFm_Emax->Fill(0.,0.,0.,0.);
    }

    TFile *f = new TFile(fout, "recreate");
    h_PF_HFp_Emax->Write();
    h_PF_HFm_Emax->Write();
    f->Close();
}