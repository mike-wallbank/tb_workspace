// Look at the spill analysis data and count up spills and particles

void countSpillParticles(std::string inFileName) {

  // struct tm start_tm, end_tm;
  // time_t startTime, endTime;
  // if (strptime(Form("%d-%d-%d_%d:%d:%d", year, month, day, hour, min, sec),
  // 	       "%Y-%m-%d_%H:%M:%S", &start_tm) != NULL)
  //   startTime = mktime(&start_tm);
  // if (strptime(Form("%d-%d-%d_%d:%d:%d", year, month, day, hour, min, sec),
  // 	       "%Y-%m-%d_%H:%M:%S", &end_tm) != NULL)
  //   endTime = mktime(&end_tm);
  int startRun = 101317;
  int endRun = 101340;

  std::cout << "Runs " << startRun << " - " << endRun << std::endl;

  TFile* inFile = new TFile(inFileName.c_str(), "READ");
  TTree* inTree = (TTree*)inFile->Get("spillana/spills");

  TCut runsCut(Form("Run>=%d&&Run<=%d&&MC6IC>=5e8", startRun, endRun));
  TCut goodSpillsCut("DAQGood==1");
  std::cout << "All spills " << inTree->GetEntries(runsCut) << std::endl;
  std::cout << "Good spills " << inTree->GetEntries(runsCut&&goodSpillsCut) << std::endl;

  inTree->Draw(">>spilllist", runsCut&&goodSpillsCut, "entrylist");
  TEntryList* goodSpills = (TEntryList*)gDirectory->Get("spilllist");

  double fMC6IC = 0;
  double fTrigDetOnBit = 0;
  double fTrigDetOnHits = 0;
  double fTrigSel = 0;
  double fTrigSelDetOnBit = 0;
  double fTrigSelDetOnHits = 0;
  double fProtonSel = 0;
  double fProtonSelDetOnBit = 0;
  double fProtonSelDetOnHits = 0;
  double fElectronSel = 0;
  double fElectronSelDetOnBit = 0;
  double fElectronSelDetOnHits = 0;
  double fKaonSel = 0;
  double fKaonSelDetOnBit = 0;
  double fKaonSelDetOnHits = 0;
  double fMuPiOtherSel = 0;
  double fMuPiOtherSelDetOnBit = 0;
  double fMuPiOtherSelDetOnHits = 0;
  inTree->SetBranchAddress("MC6IC",                 &fMC6IC);
  inTree->SetBranchAddress("TrigDetOnBit",          &fTrigDetOnBit);
  inTree->SetBranchAddress("TrigDetOnHits",         &fTrigDetOnHits);
  inTree->SetBranchAddress("TrigSel",               &fTrigSel);
  inTree->SetBranchAddress("TrigSelDetOnBit",       &fTrigSelDetOnBit);
  inTree->SetBranchAddress("TrigSelDetOnHits",      &fTrigSelDetOnHits);
  inTree->SetBranchAddress("ProtonSel",             &fProtonSel);
  inTree->SetBranchAddress("ProtonSelDetOnBit",     &fProtonSelDetOnBit);
  inTree->SetBranchAddress("ProtonSelDetOnHits",    &fProtonSelDetOnHits);
  inTree->SetBranchAddress("ElectronSel",           &fElectronSel);
  inTree->SetBranchAddress("ElectronSelDetOnBit",   &fElectronSelDetOnBit);
  inTree->SetBranchAddress("ElectronSelDetOnHits",  &fElectronSelDetOnHits);
  inTree->SetBranchAddress("KaonSel",               &fKaonSel);
  inTree->SetBranchAddress("KaonSelDetOnBit",       &fKaonSelDetOnBit);
  inTree->SetBranchAddress("KaonSelDetOnHits",      &fKaonSelDetOnHits);
  inTree->SetBranchAddress("MuPiOtherSel",          &fMuPiOtherSel);
  inTree->SetBranchAddress("MuPiOtherSelDetOnBit",  &fMuPiOtherSelDetOnBit);
  inTree->SetBranchAddress("MuPiOtherSelDetOnHits", &fMuPiOtherSelDetOnHits);

  double totMC6IC = 0;
  double totTrigDetOnBit = 0;
  double totTrigDetOnHits = 0;
  double totTrigSel = 0;
  double totTrigSelDetOnBit = 0;
  double totTrigSelDetOnHits = 0;
  double totProtonSel = 0;
  double totProtonSelDetOnBit = 0;
  double totProtonSelDetOnHits = 0;
  double totElectronSel = 0;
  double totElectronSelDetOnBit = 0;
  double totElectronSelDetOnHits = 0;
  double totKaonSel = 0;
  double totKaonSelDetOnBit = 0;
  double totKaonSelDetOnHits = 0;
  double totMuPiOtherSel = 0;
  double totMuPiOtherSelDetOnBit = 0;
  double totMuPiOtherSelDetOnHits = 0;

  int nGoodSpills = goodSpills->GetN();
  for (int spill = 0; spill < nGoodSpills; ++spill) {

    inTree->GetEntry(goodSpills->GetEntry(spill));

    totMC6IC += fMC6IC;
    totTrigDetOnBit += fTrigDetOnBit;
    totTrigDetOnHits += fTrigDetOnHits;
    totTrigSel += fTrigSel;
    totTrigSelDetOnBit += fTrigSelDetOnBit;
    totTrigSelDetOnHits += fTrigSelDetOnHits;
    totProtonSel += fProtonSel;
    totProtonSelDetOnBit += fProtonSelDetOnBit;
    totProtonSelDetOnHits += fProtonSelDetOnHits;
    totElectronSel += fElectronSel;
    totElectronSelDetOnBit += fElectronSelDetOnBit;
    totElectronSelDetOnHits += fElectronSelDetOnHits;
    totKaonSel += fKaonSel;
    totKaonSelDetOnBit += fKaonSelDetOnBit;
    totKaonSelDetOnHits += fKaonSelDetOnHits;
    totMuPiOtherSel += fMuPiOtherSel;
    totMuPiOtherSelDetOnBit += fMuPiOtherSelDetOnBit;
    totMuPiOtherSelDetOnHits += fMuPiOtherSelDetOnHits;

  }

  double avMC6IC = totMC6IC/(double)nGoodSpills;
  std::cout << "Total MC6IC " << totMC6IC << ", average " << avMC6IC << std::endl
	    << "Particles selected - " << totTrigSel << " (" << totTrigSelDetOnBit << "/" << totTrigSelDetOnHits << "):" << std::endl
	    << "    per spill " << totTrigSel/(double)nGoodSpills << " (" << totTrigSelDetOnBit/(double)nGoodSpills << "/" << totTrigSelDetOnHits/(double)nGoodSpills << ")" << std::endl
	    << "    per 1e9ppp " << totTrigSel/(totMC6IC/1.e9) << " (" << totTrigSelDetOnBit/(totMC6IC/1.e9) << "/" << totTrigSelDetOnHits/(totMC6IC/1.e9) << ")" << std::endl
	    << "    per hour " << totTrigSel*60./(double)nGoodSpills << " (" << totTrigSelDetOnBit*60./(double)nGoodSpills << "/" << totTrigSelDetOnHits*60./(double)nGoodSpills << ")" << std::endl
	    << "  Protons - " << totProtonSel << " (" << totProtonSelDetOnBit << "/" << totProtonSelDetOnHits << ")" << std::endl
	    << "    per spill " << totProtonSel/(double)nGoodSpills << " (" << totProtonSelDetOnBit/(double)nGoodSpills << "/" << totProtonSelDetOnHits/(double)nGoodSpills << ")" << std::endl
	    << "    per 1e9ppp " << totProtonSel/(totMC6IC/1.e9) << " (" << totProtonSelDetOnBit/(totMC6IC/1.e9) << "/" << totProtonSelDetOnHits/(totMC6IC/1.e9) << ")" << std::endl
	    << "    per hour " << totProtonSel*60./(double)nGoodSpills << " (" << totProtonSelDetOnBit*60./(double)nGoodSpills << "/" << totProtonSelDetOnHits*60./(double)nGoodSpills << ")" << std::endl
	    << "  Electrons - " << totElectronSel << " (" << totElectronSelDetOnBit << "/" << totElectronSelDetOnHits << ")" << std::endl
	    << "    per spill " << totElectronSel/(double)nGoodSpills << " (" << totElectronSelDetOnBit/(double)nGoodSpills << "/" << totElectronSelDetOnHits/(double)nGoodSpills << ")" << std::endl
	    << "    per 1e9ppp " << totElectronSel/(totMC6IC/1.e9) << " (" << totElectronSelDetOnBit/(totMC6IC/1.e9) << "/" << totElectronSelDetOnHits/(totMC6IC/1.e9) << ")" << std::endl
	    << "    per hour " << totElectronSel*60./(double)nGoodSpills << " (" << totElectronSelDetOnBit*60./(double)nGoodSpills << "/" << totElectronSelDetOnHits*60./(double)nGoodSpills << ")" << std::endl
	    << "  Kaons - " << totKaonSel << " (" << totKaonSelDetOnBit << "/" << totKaonSelDetOnHits << ")" << std::endl
	    << "    per spill " << totKaonSel/(double)nGoodSpills << " (" << totKaonSelDetOnBit/(double)nGoodSpills << "/" << totKaonSelDetOnHits/(double)nGoodSpills << ")" << std::endl
	    << "    per 1e9ppp " << totKaonSel/(totMC6IC/1.e9) << " (" << totKaonSelDetOnBit/(totMC6IC/1.e9) << "/" << totKaonSelDetOnHits/(totMC6IC/1.e9) << ")" << std::endl
	    << "    per hour " << totKaonSel*60./(double)nGoodSpills << " (" << totKaonSelDetOnBit*60./(double)nGoodSpills << "/" << totKaonSelDetOnHits*60./(double)nGoodSpills << ")" << std::endl
	    << "  MuPiOthers - " << totMuPiOtherSel << " (" << totMuPiOtherSelDetOnBit << "/" << totMuPiOtherSelDetOnHits << ")" << std::endl
	    << "    per spill " << totMuPiOtherSel/(double)nGoodSpills << " (" << totMuPiOtherSelDetOnBit/(double)nGoodSpills << "/" << totMuPiOtherSelDetOnHits/(double)nGoodSpills << ")" << std::endl
	    << "    per 1e9ppp " << totMuPiOtherSel/(totMC6IC/1.e9) << " (" << totMuPiOtherSelDetOnBit/(totMC6IC/1.e9) << "/" << totMuPiOtherSelDetOnHits/(totMC6IC/1.e9) << ")" << std::endl
	    << "    per hour " << totMuPiOtherSel*60./(double)nGoodSpills << " (" << totMuPiOtherSelDetOnBit*60./(double)nGoodSpills << "/" << totMuPiOtherSelDetOnHits*60./(double)nGoodSpills << ")" << std::endl;

}
