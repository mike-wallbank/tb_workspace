#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TH2F.h"

#include <iostream>

void hit_time_ana() {

  TFile* inFile
    = TFile::Open("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period3/R21-07-27-testbeam-production.a/TBRecoAna_r100985-r101483.root",
		  "READ");
  TTree* evts = (TTree*)inFile->Get("tbrecoana/evts");

  // basic
  Int_t run = -1, subrun = -1, event = -1;
  evts->SetBranchAddress("run",    &run);
  evts->SetBranchAddress("subrun", &subrun);
  evts->SetBranchAddress("event",  &event);

  // database
  Double_t mc7mag = -1;
  evts->SetBranchAddress("mc7mag", &mc7mag);

  // beamline
  Double_t wcmom = -1, toftime = -1, wcmagdist = -1;
  evts->SetBranchAddress("wcmom",     &wcmom);
  evts->SetBranchAddress("toftime",   &toftime);
  evts->SetBranchAddress("wcMagDist", &wcmagdist);

  // nova
  std::vector<Int_t> *winTrkSlice = nullptr;
  std::vector<Double_t> *winTrkNhit = nullptr,
    *winTrkStrtX = nullptr, *winTrkStrtY = nullptr,
    *winTrkStrtZ = nullptr, *winTrkMinTime = nullptr;
  std::vector<Double_t> *winTrkCalE = nullptr;
  evts->SetBranchAddress("winTrkSlice",   &winTrkSlice);
  evts->SetBranchAddress("winTrkNhit",    &winTrkNhit);
  evts->SetBranchAddress("winTrkStrtX",   &winTrkStrtX);
  evts->SetBranchAddress("winTrkStrtY",   &winTrkStrtY);
  evts->SetBranchAddress("winTrkStrtZ",   &winTrkStrtZ);
  evts->SetBranchAddress("winTrkMinTime", &winTrkMinTime);
  evts->SetBranchAddress("winTrkCalE",    &winTrkCalE);

  std::vector<Double_t> *sliceCalE = nullptr;
  evts->SetBranchAddress("sliceCalE", &sliceCalE);

  std::vector<Int_t>* hitSlice = nullptr;
  std::vector<Double_t>* hitGeV = nullptr;
  std::vector<Double_t>* hitTime = nullptr;
  std::vector<Int_t> *hitPlane = nullptr, *hitCell = nullptr;
  evts->SetBranchAddress("hitSlice", &hitSlice);
  evts->SetBranchAddress("hitGeV",   &hitGeV);
  evts->SetBranchAddress("hitTime",  &hitTime);
  evts->SetBranchAddress("hitPlane", &hitPlane);
  evts->SetBranchAddress("hitCell",  &hitCell);

  for (unsigned int eventIt = 0; eventIt < evts->GetEntriesFast(); ++eventIt) {

    if (eventIt % 1000 == 0)
      std::cout << "Event " << eventIt << " (" << int(eventIt*100/evts->GetEntriesFast()) << "%)" << std::endl;
    evts->GetEntry(eventIt);

    // select the beamline particle
    bool proton = false;
    if (wcmom > 0 and wcmagdist < 5 and
	( (mc7mag > 900 and mc7mag < 1100 and toftime > 39 and toftime < 50) or
	  (mc7mag > 650 and mc7mag < 850 and toftime > 42 and toftime < 60) or
	  (mc7mag > 400 and mc7mag < 600 and toftime > 56 and toftime < 80) )
	)
      proton = true;

    if (!proton)
      continue;

    // select the track
    int slice = -1, track = -1;
    for (unsigned int winTrk = 0; winTrk < winTrkNhit->size(); ++winTrk) {

      if (winTrkNhit->at(winTrk) > 5 and
    	  abs(winTrkStrtX->at(winTrk))<20 and winTrkStrtY->at(winTrk)>-25 and winTrkStrtY->at(winTrk)<15 and winTrkStrtZ->at(winTrk)<18 and
    	  winTrkMinTime->at(winTrk)>45000 and winTrkMinTime->at(winTrk)<55000) {

	slice = winTrkSlice->at(winTrk);
	track = winTrk;

	// look at the slice hits
	for (unsigned int hit = 0; hit < hitSlice->size(); ++hit) {
	  if (hitSlice->at(hit) != slice)
	    continue;
	  std::cout << " Proton hit on plane " << hitPlane->at(hit) << ", cell " << hitCell->at(hit)
		    << " at time " << hitTime->at(hit) << std::endl;
	} // hits

      } // track pass cut

    } // tracks

  } // events

}
