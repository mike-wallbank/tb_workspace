// root
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TVector3.h"

// stl
#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include "/nova/app/users/wallbank/test_testbeam/TestBeamAna/TestBeamCuts.h"

// --------------------------------------------------------------------------------------------------
std::vector<std::vector<TVector3> > BuildCellGeoMap();

// --------------------------------------------------------------------------------------------------
void middleCellAna() {

  gROOT->SetBatch(1);

  std::vector<std::vector<TVector3> > cellGeo = BuildCellGeoMap();

  // TFile* inFile
  //   = new TFile("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period3/R21-07-27-testbeam-production.a/TBRecoAna_r101400-r101483.root",
  // 		"READ");
  TFile* inFile
    = new TFile("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period3/R21-07-27-testbeam-production.a/TBRecoAna_r100985-r101483.root",
  		"READ");
  TTree* inTree = (TTree*)inFile->Get("tbrecoana/evts");

  gROOT->cd();
  TTree* evts_cuts = (TTree*)inTree->CopyTree(particle);

  Int_t run, subrun, event;
  evts_cuts->SetBranchAddress("run",    &run);
  evts_cuts->SetBranchAddress("subrun", &subrun);
  evts_cuts->SetBranchAddress("event",  &event);

  Double_t mc7mag;
  evts_cuts->SetBranchAddress("mc7mag", &mc7mag);

  Double_t toftime, wcmom, ckovadc;
  evts_cuts->SetBranchAddress("toftime", &toftime);
  evts_cuts->SetBranchAddress("wcmom", &wcmom);
  evts_cuts->SetBranchAddress("ckovadc", &ckovadc);

  std::vector<Int_t> *hitSlice = nullptr, *hitPlane = nullptr, *hitCell = nullptr;
  std::vector<Double_t> *hitTime = nullptr;
  evts_cuts->SetBranchAddress("hitSlice", &hitSlice);
  evts_cuts->SetBranchAddress("hitPlane", &hitPlane);
  evts_cuts->SetBranchAddress("hitCell", &hitCell);
  evts_cuts->SetBranchAddress("hitTime", &hitTime);

  std::vector<Int_t> *winTrkSlice = nullptr;
  std::vector<Double_t> *winTrkMinTime = nullptr, *winTrkNhit = nullptr,
    *winTrkStrtX = nullptr, *winTrkStrtY = nullptr, *winTrkStrtZ = nullptr,
    *winTrkStopX = nullptr, *winTrkStopY = nullptr, *winTrkStopZ = nullptr;
  evts_cuts->SetBranchAddress("winTrkSlice",   &winTrkSlice);
  evts_cuts->SetBranchAddress("winTrkMinTime", &winTrkMinTime);
  evts_cuts->SetBranchAddress("winTrkNhit",    &winTrkNhit);
  evts_cuts->SetBranchAddress("winTrkStrtX",   &winTrkStrtX);
  evts_cuts->SetBranchAddress("winTrkStrtY",   &winTrkStrtY);
  evts_cuts->SetBranchAddress("winTrkStrtZ",   &winTrkStrtZ);
  evts_cuts->SetBranchAddress("winTrkStopX",   &winTrkStopX);
  evts_cuts->SetBranchAddress("winTrkStopY",   &winTrkStopY);
  evts_cuts->SetBranchAddress("winTrkStopZ",   &winTrkStopZ);

  // data on cell 31 hits!
  int cell_to_investigate = 30;
  std::map<std::string, int> beforeOverfillTotal, beforeOverfillMissed,
    beforeOverfillHitTotal, beforeOverfillHitMissed,
    afterOverfillTotal, afterOverfillMissed,
    afterOverfillHitTotal, afterOverfillHitMissed;

  for (int eventIt = 1; eventIt < evts_cuts->GetEntriesFast(); ++eventIt) {

    evts_cuts->GetEntry(eventIt);

    if (eventIt % 1000 == 0)
      std::cout << "Event " << eventIt << ": " << event
		<< " (" << (int)100.*eventIt/evts_cuts->GetEntriesFast() << "%)" << std::endl;

    // pid
    std::string pid = PID(toftime, ckovadc, mc7mag);

    // get the particle properties
    int slice = -1;
    TVector3 trackStrt, trackStop;
    for (unsigned int trackIt = 0; trackIt < winTrkSlice->size(); ++trackIt) {
      if (abs(winTrkStrtX->at(trackIt)) < 20 and winTrkStrtY->at(trackIt) > -25 and winTrkStrtY->at(trackIt) < 15 and
	  winTrkStrtZ->at(trackIt) < 18 and winTrkNhit->at(trackIt) >= 5 and
	  winTrkMinTime->at(trackIt) > 45000 and winTrkMinTime->at(trackIt) < 55000) {
	slice = winTrkSlice->at(trackIt);
	trackStrt = TVector3(winTrkStrtX->at(trackIt), winTrkStrtY->at(trackIt), winTrkStrtZ->at(trackIt));
	trackStop = TVector3(winTrkStopX->at(trackIt), winTrkStopY->at(trackIt), winTrkStopZ->at(trackIt));
	break;
      }
    }

    if (slice == -1)
      continue;

    // determine if the track passes through a cell 31
    std::vector<int> cell31Planes;

    // walk along the track in 1mm steps (TBD how painfully slow this will be)
    TVector3 trackDir = (trackStop-trackStrt).Unit();
    float trackLengthCM = (trackStop-trackStrt).Mag();
    for (float step = 0; step < trackLengthCM; step+=0.1) {
      TVector3 trackPoint = trackStrt + (step*trackDir);

      // determine how close it gets to any of the cell 31s
      for (unsigned int plane = 0; plane < 61; ++plane) {
	TVector3 cellPos = cellGeo[plane][cell_to_investigate];
	// if (abs(cellPos.Y()-trackPoint.Y()) < 3.56/2. and
	//     abs(cellPos.Z()-trackPoint.Z()) < 5.59/2. and
	if (abs(cellPos.Y()-trackPoint.Y()) < 1. and
	    abs(cellPos.Z()-trackPoint.Z()) < 2. and
	    std::find(cell31Planes.begin(), cell31Planes.end(), plane) == cell31Planes.end())
	  cell31Planes.push_back(plane);
      }
    }

    // determine how many of these cells have hits
    std::vector<int> cell31Hits;
    for (unsigned int hit = 0; hit < hitPlane->size(); ++hit) {
      if (hitSlice->at(hit) != slice or hitCell->at(hit) != cell_to_investigate)
	continue;
      if (std::find(cell31Planes.begin(), cell31Planes.end(), hitPlane->at(hit)) != cell31Planes.end() and
	  std::find(cell31Hits.begin(), cell31Hits.end(), hitPlane->at(hit)) == cell31Hits.end())
	cell31Hits.push_back(hitPlane->at(hit));
    }

    if (cell31Planes.size()) {
      if (run < 101326) {
	beforeOverfillTotal[pid]++;
	beforeOverfillHitTotal[pid] += cell31Planes.size();
	beforeOverfillHitMissed[pid] += cell31Planes.size() - cell31Hits.size();
	if (cell31Hits.size() < cell31Planes.size())
	  beforeOverfillMissed[pid]++;
      } else if (run >= 101357) {
	afterOverfillTotal[pid]++;
	afterOverfillHitTotal[pid] += cell31Planes.size();
	afterOverfillHitMissed[pid] += cell31Planes.size() - cell31Hits.size();
	if (cell31Hits.size() < cell31Planes.size())
	  afterOverfillMissed[pid]++;
      }
    }

  }

  std::cout << "Total numbers:" << std::endl;
  for (std::map<std::string, int>::const_iterator beforeIt = beforeOverfillTotal.begin();
       beforeIt != beforeOverfillTotal.end(); ++beforeIt)
    std::cout << " " << beforeIt->first << ":" << std::endl
	      << "   before: particles with cell " << cell_to_investigate << " missed " << beforeOverfillMissed[beforeIt->first]
	      << " of " << beforeIt->second
	      << " (" << 100*beforeOverfillMissed[beforeIt->first]/(float)beforeIt->second << "%)"
	      << std::endl
	      << "           hits missed " << beforeOverfillHitMissed[beforeIt->first]
	      << " of " << beforeOverfillHitTotal[beforeIt->first]
	      << " (" << 100*beforeOverfillHitMissed[beforeIt->first]/(float)beforeOverfillHitTotal[beforeIt->first] << "%)"
	      << std::endl
	      << "   after: particles with cell " << cell_to_investigate << " missed " << afterOverfillMissed[beforeIt->first]
	      << " of " << afterOverfillTotal[beforeIt->first]
	      << " (" << 100*afterOverfillMissed[beforeIt->first]/(float)afterOverfillTotal[beforeIt->first] << "%)"
	      << std::endl
	      << "          hits missed " << afterOverfillHitMissed[beforeIt->first]
	      << " of " << afterOverfillHitTotal[beforeIt->first]
	      << " (" << 100*afterOverfillHitMissed[beforeIt->first]/(float)afterOverfillHitTotal[beforeIt->first] << "%)"
	      << std::endl;

  return;

}

// --------------------------------------------------------------------------------------------------
std::vector<std::vector<TVector3> > BuildCellGeoMap() {

  std::vector<std::vector<TVector3> > cellGeo(63, std::vector<TVector3>(64));

  std::ifstream inFile("detgeo.txt", std::ifstream::in);
  std::string line;
  std::string plane, cell, x, y, z;

  while (getline(inFile, line)) {
    std::stringstream ss(line);
    ss >> plane;
    ss >> cell;
    ss >> x;
    ss >> y;
    ss >> z;
    TVector3 xyz(std::stof(x), std::stof(y), std::stof(z));
    cellGeo[std::stoi(plane)][std::stoi(cell)] = xyz;
  }

  return cellGeo;

}
