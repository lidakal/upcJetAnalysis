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

void plot_PF_distribution(TString fin="", TString fout="pf_distribution.root")
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
        t.Add("/u/user/lidakal/SE_UserHome/HIForward0/crab_HiForward0_HIRun2023A-16Jan2024-v1_ZDCjson_wCCfilter/260629_023836/0000/HiForestMiniAOD_*.root");
    }
    t.Init();

    // jet eta
    TH3F *h_eta = new TH3F("h_eta", "x=eta1, y=eta2, z=(eta1+eta2)/2", neta_bins_s, eta_bins_s, neta_bins_s, eta_bins_s, neta_bins_s, eta_bins_s);

    // one entry per PF candidate (incl. jet const.)
    TH3F *h_PF = new TH3F("h_PF", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    // one entry per PF candidation (excl. jet const.)
    TH3F *h_PF_forward = new TH3F("h_PF_forward", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_backward = new TH3F("h_PF_backward", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);

    // one entry per event (PF with Emax in forward/backward (excl. jet const.))
    TH3F *h_PF_forward_Emax = new TH3F("h_PF_forward_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_backward_Emax = new TH3F("h_PF_backward_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);

    // one entry per event (PF with Emax in HF (excl. jet const.))
    TH3F *h_PF_forward_HF_Emax = new TH3F("h_PF_forward_HF_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_backward_HF_Emax = new TH3F("h_PF_backward_HF_Emax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);

    // one entry per event (PF with Etamax in forward/backward (excl. jet const.))
    TH3F *h_PF_forward_Etamax = new TH3F("h_PF_forward_Etamax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);
    TH3F *h_PF_backward_Etamax = new TH3F("h_PF_backward_Etamax", "x=eta, y=phi, z=E", neta_bins_s, eta_bins_s, nphi_bins_s, phi_bins_s, nE_bins_s, E_bins_s);

    // one entry per event 
    TH2D *h_rapgap_Emax = new TH2D("h_rapgap_Emax", "x=deta_forward, y=deta_backward", ndeta_bins_s, deta_bins_s, ndeta_bins_s, deta_bins_s);
    TH2D *h_rapgap_Etamax = new TH2D("h_rapgap_Etamax", "x=deta_forward, y=deta_backward", ndeta_bins_s, deta_bins_s, ndeta_bins_s, deta_bins_s);

    TLorentzVector jet1, jet2, pfcand;
    for (Long64_t ient=0; ient<t.GetEntries(); ient++) {
        if (ient % 100000 == 0) 
            std::cout << "Processing entry " << ient << "/" << t.GetEntries() << std::endl;

        // if (ient < 100000) continue;
        // if (ient > 200000) break;

        t.GetEntry(ient); 

        // if (t.nPF > 0) std::cout << "Entry " << ient << ": nPF = " << t.nPF << std::endl;

        // do not cut on  rapidity gap
        if (!t.passFilter(ient, true, true, true, true, false)) continue;

        // event topology
        double mideta = (t.jteta[0] + t.jteta[1]) / 2.0;
        double etamin = std::min(t.jteta[0], t.jteta[1])-0.5; 
        double etamax = std::max(t.jteta[0], t.jteta[1])+0.5; 
        if (std::abs(etamax) < std::abs(etamin)) std::swap(etamax, etamin);
        
        h_eta->Fill(t.jteta[0], t.jteta[1], mideta, t.weight);

        // index of PF candidate
        int imaxE_forward = -1;
        int imaxE_backward = -1;
        int imaxE_forward_HF = -1;
        int imaxE_backward_HF = -1;
        int imaxEta_forward = -1;
        int imaxEta_backward = -1;

        int nPF_forward = 0;
        int nPF_backward = 0;

        for (int i=0; i<t.nPF; i++) {
            // all candidates
            h_PF->Fill(t.pfEta->at(i), t.pfPhi->at(i), t.pfE->at(i), t.weight);

            double maxE_forward = (imaxE_forward >= 0) ? t.pfE->at(imaxE_forward) : 0;
            double maxE_backward = (imaxE_backward >= 0) ? t.pfE->at(imaxE_backward) : 0;
            double maxE_forward_HF = (imaxE_forward_HF >= 0) ? t.pfE->at(imaxE_forward_HF) : 0;
            double maxE_backward_HF = (imaxE_backward_HF >= 0) ? t.pfE->at(imaxE_backward_HF) : 0;
            double maxDEtamin_forward = (imaxEta_forward >= 0) ? std::abs(t.pfEta->at(i) - etamin) : 0;
            double maxDEtamax_backward = (imaxEta_backward >= 0) ? std::abs(t.pfEta->at(i) - etamax) : 0;

            // backward is for etaPF<etamax<etamin or etamin<etamax<etaPF
            if (    ((t.pfEta->at(i) < etamax) && (etamax < etamin))
                ||  ((t.pfEta->at(i) > etamax) && (etamax > etamin))) {
                nPF_backward++;
                h_PF_backward->Fill(t.pfEta->at(i), t.pfPhi->at(i), t.pfE->at(i), t.weight); // backward candidates
                if (t.pfE->at(i) > maxE_backward) imaxE_backward = i;
                if (std::abs(t.pfEta->at(i)) > 3) { // HF
                    if (t.pfE->at(i) > maxE_backward_HF) imaxE_backward_HF = i;
                }
                // furthest away from etamax
                if ((t.pfPt->at(i) > 0.2) && (std::abs(t.pfEta->at(i)-etamax) > maxDEtamax_backward)) imaxEta_backward = i;
            }

            // forward is for etamax<etamin<etaPF or etaPF<etamin<etamax 
            if (    ((t.pfEta->at(i) > etamin) && (etamin > etamax))
                ||  ((t.pfEta->at(i) < etamin) && (etamin < etamax))) {
                nPF_forward++;
                h_PF_forward->Fill(t.pfEta->at(i), t.pfPhi->at(i), t.pfE->at(i), t.weight); // forward candidates
                if (t.pfE->at(i) > maxE_forward) imaxE_forward = i;
                if (std::abs(t.pfEta->at(i)) > 3.) { // HF
                    // std::cout << "Forward HF candidate: eta = " << t.pfEta->at(i) << ", phi = " << t.pfPhi->at(i) << ", E = " << t.pfE->at(i) << std::endl;
                    if (t.pfE->at(i) > maxE_forward_HF) imaxE_forward_HF = i;
                }
                // furthest away from etamin
                if ((t.pfPt->at(i) > 0.2) && (std::abs(t.pfEta->at(i)-etamin) > maxDEtamin_forward)) imaxEta_forward = i;
            }
        }

        // std::cout << "Entry " << ient 
        //           << ": nPF = " << t.nPF 
        //           << ", nPF_forward = " << nPF_forward 
        //           << ", nPF_backward = " << nPF_backward 
        //           << ", t.jtPfCHM[0]+t.jtPfNHM[0]+t.jtPfCEM[0]+t.jtPfNEM[0]+t.jtPfMUM[0] = " << t.jtPfCHM[0]+t.jtPfNHM[0]+t.jtPfCEM[0]+t.jtPfNEM[0]+t.jtPfMUM[0]
        //           << ", t.jtPfCHM[1]+t.jtPfNHM[1]+t.jtPfCEM[1]+t.jtPfNEM[1]+t.jtPfMUM[1] = " << t.jtPfCHM[1]+t.jtPfNHM[1]+t.jtPfCEM[1]+t.jtPfNEM[1]+t.jtPfMUM[1]                  
        //           << std::endl;

        double deta_forward_Emax = 0;
        if (imaxE_forward>=0) {
            h_PF_forward_Emax->Fill(t.pfEta->at(imaxE_forward), t.pfPhi->at(imaxE_forward), t.pfE->at(imaxE_forward), t.weight);
            if (t.pfEta->at(imaxE_forward) > mideta) {
                deta_forward_Emax = 5.2 - t.pfEta->at(imaxE_forward);
            } else {
                deta_forward_Emax = 5.2 + t.pfEta->at(imaxE_forward);
            }
        }
        double deta_backward_Emax = 0;
        if (imaxE_backward>=0) {
            h_PF_backward_Emax->Fill(t.pfEta->at(imaxE_backward), t.pfPhi->at(imaxE_backward), t.pfE->at(imaxE_backward), t.weight);
            deta_backward_Emax = 5.2 - std::abs(t.pfEta->at(imaxE_backward));
        }
        if (deta_forward_Emax>0 && deta_backward_Emax>0) {
            h_rapgap_Emax->Fill(deta_forward_Emax, deta_backward_Emax, t.weight);
        }

        if (imaxE_forward_HF>=0) h_PF_forward_HF_Emax->Fill(t.pfEta->at(imaxE_forward_HF), t.pfPhi->at(imaxE_forward_HF), t.pfE->at(imaxE_forward_HF), t.weight);
        if (imaxE_backward_HF>=0) h_PF_backward_HF_Emax->Fill(t.pfEta->at(imaxE_backward_HF), t.pfPhi->at(imaxE_backward_HF), t.pfE->at(imaxE_backward_HF), t.weight);

        double deta_forward_Etamax = 0;
        if (imaxEta_forward>=0) {
            h_PF_forward_Etamax->Fill(t.pfEta->at(imaxEta_forward), t.pfPhi->at(imaxEta_forward), t.pfE->at(imaxEta_forward), t.weight);
            if (t.pfEta->at(imaxEta_forward) > mideta) {
                deta_forward_Etamax = 5.2 - t.pfEta->at(imaxEta_forward);
            } else {
                deta_forward_Etamax = 5.2 + t.pfEta->at(imaxEta_forward);
            }
        }
        double deta_backward_Etamax = 0;
        if (imaxEta_backward>=0) {
            h_PF_backward_Etamax->Fill(t.pfEta->at(imaxEta_backward), t.pfPhi->at(imaxEta_backward), t.pfE->at(imaxEta_backward), t.weight);
            deta_backward_Etamax = 5.2 - std::abs(t.pfEta->at(imaxEta_backward));
        }
        if (deta_forward_Etamax>0 && deta_backward_Etamax>0) {
            h_rapgap_Etamax->Fill(deta_forward_Etamax, deta_backward_Etamax, t.weight);
        }
    }

    TFile *f = new TFile(fout, "recreate");
    h_eta->Write();
    h_PF_forward->Write();
    h_PF_backward->Write();
    h_PF_forward_Emax->Write();
    h_PF_backward_Emax->Write();
    h_PF_forward_HF_Emax->Write();
    h_PF_backward_HF_Emax->Write();
    h_PF_forward_Etamax->Write();
    h_PF_backward_Etamax->Write();
    h_rapgap_Emax->Write();
    h_rapgap_Etamax->Write();
    f->Close();
}