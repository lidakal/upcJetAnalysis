void event_match()
{
    TFile *fin = new TFile("~/SE_UserHome/HIForward0/crab_HiForward0_HIRun2023A-PromptReco-v2_ZDCjson_v7/260216_070726/0000/merged_HiForestMiniAOD.root");
    TTree *t = (TTree*) fin->Get("ak4PFJetAnalyzer/t");
    TTree *HltTree = (TTree*) fin->Get("hltanalysis/HltTree");

    int i=0;
    for (Long64_t ient = 0; ient < t->GetEntries(); ient++) {
        // if (ient > 1000) break;
        if (ient % 100000 == 0)
            std::cout << "Processing entry " << ient << " / " << t->GetEntries() << std::endl;

        t->GetEntry(ient);
        HltTree->GetEntry(ient);

        if (t->GetLeaf("evt")->GetValue() != HltTree->GetLeaf("Event")->GetValue() ||
            t->GetLeaf("run")->GetValue() != HltTree->GetLeaf("Run")->GetValue() ||
            t->GetLeaf("lumi")->GetValue() != HltTree->GetLeaf("LumiBlock")->GetValue()) {
            std::cout << "Entry " << ient << "\n" 
                    << "\tevt: " << t->GetLeaf("evt")->GetValue() << " " << HltTree->GetLeaf("Event")->GetValue() << "\n"
                    << "\trun: " << t->GetLeaf("run")->GetValue() << " " << HltTree->GetLeaf("Run")->GetValue() << "\n"
                    << "\tlumi: " << t->GetLeaf("lumi")->GetValue() << " " << HltTree->GetLeaf("LumiBlock")->GetValue()
                    << std::endl;
            i++;
        }
        if (i > 10) {
            std::cout << "More than 10 mismatches, stopping." << std::endl;
            break;
        }
    }
}