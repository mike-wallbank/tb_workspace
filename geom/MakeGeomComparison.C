
// framework
#include "CAFAna/Core/SpectrumLoader.h"
#include "CAFAna/Core/Spectrum.h"
#include "CAFAna/Core/Var.h"

// test beam
#include "TestBeamAna/Analysis/TestBeamLoaders.h"
#include "TestBeamAna/Cuts/Cuts.h"
#include "TestBeamAna/Vars/BeamlineVars.h"
#include "TestBeamAna/Vars/Vars.h"

// stl
#include "string"

// root
#include "TFile.h"

using namespace ana;

// ----------------------------------------------------------------
void MakeGeomComparison() {

  TestBeamPeriod3Loader* loader = new TestBeamPeriod3Loader();
  //SpectrumLoader* loader = new SpectrumLoader("defname: caf_testbeam_period3_S22-04-08 with limit 10");

  const Var kXDiff = kSelProngStrtX - kBLTrackNOvAFaceX;
  const Var kYDiff = kSelProngStrtY - kBLTrackNOvAFaceY;

  Spectrum sXDiff = Spectrum(*loader, HistAxis("NOvA Reco Start X - WC Reco Start X", Binning::Simple(1000, -50, 50), kXDiff), kTBParticle);
  Spectrum sYDiff = Spectrum(*loader, HistAxis("NOvA Reco Start Y - WC Reco Start Y", Binning::Simple(1000, -50, 50), kYDiff), kTBParticle);

  loader->Go();

  // save
  TFile* outFile = new TFile("GeomComparison.root", "RECREATE");
  sXDiff.SaveTo(outFile->mkdir("XDiff"), "XDiff");
  sYDiff.SaveTo(outFile->mkdir("YDiff"), "YDiff");
  outFile->Close();

}
