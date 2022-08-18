//////////////////////////////////////////////////////////////
// MakeParticleProperties.C
// M Wallbank (wallbank@fnal.gov)
// February 2022
//
// Example macro showing how to apply Test Beam selection to
// make plots of particle properties.
//////////////////////////////////////////////////////////////

// framework
#include "CAFAna/Core/EventList.h"
#include "CAFAna/Core/SpectrumLoader.h"
#include "CAFAna/Vars/Vars.h"
#include "TestBeamAna/Cuts/Cuts.h"
#include "TestBeamAna/Vars/BeamlineVars.h"
#include "TestBeamAna/Vars/HistAxes.h"
#include "TestBeamAna/Vars/Vars.h"

// stl
#include <iostream>

// root
#include "TFile.h"

// -----------------------------------------------------------
using namespace ana;

// -----------------------------------------------------------
void MakeParticleProperties() {

  // Make a loader
  std::string fileName = "/nova/ana/users/wallbank/TestBeam/CAF/testbeam_r00101402_beamline_R21-07-27-testbeam-production.caf.root";
  //std::string fileName = "/nova/app/users/wallbank/tb_caf/testbeam_r00101402_s00_beamline_R21-07-27-testbeam-production.caf.root";
  SpectrumLoader loader(fileName);

  // Momentum plots
  Spectrum p_proton(loader, kMomAxis, kProton);
  Spectrum p_electron(loader, kMomAxis, kElectron);
  Spectrum p_pimu(loader, kMomAxis, kPiMu);
  Spectrum p_kaon(loader, kMomAxis, kKaon);

  loader.Go();

  // Particle properties
  std::vector<const Var*> variables = {&kRun, &kSubrun, &kEvt, &kSlc,
				       &kMomentum, &kToFShort, &kCkovADC, &kTransDistMagAxis,
				       &kSelProngNHit, &kSelProngStrtX, &kSelProngStrtY, &kSelProngStrtZ, &kSelProngMinTime};

  MakeTextListFile(fileName,
  		   {kProton, kElectron, kPiMu, kKaon},
                   {"select_proton.txt", "select_electron.txt", "select_pimu.txt", "select_kaon.txt"},
  		   variables);

  TFile* outFile = new TFile("ParticleProperties.root", "RECREATE");
  p_proton.SaveTo(outFile->mkdir("p_proton"), "p_proton");
  p_electron.SaveTo(outFile->mkdir("p_electron"), "p_electron");
  p_pimu.SaveTo(outFile->mkdir("p_pimu"), "p_pimu");
  p_kaon.SaveTo(outFile->mkdir("p_kaon"), "p_kaon");
  outFile->Close();

  return;
}
