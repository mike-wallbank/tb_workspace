{

  TFile* trigTimeFile = new TFile("/nova/ana/users/wallbank/TestBeam/BeamTrigEventInfo/BeamTrigEventInfo_Period3.root", "READ");
  TTree* trigTimeTree = (TTree*)trigTimeFile->Get("beamtrigeventinfo/BeamTriggers");

  //TFile* deadTimeFile = new TFile("/nova/ana/users/wallbank/TestBeam/DeadTime/Period3/TBDeadTime_Period3.root", "READ");
  TFile* deadTimeFile = new TFile("/pnfs/nova/scratch/users/wallbank/testbeam/data/DeadTime/Period3/50us/TBDeadTime_r100985-r101483.root", "READ");
  TTree* deadTimeTree = (TTree*)deadTimeFile->Get("tbdeadtime/DeadTimeInfo");

  int trigTimeRun = -1, trigTimeSubrun = -1, trigTimeEvent = -1;
  trigTimeTree->SetBranchAddress("run",    &trigTimeRun);
  trigTimeTree->SetBranchAddress("subrun", &trigTimeSubrun);
  trigTimeTree->SetBranchAddress("event",  &trigTimeEvent);
  // int deadTimeRun = -1, deadTimeSubrun = -1, deadTimeEvent = -1;
  // deadTimeTree->SetBranchAddress("run",    &deadTimeRun);
  // deadTimeTree->SetBranchAddress("subrun", &deadTimeSubrun);
  // deadTimeTree->SetBranchAddress("event",  &deadTimeEvent);

  for (int run = 100985; run <= 101483; ++run) {
  //for (int run = 101200; run <= 101483; ++run) {

    std::cout << "run " << run << std::endl;

    int runevents_trigtime = trigTimeTree->GetEntries(Form("run==%d", run));
    int runevents_deadtime = deadTimeTree->GetEntries(Form("run==%d", run));

    if (runevents_trigtime != runevents_deadtime) {

      std::cout << "Run " << run << " missing events" << std::endl;

      for (int subrun = 0; subrun < 64; ++subrun) {

    	int subrunevents_trigtime = trigTimeTree->GetEntries(Form("run==%d&&subrun==%d", run, subrun));
    	int subrunevents_deadtime = deadTimeTree->GetEntries(Form("run==%d&&subrun==%d", run, subrun));

    	if (subrunevents_trigtime != subrunevents_deadtime) {
    	  std::cout << "Run " << run << ", subrun " << subrun << " missing events" << std::endl;
    	  std::cout << subrunevents_trigtime << " triggers, " << subrunevents_deadtime << " deadtime" << std::endl;
    	}
      }

    }

  }

  // int nmissed = 0;
  // for (int event = 0; event < trigTimeTree->GetEntriesFast(); ++event) {
  //   std::cout << "event " << event << std::endl;

  //   if (event % 1000 == 0)
  //     std::cout << "Processing event " << event << " (" << event*100./trigTimeTree->GetEntriesFast() << "%)" << std::endl;

  //   trigTimeTree->GetEntry(event);
  //   int deadTreeEntries = trigTimeTree->GetEntries(Form("run==%d&&subrun==%d&&event==%d", trigTimeRun, trigTimeSubrun, trigTimeEvent));

  //   if (deadTreeEntries == 0) {
  //     ++nmissed;
  //     std::cout << "Run " << trigTimeRun << ", subrun " << trigTimeSubrun << ", event " << trigTimeEvent << " missed" << std::endl;
  //   }

  // }

  // std::cout << "Total missed: " << nmissed << std::endl;

}
