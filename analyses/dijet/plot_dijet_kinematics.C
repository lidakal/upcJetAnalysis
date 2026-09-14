#include "../common/tree.h"
#include "../common/bins.h"
#include <math.h>
#include <random>

void plot_dijet_kinematics(TString fin="", TString fout="dijet_kinematics.root") 
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

    TH2F *h_pt1_pt2 = new TH2F("h_pt1_pt2", "x=pt1, y=pt2", npt_bins, pt_bins, npt_bins, pt_bins);
    TH2F *h_eta1_eta2 = new TH2F("h_eta1_eta2", "x=eta1, y=eta2", neta_bins_s, eta_bins_s, neta_bins_s, eta_bins_s);
    TH3F *h_eta1_eta2_midEta = new TH3F("h_eta1_eta2_midEta", "x=eta1, y=eta2, y=midEta", neta_bins_s, eta_bins_s, neta_bins_s, eta_bins_s, neta_bins_s, eta_bins_s);
    TH3F *h_eta1_eta2_dijetEta = new TH3F("h_eta1_eta2_dijetEta", "x=eta1, y=eta2, y=dijetEta", neta_bins_s, eta_bins_s, neta_bins_s, eta_bins_s, neta_bins_s, eta_bins_s);
    TH2F *h_midEta_dijetEta = new TH2F("h_midEta_dijetEta", "x=midEta, y=dijetEta", neta_bins_s, eta_bins_s, neta_bins_s, eta_bins_s);
    TH1F *h_dphi = new TH1F("h_dphi", "dijet #Delta#phi", ndphi_bins, dphi_bins);
    TH1F *h_deta = new TH1F("h_deta", "dijet #Delta#eta", ndeta_bins, deta_bins);
    TH1F *h_dR = new TH1F("h_dR", "dijet #DeltaR", ndeta_bins, deta_bins);
    TH1F *h_QT = new TH1F("h_QT", "dijet QT", nQT_bins, QT_bins);
    TH1F *h_PT = new TH1F("h_PT", "dijet PT", nQT_bins, QT_bins);
    TH2F *h_QT_PT = new TH2F("h_QT_PT", "x=qt, y=pt", nQT_bins, QT_bins, nQT_bins, QT_bins);
    TH1F *h_Minv = new TH1F("h_Minv", "dijet invariant mass", nMinv_bins, Minv_bins);
    TH1F *h_y = new TH1F("h_y", "dijet rapidity", neta_bins_s, eta_bins_s);
    TH1F *h_y_wSwap = new TH1F("h_y_wSwap", "dijet rapidity (with swap)", neta_bins_s, eta_bins_s);
    TH1F *h_absy = new TH1F("h_absy", "dijet rapidity", 50, 0, 5);
    TH1F *h_PHI = new TH1F("h_PHI", "PHI(QT,PT)", nPHI_bins, PHI_bins);
    TH1F *h_PHI_signed = new TH1F("h_PHI_signed", "PHI(QT,PT) signed", nPHI_signed_bins, PHI_signed_bins);
    TH2F *h_cos2PHI_vs_QT = new TH2F("h_cos2PHI_vs_QT", "cos(2*PHI) vs QT", nQT_bins, QT_bins, ncos2PHI_bins, cos2PHI_bins);
    TH3F *h_cos2PHI_vs_QT_vs_y = new TH3F("h_cos2PHI_vs_QT_vs_y", "x=qt, y=dijet rapidity, z=cos(2*PHI)", nQT_bins, QT_bins, neta_bins_s, eta_bins_s, ncos2PHI_bins, cos2PHI_bins);
    TH3F *h_cos2PHI_vs_QT_vs_x1 = new TH3F("h_cos2PHI_vs_QT_vs_x1", "x=qt, y=xBj(with -|yjj|), z=cos(2*PHI)", nQT_bins, QT_bins, nx_bins, x_bins, ncos2PHI_bins, cos2PHI_bins);
    TH3F *h_cos2PHI_vs_QT_vs_x2 = new TH3F("h_cos2PHI_vs_QT_vs_x2", "x=qt, y=xBj(with +|yjj|), z=cos(2*PHI)", nQT_bins, QT_bins, nx_bins, x_bins, ncos2PHI_bins, cos2PHI_bins);
    TH3F *h_cos2PHI_vs_Minv_vs_y = new TH3F("h_cos2PHI_vs_Minv_vs_y", "x=dijet invariant mass, y=dijet rapidity, z=cos(2*PHI)", nMinv_bins, Minv_bins, neta_bins_s, eta_bins_s, ncos2PHI_bins, cos2PHI_bins);
    TH1F *h_Minv_after_cuts = new TH1F("h_Minv_after_cuts", "dijet invariant mass after all cuts", nMinv_bins, Minv_bins);

    // Random number generator for randomizing jet order
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0., 1.);

    TLorentzVector jet1, jet2;
    // TLorentzVector jet1_wSwap, jet2_wSwap;

    for (Long64_t ient=0; ient<t.GetEntries(); ient++) {
        if (ient % 100000 == 0) 
            std::cout << "Processing entry " << ient << "/" << t.GetEntries() << std::endl;

        // if (ient < 100000) continue;
        // if (ient > 10000) break;

        

        t.GetEntry(ient); 

        // hlt, zdc, dijet, add. activity, rapidity gap selections
        if (!t.passFilter(ient, true, true, true, true, true)) continue;
        double weight = t.weight;

        // std::cout << "Entry = " << ient << std::endl;

        h_pt1_pt2->Fill(t.jtpt[0], t.jtpt[1], weight);
        h_eta1_eta2->Fill(t.jteta[0], t.jteta[1], weight);
        double dphi = std::acos(std::cos(t.jtphi[0] - t.jtphi[1]));
        double deta = std::abs(t.jteta[0] - t.jteta[1]);
        double dR = std::sqrt(deta*deta + dphi*dphi);
        h_dphi->Fill(dphi, weight);
        h_deta->Fill(deta, weight);
        h_dR->Fill(dR, weight);

        jet1.SetPtEtaPhiM(t.jtpt[0], t.jteta[0], t.jtphi[0], t.jtm[0]);
        jet2.SetPtEtaPhiM(t.jtpt[1], t.jteta[1], t.jtphi[1], t.jtm[1]);

        if (t.FRG > t.BRG) {
            // continue;
            // std::cout << "\tFRG > BRG, mirroring etas" << std::endl;
            // jet1_wSwap.SetPtEtaPhiM(t.jtpt[0], -t.jteta[0], t.jtphi[0], t.jtm[0]);
            // jet2_wSwap.SetPtEtaPhiM(t.jtpt[1], -t.jteta[1], t.jtphi[1], t.jtm[1]);
            jet1.SetPtEtaPhiM(t.jtpt[0], -t.jteta[0], t.jtphi[0], t.jtm[0]);
            jet2.SetPtEtaPhiM(t.jtpt[1], -t.jteta[1], t.jtphi[1], t.jtm[1]);
        } else {
            // jet1_wSwap.SetPtEtaPhiM(t.jtpt[0], t.jteta[0], t.jtphi[0], t.jtm[0]);
            // jet2_wSwap.SetPtEtaPhiM(t.jtpt[1], t.jteta[1], t.jtphi[1], t.jtm[1]);
        }

        // Randomize jet1 and jet2 to avoid bias in QT and PT calculation
        if (dis(gen) < 0.5) {
            std::swap(jet1, jet2);
            // std::swap(jet1_wSwap, jet2_wSwap);
        }

        // Calculate observables
        TLorentzVector QT = jet1 + jet2;
        TLorentzVector PT = 0.5 * (jet1 - jet2); // Only for transverse use, do not use as a 4-vector
    
        double qt = QT.Pt();
        double pt = PT.Pt();
        double minv = QT.M();
        double y = QT.Rapidity();

        double dot2D = QT.Px()*PT.Px() + QT.Py()*PT.Py();
        double cosPHI = dot2D / (QT.Pt() * PT.Pt());
        double cos2PHI = 2.0 * cosPHI * cosPHI - 1.0;
        double PHI = std::acos(cosPHI);

        // Debugging: check if cosPHI calculation is correct
        // TVector2 pt1(jet1.Px(), jet1.Py());
        // TVector2 pt2(jet2.Px(), jet2.Py());
        // TVector2 QT_tmp = pt1 + pt2;
        // TVector2 PT_tmp = 0.5 * (pt1 - pt2);
        // double cosPHI_tmp = (QT_tmp * PT_tmp) / (QT_tmp.Mod() * PT_tmp.Mod());

        // Signed angle from QT to PT: positive = CCW, negative = CW
        double cross = QT.Px()*PT.Py() - QT.Py()*PT.Px();  // 2D cross product
        double dot   = QT.Px()*PT.Px() + QT.Py()*PT.Py();  // 2D dot product
        double PHI_signed = TMath::ATan2(cross, dot);      // arctan(cross/dot), returns value in [-pi, pi]                
        // std::cout << "qt: " << qt << ", pt: " << pt << ", minv: " << minv << ", y: " << y 
                //   << ", cosPHI: " << cosPHI << ", cosPHI_tmp: " << cosPHI_tmp 
                //   << ", PHI: " << PHI << ", PHI_signed: " << PHI_signed 
                //   << std::endl;

        // Debugging: check if jet*, jet*_wSwap give same QT,PT, PHI
        // TLorentzVector QT_v2 = jet1_wSwap + jet2_wSwap;
        // TLorentzVector PT_v2 = 0.5 * (jet1_wSwap - jet2_wSwap);
        // double qt_v2 = QT_v2.Pt();
        // double pt_v2 = PT_v2.Pt();
        // double minv_v2 = QT_v2.M();
        // double y_v2 = QT_v2.Rapidity();
        // double cross_v2 = QT_v2.Px()*PT_v2.Py() - QT_v2.Py()*PT_v2.Px();  // 2D cross product
        // double dot_v2   = QT_v2.Px()*PT_v2.Px() + QT_v2.Py()*PT_v2.Py();  // 2D dot product
        // double PHI_signed_v2 = TMath::ATan2(cross_v2, dot_v2);      // arctan(cross/dot), returns value in [-pi, pi] 
        // std::cout << "\tQT (v1) = " << qt << ", QT (v2) = " << qt_v2
        //           << "\n\tPT (v1) = " << pt << ", PT (v2) = " << pt_v2
        //           << "\n\tMinv (v1) = " << minv << ", Minv (v2) = " << minv_v2
        //           << "\n\ty (v1) = " << y << ", y (v2) = " << y_v2
        //           << "\n\tPHI_signed (v1) = " << PHI_signed << ", PHI_signed (v2) = " << PHI_signed_v2
        //           << std::endl;


        double midEta = (t.jteta[0]+t.jteta[1])/2.;
        double dijetEta = QT.Eta();
        h_eta1_eta2_midEta->Fill(t.jteta[0], t.jteta[1], midEta, weight);
        h_eta1_eta2_dijetEta->Fill(t.jteta[0], t.jteta[1], dijetEta, weight);        
        h_midEta_dijetEta->Fill(midEta, dijetEta, weight);

        h_QT->Fill(qt, weight);
        h_PT->Fill(pt, weight);
        h_QT_PT->Fill(pt, qt, weight);
        h_Minv->Fill(minv, weight);
        h_y->Fill(y, weight);
        // h_y_wSwap->Fill(y_v2, weight);
        h_absy->Fill(std::abs(y), weight);

        if (qt < pt) {
            h_Minv_after_cuts->Fill(minv, weight);
            h_PHI->Fill(PHI, weight);
            h_PHI_signed->Fill(PHI_signed, weight);
            h_cos2PHI_vs_QT->Fill(qt, cos2PHI, weight);
            h_cos2PHI_vs_QT_vs_y->Fill(qt, y, cos2PHI, weight);
            h_cos2PHI_vs_Minv_vs_y->Fill(minv, y, cos2PHI, weight);

            double sqrtsNN = 5360.; // GeV
            double x1 = (minv / sqrtsNN) * std::exp(-std::abs(y));
            h_cos2PHI_vs_QT_vs_x1->Fill(qt, x1, cos2PHI, weight);
            double x2 = (minv / sqrtsNN) * std::exp(+std::abs(y));
            h_cos2PHI_vs_QT_vs_x2->Fill(qt, x2, cos2PHI, weight);

            if (x1>1) std::cout << "ient = " << ient 
                                << "\n\tWarning: x1 > 1, x1 = " << x1 << ", minv = " << minv << ", y = " << y << std::endl;
            if (x2>1) std::cout << "ient = " << ient 
                                << "\n\tWarning: x2 > 1, x2 = " << x2 << ", minv = " << minv << ", y = " << y << std::endl;
        }
    }

    t.EntryCount();

    TFile *f = new TFile(fout, "recreate");
    h_dphi->Write();
    h_deta->Write();
    h_dR->Write();
    h_QT->Write();
    h_PT->Write();
    h_QT_PT->Write();
    h_eta1_eta2->Write();
    h_pt1_pt2->Write();
    h_Minv->Write();
    h_y->Write();
    // h_y_wSwap->Write();
    h_absy->Write();
    h_PHI->Write();
    h_PHI_signed->Write();
    h_cos2PHI_vs_QT->Write();
    h_cos2PHI_vs_QT_vs_y->Write();
    h_Minv_after_cuts->Write();
    h_cos2PHI_vs_QT_vs_x1->Write();
    h_cos2PHI_vs_QT_vs_x2->Write();
    h_cos2PHI_vs_Minv_vs_y->Write();
    h_midEta_dijetEta->Write();
    h_eta1_eta2_midEta->Write();
    h_eta1_eta2_dijetEta->Write();
    f->Close();
} 