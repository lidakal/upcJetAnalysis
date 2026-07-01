#include <TChain.h>

#include <vector>

class tree {
    public:
        TChain *t; 
        TChain *hlt; 
        TChain *hi; 
        TChain *zdc;
        TChain *pf;

        tree(TString="ak0PFJetAnalyzer/t");
        ~tree();

        std::vector<TString> fileNames;

        void Add(TString);
        void Init();
        Long64_t GetEntries();
        void GetEntry(Long64_t);
        bool passFilter(Long64_t);
        void loadVetoMap(const std::string);
        bool passVetoMap(Float_t, Float_t);
        bool passJetID(Float_t, Float_t, Float_t, Float_t);
        bool pass0n0n(Float_t, Float_t);

        bool isMC = false;
        TH2D* hvetomap_;
        TString JECPath = "";
        const static Int_t MAXJETS = 100;

        // jet analyzer variables
        Int_t nref = 0;
        Float_t jtpt[MAXJETS];
        Float_t jteta[MAXJETS];
        Float_t jtphi[MAXJETS];
        Float_t jtm[MAXJETS];
        Float_t jtPfCEF[MAXJETS];
        Float_t jtPfNEF[MAXJETS];
        Float_t jtPfMUF[MAXJETS];

        Float_t refpt[MAXJETS];
        Float_t refeta[MAXJETS];
        Float_t refphi[MAXJETS];
        Float_t refm[MAXJETS];
        
        // event info variables
        Float_t weight = 0.;

        // hlt variables
        Int_t HLT_SingleJet8_NotMBHF2AND = -1;
        Int_t HLT_SingleJet12_NotMBHF2AND = -1;
        Int_t HLT_SingleJet16_NotMBHF2AND = -1;
        Int_t HLT_SingleJet20_NotMBHF2AND = -1;
        Int_t HLT_ZDC1nOr = -1;

        // zdc variables
        Float_t sumPlus = 0.;
        Float_t sumMinus = 0.;

        // pf variables
        Int_t nPF = 0;
        std::vector<float> *pfPt = nullptr;
        std::vector<float> *pfEta = nullptr;
        std::vector<float> *pfPhi = nullptr;
        std::vector<float> *pfE = nullptr;
};

// Constructor and destructor
tree::tree(TString treeName) {
    // jet tree can change name based on R
    t = new TChain(treeName);
    hlt = new TChain("hltanalysis/HltTree");
    hi = new TChain("hiEvtAnalyzer/HiTree");
    zdc = new TChain("zdcanalyzer/zdcrechit");
    pf = new TChain("particleFlowAnalyser/pftree");

    // loadVetoMap("/u/user/lidakal/UPC2023/upcJetAnalysis/analyses/common/vetomaps/Summer23BPixPrompt23_RunD_v1.root");
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
    if (!fileNames[0].Contains("HIForward")) isMC = true;

    for (const auto& fileName : fileNames) {
        t->Add(fileName);
        hlt->Add(fileName);
        hi->Add(fileName);
        zdc->Add(fileName);
        pf->Add(fileName);
    }

    // force TChain to load the files
    auto nentries = t->GetEntries(); 
    hlt->GetEntries();
    hi->GetEntries();
    zdc->GetEntries();
    pf->GetEntries();
    std::cout << "Added " << nentries << " entries from " << fileNames.size() << " files." << std::endl;

    // jet analyzer branches
    t->SetBranchAddress("nref", &nref);
    t->SetBranchAddress("jtpt", jtpt);
    t->SetBranchAddress("jteta", jteta);
    t->SetBranchAddress("jtphi", jtphi);
    t->SetBranchAddress("jtm", jtm);
    t->SetBranchAddress("jtPfCEF", jtPfCEF);
    t->SetBranchAddress("jtPfNEF", jtPfNEF);
    t->SetBranchAddress("jtPfMUF", jtPfMUF);

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
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet8_NotMBHF2AND_MaxPixelCluster50000_v2", &HLT_SingleJet8_NotMBHF2AND);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet12_NotMBHF2AND_MaxPixelCluster50000_v2", &HLT_SingleJet12_NotMBHF2AND);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet16_NotMBHF2AND_MaxPixelCluster50000_v2", &HLT_SingleJet16_NotMBHF2AND);
    hlt->SetBranchAddress("HLT_HIUPC_SingleJet20_NotMBHF2AND_MaxPixelCluster50000_v2", &HLT_SingleJet20_NotMBHF2AND);
    hlt->SetBranchAddress("HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v8", &HLT_ZDC1nOr);

    // zdc branches
    zdc->SetBranchAddress("sumPlus", &sumPlus);
    zdc->SetBranchAddress("sumMinus", &sumMinus);

    // pf branches
    pf->SetBranchAddress("nPF", &nPF);
    pf->SetBranchAddress("pfPt", &pfPt);
    pf->SetBranchAddress("pfEta", &pfEta);
    pf->SetBranchAddress("pfPhi", &pfPhi);
    pf->SetBranchAddress("pfE", &pfE);
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
}
bool tree::passFilter(Long64_t ientry) {
    // std::cout << "Filtering entry " << ientry << std::endl;
    GetEntry(ientry);
    
    // hlt
    if (!HLT_SingleJet20_NotMBHF2AND) return false;
    // if (HLT_ZDC1nOr) return false;
    // std::cout << "\tHLT passed" << std::endl;

    // zdc cuts for 0n0n
    if (!isMC)
        if (!pass0n0n(sumPlus, sumMinus)) return false;

    // rapidity gap
    TLorentzVector jet1, jet2;
    jet1.SetPtEtaPhiM(jtpt[0], jteta[0], jtphi[0], jtm[0]);
    jet2.SetPtEtaPhiM(jtpt[1], jteta[1], jtphi[1], jtm[1]);
    auto dijet = jet1 + jet2;
    double dijet_eta = dijet.Eta();

    double maxE_forward = 0;
    double maxE_backward = 0;
    for (int i=0; i<nPF; i++) {        
        // check for same hemisphere as dijet
        bool is_forward = (pfEta->at(i) * dijet_eta > 0);

        if (is_forward) {
            if (std::abs(pfEta->at(i)) > 3)
                if (pfE->at(i) > maxE_forward) maxE_forward = pfE->at(i);
        } else {
            if (std::abs(pfEta->at(i)) > 3)
                if (pfE->at(i) > maxE_backward) maxE_backward = pfE->at(i);
        }
    }
    if (maxE_backward > 10) return false;
    // add DetaB > 1.2
    // add DetaB > DetaF
    
    // dijet selections
    if (nref < 2) return false;
    if (jtpt[0] < 30) return false;
    if (jtpt[1] < 20) return false;
    for (Int_t ijet=0; ijet<2; ijet++) {
        // jet kinematics
        if (std::abs(jteta[ijet]) > 2.5) return false;

        // jet id selections
        // if (!passJetID(jteta[ijet], jtPfCEF[ijet], jtPfNEF[ijet], jtPfMUF[ijet])) return false;
        // jet veto map
        // if (!passVetoMap(jteta[ijet], jtphi[ijet])) return false;
    }

    // additional activiy
    if (nref>2 && jtpt[2] > 20) return false;
    // add veto for tracks in forward w pt>6
    // add Deta(jt,trk) < 1 for either jet and track defining DetaB
    // std::cout << "\tAdditional activity passed" << std::endl;

    // maybe QT < PT (in the future)

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

bool tree::pass0n0n(Float_t sumPlus, Float_t sumMinus) {
    return (sumPlus < 1100 && sumMinus < 1000);
}

bool tree::passVetoMap(Float_t eta, Float_t phi) {
    if (!hvetomap_) throw std::runtime_error("Error: Veto map not loaded!");
    Double_t vetomapval = hvetomap_->GetBinContent(hvetomap_->FindBin(eta, phi));
    return (vetomapval == 0);
}

// limits from Nick
bool tree::passJetID(Float_t eta, Float_t CEF, Float_t NEF, Float_t MUF) {
    // info: https://cms-talk.web.cern.ch/t/updated-jet-selection-criterion-for-jet-veto-map/130527
    // info: https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID13p6TeV#nanoAOD_Flags
    if (std::abs(eta) <= 2.6) {
        if ((NEF>0.9) || (MUF>0.8) || (CEF>0.8)) return false;
    } else if (std::abs(eta) <= 2.7) {
        if ((NEF>0.99) || (MUF>0.8) || (CEF>0.8)) return false;
    } else if (std::abs(eta) <= 3.0) {
        if (NEF>0.99) return false;
    } else if (std::abs(eta) <= 5.2) {
        if (NEF>0.9) return false;
    }
    return true;
}