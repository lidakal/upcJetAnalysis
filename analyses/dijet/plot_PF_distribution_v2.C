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
//  Plus = eta > 0
//  Minus = eta < 0
//  Forward = eta > etaMax 
//  Backward = eta < etaMin
//  if midEta < 0 => swap forward and backward AT THE END
//
// ----------------------- //

void plot_PF_distribution_v2(TString fin="", TString fout="pf_distribution.root")
{
    std::cout << "Input file: " << fin << std::endl;
    std::cout << "Output file: " << fout << std::endl;

    tree t;
    if (fin != "") {
        t.Add(fin);
    } else {
        // fin = "/u/user/lidakal/SE_UserHome/GNucleus-QCD_Pthat10_5p36TeV_pythia8/crab_GNucleus-QCD_Pthat10_5p36TeV-forest_v2/260831_090609/0000/HiForestMiniAOD_1*.root";
        // fin = "/u/user/lidakal/SE_UserHome/GNucleus-Diffraction-PhotonBeamB_Pthat10_5p36TeV/crab_GNucleus-Diffraction-PhotonBeamB_Pthat10_5p36TeV-forest_v2/260813_082421/0000/HiForestMiniAOD_*.root";
        // fin = "/u/user/lidakal/SE_UserHome/HIEmptyBX/crab_HiEmptyBX_HIRun2023A-16Jan2024-v1_ZDCjson_v2/260710_034030/0000/HiForestMiniAOD_100.root";
        fin = "/u/user/lidakal/SE_UserHome/HIForward0/crab_HiForward0_HIRun2023A-16Jan2024-v1_ZDCjson_wCCfilter/260629_023836/0000/HiForestMiniAOD_*.root";
        t.Add(fin);
    }
    t.Init();

    // jet eta
    TH3F *h_eta = new TH3F("h_eta", "x=eta1, y=eta2, z=(eta1+eta2)/2", neta_bins_s, eta_bins_s, neta_bins_s, eta_bins_s, neta_bins_s, eta_bins_s);

    // one entry per PF candidate (incl. jet const.)
    TH3F *h_PF = new TH3F("h_PF", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    // one entry per PF candidate (excl. jet const.)
    TH3F *h_PF_plus = new TH3F("h_PF_plus", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_minus = new TH3F("h_PF_minus", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_forward = new TH3F("h_PF_forward", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_backward = new TH3F("h_PF_backward", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);

    // one entry per event (PF with Emax in forward/backward (excl. jet const.))
    TH3F *h_PF_plus_Emax = new TH3F("h_PF_plus_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_minus_Emax = new TH3F("h_PF_minus_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_forward_Emax = new TH3F("h_PF_forward_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_backward_Emax = new TH3F("h_PF_backward_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);

    // one entry per event (PF with Emax in trackerforward/backward (excl. jet const.))
    TH3F *h_PF_plus_Emax_tracker = new TH3F("h_PF_plus_Emax_tracker", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_minus_Emax_tracker = new TH3F("h_PF_minus_Emax_tracker", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_forward_Emax_tracker = new TH3F("h_PF_forward_Emax_tracker", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_backward_Emax_tracker = new TH3F("h_PF_backward_Emax_tracker", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);

    // one entry per event (PF with Emax in BB (excl. jet const.))
    TH3F *h_PF_plus_BB_Emax = new TH3F("h_PF_plus_BB_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_minus_BB_Emax = new TH3F("h_PF_minus_BB_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_forward_BB_Emax = new TH3F("h_PF_forward_BB_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_backward_BB_Emax = new TH3F("h_PF_backward_BB_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);

    // one entry per event (PF with Emax in EC1 (excl. jet const.))
    TH3F *h_PF_plus_EC1_Emax = new TH3F("h_PF_plus_EC1_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_minus_EC1_Emax = new TH3F("h_PF_minus_EC1_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_forward_EC1_Emax = new TH3F("h_PF_forward_EC1_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_backward_EC1_Emax = new TH3F("h_PF_backward_EC1_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);

    // one entry per event (PF with Emax in EC2 (excl. jet const.))
    TH3F *h_PF_plus_EC2_Emax = new TH3F("h_PF_plus_EC2_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_minus_EC2_Emax = new TH3F("h_PF_minus_EC2_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_forward_EC2_Emax = new TH3F("h_PF_forward_EC2_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_backward_EC2_Emax = new TH3F("h_PF_backward_EC2_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);

    // one entry per event (PF with Emax in HF (excl. jet const.))
    TH3F *h_PF_plus_HF_Emax = new TH3F("h_PF_plus_HF_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_minus_HF_Emax = new TH3F("h_PF_minus_HF_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_forward_HF_Emax = new TH3F("h_PF_forward_HF_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_backward_HF_Emax = new TH3F("h_PF_backward_HF_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);

    // one entry per event (PF with Etamax in forward/backward (excl. jet const.))
    TH3F *h_PF_plus_Etamax = new TH3F("h_PF_plus_Etamax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_minus_Etamax = new TH3F("h_PF_minus_Etamax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_forward_Etamax = new TH3F("h_PF_forward_Etamax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_backward_Etamax = new TH3F("h_PF_backward_Etamax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);

    // one entry per event (PF with Etamax in tracker forward/backward (excl. jet const.))
    TH3F *h_PF_plus_Etamax_tracker = new TH3F("h_PF_plus_Etamax_tracker", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_minus_Etamax_tracker = new TH3F("h_PF_minus_Etamax_tracker", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_forward_Etamax_tracker = new TH3F("h_PF_forward_Etamax_tracker", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_backward_Etamax_tracker = new TH3F("h_PF_backward_Etamax_tracker", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);

    // one entry per event (rap. gap in all detector)
    TH2F *h_rapgap_fb_Emax = new TH2F("h_rapgap_fb_Emax", "x=deta_forward, y=deta_backward", ndeta_bins_s, deta_bins_s, ndeta_bins_s, deta_bins_s);
    TH2F *h_rapgap_pm_Emax = new TH2F("h_rapgap_pm_Emax", "x=deta_plus, y=deta_minus", ndeta_bins_s, deta_bins_s, ndeta_bins_s, deta_bins_s);
    TH2F *h_rapgap_fb_Etamax = new TH2F("h_rapgap_fb_Etamax", "x=deta_forward, y=deta_backward", ndeta_bins_s, deta_bins_s, ndeta_bins_s, deta_bins_s);
    TH2F *h_rapgap_pm_Etamax = new TH2F("h_rapgap_pm_Etamax", "x=deta_forward, y=deta_backward", ndeta_bins_s, deta_bins_s, ndeta_bins_s, deta_bins_s);

    // one entry per event (rap. gap in tracker)
    TH2F *h_rapgap_fb_Emax_tracker = new TH2F("h_rapgap_fb_Emax_tracker", "x=deta_forward, y=deta_backward", ndeta_bins_s, deta_bins_s, ndeta_bins_s, deta_bins_s);
    TH2F *h_rapgap_pm_Emax_tracker = new TH2F("h_rapgap_pm_Emax_tracker", "x=deta_plus, y=deta_minus", ndeta_bins_s, deta_bins_s, ndeta_bins_s, deta_bins_s);
    TH2F *h_rapgap_fb_Etamax_tracker = new TH2F("h_rapgap_fb_Etamax_tracker", "x=deta_forward, y=deta_backward", ndeta_bins_s, deta_bins_s, ndeta_bins_s, deta_bins_s);
    TH2F *h_rapgap_pm_Etamax_tracker = new TH2F("h_rapgap_pm_Etamax_tracker", "x=deta_forward, y=deta_backward", ndeta_bins_s, deta_bins_s, ndeta_bins_s, deta_bins_s);

    double PFEmin = 0.5; // for maxEta
    double PFPtmin = 0.2; // for maxEta
    double trackerLim = 3.0; // for rapidity gap in tracker
    bool   chargedOnly = true; // for rapidity gap in tracker

    TLorentzVector jet1, jet2, pfcand;
    for (Long64_t ient=0; ient<t.GetEntries(); ient++) {
        if (ient % 100000 == 0) 
            std::cout << "Processing entry " << ient << "/" << t.GetEntries() << std::endl;

        // if (ient < 100000) continue;
        // if (ient > 1000) break;

        t.GetEntry(ient); 

        // if (t.nPF > 0) std::cout << "Entry " << ient << ": nPF = " << t.nPF << std::endl;

        bool isEmptyBX = fin.Contains("HIEmptyBX");
        if (isEmptyBX) {
            if (!(t.HLT_HIL1NotBptxOR==1)) continue;
        } else {
            // hlt, zdc, dijet, add. activity, rapidity gap selections
            if (!t.passFilter(ient, true, true, true, true, true)) continue; 
        
        }
        double weight = t.weight;
        // std::cout << "weight=" << weight << std::endl;

        // event topology
        double midEta = 0;
        double dijetEta = 0;
        double etaMin = 0;
        double etaMax = 0;

        if (!isEmptyBX) {
            midEta = (t.jteta[0] + t.jteta[1]) / 2.0;
            etaMin = std::min(t.jteta[0], t.jteta[1])-0.5; 
            etaMax = std::max(t.jteta[0], t.jteta[1])+0.5; 
            // std::cout << "etaMin=" << etaMin << ", etaMax=" << etaMax << std::endl;
            
            jet1.SetPtEtaPhiM(t.jtpt[0], t.jteta[0], t.jtphi[0], t.jtm[0]);
            jet2.SetPtEtaPhiM(t.jtpt[1], t.jteta[1], t.jtphi[1], t.jtm[1]);
            dijetEta = (jet1+jet2).Eta();

            h_eta->Fill(t.jteta[0], t.jteta[1], midEta, t.weight);
        }

        // index of PF candidate
        int imaxE_plus = -1;
        int imaxE_minus = -1;
        int imaxE_forward = -1;
        int imaxE_backward = -1;

        int imaxE_plus_tracker = -1;
        int imaxE_minus_tracker = -1;
        int imaxE_forward_tracker = -1;
        int imaxE_backward_tracker = -1;

        int imaxE_plus_BB = -1;
        int imaxE_minus_BB = -1;
        int imaxE_forward_BB = -1;
        int imaxE_backward_BB = -1;

        int imaxE_plus_EC1 = -1;
        int imaxE_minus_EC1 = -1;
        int imaxE_forward_EC1 = -1;
        int imaxE_backward_EC1 = -1;

        int imaxE_plus_EC2 = -1;
        int imaxE_minus_EC2 = -1;
        int imaxE_forward_EC2 = -1;
        int imaxE_backward_EC2 = -1;

        int imaxE_plus_HF = -1;
        int imaxE_minus_HF = -1;
        int imaxE_forward_HF = -1;
        int imaxE_backward_HF = -1;

        int imaxEta_plus = -1;
        int imaxEta_minus = -1;
        int imaxEta_forward = -1;
        int imaxEta_backward = -1;

        int imaxEta_plus_tracker = -1;
        int imaxEta_minus_tracker = -1;
        int imaxEta_forward_tracker = -1;
        int imaxEta_backward_tracker = -1;

        int nPF_plus = 0;
        int nPF_minus = 0;
        int nPF_forward = 0;
        int nPF_backward = 0;

        for (int i=0; i<t.nPF; i++) {
            double pfEta = t.pfEta->at(i);
            double pfPhi = t.pfPhi->at(i);
            double pfE   = t.pfE->at(i);
            double pfPt  = t.pfPt->at(i);
            int    pfId  = t.pfId->at(i);

            // all candidates
            h_PF->Fill(pfEta, pfPhi, pfE, weight);

            double maxE_plus = (imaxE_plus >= 0) ? t.pfE->at(imaxE_plus) : 0;
            double maxE_minus = (imaxE_minus >= 0) ? t.pfE->at(imaxE_minus) : 0;
            double maxE_forward = (imaxE_forward >= 0) ? t.pfE->at(imaxE_forward) : 0;
            double maxE_backward = (imaxE_backward >= 0) ? t.pfE->at(imaxE_backward) : 0;

            double maxE_plus_tracker = (imaxE_plus_tracker >= 0) ? t.pfE->at(imaxE_plus_tracker) : 0;
            double maxE_minus_tracker = (imaxE_minus_tracker >= 0) ? t.pfE->at(imaxE_minus_tracker) : 0;
            double maxE_forward_tracker = (imaxE_forward_tracker >= 0) ? t.pfE->at(imaxE_forward_tracker) : 0;
            double maxE_backward_tracker = (imaxE_backward_tracker >= 0) ? t.pfE->at(imaxE_backward_tracker) : 0;

            double maxE_plus_BB = (imaxE_plus_BB >= 0) ? t.pfE->at(imaxE_plus_BB) : 0;
            double maxE_minus_BB = (imaxE_minus_BB >= 0) ? t.pfE->at(imaxE_minus_BB) : 0;
            double maxE_forward_BB = (imaxE_forward_BB >= 0) ? t.pfE->at(imaxE_forward_BB) : 0;
            double maxE_backward_BB = (imaxE_backward_BB >= 0) ? t.pfE->at(imaxE_backward_BB) : 0;

            double maxE_plus_EC1 = (imaxE_plus_EC1 >= 0) ? t.pfE->at(imaxE_plus_EC1) : 0;
            double maxE_minus_EC1 = (imaxE_minus_EC1 >= 0) ? t.pfE->at(imaxE_minus_EC1) : 0;
            double maxE_forward_EC1 = (imaxE_forward_EC1 >= 0) ? t.pfE->at(imaxE_forward_EC1) : 0;
            double maxE_backward_EC1 = (imaxE_backward_EC1 >= 0) ? t.pfE->at(imaxE_backward_EC1) : 0;

            double maxE_plus_EC2 = (imaxE_plus_EC2 >= 0) ? t.pfE->at(imaxE_plus_EC2) : 0;
            double maxE_minus_EC2 = (imaxE_minus_EC2 >= 0) ? t.pfE->at(imaxE_minus_EC2) : 0;
            double maxE_forward_EC2 = (imaxE_forward_EC2 >= 0) ? t.pfE->at(imaxE_forward_EC2) : 0;
            double maxE_backward_EC2 = (imaxE_backward_EC2 >= 0) ? t.pfE->at(imaxE_backward_EC2) : 0;

            double maxE_plus_HF = (imaxE_plus_HF >= 0) ? t.pfE->at(imaxE_plus_HF) : 0;
            double maxE_minus_HF = (imaxE_minus_HF >= 0) ? t.pfE->at(imaxE_minus_HF) : 0;
            double maxE_forward_HF = (imaxE_forward_HF >= 0) ? t.pfE->at(imaxE_forward_HF) : 0;
            double maxE_backward_HF = (imaxE_backward_HF >= 0) ? t.pfE->at(imaxE_backward_HF) : 0;

            // maxEta is signed
            double maxEta_plus = (imaxEta_plus >= 0) ? t.pfEta->at(imaxEta_plus) : 0;
            double maxEta_minus = (imaxEta_minus >= 0) ? t.pfEta->at(imaxEta_minus) : 0;
            double maxEta_forward = (imaxEta_forward >= 0) ? t.pfEta->at(imaxEta_forward) : midEta;
            double maxEta_backward = (imaxEta_backward >= 0) ? t.pfEta->at(imaxEta_backward) : midEta;

            double maxEta_plus_tracker = (imaxEta_plus_tracker >= 0) ? t.pfEta->at(imaxEta_plus_tracker) : 0;
            double maxEta_minus_tracker = (imaxEta_minus_tracker >= 0) ? t.pfEta->at(imaxEta_minus_tracker) : 0;
            double maxEta_forward_tracker = (imaxEta_forward_tracker >= 0) ? t.pfEta->at(imaxEta_forward_tracker) : midEta;
            double maxEta_backward_tracker = (imaxEta_backward_tracker >= 0) ? t.pfEta->at(imaxEta_backward_tracker) : midEta;

            // Go over plus/minus
            if (pfEta > 0) {
                nPF_plus++;
                h_PF_plus->Fill(pfEta, pfPhi, pfE, weight);

                // max E
                if (pfE > maxE_plus) imaxE_plus = i;
                if (((!chargedOnly)||t.pfIsCharged(pfId)) && (std::abs(pfEta) < trackerLim) && (pfE > maxE_plus_tracker)) imaxE_plus_tracker = i;

                if (std::abs(pfEta) < 1.3) {
                    if (pfE > maxE_plus_BB) imaxE_plus_BB = i;
                } else if (std::abs(pfEta) < 2.5) {
                    if (pfE > maxE_plus_EC1) imaxE_plus_EC1 = i;
                } else if (std::abs(pfEta) < 3.) {
                    if (pfE > maxE_plus_EC2) imaxE_plus_EC2 = i;
                } else {
                    if (pfE > maxE_plus_HF) imaxE_plus_HF = i;
                }

                // max Eta
                if (pfPt > PFPtmin) {
                    if (std::abs(pfEta) > std::abs(maxEta_plus)) imaxEta_plus = i;
                    if (((!chargedOnly)||t.pfIsCharged(pfId)) && (std::abs(pfEta) < trackerLim) && (std::abs(pfEta) > std::abs(maxEta_plus_tracker))) imaxEta_plus_tracker = i;
                }
            } else {
                nPF_minus++;
                h_PF_minus->Fill(pfEta, pfPhi, pfE, weight);

                // max E
                if (pfE > maxE_minus) imaxE_minus = i;
                if (((!chargedOnly)||t.pfIsCharged(pfId)) && (std::abs(pfEta) < trackerLim) && (pfE > maxE_minus_tracker)) imaxE_minus_tracker = i;

                if (std::abs(pfEta) < 1.3) {
                    if (pfE > maxE_minus_BB) imaxE_minus_BB = i;
                } else if (std::abs(pfEta) < 2.5) {
                    if (pfE > maxE_minus_EC1) imaxE_minus_EC1 = i;
                } else if (std::abs(pfEta) < 3.) {
                    if (pfE > maxE_minus_EC2) imaxE_minus_EC2 = i;
                } else {
                    if (pfE > maxE_minus_HF) imaxE_minus_HF = i;
                }

                // max Eta
                if (pfPt > PFPtmin) {
                    if (std::abs(pfEta) > std::abs(maxEta_minus)) imaxEta_minus = i;
                    if (((!chargedOnly)||t.pfIsCharged(pfId)) && (std::abs(pfEta) < trackerLim) && (std::abs(pfEta) > std::abs(maxEta_minus_tracker))) imaxEta_minus_tracker = i;
                }
            }

            // Go over forward/backward
            if (pfEta > etaMax) {
                nPF_forward++;
                h_PF_forward->Fill(pfEta, pfPhi, pfE, weight); 

                // max E
                if (pfE > maxE_forward) imaxE_forward = i;
                if (((!chargedOnly)||t.pfIsCharged(pfId)) && ((std::abs(pfEta) < trackerLim)) && (pfE > maxE_forward_tracker)) imaxE_forward_tracker = i;

                if (std::abs(pfEta) < 1.3) {
                    if (pfE > maxE_forward_BB) imaxE_forward_BB = i;
                } else if (std::abs(pfEta) < 2.5) {
                    if (pfE > maxE_forward_EC1) imaxE_forward_EC1 = i;
                } else if (std::abs(pfEta) < 3.) {
                    if (pfE > maxE_forward_EC2) imaxE_forward_EC2 = i;
                } else {
                    if (pfE > maxE_forward_HF) imaxE_forward_HF = i;
                }

                // max Eta
                if (pfPt > PFPtmin) {
                    if (pfEta > maxEta_forward) imaxEta_forward = i;
                    if (((!chargedOnly)||t.pfIsCharged(pfId)) && (std::abs(pfEta) < trackerLim) && (pfEta > maxEta_forward_tracker)) imaxEta_forward_tracker = i;
                }
            } else if (pfEta < etaMin) {
                nPF_backward++;
                h_PF_backward->Fill(pfEta, pfPhi, pfE, weight); 

                // max E
                if (pfE > maxE_backward) imaxE_backward = i;
                if (((!chargedOnly)||t.pfIsCharged(pfId)) && ((std::abs(pfEta) < trackerLim)) && (pfE > maxE_backward_tracker)) imaxE_backward_tracker = i;

                if (std::abs(pfEta) < 1.3) {
                    if (pfE > maxE_backward_BB) imaxE_backward_BB = i;
                } else if (std::abs(pfEta) < 2.5) {
                    if (pfE > maxE_backward_EC1) imaxE_backward_EC1 = i;
                } else if (std::abs(pfEta) < 3.) {
                    if (pfE > maxE_backward_EC2) imaxE_backward_EC2 = i;
                } else {
                    if (pfE > maxE_backward_HF) imaxE_backward_HF = i;
                }

                // max Eta
                if (pfPt > PFPtmin) {
                    if (pfEta < maxEta_backward) imaxEta_backward = i;
                    if (((!chargedOnly)||t.pfIsCharged(pfId)) && (std::abs(pfEta) < trackerLim) && (pfEta < maxEta_backward_tracker)) imaxEta_backward_tracker = i;
                }            
            }

        }
        // std::cout << "nPF_plus=" << nPF_plus << ", nPF_minus=" << nPF_minus << std::endl;
        // std::cout << "nPF_forward=" << nPF_forward << ", nPF_backward=" << nPF_backward << std::endl;

        // plus/minus rapidity gap in all detector
        double deta_plus_Emax = (etaMax>0) ? 5.2 - etaMax : 5.2;
        if (imaxE_plus>=0) {
            h_PF_plus_Emax->Fill(t.pfEta->at(imaxE_plus), t.pfPhi->at(imaxE_plus), t.pfE->at(imaxE_plus), t.weight);
            deta_plus_Emax = 5.2 - t.pfEta->at(imaxE_plus);
        }
        double deta_minus_Emax = (etaMin<0) ? etaMin + 5.2 : 5.2;
        if (imaxE_minus>=0) {
            h_PF_minus_Emax->Fill(t.pfEta->at(imaxE_minus), t.pfPhi->at(imaxE_minus), t.pfE->at(imaxE_minus), t.weight);
            deta_minus_Emax = t.pfEta->at(imaxE_minus) + 5.2;
        }
        h_rapgap_pm_Emax->Fill(deta_plus_Emax, deta_minus_Emax, weight);

        double deta_plus_Etamax = (etaMax>0) ? 5.2 - etaMax : 5.2;
        if (imaxEta_plus>=0) {
            h_PF_plus_Etamax->Fill(t.pfEta->at(imaxEta_plus), t.pfPhi->at(imaxEta_plus), t.pfE->at(imaxEta_plus), t.weight);
            deta_plus_Etamax = 5.2 - t.pfEta->at(imaxEta_plus);
        }
        double deta_minus_Etamax = (etaMin<0) ? etaMin + 5.2 : 5.2;
        if (imaxEta_minus>=0) {
            h_PF_minus_Etamax->Fill(t.pfEta->at(imaxEta_minus), t.pfPhi->at(imaxEta_minus), t.pfE->at(imaxEta_minus), t.weight);
            deta_minus_Etamax = t.pfEta->at(imaxEta_minus) + 5.2;
        }
        h_rapgap_pm_Etamax->Fill(deta_plus_Etamax, deta_minus_Etamax, weight);

        // plus/minus rapidity gap in tracker 
        double deta_plus_Emax_tracker = 0.;
        if (etaMax < trackerLim) {
            if (etaMax > 0.) deta_plus_Emax_tracker = trackerLim - etaMax;
            else deta_plus_Emax_tracker = trackerLim;
        } 
        if (imaxE_plus_tracker>=0) {
            h_PF_plus_Emax_tracker->Fill(t.pfEta->at(imaxE_plus_tracker), t.pfPhi->at(imaxE_plus_tracker), t.pfE->at(imaxE_plus_tracker), t.weight);
            deta_plus_Emax_tracker = trackerLim - t.pfEta->at(imaxE_plus_tracker);
        }
        double deta_minus_Emax_tracker = 0.;
        if (etaMin > -trackerLim) {
            if (etaMin < 0.) deta_minus_Emax_tracker = trackerLim + etaMin;
            else deta_minus_Emax_tracker = trackerLim;
        }
        if (imaxE_minus_tracker>=0) {
            h_PF_minus_Emax_tracker->Fill(t.pfEta->at(imaxE_minus_tracker), t.pfPhi->at(imaxE_minus_tracker), t.pfE->at(imaxE_minus_tracker), t.weight);
            deta_minus_Emax_tracker = t.pfEta->at(imaxE_minus_tracker) + trackerLim;
        }
        h_rapgap_pm_Emax_tracker->Fill(deta_plus_Emax_tracker, deta_minus_Emax_tracker, weight);

        double deta_plus_Etamax_tracker = 0.;
        if (etaMax < trackerLim) {
            if (etaMax > 0.) deta_plus_Etamax_tracker = trackerLim - etaMax;
            else deta_plus_Etamax_tracker = trackerLim;
        } 
        if (imaxEta_plus_tracker>=0) {
            h_PF_plus_Etamax_tracker->Fill(t.pfEta->at(imaxEta_plus_tracker), t.pfPhi->at(imaxEta_plus_tracker), t.pfE->at(imaxEta_plus_tracker), t.weight);
            deta_plus_Etamax_tracker = trackerLim - t.pfEta->at(imaxEta_plus_tracker);
        }
        double deta_minus_Etamax_tracker = 0.;
        if (etaMin > -trackerLim) {
            if (etaMin < 0.) deta_minus_Etamax_tracker = trackerLim + etaMin;
            else deta_minus_Etamax_tracker = trackerLim;
        }
        if (imaxEta_minus_tracker>=0) {
            h_PF_minus_Etamax_tracker->Fill(t.pfEta->at(imaxEta_minus_tracker), t.pfPhi->at(imaxEta_minus_tracker), t.pfE->at(imaxEta_minus_tracker), t.weight);
            deta_minus_Etamax_tracker = t.pfEta->at(imaxEta_minus_tracker) + trackerLim;
        }
        h_rapgap_pm_Etamax_tracker->Fill(deta_plus_Etamax_tracker, deta_minus_Etamax_tracker, weight);

        
        // forward/backward rapidity gap in all detector
        double deta_forward_Emax = 5.2 - etaMax;
        if (imaxE_forward>=0) {
            h_PF_forward_Emax->Fill(t.pfEta->at(imaxE_forward), t.pfPhi->at(imaxE_forward), t.pfE->at(imaxE_forward), t.weight);
            deta_forward_Emax = 5.2 - t.pfEta->at(imaxE_forward);
        }
        double deta_backward_Emax = etaMin + 5.2;
        if (imaxE_backward>=0) {
            h_PF_backward_Emax->Fill(t.pfEta->at(imaxE_backward), t.pfPhi->at(imaxE_backward), t.pfE->at(imaxE_backward), t.weight);
            deta_backward_Emax = t.pfEta->at(imaxE_backward) + 5.2;
        }
        if (midEta < 0.) std::swap(deta_forward_Emax, deta_backward_Emax);
        h_rapgap_fb_Emax->Fill(deta_forward_Emax, deta_backward_Emax, weight);

        double deta_forward_Etamax = 5.2 - midEta;
        if (imaxEta_forward>=0) {
            h_PF_forward_Etamax->Fill(t.pfEta->at(imaxEta_forward), t.pfPhi->at(imaxEta_forward), t.pfE->at(imaxEta_forward), t.weight);
            deta_forward_Etamax = 5.2 - t.pfEta->at(imaxEta_forward);
        }
        double deta_backward_Etamax = 5.2 + midEta;
        if (imaxEta_backward>=0) {
            h_PF_backward_Etamax->Fill(t.pfEta->at(imaxEta_backward), t.pfPhi->at(imaxEta_backward), t.pfE->at(imaxEta_backward), t.weight);
            deta_backward_Etamax = t.pfEta->at(imaxEta_backward) + 5.2;
        }
        if (midEta < 0.) std::swap(deta_forward_Etamax, deta_backward_Etamax);
        h_rapgap_fb_Etamax->Fill(deta_forward_Etamax, deta_backward_Etamax, weight);

        // forward/backward rapidity gap in tracker 
        double deta_forward_Emax_tracker = (etaMax < trackerLim) ? trackerLim - etaMax : 0.;
        if (imaxE_forward_tracker>=0) {
            h_PF_forward_Emax_tracker->Fill(t.pfEta->at(imaxE_forward_tracker), t.pfPhi->at(imaxE_forward_tracker), t.pfE->at(imaxE_forward_tracker), t.weight);
            deta_forward_Emax_tracker = trackerLim - t.pfEta->at(imaxE_forward_tracker);
        }
        double deta_backward_Emax_tracker = (etaMin > -trackerLim) ? trackerLim + etaMin : 0.;
        if (imaxE_backward_tracker>=0) {
            h_PF_backward_Emax_tracker->Fill(t.pfEta->at(imaxE_backward_tracker), t.pfPhi->at(imaxE_backward_tracker), t.pfE->at(imaxE_backward_tracker), t.weight);
            deta_backward_Emax_tracker = t.pfEta->at(imaxE_backward_tracker) + trackerLim;
        }
        if (midEta < 0.) std::swap(deta_forward_Emax_tracker, deta_backward_Emax_tracker);
        h_rapgap_fb_Emax_tracker->Fill(deta_forward_Emax_tracker, deta_backward_Emax_tracker, weight);

        double deta_forward_Etamax_tracker = trackerLim - midEta;
        if (imaxEta_forward_tracker>=0) {
            h_PF_forward_Etamax_tracker->Fill(t.pfEta->at(imaxEta_forward_tracker), t.pfPhi->at(imaxEta_forward_tracker), t.pfE->at(imaxEta_forward_tracker), t.weight);
            deta_forward_Etamax_tracker = trackerLim - t.pfEta->at(imaxEta_forward_tracker);
        }
        double deta_backward_Etamax_tracker = trackerLim + midEta;
        if (imaxEta_backward_tracker>=0) {
            h_PF_backward_Etamax_tracker->Fill(t.pfEta->at(imaxEta_backward_tracker), t.pfPhi->at(imaxEta_backward_tracker), t.pfE->at(imaxEta_backward_tracker), t.weight);
            deta_backward_Etamax_tracker = t.pfEta->at(imaxEta_backward_tracker) + trackerLim;
        }
        if (midEta < 0.) std::swap(deta_forward_Etamax_tracker, deta_backward_Etamax_tracker);
        h_rapgap_fb_Etamax_tracker->Fill(deta_forward_Etamax_tracker, deta_backward_Etamax_tracker, weight);

        // Swap forward/backward if needed (NEED to ALREADY have filled/swapped deta)
        if (midEta < 0.) {
            std::swap(imaxE_forward, imaxE_backward);
            std::swap(imaxE_forward_tracker, imaxE_backward_tracker);

            std::swap(imaxE_forward_BB, imaxE_backward_BB);
            std::swap(imaxE_forward_EC1, imaxE_backward_EC1);
            std::swap(imaxE_forward_EC2, imaxE_backward_EC2);
            std::swap(imaxE_forward_HF, imaxE_backward_HF);

            std::swap(imaxEta_forward, imaxEta_backward);
            std::swap(imaxEta_forward_tracker, imaxEta_backward_tracker);
        }

        // Fill histograms
        if (imaxE_plus>=0) h_PF_plus_Emax->Fill(t.pfEta->at(imaxE_plus), t.pfPhi->at(imaxE_plus), t.pfE->at(imaxE_plus), weight);
        else h_PF_plus_Emax->Fill(0., 0., 0., weight);
        if (imaxE_minus>=0) h_PF_minus_Emax->Fill(t.pfEta->at(imaxE_minus), t.pfPhi->at(imaxE_minus), t.pfE->at(imaxE_minus), weight);
        else h_PF_minus_Emax->Fill(0., 0., 0., weight);

        if (imaxE_plus_tracker>=0) h_PF_plus_Emax_tracker->Fill(t.pfEta->at(imaxE_plus_tracker), t.pfPhi->at(imaxE_plus_tracker), t.pfE->at(imaxE_plus), weight);
        else h_PF_plus_Emax_tracker->Fill(0., 0., 0., weight);
        if (imaxE_minus_tracker>=0) h_PF_minus_Emax_tracker->Fill(t.pfEta->at(imaxE_minus_tracker), t.pfPhi->at(imaxE_minus_tracker), t.pfE->at(imaxE_minus_tracker), weight);
        else h_PF_minus_Emax_tracker->Fill(0., 0., 0., weight);

        if (imaxE_forward>=0) h_PF_forward_Emax->Fill(t.pfEta->at(imaxE_forward), t.pfPhi->at(imaxE_forward), t.pfE->at(imaxE_forward), weight);
        else h_PF_forward_Emax->Fill(0., 0., 0., weight);
        if (imaxE_backward>=0) h_PF_backward_Emax->Fill(t.pfEta->at(imaxE_backward), t.pfPhi->at(imaxE_backward), t.pfE->at(imaxE_backward), weight);
        else h_PF_backward_Emax->Fill(0., 0., 0., weight);

        if (imaxE_forward_tracker>=0) h_PF_forward_Emax_tracker->Fill(t.pfEta->at(imaxE_forward_tracker), t.pfPhi->at(imaxE_forward_tracker), t.pfE->at(imaxE_forward), weight);
        else h_PF_forward_Emax_tracker->Fill(0., 0., 0., weight);
        if (imaxE_backward_tracker>=0) h_PF_backward_Emax_tracker->Fill(t.pfEta->at(imaxE_backward_tracker), t.pfPhi->at(imaxE_backward_tracker), t.pfE->at(imaxE_backward_tracker), weight);
        else h_PF_backward_Emax_tracker->Fill(0., 0., 0., weight);

        if (imaxE_plus_BB>=0) h_PF_plus_BB_Emax->Fill(t.pfEta->at(imaxE_plus_BB), t.pfPhi->at(imaxE_plus_BB), t.pfE->at(imaxE_plus_BB), weight);
        else h_PF_plus_BB_Emax->Fill(0., 0., 0., weight);
        if (imaxE_minus_BB>=0) h_PF_minus_BB_Emax->Fill(t.pfEta->at(imaxE_minus_BB), t.pfPhi->at(imaxE_minus_BB), t.pfE->at(imaxE_minus_BB), weight);
        else h_PF_minus_BB_Emax->Fill(0., 0., 0., weight);

        if (imaxE_forward_BB>=0) h_PF_forward_BB_Emax->Fill(t.pfEta->at(imaxE_forward_BB), t.pfPhi->at(imaxE_forward_BB), t.pfE->at(imaxE_forward_BB), weight);
        else h_PF_forward_BB_Emax->Fill(0., 0., 0., weight);
        if (imaxE_backward_BB>=0) h_PF_backward_BB_Emax->Fill(t.pfEta->at(imaxE_backward_BB), t.pfPhi->at(imaxE_backward_BB), t.pfE->at(imaxE_backward_BB), weight);
        else h_PF_backward_BB_Emax->Fill(0., 0., 0., weight);

        if (imaxE_plus_EC1>=0) h_PF_plus_EC1_Emax->Fill(t.pfEta->at(imaxE_plus_EC1), t.pfPhi->at(imaxE_plus_EC1), t.pfE->at(imaxE_plus_EC1), weight);
        else h_PF_plus_EC1_Emax->Fill(0., 0., 0., weight);
        if (imaxE_minus_EC1>=0) h_PF_minus_EC1_Emax->Fill(t.pfEta->at(imaxE_minus_EC1), t.pfPhi->at(imaxE_minus_EC1), t.pfE->at(imaxE_minus_EC1), weight);
        else h_PF_minus_EC1_Emax->Fill(0., 0., 0., weight);

        if (imaxE_forward_EC1>=0) h_PF_forward_EC1_Emax->Fill(t.pfEta->at(imaxE_forward_EC1), t.pfPhi->at(imaxE_forward_EC1), t.pfE->at(imaxE_forward_EC1), weight);
        else h_PF_forward_EC1_Emax->Fill(0., 0., 0., weight);
        if (imaxE_backward_EC1>=0) h_PF_backward_EC1_Emax->Fill(t.pfEta->at(imaxE_backward_EC1), t.pfPhi->at(imaxE_backward_EC1), t.pfE->at(imaxE_backward_EC1), weight);
        else h_PF_backward_EC1_Emax->Fill(0., 0., 0., weight);

        if (imaxE_plus_EC2>=0) h_PF_plus_EC2_Emax->Fill(t.pfEta->at(imaxE_plus_EC2), t.pfPhi->at(imaxE_plus_EC2), t.pfE->at(imaxE_plus_EC2), weight);
        else h_PF_plus_EC2_Emax->Fill(0., 0., 0., weight);
        if (imaxE_minus_EC2>=0) h_PF_minus_EC2_Emax->Fill(t.pfEta->at(imaxE_minus_EC2), t.pfPhi->at(imaxE_minus_EC2), t.pfE->at(imaxE_minus_EC2), weight);
        else h_PF_minus_EC2_Emax->Fill(0., 0., 0., weight);

        if (imaxE_forward_EC2>=0) h_PF_forward_EC2_Emax->Fill(t.pfEta->at(imaxE_forward_EC2), t.pfPhi->at(imaxE_forward_EC2), t.pfE->at(imaxE_forward_EC2), weight);
        else h_PF_forward_EC2_Emax->Fill(0., 0., 0., weight);
        if (imaxE_backward_EC2>=0) h_PF_backward_EC2_Emax->Fill(t.pfEta->at(imaxE_backward_EC2), t.pfPhi->at(imaxE_backward_EC2), t.pfE->at(imaxE_backward_EC2), weight);
        else h_PF_backward_EC2_Emax->Fill(0., 0., 0., weight);

        if (imaxE_plus_HF>=0) h_PF_plus_HF_Emax->Fill(t.pfEta->at(imaxE_plus_HF), t.pfPhi->at(imaxE_plus_HF), t.pfE->at(imaxE_plus_HF), weight);
        else h_PF_plus_HF_Emax->Fill(0., 0., 0., weight);
        if (imaxE_minus_HF>=0) h_PF_minus_HF_Emax->Fill(t.pfEta->at(imaxE_minus_HF), t.pfPhi->at(imaxE_minus_HF), t.pfE->at(imaxE_minus_HF), weight);
        else h_PF_minus_HF_Emax->Fill(0., 0., 0., weight);

        if (imaxE_forward_HF>=0) h_PF_forward_HF_Emax->Fill(t.pfEta->at(imaxE_forward_HF), t.pfPhi->at(imaxE_forward_HF), t.pfE->at(imaxE_forward_HF), weight);
        else h_PF_forward_HF_Emax->Fill(0., 0., 0., weight);
        if (imaxE_backward_HF>=0) h_PF_backward_HF_Emax->Fill(t.pfEta->at(imaxE_backward_HF), t.pfPhi->at(imaxE_backward_HF), t.pfE->at(imaxE_backward_HF), weight);
        else h_PF_backward_HF_Emax->Fill(0., 0., 0., weight);

        if (imaxEta_plus>=0) h_PF_plus_Etamax->Fill(t.pfEta->at(imaxEta_plus), t.pfPhi->at(imaxEta_plus), t.pfE->at(imaxEta_plus), weight);
        else h_PF_plus_Etamax->Fill(0., 0., 0., weight);
        if (imaxEta_minus>=0) h_PF_minus_Etamax->Fill(t.pfEta->at(imaxEta_minus), t.pfPhi->at(imaxEta_minus), t.pfE->at(imaxEta_minus), weight);
        else h_PF_minus_Etamax->Fill(0., 0., 0., weight);

        if (imaxEta_plus_tracker>=0) h_PF_plus_Etamax_tracker->Fill(t.pfEta->at(imaxEta_plus_tracker), t.pfPhi->at(imaxEta_plus_tracker), t.pfE->at(imaxEta_plus), weight);
        else h_PF_plus_Etamax_tracker->Fill(0., 0., 0., weight);
        if (imaxEta_minus_tracker>=0) h_PF_minus_Etamax_tracker->Fill(t.pfEta->at(imaxEta_minus_tracker), t.pfPhi->at(imaxEta_minus_tracker), t.pfE->at(imaxEta_minus_tracker), weight);
        else h_PF_minus_Etamax_tracker->Fill(0., 0., 0., weight);

        if (imaxEta_forward>=0) h_PF_forward_Etamax->Fill(t.pfEta->at(imaxEta_forward), t.pfPhi->at(imaxEta_forward), t.pfE->at(imaxEta_forward), weight);
        else h_PF_forward_Etamax->Fill(0., 0., 0., weight);
        if (imaxEta_backward>=0) h_PF_backward_Etamax->Fill(t.pfEta->at(imaxEta_backward), t.pfPhi->at(imaxEta_backward), t.pfE->at(imaxEta_backward), weight);
        else h_PF_backward_Etamax->Fill(0., 0., 0., weight);

        if (imaxEta_forward_tracker>=0) h_PF_forward_Etamax_tracker->Fill(t.pfEta->at(imaxEta_forward_tracker), t.pfPhi->at(imaxEta_forward_tracker), t.pfE->at(imaxEta_forward), weight);
        else h_PF_forward_Etamax_tracker->Fill(0., 0., 0., weight);
        if (imaxEta_backward_tracker>=0) h_PF_backward_Etamax_tracker->Fill(t.pfEta->at(imaxEta_backward_tracker), t.pfPhi->at(imaxEta_backward_tracker), t.pfE->at(imaxEta_backward_tracker), weight);
        else h_PF_backward_Etamax_tracker->Fill(0., 0., 0., weight);
    }

    TFile *f = new TFile(fout, "recreate");
    for (auto h : {
        h_eta,
        h_PF, h_PF_plus, h_PF_minus, h_PF_forward, h_PF_backward,
        h_PF_plus_Emax, h_PF_minus_Emax, h_PF_forward_Emax, h_PF_backward_Emax,
        h_PF_plus_Emax_tracker, h_PF_minus_Emax_tracker, h_PF_forward_Emax_tracker, h_PF_backward_Emax_tracker,
        h_PF_plus_BB_Emax, h_PF_minus_BB_Emax, h_PF_forward_BB_Emax, h_PF_backward_BB_Emax,
        h_PF_plus_EC1_Emax, h_PF_minus_EC1_Emax, h_PF_forward_EC1_Emax, h_PF_backward_EC1_Emax,
        h_PF_plus_EC2_Emax, h_PF_minus_EC2_Emax, h_PF_forward_EC2_Emax, h_PF_backward_EC2_Emax,
        h_PF_plus_HF_Emax, h_PF_minus_HF_Emax, h_PF_forward_HF_Emax, h_PF_backward_HF_Emax,
        h_PF_plus_Etamax, h_PF_minus_Etamax, h_PF_forward_Etamax, h_PF_backward_Etamax,
        h_PF_plus_Etamax_tracker, h_PF_minus_Etamax_tracker, h_PF_forward_Etamax_tracker, h_PF_backward_Etamax_tracker,
    }) {
        h->Write();
    }
    for (auto h : {
        h_rapgap_pm_Emax, h_rapgap_fb_Emax,
        h_rapgap_pm_Emax_tracker, h_rapgap_fb_Emax_tracker,
        h_rapgap_pm_Etamax, h_rapgap_fb_Etamax,
        h_rapgap_pm_Etamax_tracker, h_rapgap_fb_Etamax_tracker,
    }) {
        h->Write();
    }
    f->Close();
}