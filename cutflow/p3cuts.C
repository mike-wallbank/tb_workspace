#include "TFile.h"
#include "TTree.h"
#include "TCut.h"

#include <iostream>

void p3cuts() {

  TFile* inFile = TFile::Open("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period3/N22-04-08/TBRecoAna_r100985-r101483.root", "READ");
  TTree* inTree = (TTree*)inFile->Get("tbrecoana/evts");

  double wcmom, mc7mag, wcMagDist, toftime;
  std::vector<double> *bpfStrtX = nullptr, *bpfStrtY = nullptr, *bpfStrtZ = nullptr, *bpfTrkMinTime = nullptr;
  bool evtStat;
  bool febStat[3][64];
  inTree->SetBranchAddress("wcmom",         &wcmom);
  inTree->SetBranchAddress("mc7mag",        &mc7mag);
  inTree->SetBranchAddress("wcMagDist",     &wcMagDist);
  inTree->SetBranchAddress("toftime",       &toftime);
  inTree->SetBranchAddress("bpfStrtX",      &bpfStrtX);
  inTree->SetBranchAddress("bpfStrtY",      &bpfStrtY);
  inTree->SetBranchAddress("bpfStrtZ",      &bpfStrtZ);
  inTree->SetBranchAddress("bpfTrkMinTime", &bpfTrkMinTime);
  inTree->SetBranchAddress("evtStat",       &evtStat);
  inTree->SetBranchAddress("febStatHits",   &febStat);

  TCut cuts[16];
  cuts[0] = TCut("");
  cuts[1] = TCut(cuts[0]+"wcmom>0");
  cuts[2] = TCut(cuts[1]+"mc7mag>900&&mc7mag<1100");
  cuts[3] = TCut(cuts[2]+"wcMagDist<8");
  cuts[4] = TCut(cuts[3]+"toftime>39&&toftime<50");
  cuts[5] = TCut(cuts[4]+"evtStat==1");
  cuts[6] = TCut(cuts[5]+"abs(bpfStrtX)<20&&bpfStrtY>-25&&bpfStrtY<15&&bpfStrtZ<18");
  cuts[7] = TCut(cuts[6]+"bpfTrkMinTime>45000&&bpfTrkMinTime<55000");
  //cuts[7] = TCut(cuts[6]+"sqrt((bpfStopX-bpfStrtX)^2+(bpfStopY-bpfStrtY)^2+(bpfStopZ-bpfStrtZ)^2)<150");

  int nevts[16];
  for (unsigned int cut = 0; cut < 16; ++cut)
    nevts[cut] = 0;

  for (unsigned int cut = 0; cut <= 7; ++cut)
    std::cout << "Events after cut " << cut << ": " << inTree->GetEntries(cuts[cut]) << std::endl;

  for (int event = 0; event < inTree->GetEntriesFast(); ++event) {
    inTree->GetEntry(event);

    ++nevts[0];
    if (wcmom > 0) {
      ++nevts[1];
      if (mc7mag > 900 && mc7mag < 1100) {
        ++nevts[2];
        if (wcMagDist < 8) {
          ++nevts[3];
          if (toftime > 39 && toftime < 50) {
            ++nevts[4];
            bool evtStat_ignore = true;
            for (unsigned int dcm = 1; dcm <= 3; ++dcm) {
              for (unsigned int feb = 0; feb < 64; ++feb) {
                if ((dcm < 3 and (feb == 8 or feb == 24 or feb == 40 or feb == 56)) or
                    (dcm == 2 and (feb == 47 or feb == 63)) or
                    (dcm == 3 and feb > 7))
                  continue;
                if ((dcm == 2 and feb == 18) or (dcm == 2 and feb == 29))
                  continue;
                if (!febStat[dcm-1][feb])
                  evtStat_ignore = false;
              }
            }
            if (evtStat_ignore == 1) {
              ++nevts[5];
              bool track_vtx = false, track_time = false;
              for (unsigned int track = 0; track < bpfStrtX->size(); ++track) {
                if (abs(bpfStrtX->at(track)) < 20 && bpfStrtY->at(track) > -25 && bpfStrtY->at(track) < 15 && bpfStrtZ->at(track) < 18) {
                  track_vtx = true;
                  if (bpfTrkMinTime->at(track) > 45000 && bpfTrkMinTime->at(track) < 55000)
                    track_time = true;
                }
              }
              if (track_vtx) {
                ++nevts[6];
                if (track_time) {
                  ++nevts[7];
                }
              }
            }
          }
        }
      }
    }

  }

  for (unsigned int cut = 0; cut <= 7; ++cut)
    std::cout << "Events after cut " << cut << ": " << nevts[cut] << std::endl;  

}
