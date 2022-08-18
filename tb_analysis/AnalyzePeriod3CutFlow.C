
#include "CAFAna/Core/LoadFromFile.h"
#include "CAFAna/Core/Spectrum.h"

#include "TFile.h"
#include "TH1.h"

#include <iostream>

using namespace ana;

void AnalyzePeriod3CutFlow() {

  TFile* inFile = TFile::Open("Period3CutFlow.root", "READ");

  Spectrum sWCTrack = *LoadFrom<Spectrum>(inFile->GetDirectory("WCTrack"), "WCTrack").release();
  Spectrum sMagCurr = *LoadFrom<Spectrum>(inFile->GetDirectory("MagCurr"), "MagCurr").release();
  Spectrum sMagDist = *LoadFrom<Spectrum>(inFile->GetDirectory("MagDist"), "MagDist").release();
  Spectrum sToFCkov = *LoadFrom<Spectrum>(inFile->GetDirectory("ToFCkov"), "ToFCkov").release();
  Spectrum sDeadTime = *LoadFrom<Spectrum>(inFile->GetDirectory("DeadTime"), "DeadTime").release();
  Spectrum sProng = *LoadFrom<Spectrum>(inFile->GetDirectory("Prong"), "Prong").release();
  Spectrum sLength = *LoadFrom<Spectrum>(inFile->GetDirectory("Length"), "Length").release();

  sWCTrack.OverridePOT(1);
  sMagCurr.OverridePOT(1);
  sMagDist.OverridePOT(1);
  sToFCkov.OverridePOT(1);
  sDeadTime.OverridePOT(1);
  sProng.OverridePOT(1);
  sLength.OverridePOT(1);

  TH1* hWCTrack = sWCTrack.ToTH1(1);
  TH1* hMagCurr = sMagCurr.ToTH1(1);
  TH1* hMagDist = sMagDist.ToTH1(1);
  TH1* hToFCkov = sToFCkov.ToTH1(1);
  TH1* hDeadTime = sDeadTime.ToTH1(1);
  TH1* hProng = sProng.ToTH1(1);
  TH1* hLength = sLength.ToTH1(1);

  std::cout << "Events after cuts:" << std::fixed << std::endl
            << " WCTrack " << hWCTrack->Integral() << std::endl
            << " MagCurr " << hMagCurr->Integral() << std::endl
            << " MagDist " << hMagDist->Integral() << std::endl
            << " ToFCkov " << hToFCkov->Integral() << std::endl
            << " DeadTime " << hDeadTime->Integral() << std::endl
            << " Prong " << hProng->Integral() << std::endl
            << " Length " << hLength->Integral() << std::endl;

}
