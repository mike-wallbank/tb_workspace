// root
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TVector3.h"

// stl
#include <iostream>
#include <fstream>

// framework
#include "/nova/app/users/wallbank/test_testbeam/TestBeamAna/TestBeamCuts.h"

void generate_p3sim() {

  std::ofstream outFile;
  outFile.open("evts.txt");

  TFile* inFile
    = TFile::Open("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period3/R21-07-27-testbeam-production.a/TBRecoAna_r100985-r101483.root",
		  "READ");
  TTree* inTree = (TTree*)inFile->Get("tbrecoana/evts");

  gROOT->cd();
  TTree* evts_cuts = (TTree*)inTree->CopyTree(particle);

  Double_t mc7mag;
  evts_cuts->SetBranchAddress("mc7mag", &mc7mag);

  Double_t toftime, wcmom, ckovadc;
  evts_cuts->SetBranchAddress("toftime", &toftime);
  evts_cuts->SetBranchAddress("wcmom", &wcmom);
  evts_cuts->SetBranchAddress("ckovadc", &ckovadc);

  Double_t wcTrkDirX, wcTrkDirY, wcTrkDirZ, wcTrkStrtX, wcTrkStrtY;
  evts_cuts->SetBranchAddress("wcTrkDirX",  &wcTrkDirX);
  evts_cuts->SetBranchAddress("wcTrkDirY",  &wcTrkDirY);
  evts_cuts->SetBranchAddress("wcTrkDirZ",  &wcTrkDirZ);
  evts_cuts->SetBranchAddress("wcTrkStrtX", &wcTrkStrtX);
  evts_cuts->SetBranchAddress("wcTrkStrtY", &wcTrkStrtY);

  int event_num = -1;

  for (int eventIt = 1; eventIt < evts_cuts->GetEntriesFast() and eventIt < 10; ++eventIt) {

    evts_cuts->GetEntry(eventIt);

    if (eventIt % 1000 == 0)
      std::cout << "Event " << eventIt << " (" << (int)100.*eventIt/evts_cuts->GetEntriesFast() << "%)" << std::endl;

    if (wcmom <= 0 or toftime < 30 or toftime > 80)
      continue;

    // particle properties
    std::string pid = PID(toftime, ckovadc, mc7mag);
    int pdg = PDG(pid);
    float mom = wcmom/1.e3;
    float upstream_offset = 445;
    TVector3 dir_vec(wcTrkDirX, wcTrkDirY, wcTrkDirZ);
    TVector3 vtx_vec(wcTrkStrtX-upstream_offset*dir_vec.X(),
		     wcTrkStrtY-upstream_offset*dir_vec.Y(),
		     -1.*upstream_offset);
    TVector3 mom_vec = mom*dir_vec;
    float mass = MassGeV(pid);
    float energy = sqrt(pow(mom, 2) + pow(mass, 2));

    std::cout << "Wire chamber track projected entry point (" << wcTrkStrtX << ", " << wcTrkStrtY << ", 0); "
	      << "back projected point (" << vtx_vec.X() << ", " << vtx_vec.Y() << ", " << vtx_vec.Z() << ")" << std::endl;

    ++event_num;
    outFile << event_num << " 1" << std::endl;
    outFile << "1 " << pdg << " 0 0 0 0 " << mom_vec.X() << " " << mom_vec.Y() << " " << mom_vec.Z() << " "
	    << energy << " " << mass << " " << vtx_vec.X() << " " << vtx_vec.Y() << " " << vtx_vec.Z() << " 84e3" << std::endl;

  }

  outFile.close();

}
