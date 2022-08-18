#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TH2F.h"

#include <iostream>

void slice_track_energy() {

  TFile* inFile = TFile::Open("/nova/ana/users/wallbank/TestBeam/Period3Data/TBRecoAna_r100985-r101483.root", "READ");
  TTree* evts = (TTree*)inFile->Get("tbrecoana/evts");

  TCut wcX("wcmom>=0");
  TCut tofc("toftime>=30");
  TCut tofX("toftime>=0");
  TCut magdist("abs(wcMagDist)<10");
  TCut blcuts(wcX&&tofc&&magdist);
  TCut electrontof("toftime>30&&toftime<36");
  TCut electron(electrontof&&"ckovadc>0");
  gROOT->cd();
  TTree* evts_electron_blcuts = (TTree*)evts->CopyTree(blcuts);

  std::cout << evts_electron_blcuts->GetEntriesFast() << " entries in tree" << std::endl;

  Int_t run = -1;
  Int_t subrun = -1;
  Int_t event = -1;
  evts_electron_blcuts->SetBranchAddress("run",    &run);
  evts_electron_blcuts->SetBranchAddress("subrun", &subrun);
  evts_electron_blcuts->SetBranchAddress("event",  &event);

  std::vector<Int_t> *winTrkSlice = nullptr;
  std::vector<Double_t> *winTrkNhit = nullptr,
    *winTrkStrtX = nullptr, *winTrkStrtY = nullptr,
    *winTrkStrtZ = nullptr, *winTrkMinTime = nullptr;
  std::vector<Double_t> *winTrkCalE = nullptr;
  evts_electron_blcuts->SetBranchAddress("winTrkSlice",   &winTrkSlice);
  evts_electron_blcuts->SetBranchAddress("winTrkNhit",    &winTrkNhit);
  evts_electron_blcuts->SetBranchAddress("winTrkStrtX",   &winTrkStrtX);
  evts_electron_blcuts->SetBranchAddress("winTrkStrtY",   &winTrkStrtY);
  evts_electron_blcuts->SetBranchAddress("winTrkStrtZ",   &winTrkStrtZ);
  evts_electron_blcuts->SetBranchAddress("winTrkMinTime", &winTrkMinTime);
  evts_electron_blcuts->SetBranchAddress("winTrkCalE",    &winTrkCalE);

  std::vector<Double_t> *sliceCalE = nullptr;
  evts_electron_blcuts->SetBranchAddress("sliceCalE", &sliceCalE);

  std::vector<Int_t> *hitSlice = nullptr;
  std::vector<Double_t> *hitGeV = nullptr;
  evts_electron_blcuts->SetBranchAddress("hitSlice", &hitSlice);
  evts_electron_blcuts->SetBranchAddress("hitGeV",   &hitGeV);

  TH2F* energyVsMom = new TH2F("energyVsMom", ";reconstructed momentum (MeV/c);reconstructed electron energy (GeV);",
			       100, 0, 1200, 100, 0, 0.005);
  TH2* trackVsSliceEnergy = new TH2F("trackVsSliceEnergy", ";slice energy (GeV);track energy (GeV);", 100, 0, 0.005, 100, 0, 0.005);
  TH1* trackSliceEnergyFrac = new TH1F("trackSliceEnergyFrac", ";fraction of slice energy in track;", 110, 0, 1.1);
  TH1* hitVsSliceEnergy = new TH1F("hitVsSliceEnergy", ";(slice energy (GeV) - summed hit energy (GeV))/summed hit energy (GeV);",
				   100, 0.5, 1.5);

  for (unsigned int eventIt = 0; eventIt < evts_electron_blcuts->GetEntriesFast(); ++eventIt) {

    if (eventIt % 1000 == 0)
      std::cout << "Event " << eventIt << " (" << int(eventIt*100/evts_electron_blcuts->GetEntriesFast()) << "%)" << std::endl;
    evts_electron_blcuts->GetEntry(eventIt);

    // select the track
    int slice = -1, track = -1;
    for (unsigned int winTrk = 0; winTrk < winTrkNhit->size(); ++winTrk) {

      if (winTrkNhit->at(winTrk) > 5 and
    	  abs(winTrkStrtX->at(winTrk))<20 and winTrkStrtY->at(winTrk)>-25 and winTrkStrtY->at(winTrk)<15 and winTrkStrtZ->at(winTrk)<18 and
    	  winTrkMinTime->at(winTrk)>45000 and winTrkMinTime->at(winTrk)<55000) {

	if (winTrkSlice->at(winTrk) >= (int)sliceCalE->size())
	  continue;

	slice = winTrkSlice->at(winTrk);
	track = winTrk;

	float frac = winTrkCalE->at(track)/sliceCalE->at(slice);
	trackSliceEnergyFrac->Fill(frac);
	trackVsSliceEnergy->Fill(sliceCalE->at(slice), winTrkCalE->at(track));

	break;

      } // track pass cut

    } // loop over tracks

    if (slice < 0)
      continue;

    // sum up hit energy for the selected slice
    double totHitEnergyInSlice = 0;
    for (unsigned int hit = 0; hit < hitSlice->size(); ++hit)
      if (hitSlice->at(hit) == slice and hitGeV->at(hit) > 0)
	totHitEnergyInSlice += hitGeV->at(hit);

    float energyFrac = (sliceCalE->at(slice)-totHitEnergyInSlice)/totHitEnergyInSlice;
    hitVsSliceEnergy->Fill(energyFrac);

  } // loop over events
 
  TFile* outFile = new TFile("SliceTrackEnergy.root", "RECREATE");
  trackVsSliceEnergy->Write();
  trackSliceEnergyFrac->Write();
  hitVsSliceEnergy->Write();

  outFile->Close();

}
