#include "../common/tree.h"
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
        t.Add("/u/user/lidakal/SE_UserHome/HIForward5/crab_HiForward5_HIRun2023A-PromptReco-v2_ZDCjson_noCCfilter/260624_071604//0000/HiForestMiniAOD_1*.root");
    }
    t.Init();

    TH1F *h_dphi = new TH1F("h_dphi", "dijet #Delta#phi", 100, 0, TMath::Pi());
    TH1F *h_deta = new TH1F("h_deta", "dijet #Delta#eta", 100, 0, 10);
    TH1F *h_dR = new TH1F("h_dR", "dijet #DeltaR", 100, 0, 10);
    TH1F *h_QT = new TH1F("h_QT", "dijet QT", 100, 0, 100);
    TH1F *h_PT = new TH1F("h_PT", "dijet PT", 100, 0, 100);
    TH1F *h_Minv = new TH1F("h_Minv", "dijet invariant mass", 100, 0, 200);
    TH1F *h_y = new TH1F("h_y", "dijet rapidity", 100, -5, 5);
    TH1F *h_PHI = new TH1F("h_PHI", "PHI(QT,PT)", 100, 0, TMath::Pi());
    TH1F *h_PHI_signed = new TH1F("h_PHI_signed", "PHI(QT,PT) signed", 100, -TMath::Pi(), TMath::Pi());
    TH2F *h_cos2PHI_vs_QT = new TH2F("h_cos2PHI_vs_QT", "cos(2*PHI) vs QT", 100, 0, 100, 100, -1, 1);

    // Random number generator for randomizing jet order
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0., 1.);

    TLorentzVector jet1, jet2;
    for (Long64_t ient=0; ient<t.GetEntries(); ient++) {
        if (ient % 100000 == 0) 
            std::cout << "Processing entry " << ient << "/" << t.GetEntries() << std::endl;

        // if (ient < 100000) continue;
        // if (ient > 10000) break;

        t.GetEntry(ient); 

        if (!t.passFilter(ient)) continue;

        double dphi = std::acos(std::cos(t.jtphi[0] - t.jtphi[1]));
        double deta = std::abs(t.jteta[0] - t.jteta[1]);
        double dR = std::sqrt(deta*deta + dphi*dphi);
        h_dphi->Fill(dphi);
        h_deta->Fill(deta);
        h_dR->Fill(dR);

        jet1.SetPtEtaPhiM(t.jtpt[0], t.jteta[0], t.jtphi[0], t.jtm[0]);
        jet2.SetPtEtaPhiM(t.jtpt[1], t.jteta[1], t.jtphi[1], t.jtm[1]);

        // Randomize jet1 and jet2 to avoid bias in QT and PT calculation
        if (dis(gen) < 0.5) {
            std::swap(jet1, jet2);
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

        h_QT->Fill(qt);
        h_PT->Fill(pt);
        h_Minv->Fill(minv);
        h_y->Fill(y);
        h_PHI->Fill(PHI);
        h_PHI_signed->Fill(PHI_signed);
        h_cos2PHI_vs_QT->Fill(qt, cos2PHI);
    }

    TFile *f = new TFile(fout, "recreate");
    h_dphi->Write();
    h_deta->Write();
    h_dR->Write();
    h_QT->Write();
    h_PT->Write();
    h_Minv->Write();
    h_y->Write();
    h_PHI->Write();
    h_PHI_signed->Write();
    h_cos2PHI_vs_QT->Write();
    f->Close();
} 