// ------------------------------------
// MakeBlessedPlots.C
// M Wallbank, July 2022
//
// Macro name is very on-the-nose.
// Make some plots designed for public
// consumption!
// ------------------------------------

// framework
#include "CAFAna/Core/Spectrum.h"
#include "TestBeamAna/Analysis/TestBeamLoaders.h"
#include "TestBeamAna/Cuts/Cuts.h"
#include "TestBeamAna/Vars/HistAxes.h"

// root
#include "TFile.h"

using namespace ana;

// ------------------------------------
void MakeBlessedPlots() {

  TestBeamPeriod3Loader* loader = new TestBeamPeriod3Loader();

  // Beamline momentum
  Spectrum p_proton(*loader, kMomAxis, kProton);//kBeamlineProton&&kEventLevel);
  Spectrum p_electron(*loader, kMomAxis, kElectron);//kBeamlineElectron&&kEventLevel);
  Spectrum p_kaon(*loader, kMomAxis, kKaon);//kBeamlineKaon&&kEventLevel);
  Spectrum p_pimu(*loader, kMomAxis, kPiMu);//kBeamlinePiMu&&kEventLevel);

  // ToF
  Spectrum tof(*loader, kToFAxis, kTBParticle);//kBeamlineReco&&kEventLevel);

  // PID plot
  Spectrum pid(*loader, kMomAxis, kToFAxis, kTBParticle);//kBeamlineReco&&kEventLevel);

  // Length plot
  Spectrum len_proton(*loader, kLengthAxis, kProton);

  loader->Go();

  // Save!
  TFile* outFile = new TFile("BlessedPlots.root", "RECREATE");
  p_proton.SaveTo(outFile->mkdir("p_proton"), "p_proton");
  p_electron.SaveTo(outFile->mkdir("p_electron"), "p_electron");
  p_kaon.SaveTo(outFile->mkdir("p_kaon"), "p_kaon");
  p_pimu.SaveTo(outFile->mkdir("p_pimu"), "p_pimu");
  tof.SaveTo(outFile->mkdir("tof"), "tof");
  pid.SaveTo(outFile->mkdir("pid"), "pid");
  outFile->Close();

  return;
}
