#include "JetUncertainty.h"
#include "JetCorrector.h"

const Int_t nrefpt_bins = 14;
const Float_t refpt_bins[] = {0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 20, 30, 50};

const Int_t njes_bins = 10;
const Float_t jes_bins[] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0};

const Int_t neta_bins = 36;
const Float_t eta_bins[] = {-5.191, -4.013, -2.964, 
    -2.500, 
    -1.740, -1.305, 
    -1.218, -1.044, -0.957, 
    -0.783, -0.696, -0.609, -0.522, -0.435, -0.348, -0.261, -0.174, -0.087, 
    +0.000,
    +0.087, +0.174, +0.261, +0.348, +0.435, +0.522, +0.609, +0.696, +0.783, 
    +0.957, +1.044, +1.218, 
    +1.305, +1.740, 
    +2.500,
    +2.964, +4.013, +5.191   
};

void plot_from_jra(TString input_file="", TString output_file="jet_kinematics.root")
{
    TStopwatch timer;
    timer.Start();

    // Read JECs
    std::vector<std::string> jec_files;
    // jec_files.push_back("/u/user/lidakal/UPC2023/CMSSW_13_2_15/src/PhysicsJetEnergyCorrection/MCTruthStudies/21153_ParallelizationWithCondor/FilesStdPlusGaus_beamAPlusB_test_config/ParallelMC_L2Relative_AK4PF.txt");
    // jec_files.push_back("/u/user/lidakal/UPC2023/CMSSW_13_2_15/src/PhysicsJetEnergyCorrection/MCTruthStudies/21153_ParallelizationWithCondor/FilesStdPlusGaus/ParallelMC_L2Relative_AK4PF.txt");
    // jec_files.push_back("/u/user/lidakal/UPC2023/CMSSW_13_2_15/src/PhysicsJetEnergyCorrection/MCTruthStudies/21153_ParallelizationWithCondor/FilesStd/ParallelMC_L2Relative_AK4PF.txt");
    jec_files.push_back("txt_files/L2L3_ppReco_2023ppRef/ParallelMC_L2Relative_AK4PF_pp_Reco_v0_12-21-2023.txt");
    std::cout << "Reading JEC from " << jec_files[0] << std::endl;
    JetCorrector JEC(jec_files);

    // Read files
    TChain *tree = new TChain("ak4pf/t");
    if (input_file != "") {
        std::cout << "Adding file " << input_file << std::endl;
        tree->Add(input_file);
    }
    else {
        // Read from multiple files
        TString base_dir = "/u/user/lidakal/SE_UserHome/GNucleus-QCD_Pthat5_5p36TeV_pythia8/crab_GNucleus-QCD_Pthat5_5p36TeV_pythia8_JRA_v3/260216_050450/";
        // TString base_dir = "/u/user/lidakal/SE_UserHome/GNucleus-QCD-PhotonBeamB_Pthat0_UPC_5p36TeV_pythia8/crab_GNucleus-QCD-PhotonBeamB_Pthat0_UPC_5p36TeV_pythia8_JRA_v2/260217_091009/";
        // TString base_dir = "/u/user/lidakal/SE_UserHome/GNucleus-QCD-PhotonBeamA_Pthat0_UPC_5p36TeV_pythia8/crab_GNucleus-QCD-PhotonBeamA_Pthat0_UPC_5p36TeV_pythia8_JRA/260217_090747/";
        // TString base_dir = "/u/user/lidakal/SE_UserHome/HIForward0/crab_HiForward0_HIRun2023A-PromptReco-v2_ZDCjson_v7/260216_070726/";
        std::cout << "Adding files from " << base_dir << std::endl;
        tree->Add(base_dir+"/0000/*.root");
    }

    Long64_t nentries = tree->GetEntries();
    std::cout << "Total entries: " << nentries << std::endl;

    // Create fout
    std::cout << "Creating file " << output_file << std::endl;
    TFile *fout = new TFile(output_file, "recreate");

    // ak4pf/t branches
    UChar_t nref;
    std::vector<float> *rawpt = nullptr;
    std::vector<float> *jtpt = nullptr;
    std::vector<float> *jteta = nullptr; 
    std::vector<float> *jtphi = nullptr;
    std::vector<float> *refpt = nullptr;
    std::vector<float> *refeta = nullptr;
    std::vector<float> *refphi = nullptr;

    tree->SetBranchAddress("nref", &nref);
    tree->SetBranchAddress("jtpt", &jtpt);
    tree->SetBranchAddress("jteta", &jteta);
    tree->SetBranchAddress("jtphi", &jtphi);
    tree->SetBranchAddress("refpt", &refpt);
    tree->SetBranchAddress("refeta", &refeta);
    tree->SetBranchAddress("refphi", &refphi);

    Float_t weight = 1.0;

    TH1F *h_rawpt = new TH1F("h_rawpt", "rawpt", nrefpt_bins, refpt_bins);
    TH1F *h_jtpt_w_jec = new TH1F("h_jtpt_w_jec", "jtpt_new_jec", nrefpt_bins, refpt_bins);
    TH1F *h_jteta = new TH1F("h_jteta", "jteta", neta_bins, eta_bins);
    TH1F *h_jtphi = new TH1F("h_jtphi", "jtphi", 25, -3.141, +3.141);

    TH2F *h_rawpt_vs_refpt = new TH2F("h_rawpt_vs_refpt", "rawpt_vs_refpt", nrefpt_bins, refpt_bins, nrefpt_bins, refpt_bins);
    TH2F *h_jtpt_w_jec_vs_refpt = new TH2F("h_jtpt_w_jec_vs_refpt", "jtpt_w_jec_vs_refpt", nrefpt_bins, refpt_bins, nrefpt_bins, refpt_bins);

    TH3F *h_jes_w_jec_vs_refpt_vs_jteta = new TH3F("h_jes_w_jec_vs_refpt_vs_jteta", "jes_w_jec_vs_refpt_vs_jteta", nrefpt_bins, refpt_bins, njes_bins, jes_bins, neta_bins, eta_bins);
    TH3F *h_jes_vs_refpt_vs_jteta = new TH3F("h_jes_vs_refpt_vs_jteta", "jes_vs_refpt_vs_jteta", nrefpt_bins, refpt_bins, njes_bins, jes_bins, neta_bins, eta_bins);

    for (Long64_t ient = 0; ient < nentries; ient++) {
        // if (ient > 10) break;
        if (ient % 100000 == 0)
            std::cout << "Processing entry " << ient << " / " << nentries << std::endl;

        tree->GetEntry(ient);

        for (Int_t ijet = 0; ijet < (int) nref; ijet++) {
            h_rawpt->Fill(jtpt->at(ijet), weight);
            h_jteta->Fill(jteta->at(ijet), weight);
            h_jtphi->Fill(jtphi->at(ijet), weight);
            h_rawpt_vs_refpt->Fill(refpt->at(ijet), jtpt->at(ijet), weight);
            if (refpt->at(ijet) > 0) h_jes_vs_refpt_vs_jteta->Fill(refpt->at(ijet), jtpt->at(ijet)/refpt->at(ijet), jteta->at(ijet), weight);
            
            JEC.SetJetPT(jtpt->at(ijet));
            JEC.SetJetEta(jteta->at(ijet));
            JEC.SetJetPhi(jtphi->at(ijet));
            float jet_pt_corr = JEC.GetCorrectedPT();
            h_jtpt_w_jec->Fill(jet_pt_corr, weight);
            h_jtpt_w_jec_vs_refpt->Fill(refpt->at(ijet), jet_pt_corr, weight);
            if (refpt->at(ijet) > 0) h_jes_w_jec_vs_refpt_vs_jteta->Fill(refpt->at(ijet), jet_pt_corr/refpt->at(ijet), jteta->at(ijet), weight);
        }
    } // entries loop

    h_rawpt->Write();
    h_jteta->Write();
    h_jtphi->Write();
    h_jtpt_w_jec->Write();
    h_rawpt_vs_refpt->Write();
    h_jtpt_w_jec_vs_refpt->Write();
    h_jes_w_jec_vs_refpt_vs_jteta->Write();
    h_jes_vs_refpt_vs_jteta->Write();

    fout->Close();
    delete fout;

    timer.Stop();
    timer.Print();
}