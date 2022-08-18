#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TEntryList.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TCanvas.h"

#include <iostream>
#include <vector>
#include <map>

void BraggPeak() {
  
  TFile* inFile
    = new TFile("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period3/R21-07-27-testbeam-production.a/TBRecoAna_r100985-r101483.root",
		"READ");
  TTree* evts = (TTree*)inFile->Get("tbrecoana/evts");

  TCut wcX("wcmom>=0");
  TCut tofc("toftime>=30");
  TCut tofX("toftime>=0");
  TCut magdist("abs(wcMagDist)<5");
  TCut blcuts(wcX&&tofX&&magdist);
  TCut nhits("winTrkNhit>5");
  TCut centralVtx("abs(winTrkStrtX)<20&&winTrkStrtY>-25&&winTrkStrtY<15&&winTrkStrtZ<18");
  TCut hittime("winTrkMinTime>45000&&winTrkMinTime<55000");
  TCut detcuts(centralVtx&&hittime&&nhits);
  TCut selection(blcuts&&detcuts);

  TCut electrontof("toftime>30&&toftime<36");
  TCut electron(selection&&electrontof&&"ckovadc>0");
  TCut electron_length(electron&&"sqrt((winTrkStopX - winTrkStrtX)^2+(winTrkStopY - winTrkStrtY)^2+(winTrkStopZ - winTrkStrtZ)^2)<300");
 
  TH2F* hBraggPeak = new TH2F("ElectronBraggPeak", ";# Planes from Track End;Energy Deposited on Plane (GeV);", 63, 0, 63, 100, 0, 0.2);

  // track properties
  std::vector<int>* winTrk = nullptr;
  std::vector<int>* winTrkSlice = nullptr;
  std::vector<int>* winTrkMaxPlane = nullptr;
  std::vector<int>* winTrkNhit = nullptr;
  std::vector<int>* winTrkStrtX = nullptr;
  std::vector<int>* winTrkStrtY = nullptr;
  std::vector<int>* winTrkStrtZ = nullptr;
  std::vector<int>* winTrkMinTime = nullptr;
  int run = 0;
  int subrun = 0;
  int printevent = 0;
  evts->SetBranchAddress("run",&run);
  evts->SetBranchAddress("subrun",&subrun);
  evts->SetBranchAddress("event",&printevent); 
  evts->SetBranchAddress("winTrk",&winTrk);
  evts->SetBranchAddress("winTrkSlice",&winTrkSlice);
  evts->SetBranchAddress("winTrkMaxPlane",&winTrkMaxPlane);
  evts->SetBranchAddress("winTrkNhit",&winTrkNhit);
  evts->SetBranchAddress("winTrkStrtX",&winTrkStrtX);
  evts->SetBranchAddress("winTrkStrtY",&winTrkStrtY);
  evts->SetBranchAddress("winTrkStrtZ",&winTrkStrtZ);
  evts->SetBranchAddress("winTrkMinTime",&winTrkMinTime);

  // hit properties
  std::vector<int>* hitPlane = nullptr;
  std::vector<int>* hitSlice = nullptr;
  std::vector<float>* hitGeV = nullptr;
  evts->SetBranchAddress("hitPlane",&hitPlane);
  evts->SetBranchAddress("hitSlice",&hitSlice);
  evts->SetBranchAddress("hitGeV",&hitGeV);

  std::cout << typeid(hitSlice).name() << typeid(hitSlice[0]).name() << std::endl;

  // get the list of electrons
  evts->Draw(">>entries", electron_length, "entrylist");
  TEntryList* entries = (TEntryList*)gDirectory->Get("entries");

  // loop over electrons
  for (int event = 0; event <= entries->GetN(); ++event) {

    evts->GetEntry(entries->GetEntry(event));
    int slice = -1;
    int track = -1;
    int max_plane = -1;

    // find the selected electron track
    for (unsigned int trackIt = 0; trackIt < winTrkSlice->size(); ++trackIt) {

      if (winTrkNhit->at(trackIt) > 5 and
	  abs(winTrkStrtX->at(trackIt)) < 20 and
	  winTrkStrtY->at(trackIt) > -25 and winTrkStrtY->at(trackIt) < 15 and
	  winTrkStrtZ->at(trackIt) < 18 and 
	  winTrkMinTime->at(trackIt) > 45000 and winTrkMinTime->at(trackIt) < 55000) {
	slice = winTrkSlice->at(trackIt);
	track = winTrk->at(trackIt);
	max_plane = winTrkMaxPlane->at(trackIt);
	std::cout << "Event Number: " << printevent << std::endl;
	break;
      } // track selection

    } // tracks

    // sum up hit energy on each plane
    std::vector<double> total_plane_energy(63, 0);
    for (unsigned int hitIt = 0; hitIt < hitSlice->size(); ++hitIt)
      if (hitSlice->at(hitIt) == slice and hitGeV->at(hitIt) > -5)
	total_plane_energy.at(hitPlane->at(hitIt)) += hitGeV->at(hitIt);

    // print out the 
    std::cout << "Max plane is " << max_plane << std::endl;
    for (unsigned int plane = max_plane; plane >= 0; --plane)
      std::cout << " Plane " << plane << " has energy " << total_plane_energy.at(plane) << std::endl;
    
    std::vector<int> low_energy_planes;
    for (unsigned int plane = 0; plane < 63; ++plane) {
      if (max_plane - plane < 3 and total_plane_energy.at(plane) < 0.015) {
	std::cout << "Plane " << plane << " has total energy " << total_plane_energy.at(plane) << std::endl;
	low_energy_planes.push_back(plane);
      }
    }

    for (unsigned int hitIt = 0; hitIt < hitSlice->size(); ++hitIt)
      if (hitSlice->at(hitIt) == slice and hitGeV->at(hitIt) > -5 and
	  std::find(low_energy_planes.begin(), low_energy_planes.end(), hitPlane->at(hitIt)) != low_energy_planes.end())
	std::cout << " Hit plane " << hitPlane->at(hitIt) << ", energy " << hitGeV->at(hitIt) << std::endl;

    // fill the total energy on each plane
    for (unsigned int planeIt = 0; planeIt < 63; ++planeIt)
      if (total_plane_energy.at(planeIt) > 0)
	//if (total_plane_energy.at(planeIt) > 0.015)
	hBraggPeak->Fill(max_plane-planeIt, total_plane_energy[planeIt]);

  } // events

  TCanvas *canv = new TCanvas("c1","", 800, 600);
  hBraggPeak->Draw("colz");
  canv->SaveAs("ElectronBraggPeak.png");

  TProfile* hBraggProf = hBraggPeak->ProfileX();
  canv->Clear();
  hBraggProf->Draw("hist");
  canv->SaveAs("ElectronBraggProfile.png");

  TFile* outFile = new TFile("ElectronBraggPeak.root", "RECREATE");
  hBraggPeak->Write("BraggPeak");
  hBraggProf->Write("BraggProf");
  outFile->Close();

}
