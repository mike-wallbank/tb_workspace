#include "TFile.h"
#include "TChain.h"
#include "TH2F.h"

#include <iostream>

void badFEBvsTime() {

  TFile* p2File = TFile::Open("/nova/ana/users/wallbank/TestBeam/DeadTime/Period2/50us/TBDeadTime_r100224-r100856.root", "READ");
  TFile* p3File = TFile::Open("/nova/ana/users/wallbank/TestBeam/DeadTime/Period3/50us/TBDeadTime_r100985-r101483.root", "READ");
  TFile* p4File = TFile::Open("/nova/ana/users/wallbank/TestBeam/DeadTime/Period4/50us/TBDeadTime_r101577-r101764.root", "READ");

  TChain chain("tbdeadtime/DeadTimeInfo");
  chain.Add("/nova/ana/users/wallbank/TestBeam/DeadTime/Period2/50us/TBDeadTime_r100224-r100856.root");
  chain.Add("/nova/ana/users/wallbank/TestBeam/DeadTime/Period3/50us/TBDeadTime_r100985-r101483.root");
  chain.Add("/nova/ana/users/wallbank/TestBeam/DeadTime/Period4/50us/TBDeadTime_r101577-r101764.root");

  TH2F* badFEB = new TH2F("badFEB", ";Run;FEB;", 1540, 100224, 101764, 126, 0, 126);
  int bin = 1;
  for (unsigned int dcm = 1; dcm <= 3; ++dcm) {
    for (unsigned int feb = 0; feb < 64; ++feb) {
      if ((dcm < 3 and (feb == 8 or feb == 24 or feb == 40 or feb == 56)) or
          (dcm == 2 and (feb == 47 or feb == 63)) or
          (dcm == 3 and feb > 7))
        continue;
      badFEB->GetYaxis()->SetBinLabel(bin, Form("DCM%dFEB%d", dcm, feb));
      ++bin;
    }
  }

  int run;
  bool spillInfo;
  bool febStatBit[3][64];
  bool febStatHits[3][64];
  bool dcmStat[3];
  chain.SetBranchAddress("run",         &run);
  chain.SetBranchAddress("spillInfo",   &spillInfo);
  chain.SetBranchAddress("febStatBit",  &febStatBit);
  chain.SetBranchAddress("febStatHits", &febStatHits);
  chain.SetBranchAddress("dcmStat",     &dcmStat);

  for (int event = 0; event < chain.GetEntries(); ++event) {

    if (event % 10000 == 0)
      std::cout << "Analyzing event " << event << " / " << chain.GetEntries() << std::endl;

    chain.GetEntry(event);

    for (unsigned int dcm = 1; dcm <= 3; ++dcm) {
      for (unsigned int feb = 0; feb < 64; ++feb) {
        if ((dcm < 3 and (feb == 8 or feb == 24 or feb == 40 or feb == 56)) or
            (dcm == 2 and (feb == 47 or feb == 63)) or
            (dcm == 3 and feb > 7))
          continue;
        if (!febStatHits[dcm-1][feb])
          badFEB->Fill(run, Form("DCM%dFEB%d", dcm, feb), 1);
      }
    }

  }

  TFile* outFile = new TFile("badFEBvsTime.root", "RECREATE");
  badFEB->Write();
  outFile->Close();

}
