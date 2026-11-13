#include "JetCorrector.h"
#include "JetUncertainty.h"

#include <TChain.h>

#include <vector>

class tree {
    public:
        TChain *t; 
        TChain *hlt; 
        TChain *hi; 
        TChain *zdc;
        TChain *pf;

        // Sequential counters 
        // Each one also passes all the previous ones
        // Calculated in passFilter() function
        Long64_t nEntries = 0;
        Long64_t nEntriesPassHLT = 0; // also PV and CC filters
        Long64_t nEntriesPassZDC = 0;
        Long64_t nEntriesPassJetKin = 0;
        Long64_t nEntriesPassJetID = 0;
        Long64_t nEntriesPassJetVM = 0;
        Long64_t nEntriesPassAddAct = 0;
        Long64_t nEntriesPassHF = 0; // also EC2
        Long64_t nEntriesPassRG = 0;
        Long64_t nEntriesPassAll = 0;
        
        // Rapidity gap variables to be reused
        // Calculated in calcRapGap() function
        bool passHFp = true;
        int iPF_HFp = -1;
        bool passHFm = true;
        int iPF_HFm = -1;

        bool passEC2p = true;
        int iPF_EC2p = -1;
        bool passEC2m = true;
        int iPF_EC2m = -1;

        double FRG = -1;
        int iPF_FRG = -1;
        double BRG = -1;
        int iPF_BRG = -1;

        tree(TString="ak0PFJetAnalyzer/t");
        ~tree();

        std::vector<TString> fileNames;

        void Add(TString);
        void Init();
        Long64_t GetEntries();
        void GetEntry(Long64_t);
        bool passFilter(Long64_t, bool, bool, bool, bool, bool);
        bool passFilterRef(Long64_t, bool, bool, bool, bool, bool);
        void loadVetoMap(const std::string);
        bool passVetoMap(Float_t, Float_t);
        bool passJetID(Float_t, Int_t, Int_t, Int_t, Int_t, Int_t, Float_t, Float_t, Float_t, Float_t, Float_t);
        void loadJEC(const std::string);
        bool pass0n0n(Float_t, Float_t);
        bool pass0nXnOneSided(Float_t, Float_t);
        bool passXn0nOneSided(Float_t, Float_t);
        bool pass0nXnInclusive(Float_t, Float_t);
        bool passXnXn(Float_t, Float_t);
        bool pfIsCharged(Int_t id);
        void calcRapGap(Long64_t ientry,
            bool chargedOnly=true, double trackerLim=2.5, double PFPtMin=0.2);
        void EntryCount();

        bool isMC = false;
        TH2D* hvetomap_;
        JetCorrector *JEC = nullptr;
        const static Int_t MAXJETS = 100;
        const double PS8 = 1.85749;
        const double PS12 = 1.70506;
        const double PS16 = 1.13695;
        const double PS20 = 1.00237;
        const double PS24 = 1.00002;

        // my variables
        Float_t corpt[MAXJETS];

        // jet analyzer variables
        Int_t run = 0;
        Int_t lumi = 0;
        Int_t evt = 0;
        Int_t nref = 0;
        Float_t rawpt[MAXJETS];
        Float_t jtpt[MAXJETS];
        Float_t jteta[MAXJETS];
        Float_t jtphi[MAXJETS];
        Float_t jtm[MAXJETS];
        Float_t jtPfCHF[MAXJETS];
        Float_t jtPfNHF[MAXJETS];
        Float_t jtPfCEF[MAXJETS];
        Float_t jtPfNEF[MAXJETS];
        Float_t jtPfMUF[MAXJETS];
        Int_t jtPfCHM[MAXJETS];
        Int_t jtPfNHM[MAXJETS];
        Int_t jtPfCEM[MAXJETS];
        Int_t jtPfNEM[MAXJETS];
        Int_t jtPfMUM[MAXJETS];

        Float_t refpt[MAXJETS];
        Float_t refeta[MAXJETS];
        Float_t refphi[MAXJETS];
        Float_t refm[MAXJETS];
        
        // event info variables
        Float_t weight = 0.;

        // hlt variables
        Int_t HLT_HIL1NotBptxOR = -1;
        Int_t HLT_SingleJet8_NotMBHF2AND = -1;
        Int_t HLT_SingleJet12_NotMBHF2AND = -1;
        Int_t HLT_SingleJet16_NotMBHF2AND = -1;
        Int_t HLT_SingleJet20_NotMBHF2AND = -1;
        Int_t HLT_SingleJet24_NotMBHF2AND = -1;
        Int_t HLT_SingleJet28_NotMBHF2AND = -1;
        Int_t HLT_ZDC1nOr = -1;
        Int_t HLT_NotMBHF2AND = -1;

        Int_t HLT_SingleJet8_NotMBHF2AND_presc_num = -1;
        Int_t HLT_SingleJet8_NotMBHF2AND_presc_denom = 1;
        Int_t HLT_SingleJet12_NotMBHF2AND_presc_num = -1;
        Int_t HLT_SingleJet12_NotMBHF2AND_presc_denom = 1;
        Int_t HLT_SingleJet16_NotMBHF2AND_presc_num = -1;
        Int_t HLT_SingleJet16_NotMBHF2AND_presc_denom = 1;
        Int_t HLT_SingleJet20_NotMBHF2AND_presc_num = -1;
        Int_t HLT_SingleJet20_NotMBHF2AND_presc_denom = 1;
        Int_t HLT_SingleJet24_NotMBHF2AND_presc_num = -1;
        Int_t HLT_SingleJet24_NotMBHF2AND_presc_denom = 1;
        Int_t HLT_SingleJet28_NotMBHF2AND_presc_num = -1;
        Int_t HLT_SingleJet28_NotMBHF2AND_presc_denom = 1;

        Int_t L1_SingleJet8_NotMBHF2AND_prescl = -1;
        Int_t L1_SingleJet12_NotMBHF2AND_prescl = -1;
        Int_t L1_SingleJet16_NotMBHF2AND_prescl = -1;
        Int_t L1_SingleJet20_NotMBHF2AND_prescl = -1;
        Int_t L1_SingleJet24_NotMBHF2AND_prescl = -1;
        Int_t L1_SingleJet28_NotMBHF2AND_prescl = -1;
        Int_t L1_NotMBHF2AND_prescl = -1;

        // zdc variables
        Float_t sumPlus = 0.;
        Float_t sumMinus = 0.;

        // pf variables
        Int_t nPF = 0;
        std::vector<float> *pfPt = nullptr;
        std::vector<float> *pfEta = nullptr;
        std::vector<float> *pfPhi = nullptr;
        std::vector<float> *pfE = nullptr;
        std::vector<int>   *pfId = nullptr;
};

// Constructor and destructor
tree::tree(TString treeName) {
    // jet tree can change name based on R
    t = new TChain(treeName);
    hlt = new TChain("hltanalysis/HltTree");
    hi = new TChain("hiEvtAnalyzer/HiTree");
    zdc = new TChain("zdcanalyzer/zdcrechit");
    pf = new TChain("particleFlowAnalyser/pftree");
}    
tree::~tree() {
    if (t) delete t;   
    if (hlt) delete hlt;
    if (hi) delete hi;
    if (zdc) delete zdc;
    if (pf) delete pf;
    return;
}

// Class functions
void tree::Add(TString fileName) {
    fileNames.push_back(fileName);
}
void tree::Init() {
    if (!t) {
        std::cerr << "Error: TChain not initialized!" << std::endl;
        return;
    }
    if (fileNames.empty()) {
        std::cerr << "Error: No input files added!" << std::endl;
        return;
    }
    if (!fileNames[0].Contains("HIForward")&&!fileNames[0].Contains("HIEmptyBX")) isMC = true;

    for (const auto& fileName : fileNames) {
        t->Add(fileName);
        hlt->Add(fileName);
        hi->Add(fileName);
        zdc->Add(fileName);
        pf->Add(fileName);
    }

    // force TChain to load the files
    nEntries = t->GetEntries(); 
    hlt->GetEntries();
    hi->GetEntries();
    zdc->GetEntries();
    pf->GetEntries();
    std::cout << "Added " << nEntries << " entries from " << fileNames.size() << " files." << std::endl;

    // jet analyzer branches
    t->SetBranchAddress("run", &run);
    t->SetBranchAddress("lumi", &lumi);
    t->SetBranchAddress("evt", &evt);
    t->SetBranchAddress("nref", &nref);
    t->SetBranchAddress("rawpt", rawpt);
    t->SetBranchAddress("jtpt", jtpt);
    t->SetBranchAddress("jteta", jteta);
    t->SetBranchAddress("jtphi", jtphi);
    t->SetBranchAddress("jtm", jtm);
    t->SetBranchAddress("jtPfCHF", jtPfCHF);
    t->SetBranchAddress("jtPfNHF", jtPfNHF);
    t->SetBranchAddress("jtPfCEF", jtPfCEF);
    t->SetBranchAddress("jtPfNEF", jtPfNEF);
    t->SetBranchAddress("jtPfMUF", jtPfMUF);
    t->SetBranchAddress("jtPfCHM", jtPfCHM);
    t->SetBranchAddress("jtPfNHM", jtPfNHM);
    t->SetBranchAddress("jtPfCEM", jtPfCEM);
    t->SetBranchAddress("jtPfNEM", jtPfNEM);
    t->SetBranchAddress("jtPfMUM", jtPfMUM);

    if (isMC) {
        t->SetBranchAddress("refpt", refpt);
        t->SetBranchAddress("refeta", refeta);
        t->SetBranchAddress("refphi", refphi);
        t->SetBranchAddress("refm", refm);
    }
 
    // evt info branches
    if (isMC) {
        hi->SetBranchAddress("weight", &weight);
    } else {
        weight = 1.0;
    }

    // hlt branches
    if (fileNames[0].Contains("HIEmptyBX")) hlt->SetBranchAddress("HLT_HIL1NotBptxOR_v10", &HLT_HIL1NotBptxOR);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet8_NotMBHF2AND_MaxPixelCluster50000_v2", &HLT_SingleJet8_NotMBHF2AND);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet12_NotMBHF2AND_MaxPixelCluster50000_v2", &HLT_SingleJet12_NotMBHF2AND);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet16_NotMBHF2AND_MaxPixelCluster50000_v2", &HLT_SingleJet16_NotMBHF2AND);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet20_NotMBHF2AND_MaxPixelCluster50000_v2", &HLT_SingleJet20_NotMBHF2AND);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet24_NotMBHF2AND_MaxPixelCluster50000_v2", &HLT_SingleJet24_NotMBHF2AND);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet28_NotMBHF2AND_MaxPixelCluster50000_v2", &HLT_SingleJet28_NotMBHF2AND);
    hlt->SetBranchAddress("HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v8", &HLT_ZDC1nOr);
    hlt->SetBranchAddress("HLT_HIUPC_NotMBHF2_v1", &HLT_NotMBHF2AND);

    hlt->SetBranchAddress("HLT_HIUPC_SingleJet8_NotMBHF2AND_MaxPixelCluster50000_v2_PrescaleNumerator", &HLT_SingleJet8_NotMBHF2AND_presc_num);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet12_NotMBHF2AND_MaxPixelCluster50000_v2_PrescaleNumerator", &HLT_SingleJet12_NotMBHF2AND_presc_num);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet16_NotMBHF2AND_MaxPixelCluster50000_v2_PrescaleNumerator", &HLT_SingleJet16_NotMBHF2AND_presc_num);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet20_NotMBHF2AND_MaxPixelCluster50000_v2_PrescaleNumerator", &HLT_SingleJet20_NotMBHF2AND_presc_num);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet24_NotMBHF2AND_MaxPixelCluster50000_v2_PrescaleNumerator", &HLT_SingleJet24_NotMBHF2AND_presc_num);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet28_NotMBHF2AND_MaxPixelCluster50000_v2_PrescaleNumerator", &HLT_SingleJet28_NotMBHF2AND_presc_num);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet8_NotMBHF2AND_MaxPixelCluster50000_v2_PrescaleDenominator", &HLT_SingleJet8_NotMBHF2AND_presc_denom);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet12_NotMBHF2AND_MaxPixelCluster50000_v2_PrescaleDenominator", &HLT_SingleJet12_NotMBHF2AND_presc_denom);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet16_NotMBHF2AND_MaxPixelCluster50000_v2_PrescaleDenominator", &HLT_SingleJet16_NotMBHF2AND_presc_denom);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet20_NotMBHF2AND_MaxPixelCluster50000_v2_PrescaleDenominator", &HLT_SingleJet20_NotMBHF2AND_presc_denom);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet24_NotMBHF2AND_MaxPixelCluster50000_v2_PrescaleDenominator", &HLT_SingleJet24_NotMBHF2AND_presc_denom);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet28_NotMBHF2AND_MaxPixelCluster50000_v2_PrescaleDenominator", &HLT_SingleJet28_NotMBHF2AND_presc_denom);

    hlt->SetBranchAddress("L1_SingleJet8_NotMinimumBiasHF2_AND_BptxAND_Prescl", &L1_SingleJet8_NotMBHF2AND_prescl);
    hlt->SetBranchAddress("L1_SingleJet12_NotMinimumBiasHF2_AND_BptxAND_Prescl", &L1_SingleJet12_NotMBHF2AND_prescl);
    hlt->SetBranchAddress("L1_SingleJet16_NotMinimumBiasHF2_AND_BptxAND_Prescl", &L1_SingleJet16_NotMBHF2AND_prescl);
    hlt->SetBranchAddress("L1_SingleJet20_NotMinimumBiasHF2_AND_BptxAND_Prescl", &L1_SingleJet20_NotMBHF2AND_prescl);
    hlt->SetBranchAddress("L1_SingleJet24_NotMinimumBiasHF2_AND_BptxAND_Prescl", &L1_SingleJet24_NotMBHF2AND_prescl);
    hlt->SetBranchAddress("L1_SingleJet28_NotMinimumBiasHF2_AND_BptxAND_Prescl", &L1_SingleJet28_NotMBHF2AND_prescl);
    hlt->SetBranchAddress("L1_NotMinimumBiasHF2_AND_BptxAND_Prescl", &L1_NotMBHF2AND_prescl);

    // zdc branches
    zdc->SetBranchAddress("sumPlus", &sumPlus);
    zdc->SetBranchAddress("sumMinus", &sumMinus);

    // pf branches
    pf->SetBranchAddress("nPF", &nPF);
    pf->SetBranchAddress("pfPt", &pfPt);
    pf->SetBranchAddress("pfEta", &pfEta);
    pf->SetBranchAddress("pfPhi", &pfPhi);
    pf->SetBranchAddress("pfE", &pfE);
    pf->SetBranchAddress("pfId", &pfId);

    // JEC
    loadJEC("/u/user/lidakal/UPC2023/CMSSW_13_2_15_OLD/src/PhysicsJetEnergyCorrection/MCTruthStudies/21153_ParallelizationWithCondor/FilesMyFunction_beamAPlusB_Pthat8_26EtaBins_allCones_relrsp0to2/ak4pf/ParallelMC_L2Relative_AK4PF.txt");

    // Veto map
    loadVetoMap("/u/user/lidakal/UPC2023/upcJetAnalysis/analyses/common/vetomaps/Summer23BPixPrompt23_RunD_v0.root");
    // loadVetoMap("/u/user/lidakal/UPC2023/upcJetAnalysis/analyses/common/vetomaps/Summer24Prompt25_RunCDEFG.root");
}
Long64_t tree::GetEntries() {
    return t->GetEntries();
}
void tree::GetEntry(Long64_t ientry) {
    t->GetEntry(ientry);
    hlt->GetEntry(ientry);
    hi->GetEntry(ientry);
    zdc->GetEntry(ientry);
    pf->GetEntry(ientry);

    // calculate corrected pt
    if (JEC) {
        for (Int_t ijet = 0; ijet < nref; ijet++) {
            JEC->SetJetPT(rawpt[ijet]);
            JEC->SetJetEta(jteta[ijet]);
            JEC->SetJetPhi(jtphi[ijet]);
            corpt[ijet] = JEC->GetCorrectedPT();
            // jtpt[ijet] = corpt[ijet];
        }
    }

    // renew values from previous event
    passHFp = true;
    iPF_HFp = -1;
    passHFm = true;
    iPF_HFm = -1;
    passEC2p = true;
    iPF_EC2p = -1;
    passEC2m = true;
    iPF_EC2m = -1;
    FRG = -1;
    iPF_FRG = -1;
    BRG = -1;
    iPF_BRG = -1;
}

void tree::calcRapGap(Long64_t ientry,
    bool chargedOnly=true, double trackerLim=2.5, double PFPtMin=0.2) {
    
    GetEntry(ientry); // renew RG values from previous event inside GetEntry()

    // Empty HF, EC2 thresholds
    double Ethr_HFp = 9.5; // GeV
    double Ethr_HFm = 9.;
    double Ethr_EC2p = 3.5;
    double Ethr_EC2m = 3.5;

    // Rap. gap in tracker
    int imaxEta_forward_tracker = -1;
    int imaxEta_backward_tracker = -1;

    
    for (int i=0; i<nPF; i++) {
        double pfeta = pfEta->at(i);
        double pfe = pfE->at(i);
        double pfpt = pfPt->at(i);
        int    pfid = pfId->at(i);

        // HF cuts
        if (pfeta > 3.) {
            if (iPF_HFp < 0) iPF_HFp = i;
            if ((pfe > pfE->at(iPF_HFp))) iPF_HFp = i;
            if (pfe > Ethr_HFp) passHFp = false;
        }
        if (pfeta < -3.) {
            if (iPF_HFm < 0) iPF_HFm = i;
            if (pfe > pfE->at(iPF_HFm)) iPF_HFm = i;
            if (pfe > Ethr_HFm) passHFm = false;
        }

        // EC2 cuts 
        if ((pfeta < 3.) && (pfeta > 2.5)) {
            if (iPF_EC2p < 0) iPF_EC2p = i;
            if (pfe > pfE->at(iPF_EC2p)) iPF_EC2p = i;
            if (pfeta > Ethr_EC2p) passEC2p = false;
        }
        if ((pfeta > -3.) && (pfeta < -2.5)) {
            if (iPF_EC2m < 0) iPF_EC2m = i;
            if (pfe > pfE->at(iPF_EC2m)) iPF_EC2m = i;
            if (pfeta > Ethr_EC2m) passEC2m = false;
        }

        // RG in tracker
        double maxEta_forward_tracker = (iPF_FRG >= 0) ? pfEta->at(iPF_FRG) : -trackerLim; // look from -trkLim -> +trkLim
        double maxEta_backward_tracker = (iPF_BRG >= 0) ? pfEta->at(iPF_BRG) : +trackerLim; // look from +trkLim -> -trkLim
        if (((!chargedOnly)||pfIsCharged(pfid)) && (std::abs(pfeta) < trackerLim) && (pfpt > PFPtMin) && (pfeta > maxEta_forward_tracker)) iPF_FRG = i;
        if (((!chargedOnly)||pfIsCharged(pfid)) && (std::abs(pfeta) < trackerLim) && (pfpt > PFPtMin) && (pfeta < maxEta_backward_tracker)) iPF_BRG = i;
    }

    // RG in tracker
    double maxEta_forward_tracker = (iPF_FRG >= 0) ? pfEta->at(iPF_FRG) : -999;
    double maxEta_backward_tracker = (iPF_BRG >= 0) ? pfEta->at(iPF_BRG) : -999;
    if ((iPF_FRG < 0) || (iPF_BRG < 0)) 
        std::cout << "Warning: No PF candidates found in tracker for entry " << ientry << std::endl;
    FRG = trackerLim - maxEta_forward_tracker;
    BRG = trackerLim + maxEta_backward_tracker;
}

bool tree::passFilter(Long64_t ientry, bool hltcond=true, bool zdccond=true, bool dijetcond=true, bool activitycond=true, bool rapgapcond=true) {
    // std::cout << "Filtering entry " << ientry << std::endl;
    GetEntry(ientry);
    
    // hlt
    if (hltcond) {
        if (isMC) {
            if (HLT_SingleJet8_NotMBHF2AND==0) return false;
        } else {
            if (HLT_SingleJet28_NotMBHF2AND==1) weight = 1.;
            else if (HLT_SingleJet24_NotMBHF2AND==1) weight = 1.;
            else if (HLT_SingleJet20_NotMBHF2AND==1) weight = 1.;
            else if (HLT_SingleJet16_NotMBHF2AND==1) weight = 1.; // EDITED FOR TEST
            else if (HLT_SingleJet8_NotMBHF2AND==1) weight = PS8; // EDITED FOR TEST
            else return false;
        }
        // if (HLT_ZDC1nOr) return false;
        // std::cout << "\tHLT passed" << std::endl;
        nEntriesPassHLT++;
    }
    
    // zdc cuts for 0n0n
    if (zdccond) {
        if (!isMC) {
            // if (!pass0n0n(sumPlus, sumMinus)) return false;
            // if (!pass0nXnInclusive(sumPlus, sumMinus)) return false;
            if (!pass0nXnOneSided(sumPlus, sumMinus)) return false;
            // if (!passXn0nOneSided(sumPlus, sumMinus)) return false;
            // if (!passXnXn(sumPlus, sumMinus)) return false;
        }
        nEntriesPassZDC++;
    }    
    
    // dijet selections
    if (dijetcond) {
        if (nref < 2) return false;
        if (jtpt[0] < 30) return false;
        if (jtpt[1] < 20) return false;
        nEntriesPassJetKin++;
        for (Int_t ijet=0; ijet<2; ijet++) {
            // jet kinematics
            if (std::abs(jteta[ijet]) > 1.) return false;
            // std::cout << "\tPassed dijet kinematics, nref=" << nref << std::endl;
            // jet id selections
            if (!passJetID(jteta[ijet], 
                jtPfCHM[ijet], jtPfNHM[ijet], jtPfCEM[ijet], jtPfNEM[ijet], jtPfMUM[ijet], 
                jtPfCHF[ijet], jtPfNHF[ijet], jtPfCEF[ijet], jtPfNEF[ijet], jtPfMUF[ijet])
            ) return false;
            // std::cout << "Passed jet ID" << std::endl;
            // jet veto map
            if (!passVetoMap(jteta[ijet], jtphi[ijet])) return false;
            
            // std::cout << "Passed jet veto map" << std::endl;
        }
        nEntriesPassJetID++;
        nEntriesPassJetVM++;
    }

    // additional activiy
    if (activitycond) {
        if (nref>2 
            // && passJetID(jteta[2], 
            //     jtPfCHM[2], jtPfNHM[2], jtPfCEM[2], jtPfNEM[2], jtPfMUM[2], 
            //     jtPfCHF[2], jtPfNHF[2], jtPfCEF[2], jtPfNEF[2], jtPfMUF[2])
            // && passVetoMap(jteta[2], jtphi[2])
            && jtpt[2] > 20) return false;
        // add veto for tracks in forward w pt>6
        // std::cout << "\tAdditional activity passed" << std::endl;
        nEntriesPassAddAct++;
    }

    // rapidity gap
    if (rapgapcond) {
        double lim = 3.;
        double ptmin = 0.2;
        calcRapGap(ientry, true, lim, ptmin);
        // HF + EC2 cuts
        if (FRG>BRG) {
            if (!passHFp) return false;
            // if (!passEC2p) return false;
        } else {
            if (!passHFm) return false;
            // if (!passEC2m) return false;
        }
        // if (!passHFp) return false;
        // if (!passHFm) return false;
        nEntriesPassHF++;

        // Tracker RG
        // if (FRG>BRG) {
        //     if (FRG<1.2) return false;
        // } else {
        //     if (BRG<1.2) return false;
        // }
        // nEntriesPassRG++;
    }

    nEntriesPassAll++;
    // std::cout << "\tAll selections passed for entry " << ientry << std::endl;
    return true;
}
bool tree::passFilterRef(Long64_t ientry, bool hltcond=true, bool zdccond=true, bool dijetcond=true, bool activitycond=true, bool rapgapcond=true) {
    // std::cout << "Filtering entry " << ientry << std::endl;
    GetEntry(ientry);
    
    // hlt
    if (hltcond) {
        if (isMC) {
            if (HLT_SingleJet8_NotMBHF2AND==0) return false;
        } else {
            std::cout << "Warning: You have given a DATA file to passFilterRef" << std::endl;
        }
        // if (HLT_ZDC1nOr) return false;
        // std::cout << "\tHLT passed" << std::endl;
        nEntriesPassHLT++;
    }
    
    // zdc cuts for 0n0n
    if (zdccond) {
        if (!isMC) {
            if (!pass0n0n(sumPlus, sumMinus)) return false;
        }
        nEntriesPassZDC++;
    }    
    
    // dijet selections
    if (dijetcond) {
        if (nref < 2) return false;
        if (refpt[0] < 30) return false;
        if (refpt[1] < 20) return false;
        nEntriesPassJetKin++;
        for (Int_t ijet=0; ijet<2; ijet++) {
            // jet kinematics
            if (std::abs(refeta[ijet]) > 2.5) return false;
            // std::cout << "\tPassed dijet kinematics, nref=" << nref << std::endl;
            // jet id selections
            // if (!passJetID(jteta[ijet], 
            //     jtPfCHM[ijet], jtPfNHM[ijet], jtPfCEM[ijet], jtPfNEM[ijet], jtPfMUM[ijet], 
            //     jtPfCHF[ijet], jtPfNHF[ijet], jtPfCEF[ijet], jtPfNEF[ijet], jtPfMUF[ijet])
            // ) return false;
            // std::cout << "Passed jet ID" << std::endl;
            // jet veto map
            // if (!passVetoMap(refeta[ijet], refphi[ijet])) return false;
            
            // std::cout << "Passed jet veto map" << std::endl;
        }
        nEntriesPassJetID++;
        nEntriesPassJetVM++;
    }

    // additional activiy
    if (activitycond) {
        if (nref>2 
            // && passJetID(jteta[2], 
            //     jtPfCHM[2], jtPfNHM[2], jtPfCEM[2], jtPfNEM[2], jtPfMUM[2], 
            //     jtPfCHF[2], jtPfNHF[2], jtPfCEF[2], jtPfNEF[2], jtPfMUF[2])
            // && passVetoMap(jteta[2], jtphi[2])
            && refpt[2] > 20) return false;
        // add veto for tracks in forward w pt>6
        // std::cout << "\tAdditional activity passed" << std::endl;
        nEntriesPassAddAct++;
    }

    // rapidity gap
    if (rapgapcond) {
        // TODO: Would need to do this on collection of gen particles (HiGenParticleAna/hi)
        // HF + EC2 cuts
        // if (FRG>BRG) {
        //     if (!passHFp) return false;
        //     if (!passEC2p) return false;
        // } else {
        //     if (!passHFm) return false;
        //     if (!passEC2m) return false;
        // }
        // nEntriesPassHF++;

        // Tracker RG
        // if (FRG>BRG) {
        //     if (FRG<1.2) return false;
        // } else {
        //     if (BRG<1.2) return false;
        // }
        // nEntriesPassRG++;
    }

    nEntriesPassAll++;
    // std::cout << "\tAll selections passed for entry " << ientry << std::endl;
    return true;
}

// function from Nick
void tree::loadVetoMap(const std::string VetoMapPath) {
    TFile *fvm = TFile::Open(VetoMapPath.c_str(),"read");
    if(!fvm){throw std::runtime_error("Error: Could not open Jet Veto Map file: " + VetoMapPath);}
    TH2D *hvetomap = (TH2D*)fvm->Get("jetvetomap_all");
    if(!hvetomap){throw std::runtime_error("Error: Veto Map histogram 'jetvetomap_all' not in file");}
    hvetomap_ = (TH2D*)hvetomap->Clone("hvetomap_");
    hvetomap_->SetDirectory(0);
    fvm->Close();

    // showing that the veto map was obtained
    std::cout << "\033[1;32mLoaded Jet Veto Map from: " << VetoMapPath << "\033[0m" << std::endl;
}

void tree::loadJEC(const std::string JECPath) {
    std::vector<std::string> jec_files = {JECPath};
    JEC = new JetCorrector(jec_files);
    std::cout << "\033[1;32mLoaded Jet Energy Corrections from: " << JECPath << "\033[0m" << std::endl;
}

bool tree::pass0n0n(Float_t sumPlus, Float_t sumMinus) {
    return (sumPlus < 1100 && sumMinus < 1000);
}

bool tree::pass0nXnOneSided(Float_t sumPlus, Float_t sumMinus) {
    return (sumPlus > 1100 && sumMinus < 1000);
}

bool tree::passXn0nOneSided(Float_t sumPlus, Float_t sumMinus) {
    return (sumPlus < 1100 && sumMinus > 1000);
}

bool tree::pass0nXnInclusive(Float_t sumPlus, Float_t sumMinus) {
    return (pass0nXnOneSided(sumPlus, sumMinus) || passXn0nOneSided(sumPlus, sumMinus));
}

bool tree::passXnXn(Float_t sumPlus, Float_t sumMinus) {
    return (sumPlus > 1100 && sumMinus > 1000);
}

bool tree::passVetoMap(Float_t eta, Float_t phi) {
    if (!hvetomap_) throw std::runtime_error("Error: Veto map not loaded!");
    Double_t vetomapval = hvetomap_->GetBinContent(hvetomap_->FindBin(eta, phi));
    return (vetomapval == 0);
}

bool tree::pfIsCharged(Int_t id) {
    if ((id > 0) && (id < 4)) return true;
    return false;
}

bool tree::passJetID(Float_t eta, Int_t CHM, Int_t NHM, Int_t CEM, Int_t NEM, Int_t MUM, Float_t CHF, Float_t NHF, Float_t CEF, Float_t NEF, Float_t MUF) {
    // info: https://cms-talk.web.cern.ch/t/updated-jet-selection-criterion-for-jet-veto-map/130527
    // info: https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID13p6TeV, 2023 BCD, AK4CHS
    Int_t mult_c = CHM + NHM + MUM;
    Int_t mult_n = CEM + NEM;
    Int_t mult = mult_c + mult_n;
    if (std::abs(eta) <= 2.6) {
        if ((mult<2) || (mult_c<1)) return false;
        if ((NHF>0.99) || (CHF<0.01) || (CEF>0.8) || (NEF>0.9) || (MUF>0.8)) return false;
    } else if (std::abs(eta) <= 2.7) {
        if (mult_c<1) return false;
        if ((NHF>0.9) || (NEF>0.99) || (CEF>0.8) || (MUF>0.8)) return false;
    } else if (std::abs(eta) <= 3.0) {
        if (mult_n<2) return false;
        if ((NHF>0.99) || (NEF>0.99)) return false;
    } else if (std::abs(eta) <= 5.0) {
        if (mult_n<11) return false;
        if (NEF>0.4) return false;
    }
    return true;
}

void tree::EntryCount() {
    std::cout << "Total entries: " << nEntries << std::endl;
    std::cout << "Entries passing HLT: " << nEntriesPassHLT << std::endl;
    std::cout << "Entries passing ZDC: " << nEntriesPassZDC << std::endl;
    std::cout << "Entries passing Jet Kinematics: " << nEntriesPassJetKin << std::endl;
    std::cout << "Entries passing Jet ID: " << nEntriesPassJetID << std::endl;
    std::cout << "Entries passing Jet Veto Map: " << nEntriesPassJetVM << std::endl;
    std::cout << "Entries passing Additional Activity: " << nEntriesPassAddAct << std::endl;
    std::cout << "Entries passing HF: " << nEntriesPassHF << std::endl;
    std::cout << "Entries passing RG: " << nEntriesPassRG << std::endl;
    std::cout << "Entries passing all: " << nEntriesPassAll << std::endl;
}