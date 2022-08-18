// MakePiMuPlots.C
// Mike Wallbank (University of Cincinnati) <wallbank@fnal.gov>, March 2022

// framework
#include "CAFAna/Core/SpectrumLoader.h"
#include "CAFAna/Core/Spectrum.h"
#include "CAFAna/Core/HistAxis.h"
#include "StandardRecord/Proxy/SRProxy.h"
#include "TestBeamAna/Vars/PIDVars.h"

// stl
#include <iostream>

// root
#include "TFile.h"

// -----------------------------------------------------------
using namespace ana;

// -----------------------------------------------------------
void MakePiMuPlots() {

  SpectrumLoader pi_loader("/nova/data/users/wallbank/tb/pimu/pi_sim_overlay_pid.caf.root");
  SpectrumLoader mu_loader("/nova/data/users/wallbank/tb/pimu/mu_sim_overlay_pid.caf.root");

  Spectrum pi_picvn(pi_loader, HistAxis("#pi CVN Response", Binning::Simple(100,0,1), kLongestProngCVNPion), kNoCut);
  Spectrum pi_mucvn(pi_loader, HistAxis("#mu CVN Response", Binning::Simple(100,0,1), kLongestProngCVNMuon), kNoCut);
  Spectrum mu_picvn(mu_loader, HistAxis("#pi CVN Response", Binning::Simple(100,0,1), kLongestProngCVNPion), kNoCut);
  Spectrum mu_mucvn(mu_loader, HistAxis("#mu CVN Response", Binning::Simple(100,0,1), kLongestProngCVNMuon), kNoCut);

  Spectrum pi_pibpfchi2(pi_loader, HistAxis("#pi BPF #chi2", Binning::Simple(100,0,8), kLongestProngBPFChi2Pion), kNoCut);
  Spectrum pi_mubpfchi2(pi_loader, HistAxis("#mu BPF #chi2", Binning::Simple(100,0,8), kLongestProngBPFChi2Muon), kNoCut);
  Spectrum mu_pibpfchi2(mu_loader, HistAxis("#pi BPF #chi2", Binning::Simple(100,0,8), kLongestProngBPFChi2Pion), kNoCut);
  Spectrum mu_mubpfchi2(mu_loader, HistAxis("#mu BPF #chi2", Binning::Simple(100,0,8), kLongestProngBPFChi2Muon), kNoCut);

  pi_loader.Go();
  mu_loader.Go();

  TFile* outFile = new TFile("pimu_ana_cafout.root", "RECREATE");
  pi_picvn.SaveTo(outFile->mkdir("pi_picvn"), "pi_picvn");
  pi_mucvn.SaveTo(outFile->mkdir("pi_mucvn"), "pi_mucvn");
  mu_picvn.SaveTo(outFile->mkdir("mu_picvn"), "mu_picvn");
  mu_mucvn.SaveTo(outFile->mkdir("mu_mucvn"), "mu_mucvn");
  pi_pibpfchi2.SaveTo(outFile->mkdir("pi_pibpfchi2"), "pi_pibpfchi2");
  pi_mubpfchi2.SaveTo(outFile->mkdir("pi_mubpfchi2"), "pi_mubpfchi2");
  mu_pibpfchi2.SaveTo(outFile->mkdir("mu_pibpfchi2"), "mu_pibpfchi2");
  mu_mubpfchi2.SaveTo(outFile->mkdir("mu_mubpfchi2"), "mu_mubpfchi2");
  outFile->Close();
  delete outFile;

  return;
}
