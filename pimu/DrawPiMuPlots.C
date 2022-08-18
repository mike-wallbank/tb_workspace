// DrawPiMuPlots.C
// Mike Wallbank (University of Cincinnati) <wallbank@fnal.gov>, March 2022

// framework
#include "CAFAna/Core/Spectrum.h"
#include "CAFAna/Core/LoadFromFile.h"

// stl
#include <iostream>

// root
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"

#include "pimu_drawing.h"

// -----------------------------------------------------------
using namespace ana;

// -----------------------------------------------------------
void DrawPiMuPlots() {

  TFile* inFile = TFile::Open("pimu_ana_cafout.root", "READ");

  Spectrum pi_picvn = *LoadFrom<Spectrum>(inFile->GetDirectory("pi_picvn"), "pi_picvn").release();
  Spectrum pi_mucvn = *LoadFrom<Spectrum>(inFile->GetDirectory("pi_mucvn"), "pi_mucvn").release();
  Spectrum mu_picvn = *LoadFrom<Spectrum>(inFile->GetDirectory("mu_picvn"), "mu_picvn").release();
  Spectrum mu_mucvn = *LoadFrom<Spectrum>(inFile->GetDirectory("mu_mucvn"), "mu_mucvn").release();

  Spectrum pi_pibpfchi2 = *LoadFrom<Spectrum>(inFile->GetDirectory("pi_pibpfchi2"), "pi_pibpfchi2").release();
  Spectrum pi_mubpfchi2 = *LoadFrom<Spectrum>(inFile->GetDirectory("pi_mubpfchi2"), "pi_mubpfchi2").release();
  Spectrum mu_pibpfchi2 = *LoadFrom<Spectrum>(inFile->GetDirectory("mu_pibpfchi2"), "mu_pibpfchi2").release();
  Spectrum mu_mubpfchi2 = *LoadFrom<Spectrum>(inFile->GetDirectory("mu_mubpfchi2"), "mu_mubpfchi2").release();

  pi_picvn.OverridePOT(1);
  pi_mucvn.OverridePOT(1);
  mu_picvn.OverridePOT(1);
  mu_mucvn.OverridePOT(1);

  pi_pibpfchi2.OverridePOT(1);
  pi_mubpfchi2.OverridePOT(1);
  mu_pibpfchi2.OverridePOT(1);
  mu_mubpfchi2.OverridePOT(1);

  TH1* h_pi_picvn = pi_picvn.ToTH1(1);
  TH1* h_pi_mucvn = pi_mucvn.ToTH1(1);
  TH1* h_mu_picvn = mu_picvn.ToTH1(1);
  TH1* h_mu_mucvn = mu_mucvn.ToTH1(1);

  TH1* h_pi_pibpfchi2 = pi_pibpfchi2.ToTH1(1);
  TH1* h_pi_mubpfchi2 = pi_mubpfchi2.ToTH1(1);
  TH1* h_mu_pibpfchi2 = mu_pibpfchi2.ToTH1(1);
  TH1* h_mu_mubpfchi2 = mu_mubpfchi2.ToTH1(1);

  TFile* outFile = new TFile("pimu_ana_cafplots.root", "RECREATE");

  // CVN
  Overlay(h_pi_picvn, h_mu_picvn, "PiCVN_CAF", outFile);
  Overlay(h_pi_mucvn, h_mu_mucvn, "MuCVN_CAF", outFile);

  // BPF -chi2
  Overlay(h_pi_pibpfchi2, h_mu_pibpfchi2, "PiBPFChi2_CAF", outFile);
  Overlay(h_pi_mubpfchi2, h_mu_mubpfchi2, "MuBPFChi2_CAF", outFile);
  
  outFile->Close();
  delete outFile;
}
