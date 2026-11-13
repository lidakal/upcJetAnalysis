#include "../analyses/common/tree.h"
#include "../analyses/common/bins.h"

const Int_t nratio_bins = 10;
const Float_t ratio_bins[] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0};

void plot_jes(TString fin="", TString fout="jes.root")
{
    // Read files
    tree t;
    if (fin != "") {
        t.Add(fin);
    } else {
        t.Add("/u/user/lidakal/SE_UserHome/GNucleus-Diffraction-PhotonBeamB_Pthat10_5p36TeV/crab_GNucleus-Diffraction-PhotonBeamB_Pthat10_5p36TeV-forest_v2/260813_082421/0000/HiForestMiniAOD_1*.root");
    }
    t.Init();

    TH3F *h_rawpt_vs_refpt_vs_jteta = new TH3F("h_rawpt_vs_refpt_vs_jteta", "x=refpt, y=rawpt, z=jteta", npt_bins, pt_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);
    TH3F *h_jtpt_vs_refpt_vs_jteta = new TH3F("h_jtpt_vs_refpt_vs_jteta", "x=refpt, y=jtpt, z=jteta", npt_bins, pt_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);
    TH3F *h_corpt_vs_refpt_vs_jteta = new TH3F("h_corpt_vs_refpt_vs_jteta", "x=refpt, y=corpt, z=jteta", npt_bins, pt_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);

    TH3F *h_rawpt_jes_vs_refpt_vs_jteta = new TH3F("h_rawpt_jes_vs_refpt_vs_jteta", "x=refpt, y=rawpt/refpt, z=jteta", npt_bins, pt_bins, nratio_bins, ratio_bins, neta_bins_s, eta_bins_s);
    TH3F *h_jtpt_jes_vs_refpt_vs_jteta = new TH3F("h_jtpt_jes_vs_refpt_vs_jteta", "x=refpt, y=jtpt/refpt, z=jteta", npt_bins, pt_bins, nratio_bins, ratio_bins, neta_bins_s, eta_bins_s);
    TH3F *h_corpt_jes_vs_refpt_vs_jteta = new TH3F("h_corpt_jes_vs_refpt_vs_jteta", "x=refpt, y=corpt/refpt, z=jteta", npt_bins, pt_bins, nratio_bins, ratio_bins, neta_bins_s, eta_bins_s);

    TH3F *h_rawpt_vs_refpt_vs_jteta_lead = new TH3F("h_rawpt_vs_refpt_vs_jteta_lead", "x=refpt, y=rawpt, z=jteta", npt_bins, pt_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);
    TH3F *h_jtpt_vs_refpt_vs_jteta_lead = new TH3F("h_jtpt_vs_refpt_vs_jteta_lead", "x=refpt, y=jtpt, z=jteta", npt_bins, pt_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);
    TH3F *h_corpt_vs_refpt_vs_jteta_lead = new TH3F("h_corpt_vs_refpt_vs_jteta_lead", "x=refpt, y=corpt, z=jteta", npt_bins, pt_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);

    TH3F *h_rawpt_jes_vs_refpt_vs_jteta_lead = new TH3F("h_rawpt_jes_vs_refpt_vs_jteta_lead", "x=refpt, y=rawpt/refpt, z=jteta", npt_bins, pt_bins, nratio_bins, ratio_bins, neta_bins_s, eta_bins_s);
    TH3F *h_jtpt_jes_vs_refpt_vs_jteta_lead = new TH3F("h_jtpt_jes_vs_refpt_vs_jteta_lead", "x=refpt, y=jtpt/refpt, z=jteta", npt_bins, pt_bins, nratio_bins, ratio_bins, neta_bins_s, eta_bins_s);
    TH3F *h_corpt_jes_vs_refpt_vs_jteta_lead = new TH3F("h_corpt_jes_vs_refpt_vs_jteta_lead", "x=refpt, y=corpt/refpt, z=jteta", npt_bins, pt_bins, nratio_bins, ratio_bins, neta_bins_s, eta_bins_s);

    TH3F *h_rawpt_vs_refpt_vs_jteta_sub = new TH3F("h_rawpt_vs_refpt_vs_jteta_sub", "x=refpt, y=rawpt, z=jteta", npt_bins, pt_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);
    TH3F *h_jtpt_vs_refpt_vs_jteta_sub = new TH3F("h_jtpt_vs_refpt_vs_jteta_sub", "x=refpt, y=jtpt, z=jteta", npt_bins, pt_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);
    TH3F *h_corpt_vs_refpt_vs_jteta_sub = new TH3F("h_corpt_vs_refpt_vs_jteta_sub", "x=refpt, y=corpt, z=jteta", npt_bins, pt_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);

    TH3F *h_rawpt_jes_vs_refpt_vs_jteta_sub = new TH3F("h_rawpt_jes_vs_refpt_vs_jteta_sub", "x=refpt, y=rawpt/refpt, z=jteta", npt_bins, pt_bins, nratio_bins, ratio_bins, neta_bins_s, eta_bins_s);
    TH3F *h_jtpt_jes_vs_refpt_vs_jteta_sub = new TH3F("h_jtpt_jes_vs_refpt_vs_jteta_sub", "x=refpt, y=jtpt/refpt, z=jteta", npt_bins, pt_bins, nratio_bins, ratio_bins, neta_bins_s, eta_bins_s);
    TH3F *h_corpt_jes_vs_refpt_vs_jteta_sub = new TH3F("h_corpt_jes_vs_refpt_vs_jteta_sub", "x=refpt, y=corpt/refpt, z=jteta", npt_bins, pt_bins, nratio_bins, ratio_bins, neta_bins_s, eta_bins_s);

    TH3F *h_rawpt_vs_refpt_vs_jteta_third = new TH3F("h_rawpt_vs_refpt_vs_jteta_third", "x=refpt, y=rawpt, z=jteta", npt_bins, pt_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);
    TH3F *h_jtpt_vs_refpt_vs_jteta_third = new TH3F("h_jtpt_vs_refpt_vs_jteta_third", "x=refpt, y=jtpt, z=jteta", npt_bins, pt_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);
    TH3F *h_corpt_vs_refpt_vs_jteta_third = new TH3F("h_corpt_vs_refpt_vs_jteta_third", "x=refpt, y=corpt, z=jteta", npt_bins, pt_bins, npt_bins, pt_bins, neta_bins_s, eta_bins_s);

    TH3F *h_rawpt_jes_vs_refpt_vs_jteta_third = new TH3F("h_rawpt_jes_vs_refpt_vs_jteta_third", "x=refpt, y=rawpt/refpt, z=jteta", npt_bins, pt_bins, nratio_bins, ratio_bins, neta_bins_s, eta_bins_s);
    TH3F *h_jtpt_jes_vs_refpt_vs_jteta_third = new TH3F("h_jtpt_jes_vs_refpt_vs_jteta_third", "x=refpt, y=jtpt/refpt, z=jteta", npt_bins, pt_bins, nratio_bins, ratio_bins, neta_bins_s, eta_bins_s);
    TH3F *h_corpt_jes_vs_refpt_vs_jteta_third = new TH3F("h_corpt_jes_vs_refpt_vs_jteta_third", "x=refpt, y=corpt/refpt, z=jteta", npt_bins, pt_bins, nratio_bins, ratio_bins, neta_bins_s, eta_bins_s);

    for (Long64_t ient = 0; ient < t.GetEntries(); ient++) {
        // if (ient > 10) break;
        if (ient % 100000 == 0)
            std::cout << "Processing entry " << ient << " / " << t.GetEntries() << std::endl;

        t.GetEntry(ient);

        // if (t.nref>0) {
        //     std::cout << "Entry = " << ient << ", jtpt[0] = " << t.jtpt[0] << ", corpt[0] = " << t.corpt[0] << std::endl;
        // }


        for (Int_t ijet = 0; ijet < t.nref; ijet++) {
            if (!t.passJetID(t.jteta[ijet], 
                t.jtPfCHM[ijet], t.jtPfNHM[ijet], t.jtPfCEM[ijet], t.jtPfNEM[ijet], t.jtPfMUM[ijet], 
                t.jtPfCHF[ijet], t.jtPfNHF[ijet], t.jtPfCEF[ijet], t.jtPfNEF[ijet], t.jtPfMUF[ijet])
            ) continue;

            if (!t.passVetoMap(t.jteta[ijet], t.jtphi[ijet])) continue;

            h_rawpt_vs_refpt_vs_jteta->Fill(t.refpt[ijet],t.rawpt[ijet], t.jteta[ijet], t.weight);
            h_jtpt_vs_refpt_vs_jteta->Fill(t.refpt[ijet], t.jtpt[ijet], t.jteta[ijet], t.weight);
            h_corpt_vs_refpt_vs_jteta->Fill(t.refpt[ijet], t.corpt[ijet], t.jteta[ijet], t.weight);

            if (t.refpt[ijet] > 0) {
                h_rawpt_jes_vs_refpt_vs_jteta->Fill(t.refpt[ijet], t.rawpt[ijet]/t.refpt[ijet], t.jteta[ijet], t.weight);
                h_jtpt_jes_vs_refpt_vs_jteta->Fill(t.refpt[ijet], t.jtpt[ijet]/t.refpt[ijet], t.jteta[ijet], t.weight);
                h_corpt_jes_vs_refpt_vs_jteta->Fill(t.refpt[ijet], t.corpt[ijet]/t.refpt[ijet], t.jteta[ijet], t.weight);
            }
        }

        if (t.nref>0) {
            h_rawpt_vs_refpt_vs_jteta_lead->Fill(t.refpt[0],t.rawpt[0], t.jteta[0], t.weight);
            h_jtpt_vs_refpt_vs_jteta_lead->Fill(t.refpt[0], t.jtpt[0], t.jteta[0], t.weight);
            h_corpt_vs_refpt_vs_jteta_lead->Fill(t.refpt[0], t.corpt[0], t.jteta[0], t.weight);

            if (t.refpt[0] > 0) {
                h_rawpt_jes_vs_refpt_vs_jteta_lead->Fill(t.refpt[0], t.rawpt[0]/t.refpt[0], t.jteta[0], t.weight);
                h_jtpt_jes_vs_refpt_vs_jteta_lead->Fill(t.refpt[0], t.jtpt[0]/t.refpt[0], t.jteta[0], t.weight);
                h_corpt_jes_vs_refpt_vs_jteta_lead->Fill(t.refpt[0], t.corpt[0]/t.refpt[0], t.jteta[0], t.weight);
            }
        }

        if (t.nref>1) {
            h_rawpt_vs_refpt_vs_jteta_sub->Fill(t.refpt[1],t.rawpt[1], t.jteta[1], t.weight);
            h_jtpt_vs_refpt_vs_jteta_sub->Fill(t.refpt[1], t.jtpt[1], t.jteta[1], t.weight);
            h_corpt_vs_refpt_vs_jteta_sub->Fill(t.refpt[1], t.corpt[1], t.jteta[1], t.weight);

            if (t.refpt[1] > 0) {
                h_rawpt_jes_vs_refpt_vs_jteta_sub->Fill(t.refpt[1], t.rawpt[1]/t.refpt[1], t.jteta[1], t.weight);
                h_jtpt_jes_vs_refpt_vs_jteta_sub->Fill(t.refpt[1], t.jtpt[1]/t.refpt[1], t.jteta[1], t.weight);
                h_corpt_jes_vs_refpt_vs_jteta_sub->Fill(t.refpt[1], t.corpt[1]/t.refpt[1], t.jteta[1], t.weight);
            }
        }

        if (t.nref>2) {
            h_rawpt_vs_refpt_vs_jteta_third->Fill(t.refpt[2],t.rawpt[2], t.jteta[2], t.weight);
            h_jtpt_vs_refpt_vs_jteta_third->Fill(t.refpt[2], t.jtpt[2], t.jteta[2], t.weight);
            h_corpt_vs_refpt_vs_jteta_third->Fill(t.refpt[2], t.corpt[2], t.jteta[2], t.weight);

            if (t.refpt[2] > 0) {
                h_rawpt_jes_vs_refpt_vs_jteta_third->Fill(t.refpt[2], t.rawpt[2]/t.refpt[2], t.jteta[2], t.weight);
                h_jtpt_jes_vs_refpt_vs_jteta_third->Fill(t.refpt[2], t.jtpt[2]/t.refpt[2], t.jteta[2], t.weight);
                h_corpt_jes_vs_refpt_vs_jteta_third->Fill(t.refpt[2], t.corpt[2]/t.refpt[2], t.jteta[2], t.weight);
            }
        }
    } // entries loop

    TFile *f = new TFile(fout, "recreate");
    for (auto h : {
        h_rawpt_vs_refpt_vs_jteta, h_jtpt_vs_refpt_vs_jteta, h_corpt_vs_refpt_vs_jteta,
        h_rawpt_jes_vs_refpt_vs_jteta, h_jtpt_jes_vs_refpt_vs_jteta, h_corpt_jes_vs_refpt_vs_jteta,

        h_rawpt_vs_refpt_vs_jteta_lead, h_jtpt_vs_refpt_vs_jteta_lead, h_corpt_vs_refpt_vs_jteta_lead,
        h_rawpt_jes_vs_refpt_vs_jteta_lead, h_jtpt_jes_vs_refpt_vs_jteta_lead, h_corpt_jes_vs_refpt_vs_jteta_lead,

        h_rawpt_vs_refpt_vs_jteta_sub, h_jtpt_vs_refpt_vs_jteta_sub, h_corpt_vs_refpt_vs_jteta_sub,
        h_rawpt_jes_vs_refpt_vs_jteta_sub, h_jtpt_jes_vs_refpt_vs_jteta_sub, h_corpt_jes_vs_refpt_vs_jteta_sub,

        h_rawpt_vs_refpt_vs_jteta_third, h_jtpt_vs_refpt_vs_jteta_third, h_corpt_vs_refpt_vs_jteta_third,
        h_rawpt_jes_vs_refpt_vs_jteta_third, h_jtpt_jes_vs_refpt_vs_jteta_third, h_corpt_jes_vs_refpt_vs_jteta_third
    }) {
        h->Write();
    }

    f->Close();
    delete f;
}