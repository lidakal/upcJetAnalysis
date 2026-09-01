#include "../tree.h"

void plot_pt_spectrum_MC(TString fin="", TString fout="pt_spectrum_mc.root") 
{
    std::cout << "Input file: " << fin << std::endl;
    std::cout << "Output file: " << fout << std::endl;

    tree t;
    if (fin != "") {
        t.Add(fin);
    } else {
        t.Add("/u/user/lidakal/SE_UserHome/GNucleus-Diffraction-PhotonBeamB_Pthat10_5p36TeV/crab_GNucleus-Diffraction-PhotonBeamB_Pthat10_5p36TeV-forest/260701_005201/0000/HiForestMiniAOD_*.root");
    }
    t.Init();

    TH2F *h_lead_pt_Jet8 = new TH2F("h_lead_pt_Jet8", "x=pt, y=passJet8", 100, 0, 200, 2, 0, 2);
    TH2F *h_lead_pt_Jet12 = new TH2F("h_lead_pt_Jet12", "x=pt, y=passJet12", 100, 0, 200, 2, 0, 2);
    TH2F *h_lead_pt_Jet16 = new TH2F("h_lead_pt_Jet16", "x=pt, y=passJet16", 100, 0, 200, 2, 0, 2);
    TH2F *h_lead_pt_Jet20 = new TH2F("h_lead_pt_Jet20", "x=pt, y=passJet20", 100, 0, 200, 2, 0, 2);

     for (Long64_t ient=0; ient<t.GetEntries(); ient++) {
        if (ient % 100000 == 0) 
            std::cout << "Processing entry " << ient << "/" << t.GetEntries() << std::endl;

        // if (ient < 100000) continue;
        // if (ient > 10000) break;

        t.GetEntry(ient); 

        // skip events without jets
        if (t.nref < 1) continue;

        // fill trigger histograms
        h_lead_pt_Jet8->Fill(t.jtpt[0], t.HLT_SingleJet8_NotMBHF2AND);
        h_lead_pt_Jet12->Fill(t.jtpt[0], t.HLT_SingleJet12_NotMBHF2AND);
        h_lead_pt_Jet16->Fill(t.jtpt[0], t.HLT_SingleJet16_NotMBHF2AND);
        h_lead_pt_Jet20->Fill(t.jtpt[0], t.HLT_SingleJet20_NotMBHF2AND);
    
    }

    TFile *f = new TFile(fout, "recreate");
    for (auto h : {h_lead_pt_Jet8, h_lead_pt_Jet12, h_lead_pt_Jet16, h_lead_pt_Jet20}) {
        h->Write();
    }
    f->Close();
}