// ------------------------------------
// DrawBlessedPlots.C
// M Wallbank, July 2022
//
// Macro name is very on-the-nose.
// Make some plots designed for public
// consumption!
// ------------------------------------

// framework
#include "CAFAna/Core/Spectrum.h"
#include "Utilities/rootlogon.C"

// root
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TLegend.h"

using namespace ana;

// ------------------------------------
void DrawBlessedPlots() {

  // Input file
  TFile* inFile = TFile::Open("/pnfs/nova/scratch/users/wallbank/testbeam/data/blessing/BlessedPlots.root", "READ");

  // Load in spectra
  Spectrum p_proton = *Spectrum::LoadFrom(inFile->GetDirectory("p_proton"), "p_proton").release();
  Spectrum p_electron = *Spectrum::LoadFrom(inFile->GetDirectory("p_electron"), "p_electron").release();
  Spectrum p_kaon = *Spectrum::LoadFrom(inFile->GetDirectory("p_kaon"), "p_kaon").release();
  Spectrum p_pimu = *Spectrum::LoadFrom(inFile->GetDirectory("p_pimu"), "p_pimu").release();

  Spectrum tof = *Spectrum::LoadFrom(inFile->GetDirectory("tof"), "tof").release();

  Spectrum pid = *Spectrum::LoadFrom(inFile->GetDirectory("pid"), "pid").release();

  // Output data
  TFile* outFile = new TFile("BlessedPlotsAna.root", "RECREATE");
  TCanvas* canv = new TCanvas("canv", "", 800, 700);
  TCanvas* canv_wide = new TCanvas("canv_wide", "", 1400, 1200);

  // Draw stack momentum
  THStack* stack = new THStack("p_stack", "");
  TLegend* leg = new TLegend(0.15, 0.6, 0.4, 0.8);
  p_kaon.OverridePOT(1);
  TH1* h_p_kaon = p_kaon.ToTH1(p_kaon.POT());
  h_p_kaon->SetLineColor(kMagenta+1);
  h_p_kaon->SetFillColor(kMagenta+1);
  stack->Add(h_p_kaon);
  leg->AddEntry(h_p_kaon, "K", "lf");
  p_electron.OverridePOT(1);
  TH1* h_p_electron = p_electron.ToTH1(p_electron.POT());
  h_p_electron->SetLineColor(kOrange+7);
  h_p_electron->SetFillColor(kOrange+7);
  stack->Add(h_p_electron);
  leg->AddEntry(h_p_electron, "e", "fl");
  p_pimu.OverridePOT(1);
  TH1* h_p_pimu = p_pimu.ToTH1(p_pimu.POT());
  h_p_pimu->SetLineColor(kGreen+2);
  h_p_pimu->SetFillColor(kGreen+2);
  stack->Add(h_p_pimu);
  leg->AddEntry(h_p_pimu, "#pi / #mu", "fl");
  p_proton.OverridePOT(1);
  TH1* h_p_proton = p_proton.ToTH1(p_proton.POT());
  h_p_proton->SetLineColor(kAzure+1);
  h_p_proton->SetFillColor(kAzure+1);
  stack->Add(h_p_proton);
  leg->AddEntry(h_p_proton, "p", "fl");
  canv->cd();
  canv->Clear();
  stack->Draw("hist");
  stack->GetYaxis()->SetTitle("Events / 10 MeV/c");
  stack->GetXaxis()->SetTitle("Reconstructed Momentum (MeV/c)");
  stack->GetYaxis()->CenterTitle();
  stack->GetXaxis()->CenterTitle();
  leg->Draw(); 
  Preliminary();
  canv->Write("MomentumStack");

  // Draw momentum
  TH1* h_p_all = (TH1*)h_p_kaon->Clone("p_all");
  h_p_all->Add(h_p_electron);
  h_p_all->Add(h_p_proton);
  h_p_all->Add(h_p_pimu);
  canv->cd();
  canv->Clear();
  h_p_all->SetFillColor(kAzure+2);
  h_p_all->SetLineColor(kAzure+2);
  h_p_all->Draw("hist");
  h_p_all->GetYaxis()->SetTitle("Events / 10 MeV/c");
  h_p_all->GetXaxis()->SetTitle("Reconstructed Momentum (MeV/c)");
  h_p_all->GetYaxis()->CenterTitle();
  h_p_all->GetXaxis()->CenterTitle();
  Preliminary();
  canv->Write("Momentum");

  // Draw time-of-flight
  tof.OverridePOT(1);
  TH1* h_tof = tof.ToTH1(tof.POT());
  canv->cd();
  canv->Clear();
  h_tof->SetFillColor(kAzure+2);
  h_tof->SetLineColor(kAzure+2);
  h_tof->Draw("hist");
  h_tof->GetYaxis()->SetTitle("Events");
  h_tof->GetXaxis()->SetTitle("Reconstructed Time-of-Flight (ns)");
  h_tof->GetYaxis()->CenterTitle();
  h_tof->GetXaxis()->CenterTitle();
  Preliminary();
  canv->Write("ToF");

  // Draw pid
  pid.OverridePOT(1);
  TH2* h_pid = pid.ToTH2(pid.POT());
  canv_wide->cd();
  canv_wide->Clear();
  h_pid->Draw("colz");
  h_pid->GetYaxis()->SetTitle("Reconstructed Momentum (GeV/c)");
  h_pid->GetXaxis()->SetTitle("Reconstructed Time-of-Flight (ns)");
  h_pid->GetYaxis()->CenterTitle();
  h_pid->GetXaxis()->CenterTitle();
  Preliminary();
  canv_wide->Write("PID");

  outFile->Close();

}
