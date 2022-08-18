{
  TFile* inFile = TFile::Open("TBDeadTime.root", "READ");
  TTree* inTree = (TTree*)inFile->Get("tbdeadtime/DeadTimeInfo");

  int run, subrun, event;
  bool eventStat;
  bool febStatBit[3][64], febStatHits[3][64];
  bool dcmStat[3];

  inTree->SetBranchAddress("run", &run);
  inTree->SetBranchAddress("subrun", &subrun);
  inTree->SetBranchAddress("event", &event);
  inTree->SetBranchAddress("evtStat", &eventStat);
  inTree->SetBranchAddress("febStatBit", febStatBit);
  inTree->SetBranchAddress("febStatHits", febStatHits);
  inTree->SetBranchAddress("dcmStat", dcmStat);

  for (int eventIt = 0; eventIt < inTree->GetEntriesFast(); ++eventIt) {

    inTree->GetEntry(eventIt);

    std::cout << "Run " << run << ", subrun " << subrun << ", event " << event << " status " << eventStat << std::endl;

    for (unsigned int dcm = 1; dcm < 4; ++dcm) {
      std::cout << "DCM " << dcm << " status " << dcmStat[dcm-1] << std::endl;

      for (unsigned int feb = 0; feb < 64; ++feb) {
        if ((dcm < 3 and (feb == 8 or feb == 24 or feb == 40 or feb == 56)) or
            (dcm == 2 and (feb == 47 or feb == 63)) or
            (dcm == 3 and feb > 7))
          continue;                
	std::cout << "DCM " << dcm << ", FEB " << feb << " status " << febStatBit[dcm-1][feb] << " (bit), " << febStatHits[dcm-1][feb] << " (hits)" << std::endl;
      }
    }

  }

}
