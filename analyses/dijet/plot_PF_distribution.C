#include "../common/tree.h"

void plot_PF_distribution(TString fin="", TString fout="pf_distribution.root")
{
    std::cout << "Input file: " << fin << std::endl;
    std::cout << "Output file: " << fout << std::endl;

    tree t;
    if (fin != "") {
        t.Add(fin);
    } else {
        t.Add("/u/user/lidakal/SE_UserHome/GNucleus-Diffraction-PhotonBeamA_Pthat10_5p36TeV/crab_GNucleus-Diffraction-PhotonBeamA_Pthat10_5p36TeV-forest/260630_071353/0000/HiForestMiniAOD_*.root");
        // t.Add("/u/user/lidakal/SE_UserHome/HIForward0/crab_HiForward0_HIRun2023A-PromptReco-v2_ZDCjson_noCCfilter/260624_111153/0000/HiForestMiniAOD_*.root");
        // t.Add("/u/user/lidakal/SE_UserHome/GNucleus-Diffraction-PhotonBeamA_Pthat10_5p36TeV/crab_GNucleus-Diffraction-PhotonBeamA_Pthat10_5p36TeV-forest/260630_071353/0000/HiForestMiniAOD_6*.root");
        // t.Add("/u/user/lidakal/SE_UserHome/GNucleus-Diffraction-PhotonBeamA_Pthat10_5p36TeV/crab_GNucleus-Diffraction-PhotonBeamA_Pthat10_5p36TeV-forest/260630_071353/0000/HiForestMiniAOD_5*.root");
    }
    t.Init();

    int pe = 0;
    TH3F *h_PF = new TH3F("h_PF", "x=eta, y=phi, z=E", 100, -5.2, 5.2, 100, -TMath::Pi(), TMath::Pi(), 100, 0, 100);
    TH3F *h_forward = new TH3F("h_forward", "x=eta, y=phi, z=E", 100, -5.2, 5.2, 100, -TMath::Pi(), TMath::Pi(), 100, 0, 100);
    TH3F *h_backward = new TH3F("h_backward", "x=eta, y=phi, z=E", 100, -5.2, 5.2, 100, -TMath::Pi(), TMath::Pi(), 100, 0, 100);
    TH1F *h_forward_Emax = new TH1F("h_forward_Emax", "x=E_{max}", 100, 0, 100);
    TH1F *h_backward_Emax = new TH1F("h_backward_Emax", "x=E_{max}", 100, 0, 100);

    TLorentzVector jet1, jet2;
    for (Long64_t ient=0; ient<t.GetEntries(); ient++) {
        if (ient % 100000 == 0) 
            std::cout << "Processing entry " << ient << "/" << t.GetEntries() << std::endl;

        // if (ient < 100000) continue;
        // if (ient > 1000) break;

        t.GetEntry(ient); 

        // if (t.nPF > 0) std::cout << "Entry " << ient << ": nPF = " << t.nPF << std::endl;
        if (!t.passFilter(ient)) continue;
        pe++;

        jet1.SetPtEtaPhiM(t.jtpt[0], t.jteta[0], t.jtphi[0], t.jtm[0]);
        jet2.SetPtEtaPhiM(t.jtpt[1], t.jteta[1], t.jtphi[1], t.jtm[1]);
        auto dijet = jet1 + jet2;
        double dijet_eta = dijet.Eta();

        double maxE_forward = 0;
        double maxE_backward = 0;
        for (int i=0; i<t.nPF; i++) {
            h_PF->Fill(t.pfEta->at(i), t.pfPhi->at(i), t.pfE->at(i), t.weight);
            
            // check for same hemisphere as dijet
            bool is_forward = (t.pfEta->at(i) * dijet_eta > 0);

            if (is_forward) {
                h_forward->Fill(t.pfEta->at(i), t.pfPhi->at(i), t.pfE->at(i), t.weight);
                if (std::abs(t.pfEta->at(i)) > 3) 
                    if (t.pfE->at(i) > maxE_forward) maxE_forward = t.pfE->at(i);
            } else {
                h_backward->Fill(t.pfEta->at(i), t.pfPhi->at(i), t.pfE->at(i), t.weight);
                if (std::abs(t.pfEta->at(i)) > 3)
                    if (t.pfE->at(i) > maxE_backward) maxE_backward = t.pfE->at(i);
            }
        }
        h_forward_Emax->Fill(maxE_forward);
        h_backward_Emax->Fill(maxE_backward);
    }

    std::cout << "Processed " << pe << " entries passing the filter." << std::endl;
    std::cout << "Filled " << h_PF->GetName() << " with " << h_PF->GetEntries() << " entries." << std::endl;

    TFile *f = new TFile(fout, "recreate");
    h_PF->Write();
    h_forward->Write();
    h_backward->Write();
    h_forward_Emax->Write();
    h_backward_Emax->Write();
    f->Close();
}