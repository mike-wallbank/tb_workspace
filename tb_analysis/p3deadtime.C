#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TEntryList.h"
#include "TH1I.h"
#include "TFile.h"

#include <iostream>
#include <map>

struct tbevent {
  int Run;
  int SubRun;
  int Event;
  tbevent(int r, int s, int e) { Run = r; SubRun = s; Event = e; }
  bool operator==(const tbevent& e) const {
    return Run == e.Run and SubRun == e.SubRun and Event == e.Event;
  }
  bool operator<(const tbevent& e) const {
    return Run < e.Run or (Run == e.Run and SubRun < e.SubRun) or (Run == e.Run and SubRun == e.SubRun and Event < e.Event);
  }
};

void p3deadtime() {

  TFile* p3File
    = TFile::Open("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period3/R21-07-27-testbeam-production.a/TBRecoAna_r100985-r101483.root",
                  "READ");
  TTree* p3Tree = (TTree*)p3File->Get("tbrecoana/evts");

  TFile* p3DeadTime = TFile::Open("/nova/ana/users/wallbank/TestBeam/DeadTime/Period3/50us/TBDeadTime_r100985-r101483.root", "READ");
  TTree* p3DeadTimeTree = (TTree*)p3DeadTime->Get("tbdeadtime/DeadTimeInfo");

  // Cuts
  TCut wc("wcmom>=0");
  TCut magcurr("mc7mag>900&&mc7mag<1100");
  TCut magdist("abs(wcMagDist)<8");
  TCut protontof("toftime>39&&toftime<50");
  TCut ckov("ckovadc<0");
  TCut centralVtx("abs(winTrkStrtX)<20&&winTrkStrtY>-25&&winTrkStrtY<15&&winTrkStrtZ<18");
  TCut hittime("winTrkMinTime>45000&&winTrkMinTime<55000");
  TCut nhit("winTrkNhit>5");

  // Cumulative
  TCut cuts[9];
  cuts[0] = TCut("No cut", "");
  cuts[1] = TCut("WC", wc);
  cuts[2] = TCut("+MagCurr", cuts[1]&&magcurr);
  cuts[3] = TCut("+MagDist", cuts[2]&&magdist);
  cuts[4] = TCut("+ToF", cuts[3]&&protontof);
  cuts[5] = TCut("+Ckov", cuts[4]&&ckov);
  cuts[6] = TCut("+DetVtx", cuts[5]&&centralVtx);
  cuts[7] = TCut("+Time", cuts[6]&&hittime);
  cuts[8] = TCut("+NHit", cuts[7]&&nhit);

  gROOT->cd();
  TTree* blcuts = (TTree*)p3Tree->CopyTree(cuts[5]);
  std::cout << "Protons passing beamline selection: " << blcuts->GetEntriesFast() << std::endl;

  int run_dt, subrun_dt, event_dt;
  bool evtStat;
  bool febStatHits[3][64];
  bool dcmStat[3];
  p3DeadTimeTree->SetBranchAddress("run",         &run_dt);
  p3DeadTimeTree->SetBranchAddress("subrun",      &subrun_dt);
  p3DeadTimeTree->SetBranchAddress("event",       &event_dt);
  p3DeadTimeTree->SetBranchAddress("evtStat",     &evtStat);
  p3DeadTimeTree->SetBranchAddress("febStatHits", &febStatHits);
  p3DeadTimeTree->SetBranchAddress("dcmStat",     &dcmStat);
  std::map<tbevent, bool> eventStatuses;
  std::map<tbevent, std::vector<std::vector<bool> > > eventFEBStat;
  std::map<tbevent, std::vector<bool> > eventDCMStat;
  for (int event = 0; event < p3DeadTimeTree->GetEntriesFast(); ++event) {
    p3DeadTimeTree->GetEntry(event);
    eventStatuses[tbevent(run_dt, subrun_dt, event_dt)] = evtStat;
    for (unsigned int dcm = 1; dcm <= 3; ++dcm) {
      std::vector<bool> dcm_febstat;
      for (unsigned int feb = 0; feb < 64; ++feb)
        dcm_febstat.push_back(febStatHits[dcm-1][feb]);
      eventFEBStat[tbevent(run_dt, subrun_dt, event_dt)].push_back(dcm_febstat);
      eventDCMStat[tbevent(run_dt, subrun_dt, event_dt)].push_back(dcmStat[dcm-1]);
    }
  }

  int run_a, subrun_a, event_a;
  blcuts->SetBranchAddress("run", &run_a);
  blcuts->SetBranchAddress("subrun", &subrun_a);
  blcuts->SetBranchAddress("event", &event_a);

  unsigned int nevt = 0;
  TH1I* numBadFEBs = new TH1I("numBadFEBs", ";Number of bad FEBs;", 100, 0, 100);
  TH1I* badFEBs = new TH1I("badFEBs", ";Bad FEB;", 126, 0, 126);
  TH1I* singleBadFEB = new TH1I("singleBadFEB", ";Bad FEB (single);", 126, 0, 126);
  TH1I* twoBadFEBs = new TH1I("twoBadFEBs", ";Bad FEB (two);", 126, 0, 126);
  TH1I* badRuns = new TH1I("badRuns", ";Bad Event;", 498, 100985, 101483);

  for (int event = 0; event < blcuts->GetEntriesFast(); ++event) {

    if (event % 1000 == 0)
      std::cout << "Analyzing event " << event << std::endl;
    blcuts->GetEntry(event);

    if (!eventStatuses.count(tbevent(run_a, subrun_a, event_a)))
      continue;

    if (eventStatuses[tbevent(run_a, subrun_a, event_a)])
      ++nevt;
    else {
      int global_index = 0;
      std::vector<unsigned int> bad_febs;
      std::vector<std::pair<unsigned int, unsigned int> > bad_febs_num;
      for (unsigned int dcm = 1; dcm <= 3; ++dcm) {
        for (unsigned int feb = 0; feb < 64; ++feb) {
          if ((dcm < 3 and (feb == 8 or feb == 24 or feb == 40 or feb == 56)) or
              (dcm == 2 and (feb == 47 or feb == 63)) or
              (dcm == 3 and feb > 7))
            continue;
          if (!eventFEBStat[tbevent(run_a, subrun_a, event_a)][dcm-1][feb]) {
            badFEBs->Fill(global_index);
            bad_febs.push_back(global_index);
            bad_febs_num.push_back(std::make_pair(dcm, feb));
          }
          ++global_index;
        }
      }
      numBadFEBs->Fill(bad_febs.size());
      if (!bad_febs.empty())
        badRuns->Fill(run_a);
      if (bad_febs.size() == 1)
        singleBadFEB->Fill(bad_febs[0]);
      if (bad_febs.size() == 2) {
        twoBadFEBs->Fill(bad_febs[0]);
        twoBadFEBs->Fill(bad_febs[1]);
        // std::cout << "Two bad FEBs: " << bad_febs_num[0].first << ":" << bad_febs_num[0].second
        //           << "; " << bad_febs_num[1].first << ":" << bad_febs_num[1].second << std::endl;
      }
    }

  }

  std::cout << "Protons passing beamline selection with no dead-time: " << nevt << std::endl;

  TFile* outFile = new TFile("p3deadtime.root", "RECREATE");
  numBadFEBs->Write();
  badFEBs->Write();
  badRuns->Write();
  singleBadFEB->Write();
  twoBadFEBs->Write();
  outFile->Close();

}
