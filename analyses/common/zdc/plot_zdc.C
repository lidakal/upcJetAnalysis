#include "../tree.h"

void plot_zdc(TString fin="", TString fout="zdc.root") 
{
    std::cout << "Input file: " << fin << std::endl;
    std::cout << "Output file: " << fout << std::endl;

    tree t;
    if (fin != "") {
        t.Add(fin);
    } else {
        t.Add("/u/user/lidakal/SE_UserHome/HIForward0/crab_HiForward0_HIRun2023A-16Jan2024-v1_ZDCjson_wCCfilter/260629_023836/0000/HiForestMiniAOD_*.root");
    }
    t.Init();

    TH2F *h_Esum = new TH2F("h_Esum", "x=sumPlus, y=sumMinus", 500, 0, 5000, 500, 0, 5000);

    for (Long64_t ient=0; ient<t.GetEntries(); ient++) {
        if (ient % 100000 == 0) 
            std::cout << "Processing entry " << ient << "/" << t.GetEntries() << std::endl;

        // if (ient < 100000) continue;
        // if (ient > 10000) break;

        t.GetEntry(ient); 

        // hlt, zdc, dijet, add. activity, rapidity gap selections
        if (!t.passFilter(ient, true, false, false, false, false)) continue;
        double weight = t.weight;

        h_Esum->Fill(t.sumPlus, t.sumMinus, weight);
    }

    TFile *f = new TFile(fout, "recreate");
    h_Esum->Write();
    f->Close();
    delete f;
}