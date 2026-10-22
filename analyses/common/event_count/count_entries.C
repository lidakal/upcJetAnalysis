// Usage: root -l -b -q count_entries.C
// Opens path/to/dir/000{0..9}/merged_JRA.root, reads tree "ak4pf/t"
// and prints the number of entries in each file plus the total.

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include <iostream>

void count_entries()
{
  const TString basePath = "/u/user/lidakal/SE_UserHome/GNucleusToD0-PhotonBeamB_Pthat8_UPC_5p36TeV_pythia8_evtgen/crab_GNucleusToD0-PhotonBeamB_Pthat8_5p36TeV-JRA/261019_093226/"; 
  const char* treeName   = "ak4pf/t";

  Long64_t total = 0;

  for (int i = 0; i <= 9; ++i) {
    TString fname = Form("%s/000%d/merged_JRA.root", basePath.Data(), i);

    TFile* f = TFile::Open(fname, "READ");
    if (!f || f->IsZombie()) {
      std::cerr << "Cannot open file: " << fname << std::endl;
      delete f;
      continue;
    }

    TTree* t = dynamic_cast<TTree*>(f->Get(treeName));
    if (!t) {
      std::cerr << "Tree " << treeName << " not found in " << fname << std::endl;
      f->Close();
      delete f;
      continue;
    }

    Long64_t n = t->GetEntries();
    std::cout << fname << " : " << n << " entries" << std::endl;
    total += n;

    f->Close();
    delete f;
  }

  std::cout << "Total entries: " << total << std::endl;
}