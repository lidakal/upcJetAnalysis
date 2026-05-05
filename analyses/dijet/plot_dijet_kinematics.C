#include "tree.h"

void plot_dijet_kinematics(TString fin="", TString fout="dijet_kinematics.root") 
{
    std::cout << "Input file: " << fin << std::endl;
    std::cout << "Output file: " << fout << std::endl;

    tree t;
    if (fin != "") {
        t.Add(fin);
    } else {
        t.Add("~/SE_UserHome/GNucleus-QCD_Pthat5_5p36TeV_pythia8/crab_GNucleus_QCD_Pthat5_jtPtMin_5_genPtMin_3/260127_033519/0000/HiForestMiniAOD_*.root");
    }
    t.Init();

    TH1F *h_QT = new TH1F("h_QT", "dijet QT", 100, 0, 100);
    TH1F *h_PT = new TH1F("h_PT", "dijet PT", 100, 0, 100);
    TH1F *h_Minv = new TH1F("h_Minv", "dijet mass", 100, 0, 200);
    TH1F *h_y = new TH1F("h_y", "dijet rapidity", 100, -5, 5);

    TLorentzVector jet1, jet2;
    for (Long64_t ient=0; ient<t.GetEntries(); ient++) {
        if (!t.passFilter(ient)) continue;

        jet1.SetPtEtaPhiM(t.jtpt[0], t.jteta[0], t.jtphi[0], t.jtm[0]);
        jet2.SetPtEtaPhiM(t.jtpt[1], t.jteta[1], t.jtphi[1], t.jtm[1]);

    
        double qt = (jet1 + jet2).Pt();
        double pt = 0.5 * (jet1 - jet2).Pt();
        double minv = (jet1 + jet2).M();
        double y = (jet1 + jet2).Rapidity();

        h_QT->Fill(qt);
        h_PT->Fill(pt);
        h_Minv->Fill(minv);
        h_y->Fill(y);
    }

    TFile *f = new TFile(fout, "recreate");
    h_QT->Write();
    h_PT->Write();
    h_Minv->Write();
    h_y->Write();
    f->Close();
} 