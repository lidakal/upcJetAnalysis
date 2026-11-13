#include "../tree.h"

void plot_pt_spectrum(TString fin="", TString fout="pt_spectrum.root") 
{
    std::cout << "Input file: " << fin << std::endl;
    std::cout << "Output file: " << fout << std::endl;

    tree t;
    if (fin != "") {
        t.Add(fin);
    } else {
        t.Add("/u/user/lidakal/SE_UserHome/HIForward0/crab_HiForward0_HIRun2023A-16Jan2024-v1_ZDCjson_wCCfilter/260629_023836/0000/HiForestMiniAOD_1*.root");
        // t.Add("/u/user/lidakal/SE_UserHome/HIForward0/crab_HiForward0_HIRun2023A-16Jan2024-v1_ZDCjson_wCCfilter_wNotMBHLT/260901_042156/0000/HiForestMiniAOD_1*.root");
        // t.Add("/u/user/lidakal/SE_UserHome/GNucleus-Diffraction-PhotonBeamB_Pthat10_5p36TeV/crab_GNucleus-Diffraction-PhotonBeamB_Pthat10_5p36TeV-forest/260701_005201/0000/HiForestMiniAOD_1*.root");
    }
    t.Init();

    // trigger maps -- only vs jet20 is useful for PS calculation
    TH2F *h_trigger_jet8_vs_jet28 = new TH2F("h_trigger_jet8_vs_jet28", "jet8 vs jet28", 2, 0, 2, 2, 0, 2);
    TH2F *h_trigger_jet12_vs_jet28 = new TH2F("h_trigger_jet12_vs_jet28", "jet12 vs jet28", 2, 0, 2, 2, 0, 2);
    TH2F *h_trigger_jet16_vs_jet28 = new TH2F("h_trigger_jet16_vs_jet28", "jet16 vs jet28", 2, 0, 2, 2, 0, 2);
    TH2F *h_trigger_jet20_vs_jet28 = new TH2F("h_trigger_jet20_vs_jet28", "jet20 vs jet28", 2, 0, 2, 2, 0, 2);
    TH2F *h_trigger_jet24_vs_jet28 = new TH2F("h_trigger_jet24_vs_jet28", "jet24 vs jet28", 2, 0, 2, 2, 0, 2);
    TH2F *h_trigger_NotMB_vs_jet28 = new TH2F("h_trigger_NotMB_vs_jet28", "NotMB vs jet28", 2, 0, 2, 2, 0, 2);

    // per-event prescales
    TH1F *h_hlt_prescale_jet8 = new TH1F("h_hlt_prescale_jet8", "HLT prescale jet8", 100, 0, 50);
    TH1F *h_hlt_prescale_jet12 = new TH1F("h_hlt_prescale_jet12", "HLT prescale jet12", 100, 0, 50);
    TH1F *h_hlt_prescale_jet16 = new TH1F("h_hlt_prescale_jet16", "HLT prescale jet16", 100, 0, 50);
    TH1F *h_hlt_prescale_jet20 = new TH1F("h_hlt_prescale_jet20", "HLT prescale jet20", 100, 0, 50);
    TH1F *h_hlt_prescale_jet24 = new TH1F("h_hlt_prescale_jet24", "HLT prescale jet24", 100, 0, 50);
    TH1F *h_hlt_prescale_jet28 = new TH1F("h_hlt_prescale_jet28", "HLT prescale jet28", 100, 0, 50);

    TH1F *h_l1_prescale_jet8 = new TH1F("h_l1_prescale_jet8", "L1 prescale jet8", 50, 0, 50);
    TH1F *h_l1_prescale_jet12 = new TH1F("h_l1_prescale_jet12", "L1 prescale jet12", 50, 0, 50);
    TH1F *h_l1_prescale_jet16 = new TH1F("h_l1_prescale_jet16", "L1 prescale jet16", 50, 0, 50);
    TH1F *h_l1_prescale_jet20 = new TH1F("h_l1_prescale_jet20", "L1 prescale jet20", 50, 0, 50);
    TH1F *h_l1_prescale_jet24 = new TH1F("h_l1_prescale_jet24", "L1 prescale jet24", 50, 0, 50);
    TH1F *h_l1_prescale_jet28 = new TH1F("h_l1_prescale_jet28", "L1 prescale jet28", 50, 0, 50);
    TH1F *h_l1_prescale_NotMB = new TH1F("h_l1_prescale_NotMB", "L1 prescale NotMB", 50, 0, 50);

    // lead pt without exclusivity selections
    TH1F *h_lead_pt_jet8 = new TH1F("h_lead_pt_jet8", "jet pt spectrum", 100, 0, 200);
    TH1F *h_lead_pt_jet12 = new TH1F("h_lead_pt_jet12", "jet pt spectrum", 100, 0, 200);
    TH1F *h_lead_pt_jet16 = new TH1F("h_lead_pt_jet16", "jet pt spectrum", 100, 0, 200);
    TH1F *h_lead_pt_jet20 = new TH1F("h_lead_pt_jet20", "jet pt spectrum", 100, 0, 200);
    TH1F *h_lead_pt_jet24 = new TH1F("h_lead_pt_jet24", "jet pt spectrum", 100, 0, 200);
    TH1F *h_lead_pt_jet28 = new TH1F("h_lead_pt_jet28", "jet pt spectrum", 100, 0, 200);
    TH1F *h_lead_pt_NotMB = new TH1F("h_lead_pt_NotMB", "jet pt spectrum", 100, 0, 200);

    // lead pt with exclusivity selections -- other combinations don't work because only jet28 is unprescaled
    TH1F* h_lead_pt_jet24not28 = new TH1F("h_lead_pt_jet24not28", "jet pt spectrum", 100, 0, 200);
    TH1F* h_lead_pt_jet20not28 = new TH1F("h_lead_pt_jet20not28", "jet pt spectrum", 100, 0, 200);
    TH1F* h_lead_pt_jet16not28 = new TH1F("h_lead_pt_jet16not28", "jet pt spectrum", 100, 0, 200);
    TH1F* h_lead_pt_jet12not28 = new TH1F("h_lead_pt_jet12not28", "jet pt spectrum", 100, 0, 200);
    TH1F* h_lead_pt_jet8not28 = new TH1F("h_lead_pt_jet8not28", "jet pt spectrum", 100, 0, 200);

    TH1F* h_lead_pt_jet20not24not28 = new TH1F("h_lead_pt_jet20not24not28", "jet pt spectrum", 100, 0, 200);
    TH1F* h_lead_pt_jet16not20not24not28 = new TH1F("h_lead_pt_jet16not20not24not28", "jet pt spectrum", 100, 0, 200);
    TH1F* h_lead_pt_jet12not16not20not24not28 = new TH1F("h_lead_pt_jet12not16not20not24not28", "jet pt spectrum", 100, 0, 200);
    TH1F* h_lead_pt_jet8not12not16not20not24not28 = new TH1F("h_lead_pt_jet8not12not16not20not24not28", "jet pt spectrum", 100, 0, 200);

    TH1F* h_lead_pt_jet8not16not20not24not28 = new TH1F("h_lead_pt_jet8not16not20not24not28", "jet pt spectrum", 100, 0, 200);

    TH1F* h_lead_pt_NotMBnotJet28 = new TH1F("h_lead_pt_NotMBnotJet28", "jet pt spectrum", 100, 0, 200);
    
     for (Long64_t ient=0; ient<t.GetEntries(); ient++) {
        if (ient % 100000 == 0) 
            std::cout << "Processing entry " << ient << "/" << t.GetEntries() << std::endl;

        // if (ient < 100000) continue;
        // if (ient > 1000000) break;

        t.GetEntry(ient); 

        // fill trigger histograms
        h_trigger_jet8_vs_jet28->Fill(t.HLT_SingleJet8_NotMBHF2AND, t.HLT_SingleJet28_NotMBHF2AND);
        h_trigger_jet12_vs_jet28->Fill(t.HLT_SingleJet12_NotMBHF2AND, t.HLT_SingleJet28_NotMBHF2AND);
        h_trigger_jet16_vs_jet28->Fill(t.HLT_SingleJet16_NotMBHF2AND, t.HLT_SingleJet28_NotMBHF2AND);
        h_trigger_jet20_vs_jet28->Fill(t.HLT_SingleJet20_NotMBHF2AND, t.HLT_SingleJet28_NotMBHF2AND);
        h_trigger_jet24_vs_jet28->Fill(t.HLT_SingleJet24_NotMBHF2AND, t.HLT_SingleJet28_NotMBHF2AND);
        h_trigger_NotMB_vs_jet28->Fill(t.HLT_NotMBHF2AND, t.HLT_SingleJet28_NotMBHF2AND);

        // fill prescale histograms
        h_hlt_prescale_jet8->Fill(t.HLT_SingleJet8_NotMBHF2AND_presc_num / (double)t.HLT_SingleJet8_NotMBHF2AND_presc_denom);
        h_hlt_prescale_jet12->Fill(t.HLT_SingleJet12_NotMBHF2AND_presc_num / (double)t.HLT_SingleJet12_NotMBHF2AND_presc_denom);
        h_hlt_prescale_jet16->Fill(t.HLT_SingleJet16_NotMBHF2AND_presc_num / (double)t.HLT_SingleJet16_NotMBHF2AND_presc_denom);
        h_hlt_prescale_jet20->Fill(t.HLT_SingleJet20_NotMBHF2AND_presc_num / (double)t.HLT_SingleJet20_NotMBHF2AND_presc_denom);
        h_hlt_prescale_jet24->Fill(t.HLT_SingleJet24_NotMBHF2AND_presc_num / (double)t.HLT_SingleJet24_NotMBHF2AND_presc_denom);
        h_hlt_prescale_jet28->Fill(t.HLT_SingleJet28_NotMBHF2AND_presc_num / (double)t.HLT_SingleJet28_NotMBHF2AND_presc_denom);

        h_l1_prescale_jet8->Fill(t.L1_SingleJet8_NotMBHF2AND_prescl);
        h_l1_prescale_jet12->Fill(t.L1_SingleJet12_NotMBHF2AND_prescl);
        h_l1_prescale_jet16->Fill(t.L1_SingleJet16_NotMBHF2AND_prescl);
        h_l1_prescale_jet20->Fill(t.L1_SingleJet20_NotMBHF2AND_prescl);
        h_l1_prescale_jet24->Fill(t.L1_SingleJet24_NotMBHF2AND_prescl);
        h_l1_prescale_jet28->Fill(t.L1_SingleJet28_NotMBHF2AND_prescl);
        h_l1_prescale_NotMB->Fill(t.L1_NotMBHF2AND_prescl);

        // skip events without jets for pt spectrum
        if (t.nref < 1) continue;

        // double lead_pt = t.rawpt[0];
        double lead_pt = t.jtpt[0];
        double weight = t.weight;

        // fill leading jet pt spectrum without exclusivity selections
        if (t.HLT_SingleJet8_NotMBHF2AND==1) h_lead_pt_jet8->Fill(lead_pt, weight);
        if (t.HLT_SingleJet12_NotMBHF2AND==1) h_lead_pt_jet12->Fill(lead_pt, weight);
        if (t.HLT_SingleJet16_NotMBHF2AND==1) h_lead_pt_jet16->Fill(lead_pt, weight);
        if (t.HLT_SingleJet20_NotMBHF2AND==1) h_lead_pt_jet20->Fill(lead_pt, weight);
        if (t.HLT_SingleJet24_NotMBHF2AND==1) h_lead_pt_jet24->Fill(lead_pt, weight);
        if (t.HLT_NotMBHF2AND==1) h_lead_pt_NotMB->Fill(lead_pt, weight);

        // fill leading jet pt spectrum with exclusivity selections
        if (t.HLT_SingleJet28_NotMBHF2AND==1) h_lead_pt_jet28->Fill(lead_pt, weight);    
        else if (t.HLT_SingleJet24_NotMBHF2AND==1) h_lead_pt_jet24not28->Fill(lead_pt, weight);        
        else if (t.HLT_SingleJet20_NotMBHF2AND==1) h_lead_pt_jet20not24not28->Fill(lead_pt, weight);        
        else if (t.HLT_SingleJet16_NotMBHF2AND==1) h_lead_pt_jet16not20not24not28->Fill(lead_pt, weight);
        else if (t.HLT_SingleJet12_NotMBHF2AND==1) h_lead_pt_jet12not16not20not24not28->Fill(lead_pt, weight);
        else if (t.HLT_SingleJet8_NotMBHF2AND==1) h_lead_pt_jet8not12not16not20not24not28->Fill(lead_pt, weight);

        if (t.HLT_SingleJet8_NotMBHF2AND==1 && t.HLT_SingleJet28_NotMBHF2AND==0) h_lead_pt_jet8not28->Fill(lead_pt, weight);
        if (t.HLT_SingleJet12_NotMBHF2AND==1 && t.HLT_SingleJet28_NotMBHF2AND==0) h_lead_pt_jet12not28->Fill(lead_pt, weight);
        if (t.HLT_SingleJet16_NotMBHF2AND==1 && t.HLT_SingleJet28_NotMBHF2AND==0) h_lead_pt_jet16not28->Fill(lead_pt, weight);
        if (t.HLT_SingleJet20_NotMBHF2AND==1 && t.HLT_SingleJet28_NotMBHF2AND==0) h_lead_pt_jet20not28->Fill(lead_pt, weight);
        if (t.HLT_NotMBHF2AND==1 && t.HLT_SingleJet28_NotMBHF2AND==0) h_lead_pt_NotMBnotJet28->Fill(lead_pt, weight);

        if (    (t.HLT_SingleJet8_NotMBHF2AND==1)
             && (t.HLT_SingleJet16_NotMBHF2AND==0)
             && (t.HLT_SingleJet20_NotMBHF2AND==0)
             && (t.HLT_SingleJet24_NotMBHF2AND==0)
             && (t.HLT_SingleJet28_NotMBHF2AND==0)
            ) 
            h_lead_pt_jet8not16not20not24not28->Fill(lead_pt, weight);
    }

    TFile *f = new TFile(fout, "recreate");
    for (auto h : {
        h_trigger_jet8_vs_jet28, h_trigger_jet12_vs_jet28, 
        h_trigger_jet16_vs_jet28, h_trigger_jet20_vs_jet28,
        h_trigger_jet24_vs_jet28,
        h_trigger_NotMB_vs_jet28
    }) {
        h->Write();
    }
    for (auto h : {
        h_hlt_prescale_jet8, h_hlt_prescale_jet12, 
        h_hlt_prescale_jet16, h_hlt_prescale_jet20,
        h_hlt_prescale_jet24, h_hlt_prescale_jet28,
        h_l1_prescale_jet8, h_l1_prescale_jet12, 
        h_l1_prescale_jet16, h_l1_prescale_jet20,
        h_l1_prescale_jet24, h_l1_prescale_jet28,
        h_l1_prescale_NotMB
    }) {
        h->Write();
    }
    for (auto h : {
        h_lead_pt_jet8, h_lead_pt_jet12, 
        h_lead_pt_jet16, h_lead_pt_jet20, 
        h_lead_pt_jet24, h_lead_pt_jet28, 
        h_lead_pt_NotMB,
        h_lead_pt_jet24not28, h_lead_pt_jet20not28, h_lead_pt_jet16not28, 
        h_lead_pt_jet12not28, h_lead_pt_jet8not28,
        h_lead_pt_NotMBnotJet28,
        h_lead_pt_jet20not24not28, h_lead_pt_jet16not20not24not28, 
        h_lead_pt_jet12not16not20not24not28, h_lead_pt_jet8not12not16not20not24not28,
        h_lead_pt_jet8not16not20not24not28
    }) {
        h->Write();
    }
    f->Close();
}