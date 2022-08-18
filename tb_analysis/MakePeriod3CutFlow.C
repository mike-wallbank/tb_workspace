
#include "CAFAna/Core/SpectrumLoader.h"
#include "CAFAna/Core/Spectrum.h"
#include "CAFAna/Core/Cut.h"
#include "CAFAna/Vars/Vars.h"
#include "TestBeamAna/Cuts/Cuts.h"
#include "TestBeamAna/Cuts/ToFCuts.h"
#include "TestBeamAna/Vars/BeamVars.h"
#include "TestBeamAna/Vars/Vars.h"

#include "TFile.h"

using namespace ana;

void MakePeriod3CutFlow() {
  
  // Period3 loader
  SpectrumLoader loader("/pnfs/nova/persistent/users/wallbank/testbeam/data/cafs/N22-04-07/period3/*.caf.root");

  // Cut flow
  Cut cWCTrack = kWCReco;
  Cut cMagCurr = cWCTrack && (kMC7Magnet > 900) && (kMC7Magnet < 1100);
  Cut cMagDist = cMagCurr && (kMagAxisDist);
  Cut cToFCkov = cMagDist && kProtonToF && !kCkovActivity;
  Cut cDeadTime = cToFCkov && kNoDeadTime;
  Cut cProng = cDeadTime && kNOvAProton;
  Cut cLength = cProng && (kSelProngBPFLength < 150);

  // Spectrum
  Spectrum sWCTrack(loader, HistAxis("Run", Binning::Simple(498, 100985, 101483), kRun), cWCTrack);
  Spectrum sMagCurr(loader, HistAxis("Run", Binning::Simple(498, 100985, 101483), kRun), cMagCurr);
  Spectrum sMagDist(loader, HistAxis("Run", Binning::Simple(498, 100985, 101483), kRun), cMagDist);
  Spectrum sToFCkov(loader, HistAxis("Run", Binning::Simple(498, 100985, 101483), kRun), cToFCkov);
  Spectrum sDeadTime(loader, HistAxis("Run", Binning::Simple(498, 100985, 101483), kRun), cDeadTime);
  Spectrum sProng(loader, HistAxis("Run", Binning::Simple(498, 100985, 101483), kRun), cProng);
  Spectrum sLength(loader, HistAxis("Run", Binning::Simple(498, 100985, 101483), kRun), cLength);

  loader.Go();

  TFile* outFile = new TFile("Period3CutFlow.root", "RECREATE");
  sWCTrack.SaveTo(outFile->mkdir("WCTrack"), "WCTrack");
  sMagCurr.SaveTo(outFile->mkdir("MagCurr"), "MagCurr");
  sMagDist.SaveTo(outFile->mkdir("MagDist"), "MagDist");
  sToFCkov.SaveTo(outFile->mkdir("ToFCkov"), "ToFCkov");
  sDeadTime.SaveTo(outFile->mkdir("DeadTime"), "DeadTime");
  sProng.SaveTo(outFile->mkdir("Prong"), "Prong");
  sLength.SaveTo(outFile->mkdir("Length"), "Length");
  outFile->Close();

  return;


}
