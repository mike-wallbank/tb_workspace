#include "TFile.h"
#include "TTree.h"
#include "TCut.h"

#include <iostream>

void cutFlow() {

  TFile* p3File
    = TFile::Open("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period3/R21-07-27-testbeam-production.a/TBRecoAna_r100985-r101483.root",
                  "READ");
  TTree* p3Tree = (TTree*)p3File->Get("tbrecoana/evts");

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

  for (unsigned int cut = 0; cut < 9; ++cut)
    std::cout << "Number of particles after cut " << cuts[cut].GetName() << ": " << p3Tree->GetEntries(cuts[cut]) << std::endl;

}
