#include <TChain.h>

#include <vector>

class tree {
    public:
        TChain *ch;

        tree(TString="ak4PFJetAnalyzer/t");
        ~tree();

        std::vector<TString> fileNames;
        std::vector<TString> friendNames;

        void Add(TString);
        void AddFriend(TString);
        void AddHLT();
        void AddEvtInfo();
        void Init();
        Long64_t GetEntries();
        Long64_t GetEntry(Long64_t ientry);
        bool passFilter(Long64_t ientry);

        const static Int_t MAXJETS = 100;

        // jet analyzer variables
        Int_t nref;
        Float_t jtpt[MAXJETS];
        Float_t jteta[MAXJETS];
        Float_t jtphi[MAXJETS];
        Float_t jtm[MAXJETS];

        Float_t refpt[MAXJETS];
        Float_t refeta[MAXJETS];
        Float_t refphi[MAXJETS];
        Float_t refm[MAXJETS];
        
        // event info variables
        Float_t weight;

        // hlt variables
        Int_t HLT_SingleJet8_ZDC1nXOR;
};

// Constructor and destructor
tree::tree(TString treeName) {
    ch = new TChain(treeName);
}    
tree::~tree() {
    if (!ch) return;
    delete ch;   
}

// Class functions
void tree::Add(TString fileName) {
    fileNames.push_back(fileName);
}
void tree::AddFriend(TString treeName) {
    friendNames.push_back(treeName);
}
void tree::AddHLT() {
    friendNames.push_back("hltanalysis/hltTree");
}
void tree::AddEvtInfo() {
    friendNames.push_back("hiEvtAnalyzer/HiTree");
}
void tree::Init() {
    for (const auto& fileName : fileNames) {
        ch->Add(fileName);
    }
    for (const auto& friendName : friendNames) {
        ch->AddFriend(friendName);
    }

    // jet analyzer branches
    ch->SetBranchAddress("nref", &nref);
    ch->SetBranchAddress("jtpt", jtpt);
    ch->SetBranchAddress("jteta", jteta);
    ch->SetBranchAddress("jtphi", jtphi);
    ch->SetBranchAddress("jtm", jtm);

    ch->SetBranchAddress("refpt", refpt);
    ch->SetBranchAddress("refeta", refeta);
    ch->SetBranchAddress("refphi", refphi);
    ch->SetBranchAddress("refm", refm);

    // add friend branches
    TList *friends = ch->GetListOfFriends();
    if (friends) {
        TIter next(friends);
        TFriendElement* fe;
        while ((fe = (TFriendElement*)next())) {
            if (TString(fe->GetName()).Contains("hiEvtAnalyzer/HiTree")) {
                ch->SetBranchAddress("weight", &weight);
            }
            else if (TString(fe->GetName()).Contains("hltanalysis/hltTree")) {
                ch->SetBranchAddress("HLT_HIUPC_SingleJet8_ZDC1nXOR_MaxPixelCluster50000_v2", &HLT_SingleJet8_ZDC1nXOR);
            }
            else {
                std::cout << "*** Warning: Unrecognized friend tree " << fe->GetName() << std::endl;
            }
        }
    } else {
        std::cout << "*** Warning: No friend trees found! If you add friends later, remember to reinitialize the tree." << std::endl;
    }
}
Long64_t tree::GetEntries() {
    return ch->GetEntries();
}
Long64_t tree::GetEntry(Long64_t ientry) {
    return ch->GetEntry(ientry);
}
bool tree::passFilter(Long64_t ientry) {
    GetEntry(ientry);
    
    // hlt
    if (!HLT_SingleJet8_ZDC1nXOR) return false;

    // zdc cuts

    // rapidity gap
    
    // jet
    if (nref < 2) return false;
    if (std::abs(jteta[0]) > 2.5) return false;
    if (std::abs(jteta[1]) > 2.5) return false;
    if (jtpt[0] < 30) return false;
    if (jtpt[1] < 20) return false;

    return true;
}