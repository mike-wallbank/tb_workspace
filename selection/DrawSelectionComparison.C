// -----------------------------------------------
// DrawSelectionComparison.C
// Mike Wallbank (July 2022)
//
// Produce comparison plots between various
// selections.
// -----------------------------------------------

// framework
#include "CAFAna/Core/Spectrum.h"

// root
#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

// stl
#include <iostream>

using namespace ana;

// -----------------------------------------------
void DrawSelectionComparison() {

  TFile* inFile = TFile::Open("/pnfs/nova/scratch/users/wallbank/testbeam/data/selection/SelectionComparison.root", "READ");
  //TFile* inFile = TFile::Open("SelectionComparison.root", "READ");

  Spectrum p_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("p_proton_prong"), "p_proton_prong").release();
  Spectrum p_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("p_pimu_prong"), "p_pimu_prong").release();
  Spectrum p_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("p_electron_prong"), "p_electron_prong").release();
  Spectrum p_proton_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("p_proton_bpf"), "p_proton_bpf").release();
  Spectrum p_pimu_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("p_pimu_bpf"), "p_pimu_bpf").release();
  Spectrum p_electron_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("p_electron_bpf"), "p_electron_bpf").release();
  Spectrum p_proton_win = *Spectrum::LoadFrom(inFile->GetDirectory("p_proton_win"), "p_proton_win").release();
  Spectrum p_pimu_win = *Spectrum::LoadFrom(inFile->GetDirectory("p_pimu_win"), "p_pimu_win").release();
  Spectrum p_electron_win = *Spectrum::LoadFrom(inFile->GetDirectory("p_electron_win"), "p_electron_win").release();
  Spectrum p_proton_cos = *Spectrum::LoadFrom(inFile->GetDirectory("p_proton_cos"), "p_proton_cos").release();
  Spectrum p_pimu_cos = *Spectrum::LoadFrom(inFile->GetDirectory("p_pimu_cos"), "p_pimu_cos").release();
  Spectrum p_electron_cos = *Spectrum::LoadFrom(inFile->GetDirectory("p_electron_cos"), "p_electron_cos").release();

  Spectrum bpfprotonvalid_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfprotonvalid_proton_prong"), "bpfprotonvalid_proton_prong").release();
  Spectrum bpfprotonvalid_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfprotonvalid_pimu_prong"), "bpfprotonvalid_pimu_prong").release();
  Spectrum bpfprotonvalid_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfprotonvalid_electron_prong"), "bpfprotonvalid_electron_prong").release();
  Spectrum bpfpionvalid_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfpionvalid_proton_prong"), "bpfpionvalid_proton_prong").release();
  Spectrum bpfpionvalid_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfpionvalid_pimu_prong"), "bpfpionvalid_pimu_prong").release();
  Spectrum bpfpionvalid_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfpionvalid_electron_prong"), "bpfpionvalid_electron_prong").release();
  Spectrum bpfmuonvalid_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfmuonvalid_proton_prong"), "bpfmuonvalid_proton_prong").release();
  Spectrum bpfmuonvalid_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfmuonvalid_pimu_prong"), "bpfmuonvalid_pimu_prong").release();
  Spectrum bpfmuonvalid_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfmuonvalid_electron_prong"), "bpfmuonvalid_electron_prong").release();

  Spectrum pronge_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("pronge_proton_prong"), "pronge_proton_prong").release();
  Spectrum pronge_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("pronge_pimu_prong"), "pronge_pimu_prong").release();
  Spectrum pronge_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("pronge_electron_prong"), "pronge_electron_prong").release();
  Spectrum pronge_proton_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("pronge_proton_bpf"), "pronge_proton_bpf").release();
  Spectrum pronge_pimu_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("pronge_pimu_bpf"), "pronge_pimu_bpf").release();
  Spectrum pronge_electron_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("pronge_electron_bpf"), "pronge_electron_bpf").release();

  Spectrum bpfe_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfe_proton_prong"), "bpfe_proton_prong").release();
  Spectrum bpfe_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfe_pimu_prong"), "bpfe_pimu_prong").release();
  Spectrum bpfe_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfe_electron_prong"), "bpfe_electron_prong").release();
  Spectrum bpfe_proton_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpfe_proton_bpf"), "bpfe_proton_bpf").release();
  Spectrum bpfe_pimu_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpfe_pimu_bpf"), "bpfe_pimu_bpf").release();
  Spectrum bpfe_electron_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpfe_electron_bpf"), "bpfe_electron_bpf").release();

  Spectrum bpflen_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpflen_proton_prong"), "bpflen_proton_prong").release();
  Spectrum bpflen_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpflen_pimu_prong"), "bpflen_pimu_prong").release();
  Spectrum bpflen_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpflen_electron_prong"), "bpflen_electron_prong").release();
  Spectrum bpflen_proton_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpflen_proton_bpf"), "bpflen_proton_bpf").release();
  Spectrum bpflen_pimu_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpflen_pimu_bpf"), "bpflen_pimu_bpf").release();
  Spectrum bpflen_electron_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpflen_electron_bpf"), "bpflen_electron_bpf").release();

  Spectrum prongx_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongx_proton_prong"), "prongx_proton_prong").release();
  Spectrum prongy_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongy_proton_prong"), "prongy_proton_prong").release();
  Spectrum prongz_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongz_proton_prong"), "prongz_proton_prong").release();
  Spectrum prongx_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongx_pimu_prong"), "prongx_pimu_prong").release();
  Spectrum prongy_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongy_pimu_prong"), "prongy_pimu_prong").release();
  Spectrum prongz_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongz_pimu_prong"), "prongz_pimu_prong").release();
  Spectrum prongx_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongx_electron_prong"), "prongx_electron_prong").release();
  Spectrum prongy_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongy_electron_prong"), "prongy_electron_prong").release();
  Spectrum prongz_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongz_electron_prong"), "prongz_electron_prong").release();

  Spectrum bpfx_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfx_proton_prong"), "bpfx_proton_prong").release();
  Spectrum bpfy_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfy_proton_prong"), "bpfy_proton_prong").release();
  Spectrum bpfz_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfz_proton_prong"), "bpfz_proton_prong").release();
  Spectrum bpfx_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfx_pimu_prong"), "bpfx_pimu_prong").release();
  Spectrum bpfy_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfy_pimu_prong"), "bpfy_pimu_prong").release();
  Spectrum bpfz_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfz_pimu_prong"), "bpfz_pimu_prong").release();
  Spectrum bpfx_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfx_electron_prong"), "bpfx_electron_prong").release();
  Spectrum bpfy_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfy_electron_prong"), "bpfy_electron_prong").release();
  Spectrum bpfz_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("bpfz_electron_prong"), "bpfz_electron_prong").release();

  Spectrum prongvbpfx_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfx_proton_prong"), "prongvbpfx_proton_prong").release();
  Spectrum prongvbpfy_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfy_proton_prong"), "prongvbpfy_proton_prong").release();
  Spectrum prongvbpfz_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfz_proton_prong"), "prongvbpfz_proton_prong").release();
  Spectrum prongvbpfx_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfx_pimu_prong"), "prongvbpfx_pimu_prong").release();
  Spectrum prongvbpfy_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfy_pimu_prong"), "prongvbpfy_pimu_prong").release();
  Spectrum prongvbpfz_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfz_pimu_prong"), "prongvbpfz_pimu_prong").release();
  Spectrum prongvbpfx_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfx_electron_prong"), "prongvbpfx_electron_prong").release();
  Spectrum prongvbpfy_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfy_electron_prong"), "prongvbpfy_electron_prong").release();
  Spectrum prongvbpfz_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfz_electron_prong"), "prongvbpfz_electron_prong").release();

  Spectrum wintrklen_proton = *Spectrum::LoadFrom(inFile->GetDirectory("wintrklen_proton"), "wintrklen_proton").release();
  Spectrum wintrklen_pimu = *Spectrum::LoadFrom(inFile->GetDirectory("wintrklen_pimu"), "wintrklen_pimu").release();
  Spectrum wintrklen_electron = *Spectrum::LoadFrom(inFile->GetDirectory("wintrklen_electron"), "wintrklen_electron").release();
  Spectrum costrklen_proton = *Spectrum::LoadFrom(inFile->GetDirectory("costrklen_proton"), "costrklen_proton").release();
  Spectrum costrklen_pimu = *Spectrum::LoadFrom(inFile->GetDirectory("costrklen_pimu"), "costrklen_pimu").release();
  Spectrum costrklen_electron = *Spectrum::LoadFrom(inFile->GetDirectory("costrklen_electron"), "costrklen_electron").release();

  Spectrum bpfprotonlen_proton_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpfprotonlen_proton_bpf"), "bpfprotonlen_proton_bpf").release();
  Spectrum bpfprotonlen_pimu_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpfprotonlen_pimu_bpf"), "bpfprotonlen_pimu_bpf").release();
  Spectrum bpfprotonlen_electron_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpfprotonlen_electron_bpf"), "bpfprotonlen_electron_bpf").release();
  Spectrum bpfpionlen_proton_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpfpionlen_proton_bpf"), "bpfpionlen_proton_bpf").release();
  Spectrum bpfpionlen_pimu_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpfpionlen_pimu_bpf"), "bpfpionlen_pimu_bpf").release();
  Spectrum bpfpionlen_electron_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpfpionlen_electron_bpf"), "bpfpionlen_electron_bpf").release();
  Spectrum bpfmuonlen_proton_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpfmuonlen_proton_bpf"), "bpfmuonlen_proton_bpf").release();
  Spectrum bpfmuonlen_pimu_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpfmuonlen_pimu_bpf"), "bpfmuonlen_pimu_bpf").release();
  Spectrum bpfmuonlen_electron_bpf = *Spectrum::LoadFrom(inFile->GetDirectory("bpfmuonlen_electron_bpf"), "bpfmuonlen_electron_bpf").release();

  Spectrum singleprongx_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongx_proton_bl"), "singleprongx_proton_bl").release();
  Spectrum singleprongy_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongy_proton_bl"), "singleprongy_proton_bl").release();
  Spectrum singleprongz_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongz_proton_bl"), "singleprongz_proton_bl").release();
  Spectrum singleprongnhit_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongnhit_proton_bl"), "singleprongnhit_proton_bl").release();
  Spectrum singleprongx_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongx_pimu_bl"), "singleprongx_pimu_bl").release();
  Spectrum singleprongy_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongy_pimu_bl"), "singleprongy_pimu_bl").release();
  Spectrum singleprongz_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongz_pimu_bl"), "singleprongz_pimu_bl").release();
  Spectrum singleprongnhit_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongnhit_pimu_bl"), "singleprongnhit_pimu_bl").release();
  Spectrum singleprongx_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongx_electron_bl"), "singleprongx_electron_bl").release();
  Spectrum singleprongy_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongy_electron_bl"), "singleprongy_electron_bl").release();
  Spectrum singleprongz_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongz_electron_bl"), "singleprongz_electron_bl").release();
  Spectrum singleprongnhit_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongnhit_electron_bl"), "singleprongnhit_electron_bl").release();
  Spectrum singleprongbpfprotonx_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfprotonx_proton_bl"), "singleprongbpfprotonx_proton_bl").release();
  Spectrum singleprongbpfprotony_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfprotony_proton_bl"), "singleprongbpfprotony_proton_bl").release();
  Spectrum singleprongbpfprotonz_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfprotonz_proton_bl"), "singleprongbpfprotonz_proton_bl").release();
  Spectrum singleprongbpfprotonnhit_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfprotonnhit_proton_bl"), "singleprongbpfprotonnhit_proton_bl").release();
  Spectrum singleprongbpfprotonx_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfprotonx_pimu_bl"), "singleprongbpfprotonx_pimu_bl").release();
  Spectrum singleprongbpfprotony_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfprotony_pimu_bl"), "singleprongbpfprotony_pimu_bl").release();
  Spectrum singleprongbpfprotonz_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfprotonz_pimu_bl"), "singleprongbpfprotonz_pimu_bl").release();
  Spectrum singleprongbpfprotonnhit_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfprotonnhit_pimu_bl"), "singleprongbpfprotonnhit_pimu_bl").release();
  Spectrum singleprongbpfprotonx_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfprotonx_electron_bl"), "singleprongbpfprotonx_electron_bl").release();
  Spectrum singleprongbpfprotony_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfprotony_electron_bl"), "singleprongbpfprotony_electron_bl").release();
  Spectrum singleprongbpfprotonz_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfprotonz_electron_bl"), "singleprongbpfprotonz_electron_bl").release();
  Spectrum singleprongbpfprotonnhit_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfprotonnhit_electron_bl"), "singleprongbpfprotonnhit_electron_bl").release();
  Spectrum singleprongbpfpionx_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfpionx_proton_bl"), "singleprongbpfpionx_proton_bl").release();
  Spectrum singleprongbpfpiony_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfpiony_proton_bl"), "singleprongbpfpiony_proton_bl").release();
  Spectrum singleprongbpfpionz_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfpionz_proton_bl"), "singleprongbpfpionz_proton_bl").release();
  Spectrum singleprongbpfpionnhit_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfpionnhit_proton_bl"), "singleprongbpfpionnhit_proton_bl").release();
  Spectrum singleprongbpfpionx_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfpionx_pimu_bl"), "singleprongbpfpionx_pimu_bl").release();
  Spectrum singleprongbpfpiony_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfpiony_pimu_bl"), "singleprongbpfpiony_pimu_bl").release();
  Spectrum singleprongbpfpionz_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfpionz_pimu_bl"), "singleprongbpfpionz_pimu_bl").release();
  Spectrum singleprongbpfpionnhit_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfpionnhit_pimu_bl"), "singleprongbpfpionnhit_pimu_bl").release();
  Spectrum singleprongbpfpionx_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfpionx_electron_bl"), "singleprongbpfpionx_electron_bl").release();
  Spectrum singleprongbpfpiony_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfpiony_electron_bl"), "singleprongbpfpiony_electron_bl").release();
  Spectrum singleprongbpfpionz_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfpionz_electron_bl"), "singleprongbpfpionz_electron_bl").release();
  Spectrum singleprongbpfpionnhit_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfpionnhit_electron_bl"), "singleprongbpfpionnhit_electron_bl").release();
  Spectrum singleprongbpfmuonx_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfmuonx_proton_bl"), "singleprongbpfmuonx_proton_bl").release();
  Spectrum singleprongbpfmuony_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfmuony_proton_bl"), "singleprongbpfmuony_proton_bl").release();
  Spectrum singleprongbpfmuonz_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfmuonz_proton_bl"), "singleprongbpfmuonz_proton_bl").release();
  Spectrum singleprongbpfmuonnhit_proton_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfmuonnhit_proton_bl"), "singleprongbpfmuonnhit_proton_bl").release();
  Spectrum singleprongbpfmuonx_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfmuonx_pimu_bl"), "singleprongbpfmuonx_pimu_bl").release();
  Spectrum singleprongbpfmuony_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfmuony_pimu_bl"), "singleprongbpfmuony_pimu_bl").release();
  Spectrum singleprongbpfmuonz_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfmuonz_pimu_bl"), "singleprongbpfmuonz_pimu_bl").release();
  Spectrum singleprongbpfmuonnhit_pimu_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfmuonnhit_pimu_bl"), "singleprongbpfmuonnhit_pimu_bl").release();
  Spectrum singleprongbpfmuonx_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfmuonx_electron_bl"), "singleprongbpfmuonx_electron_bl").release();
  Spectrum singleprongbpfmuony_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfmuony_electron_bl"), "singleprongbpfmuony_electron_bl").release();
  Spectrum singleprongbpfmuonz_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfmuonz_electron_bl"), "singleprongbpfmuonz_electron_bl").release();
  Spectrum singleprongbpfmuonnhit_electron_bl = *Spectrum::LoadFrom(inFile->GetDirectory("singleprongbpfmuonnhit_electron_bl"), "singleprongbpfmuonnhit_electron_bl").release();

  inFile->Close();

  // Output file
  TFile* outFile = new TFile("SelectionComparisonAna.root", "RECREATE");

  // First, let's just see how many of each particle pass the selection
  p_proton_prong.OverridePOT(1);
  int n_proton_prong = p_proton_prong.ToTH1(p_proton_prong.POT())->Integral();
  p_pimu_prong.OverridePOT(1);
  int n_pimu_prong = p_pimu_prong.ToTH1(p_pimu_prong.POT())->Integral();
  p_electron_prong.OverridePOT(1);
  int n_electron_prong = p_electron_prong.ToTH1(p_electron_prong.POT())->Integral();
  p_proton_bpf.OverridePOT(1);
  int n_proton_bpf = p_proton_bpf.ToTH1(p_proton_bpf.POT())->Integral();
  p_pimu_bpf.OverridePOT(1);
  int n_pimu_bpf = p_pimu_bpf.ToTH1(p_pimu_bpf.POT())->Integral();
  p_electron_bpf.OverridePOT(1);
  int n_electron_bpf = p_electron_bpf.ToTH1(p_electron_bpf.POT())->Integral();
  p_proton_win.OverridePOT(1);
  int n_proton_win = p_proton_win.ToTH1(p_proton_win.POT())->Integral();
  p_pimu_win.OverridePOT(1);
  int n_pimu_win = p_pimu_win.ToTH1(p_pimu_win.POT())->Integral();
  p_electron_win.OverridePOT(1);
  int n_electron_win = p_electron_win.ToTH1(p_electron_win.POT())->Integral();
  p_proton_cos.OverridePOT(1);
  int n_proton_cos = p_proton_cos.ToTH1(p_proton_cos.POT())->Integral();
  p_pimu_cos.OverridePOT(1);
  int n_pimu_cos = p_pimu_cos.ToTH1(p_pimu_cos.POT())->Integral();
  p_electron_cos.OverridePOT(1);
  int n_electron_cos = p_electron_cos.ToTH1(p_electron_cos.POT())->Integral();
  std::cout << std::endl << "Beamline momentum..." << std::endl
            << "\t\tProng\tBPF\tWindow\tCosmic" << std::endl
            << "Proton\t\t" << n_proton_prong << "\t" << n_proton_bpf << "\t" << n_proton_win << "\t" << n_proton_cos << std::endl
            << "Pi/Mu\t\t" << n_pimu_prong << "\t" << n_pimu_bpf << "\t" << n_pimu_win << "\t" << n_pimu_cos << std::endl
            << "Electron\t" << n_electron_prong << "\t" << n_electron_bpf << "\t" << n_electron_win << "\t" << n_electron_cos << std::endl;

  // Confirm that we have the same number of entries in prong energy
  pronge_proton_prong.OverridePOT(1);
  int n_pronge_proton_prong = pronge_proton_prong.ToTH1(pronge_proton_prong.POT())->Integral();
  pronge_pimu_prong.OverridePOT(1);
  int n_pronge_pimu_prong = pronge_pimu_prong.ToTH1(pronge_pimu_prong.POT())->Integral();
  pronge_electron_prong.OverridePOT(1);
  int n_pronge_electron_prong = pronge_electron_prong.ToTH1(pronge_electron_prong.POT())->Integral();
  pronge_proton_bpf.OverridePOT(1);
  int n_pronge_proton_bpf = pronge_proton_bpf.ToTH1(pronge_proton_bpf.POT())->Integral();
  pronge_pimu_bpf.OverridePOT(1);
  int n_pronge_pimu_bpf = pronge_pimu_bpf.ToTH1(pronge_pimu_bpf.POT())->Integral();
  pronge_electron_bpf.OverridePOT(1);
  int n_pronge_electron_bpf = pronge_electron_bpf.ToTH1(pronge_electron_bpf.POT())->Integral();
  std::cout << std::endl << "Prong energy..." << std::endl
            << "\t\tProng selection\tBPF selection" << std::endl
            << "Proton\t\t" << n_pronge_proton_prong << "\t\t" << n_pronge_proton_bpf << std::endl
            << "Pi/Mu\t\t" << n_pronge_pimu_prong << "\t\t" << n_pronge_pimu_bpf << std::endl
            << "Electron\t" << n_pronge_electron_prong << "\t\t" << n_pronge_electron_bpf << std::endl;

  // Let's see what happens when we look at BPF energy
  bpfe_proton_prong.OverridePOT(1);
  int n_bpfe_proton_prong = bpfe_proton_prong.ToTH1(bpfe_proton_prong.POT())->Integral();
  bpfe_pimu_prong.OverridePOT(1);
  int n_bpfe_pimu_prong = bpfe_pimu_prong.ToTH1(bpfe_pimu_prong.POT())->Integral();
  bpfe_electron_prong.OverridePOT(1);
  int n_bpfe_electron_prong = bpfe_electron_prong.ToTH1(bpfe_electron_prong.POT())->Integral();
  bpfe_proton_bpf.OverridePOT(1);
  int n_bpfe_proton_bpf = bpfe_proton_bpf.ToTH1(bpfe_proton_bpf.POT())->Integral();
  bpfe_pimu_bpf.OverridePOT(1);
  int n_bpfe_pimu_bpf = bpfe_pimu_bpf.ToTH1(bpfe_pimu_bpf.POT())->Integral();
  bpfe_electron_bpf.OverridePOT(1);
  int n_bpfe_electron_bpf = bpfe_electron_bpf.ToTH1(bpfe_electron_bpf.POT())->Integral();
  std::cout << std::endl << "BPF energy..." << std::endl
            << "\t\tProng selection\tBPF selection" << std::endl
            << "Proton\t\t" << n_bpfe_proton_prong << "\t\t" << n_bpfe_proton_bpf << std::endl
            << "Pi/Mu\t\t" << n_bpfe_pimu_prong << "\t\t" << n_bpfe_pimu_bpf << std::endl
            << "Electron\t" << n_bpfe_electron_prong << "\t\t" << n_bpfe_electron_bpf << std::endl;

  // Plots of length
  TCanvas* canv = new TCanvas("canv", "", 800, 600);
  TLegend* leg = new TLegend(0.7, 0.7, 0.85, 0.85);

  canv->cd();
  bpflen_proton_prong.OverridePOT(1);
  TH1* h_bpflen_proton_prong = bpflen_proton_prong.ToTH1(bpflen_proton_prong.POT());
  h_bpflen_proton_prong->SetLineColor(kBlack);
  h_bpflen_proton_prong->Draw("hist");
  leg->AddEntry(h_bpflen_proton_prong, "BPF, Prong Sel", "l");
  bpflen_proton_bpf.OverridePOT(1);
  TH1* h_bpflen_proton_bpf = bpflen_proton_bpf.ToTH1(bpflen_proton_bpf.POT());
  h_bpflen_proton_bpf->SetLineColor(kRed);
  h_bpflen_proton_bpf->Draw("hist same");
  leg->AddEntry(h_bpflen_proton_bpf, "BPF, BPF Sel", "l");
  wintrklen_proton.OverridePOT(1);
  TH1* h_wintrklen_proton = wintrklen_proton.ToTH1(wintrklen_proton.POT());
  h_wintrklen_proton->SetLineColor(kBlue);
  h_wintrklen_proton->Draw("hist same");
  leg->AddEntry(h_wintrklen_proton, "WinTrk", "l");
  costrklen_proton.OverridePOT(1);
  TH1* h_costrklen_proton = costrklen_proton.ToTH1(costrklen_proton.POT());
  h_costrklen_proton->SetLineColor(kGreen+2);
  h_costrklen_proton->Draw("hist same");
  leg->AddEntry(h_costrklen_proton, "CosTrk", "l");
  leg->Draw();
  outFile->cd();
  canv->Write("ProtonLength");

  canv->cd();
  canv->Clear();
  leg->Clear();
  bpflen_pimu_prong.OverridePOT(1);
  TH1* h_bpflen_pimu_prong = bpflen_pimu_prong.ToTH1(bpflen_pimu_prong.POT());
  h_bpflen_pimu_prong->SetLineColor(kBlack);
  h_bpflen_pimu_prong->Draw("hist");
  leg->AddEntry(h_bpflen_pimu_prong, "BPF, Prong Sel", "l");
  bpflen_pimu_bpf.OverridePOT(1);
  TH1* h_bpflen_pimu_bpf = bpflen_pimu_bpf.ToTH1(bpflen_pimu_bpf.POT());
  h_bpflen_pimu_bpf->SetLineColor(kRed);
  h_bpflen_pimu_bpf->Draw("hist same");
  leg->AddEntry(h_bpflen_pimu_bpf, "BPF, BPF Sel", "l");
  wintrklen_pimu.OverridePOT(1);
  TH1* h_wintrklen_pimu = wintrklen_pimu.ToTH1(wintrklen_pimu.POT());
  h_wintrklen_pimu->SetLineColor(kBlue);
  h_wintrklen_pimu->Draw("hist same");
  leg->AddEntry(h_wintrklen_pimu, "WinTrk", "l");
  costrklen_pimu.OverridePOT(1);
  TH1* h_costrklen_pimu = costrklen_pimu.ToTH1(costrklen_pimu.POT());
  h_costrklen_pimu->SetLineColor(kGreen+2);
  h_costrklen_pimu->Draw("hist same");
  leg->AddEntry(h_costrklen_pimu, "CosTrk", "l");
  leg->Draw();
  outFile->cd();
  canv->Write("PiMuLength");

  canv->cd();
  canv->Clear();
  leg->Clear();
  bpflen_electron_prong.OverridePOT(1);
  TH1* h_bpflen_electron_prong = bpflen_electron_prong.ToTH1(bpflen_electron_prong.POT());
  h_bpflen_electron_prong->SetLineColor(kBlack);
  h_bpflen_electron_prong->Draw("hist");
  leg->AddEntry(h_bpflen_electron_prong, "BPF, Prong Sel", "l");
  bpflen_electron_bpf.OverridePOT(1);
  TH1* h_bpflen_electron_bpf = bpflen_electron_bpf.ToTH1(bpflen_electron_bpf.POT());
  h_bpflen_electron_bpf->SetLineColor(kRed);
  h_bpflen_electron_bpf->Draw("hist same");
  leg->AddEntry(h_bpflen_electron_bpf, "BPF, BPF Sel", "l");
  wintrklen_electron.OverridePOT(1);
  TH1* h_wintrklen_electron = wintrklen_electron.ToTH1(wintrklen_electron.POT());
  h_wintrklen_electron->SetLineColor(kBlue);
  h_wintrklen_electron->Draw("hist same");
  leg->AddEntry(h_wintrklen_electron, "WinTrk", "l");
  costrklen_electron.OverridePOT(1);
  TH1* h_costrklen_electron = costrklen_electron.ToTH1(costrklen_electron.POT());
  h_costrklen_electron->SetLineColor(kGreen+2);
  h_costrklen_electron->Draw("hist same");
  leg->AddEntry(h_costrklen_electron, "CosTrk", "l");
  leg->Draw();
  outFile->cd();
  canv->Write("ElectronLength");

  // Plot lengths for different BPF hypotheses
  canv->cd();
  canv->Clear();
  leg->Clear();
  bpfprotonlen_proton_bpf.OverridePOT(1);
  TH1* h_bpfprotonlen_proton_bpf = bpfprotonlen_proton_bpf.ToTH1(bpfprotonlen_proton_bpf.POT());
  h_bpfprotonlen_proton_bpf->SetLineColor(kBlack);
  h_bpfprotonlen_proton_bpf->Draw("hist");
  leg->AddEntry(h_bpfprotonlen_proton_bpf, "Proton Hypothesis", "l");
  bpfpionlen_proton_bpf.OverridePOT(1);
  TH1* h_bpfpionlen_proton_bpf = bpfpionlen_proton_bpf.ToTH1(bpfpionlen_proton_bpf.POT());
  h_bpfpionlen_proton_bpf->SetLineColor(kRed);
  h_bpfpionlen_proton_bpf->Draw("hist same");
  leg->AddEntry(h_bpfpionlen_proton_bpf, "Pion Hypothesis", "l");
  bpfmuonlen_proton_bpf.OverridePOT(1);
  TH1* h_bpfmuonlen_proton_bpf = bpfmuonlen_proton_bpf.ToTH1(bpfmuonlen_proton_bpf.POT());
  h_bpfmuonlen_proton_bpf->SetLineColor(kBlue);
  h_bpfmuonlen_proton_bpf->Draw("hist same");
  leg->AddEntry(h_bpfmuonlen_proton_bpf, "Muon Hypothesis", "l");
  leg->Draw();
  outFile->cd();
  canv->Write("SelProtonLength");

  canv->cd();
  canv->Clear();
  leg->Clear();
  bpfprotonlen_pimu_bpf.OverridePOT(1);
  TH1* h_bpfprotonlen_pimu_bpf = bpfprotonlen_pimu_bpf.ToTH1(bpfprotonlen_pimu_bpf.POT());
  h_bpfprotonlen_pimu_bpf->SetLineColor(kBlack);
  h_bpfprotonlen_pimu_bpf->Draw("hist");
  leg->AddEntry(h_bpfprotonlen_pimu_bpf, "Proton Hypothesis", "l");
  bpfpionlen_pimu_bpf.OverridePOT(1);
  TH1* h_bpfpionlen_pimu_bpf = bpfpionlen_pimu_bpf.ToTH1(bpfpionlen_pimu_bpf.POT());
  h_bpfpionlen_pimu_bpf->SetLineColor(kRed);
  h_bpfpionlen_pimu_bpf->Draw("hist same");
  leg->AddEntry(h_bpfpionlen_pimu_bpf, "Pion Hypothesis", "l");
  bpfmuonlen_pimu_bpf.OverridePOT(1);
  TH1* h_bpfmuonlen_pimu_bpf = bpfmuonlen_pimu_bpf.ToTH1(bpfmuonlen_pimu_bpf.POT());
  h_bpfmuonlen_pimu_bpf->SetLineColor(kBlue);
  h_bpfmuonlen_pimu_bpf->Draw("hist same");
  leg->AddEntry(h_bpfmuonlen_pimu_bpf, "Muon Hypothesis", "l");
  leg->Draw();
  outFile->cd();
  canv->Write("SelPiMuLength");

  canv->cd();
  canv->Clear();
  leg->Clear();
  bpfprotonlen_electron_bpf.OverridePOT(1);
  TH1* h_bpfprotonlen_electron_bpf = bpfprotonlen_electron_bpf.ToTH1(bpfprotonlen_electron_bpf.POT());
  h_bpfprotonlen_electron_bpf->SetLineColor(kBlack);
  h_bpfprotonlen_electron_bpf->Draw("hist");
  leg->AddEntry(h_bpfprotonlen_electron_bpf, "Proton Hypothesis", "l");
  bpfpionlen_electron_bpf.OverridePOT(1);
  TH1* h_bpfpionlen_electron_bpf = bpfpionlen_electron_bpf.ToTH1(bpfpionlen_electron_bpf.POT());
  h_bpfpionlen_electron_bpf->SetLineColor(kRed);
  h_bpfpionlen_electron_bpf->Draw("hist same");
  leg->AddEntry(h_bpfpionlen_electron_bpf, "Pion Hypothesis", "l");
  bpfmuonlen_electron_bpf.OverridePOT(1);
  TH1* h_bpfmuonlen_electron_bpf = bpfmuonlen_electron_bpf.ToTH1(bpfmuonlen_electron_bpf.POT());
  h_bpfmuonlen_electron_bpf->SetLineColor(kBlue);
  h_bpfmuonlen_electron_bpf->Draw("hist same");
  leg->AddEntry(h_bpfmuonlen_electron_bpf, "Muon Hypothesis", "l");
  leg->Draw();
  outFile->cd();
  canv->Write("SelElectronLength");

  // Look at prong vs BPF vertex
  canv->cd();
  canv->Clear();
  leg->Clear();
  prongx_pimu_prong.OverridePOT(1);
  TH1* h_prongx_pimu_prong = prongx_pimu_prong.ToTH1(prongx_pimu_prong.POT());
  h_prongx_pimu_prong->SetLineColor(kRed);
  h_prongx_pimu_prong->SetLineStyle(kSolid);
  h_prongx_pimu_prong->GetXaxis()->SetTitle("x (cm)");
  h_prongx_pimu_prong->Draw("hist");
  leg->AddEntry(h_prongx_pimu_prong, "#{pi}/#{mu} Prong");
  bpfx_pimu_prong.OverridePOT(1);
  TH1* h_bpfx_pimu_prong = bpfx_pimu_prong.ToTH1(bpfx_pimu_prong.POT());
  h_bpfx_pimu_prong->SetLineColor(kRed);
  h_bpfx_pimu_prong->SetLineStyle(kDashed);
  h_bpfx_pimu_prong->Draw("hist same");
  leg->AddEntry(h_bpfx_pimu_prong, "#{pi}/#{mu} BPF");
  prongx_proton_prong.OverridePOT(1);
  TH1* h_prongx_proton_prong = prongx_proton_prong.ToTH1(prongx_proton_prong.POT());
  h_prongx_proton_prong->SetLineColor(kBlack);
  h_prongx_proton_prong->SetLineStyle(kSolid);
  h_prongx_proton_prong->GetXaxis()->SetTitle("x (cm)");
  h_prongx_proton_prong->Draw("hist same");
  leg->AddEntry(h_prongx_proton_prong, "Proton Prong");
  bpfx_proton_prong.OverridePOT(1);
  TH1* h_bpfx_proton_prong = bpfx_proton_prong.ToTH1(bpfx_proton_prong.POT());
  h_bpfx_proton_prong->SetLineColor(kBlack);
  h_bpfx_proton_prong->SetLineStyle(kDashed);
  h_bpfx_proton_prong->Draw("hist same");
  leg->AddEntry(h_bpfx_proton_prong, "Proton BPF");
  prongx_electron_prong.OverridePOT(1);
  TH1* h_prongx_electron_prong = prongx_electron_prong.ToTH1(prongx_electron_prong.POT());
  h_prongx_electron_prong->SetLineColor(kBlue);
  h_prongx_electron_prong->SetLineStyle(kSolid);
  h_prongx_electron_prong->GetXaxis()->SetTitle("x (cm)");
  h_prongx_electron_prong->Draw("hist same");
  leg->AddEntry(h_prongx_electron_prong, "Electron Prong");
  bpfx_electron_prong.OverridePOT(1);
  TH1* h_bpfx_electron_prong = bpfx_electron_prong.ToTH1(bpfx_electron_prong.POT());
  h_bpfx_electron_prong->SetLineColor(kBlue);
  h_bpfx_electron_prong->SetLineStyle(kDashed);
  h_bpfx_electron_prong->Draw("hist same");
  leg->AddEntry(h_bpfx_electron_prong, "Electron BPF");
  leg->Draw();
  outFile->cd();
  canv->Write("VertexX");

  canv->cd();
  canv->Clear();
  leg->Clear();
  prongy_pimu_prong.OverridePOT(1);
  TH1* h_prongy_pimu_prong = prongy_pimu_prong.ToTH1(prongy_pimu_prong.POT());
  h_prongy_pimu_prong->SetLineColor(kRed);
  h_prongy_pimu_prong->SetLineStyle(kSolid);
  h_prongy_pimu_prong->GetXaxis()->SetTitle("y (cm)");
  h_prongy_pimu_prong->Draw("hist");
  leg->AddEntry(h_prongy_pimu_prong, "#{pi}/#{mu} Prong");
  bpfy_pimu_prong.OverridePOT(1);
  TH1* h_bpfy_pimu_prong = bpfy_pimu_prong.ToTH1(bpfy_pimu_prong.POT());
  h_bpfy_pimu_prong->SetLineColor(kRed);
  h_bpfy_pimu_prong->SetLineStyle(kDashed);
  h_bpfy_pimu_prong->Draw("hist same");
  leg->AddEntry(h_bpfy_pimu_prong, "#{pi}/#{mu} BPF");
  prongy_proton_prong.OverridePOT(1);
  TH1* h_prongy_proton_prong = prongy_proton_prong.ToTH1(prongy_proton_prong.POT());
  h_prongy_proton_prong->SetLineColor(kBlack);
  h_prongy_proton_prong->SetLineStyle(kSolid);
  h_prongy_proton_prong->GetXaxis()->SetTitle("y (cm)");
  h_prongy_proton_prong->Draw("hist same");
  leg->AddEntry(h_prongy_proton_prong, "Proton Prong");
  bpfy_proton_prong.OverridePOT(1);
  TH1* h_bpfy_proton_prong = bpfy_proton_prong.ToTH1(bpfy_proton_prong.POT());
  h_bpfy_proton_prong->SetLineColor(kBlack);
  h_bpfy_proton_prong->SetLineStyle(kDashed);
  h_bpfy_proton_prong->Draw("hist same");
  leg->AddEntry(h_bpfy_proton_prong, "Proton BPF");
  prongy_electron_prong.OverridePOT(1);
  TH1* h_prongy_electron_prong = prongy_electron_prong.ToTH1(prongy_electron_prong.POT());
  h_prongy_electron_prong->SetLineColor(kBlue);
  h_prongy_electron_prong->SetLineStyle(kSolid);
  h_prongy_electron_prong->GetXaxis()->SetTitle("y (cm)");
  h_prongy_electron_prong->Draw("hist same");
  leg->AddEntry(h_prongy_electron_prong, "Electron Prong");
  bpfy_electron_prong.OverridePOT(1);
  TH1* h_bpfy_electron_prong = bpfy_electron_prong.ToTH1(bpfy_electron_prong.POT());
  h_bpfy_electron_prong->SetLineColor(kBlue);
  h_bpfy_electron_prong->SetLineStyle(kDashed);
  h_bpfy_electron_prong->Draw("hist same");
  leg->AddEntry(h_bpfy_electron_prong, "Electron BPF");
  leg->Draw();
  outFile->cd();
  canv->Write("VertexY");

  canv->cd();
  canv->Clear();
  leg->Clear();
  prongz_pimu_prong.OverridePOT(1);
  TH1* h_prongz_pimu_prong = prongz_pimu_prong.ToTH1(prongz_pimu_prong.POT());
  h_prongz_pimu_prong->SetLineColor(kRed);
  h_prongz_pimu_prong->SetLineStyle(kSolid);
  h_prongz_pimu_prong->GetXaxis()->SetTitle("z (cm)");
  h_prongz_pimu_prong->Draw("hist");
  leg->AddEntry(h_prongz_pimu_prong, "#{pi}/#{mu} Prong");
  bpfz_pimu_prong.OverridePOT(1);
  TH1* h_bpfz_pimu_prong = bpfz_pimu_prong.ToTH1(bpfz_pimu_prong.POT());
  h_bpfz_pimu_prong->SetLineColor(kRed);
  h_bpfz_pimu_prong->SetLineStyle(kDashed);
  h_bpfz_pimu_prong->Draw("hist same");
  leg->AddEntry(h_bpfz_pimu_prong, "#{pi}/#{mu} BPF");
  prongz_proton_prong.OverridePOT(1);
  TH1* h_prongz_proton_prong = prongz_proton_prong.ToTH1(prongz_proton_prong.POT());
  h_prongz_proton_prong->SetLineColor(kBlack);
  h_prongz_proton_prong->SetLineStyle(kSolid);
  h_prongz_proton_prong->GetXaxis()->SetTitle("z (cm)");
  h_prongz_proton_prong->Draw("hist same");
  leg->AddEntry(h_prongz_proton_prong, "Proton Prong");
  bpfz_proton_prong.OverridePOT(1);
  TH1* h_bpfz_proton_prong = bpfz_proton_prong.ToTH1(bpfz_proton_prong.POT());
  h_bpfz_proton_prong->SetLineColor(kBlack);
  h_bpfz_proton_prong->SetLineStyle(kDashed);
  h_bpfz_proton_prong->Draw("hist same");
  leg->AddEntry(h_bpfz_proton_prong, "Proton BPF");
  prongz_electron_prong.OverridePOT(1);
  TH1* h_prongz_electron_prong = prongz_electron_prong.ToTH1(prongz_electron_prong.POT());
  h_prongz_electron_prong->SetLineColor(kBlue);
  h_prongz_electron_prong->SetLineStyle(kSolid);
  h_prongz_electron_prong->GetXaxis()->SetTitle("z (cm)");
  h_prongz_electron_prong->Draw("hist same");
  leg->AddEntry(h_prongz_electron_prong, "Electron Prong");
  bpfz_electron_prong.OverridePOT(1);
  TH1* h_bpfz_electron_prong = bpfz_electron_prong.ToTH1(bpfz_electron_prong.POT());
  h_bpfz_electron_prong->SetLineColor(kBlue);
  h_bpfz_electron_prong->SetLineStyle(kDashed);
  h_bpfz_electron_prong->Draw("hist same");
  leg->AddEntry(h_bpfz_electron_prong, "Electron BPF");
  leg->Draw();
  outFile->cd();
  canv->Write("VertexZ");

  // Spectrum prongvbpfx_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfx_proton_prong"), "prongvbpfx_proton_prong").release();
  // Spectrum prongvbpfy_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfy_proton_prong"), "prongvbpfy_proton_prong").release();
  // Spectrum prongvbpfz_proton_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfz_proton_prong"), "prongvbpfz_proton_prong").release();
  // Spectrum prongvbpfx_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfx_pimu_prong"), "prongvbpfx_pimu_prong").release();
  // Spectrum prongvbpfy_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfy_pimu_prong"), "prongvbpfy_pimu_prong").release();
  // Spectrum prongvbpfz_pimu_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfz_pimu_prong"), "prongvbpfz_pimu_prong").release();
  // Spectrum prongvbpfx_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfx_electron_prong"), "prongvbpfx_electron_prong").release();
  // Spectrum prongvbpfy_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfy_electron_prong"), "prongvbpfy_electron_prong").release();
  // Spectrum prongvbpfz_electron_prong = *Spectrum::LoadFrom(inFile->GetDirectory("prongvbpfz_electron_prong"), "prongvbpfz_electron_prong").release();

  // Pring some length numbers for sanity
  int n_bpflen_proton_prong = h_bpflen_proton_prong->Integral();
  int n_bpflen_pimu_prong = h_bpflen_pimu_prong->Integral();
  int n_bpflen_electron_prong = h_bpflen_electron_prong->Integral();
  int n_bpflen_proton_bpf = h_bpflen_proton_bpf->Integral();
  int n_bpflen_pimu_bpf = h_bpflen_pimu_bpf->Integral();
  int n_bpflen_electron_bpf = h_bpflen_electron_bpf->Integral();
  std::cout << std::endl << "BPF length..." << std::endl
            << "\t\tProng selection\tBPF selection" << std::endl
            << "Proton\t\t" << n_bpflen_proton_prong << "\t\t" << n_bpflen_proton_bpf << std::endl
            << "Pi/Mu\t\t" << n_bpflen_pimu_prong << "\t\t" << n_bpflen_pimu_bpf << std::endl
            << "Electron\t" << n_bpflen_electron_prong << "\t\t" << n_bpflen_electron_bpf << std::endl;

  // And the x,y,z coords
  int n_prongx_proton_prong = h_prongx_proton_prong->Integral();
  int n_prongx_pimu_prong = h_prongx_pimu_prong->Integral();
  int n_prongx_electron_prong = h_prongx_electron_prong->Integral();
  int n_bpfx_proton_prong = h_bpfx_proton_prong->Integral();
  int n_bpfx_proton_prong_cut = h_bpfx_proton_prong->Integral(h_bpfx_proton_prong->FindBin(-20), h_bpfx_proton_prong->FindBin(20));
  int n_bpfx_pimu_prong = h_bpfx_pimu_prong->Integral();
  int n_bpfx_pimu_prong_cut = h_bpfx_pimu_prong->Integral(h_bpfx_pimu_prong->FindBin(-20), h_bpfx_pimu_prong->FindBin(20));
  int n_bpfx_electron_prong = h_bpfx_electron_prong->Integral();
  int n_bpfx_electron_prong_cut = h_bpfx_electron_prong->Integral(h_bpfx_electron_prong->FindBin(-20), h_bpfx_electron_prong->FindBin(20));
  int n_prongy_proton_prong = h_prongy_proton_prong->Integral();
  int n_prongy_pimu_prong = h_prongy_pimu_prong->Integral();
  int n_prongy_electron_prong = h_prongy_electron_prong->Integral();
  int n_bpfy_proton_prong = h_bpfy_proton_prong->Integral();
  int n_bpfy_proton_prong_cut = h_bpfy_proton_prong->Integral(h_bpfy_proton_prong->FindBin(-25), h_bpfy_proton_prong->FindBin(15));
  int n_bpfy_pimu_prong = h_bpfy_pimu_prong->Integral();
  int n_bpfy_pimu_prong_cut = h_bpfy_pimu_prong->Integral(h_bpfy_pimu_prong->FindBin(-25), h_bpfy_pimu_prong->FindBin(15));
  int n_bpfy_electron_prong = h_bpfy_electron_prong->Integral();
  int n_bpfy_electron_prong_cut = h_bpfy_electron_prong->Integral(h_bpfy_electron_prong->FindBin(-25), h_bpfy_electron_prong->FindBin(15));
  int n_prongz_proton_prong = h_prongz_proton_prong->Integral();
  int n_prongz_pimu_prong = h_prongz_pimu_prong->Integral();
  int n_prongz_electron_prong = h_prongz_electron_prong->Integral();
  int n_bpfz_proton_prong = h_bpfz_proton_prong->Integral();
  int n_bpfz_proton_prong_cut = h_bpfz_proton_prong->Integral(h_bpfz_proton_prong->FindBin(0), h_bpfz_proton_prong->FindBin(18));
  int n_bpfz_pimu_prong = h_bpfz_pimu_prong->Integral();
  int n_bpfz_pimu_prong_cut = h_bpfz_pimu_prong->Integral(h_bpfz_pimu_prong->FindBin(0), h_bpfz_pimu_prong->FindBin(18));
  int n_bpfz_electron_prong = h_bpfz_electron_prong->Integral();
  int n_bpfz_electron_prong_cut = h_bpfz_electron_prong->Integral(h_bpfz_electron_prong->FindBin(0), h_bpfz_electron_prong->FindBin(18));
  std::cout << std::endl << "Vertex..." << std::endl
            << "\t\tProng\t\t\tBPF\t\t\tBPF (selection)" << std::endl
            << "Proton\t\t" << n_prongx_proton_prong << "," << n_prongy_proton_prong << "," << n_prongx_proton_prong
            << "\t\t" << n_bpfx_proton_prong << "," << n_bpfy_proton_prong << "," << n_bpfz_proton_prong
            << "\t\t" << n_bpfx_proton_prong_cut << "," << n_bpfy_proton_prong_cut << "," << n_bpfz_proton_prong_cut << std::endl
            << "Pi/Mu\t\t" << n_prongx_pimu_prong << "," << n_prongy_pimu_prong << "," << n_prongx_pimu_prong
            << "\t" << n_bpfx_pimu_prong << "," << n_bpfy_pimu_prong << "," << n_bpfz_pimu_prong
            << "\t" << n_bpfx_pimu_prong_cut << "," << n_bpfy_pimu_prong_cut << "," << n_bpfz_pimu_prong_cut << std::endl
            << "Electron\t" << n_prongx_electron_prong << "," << n_prongy_electron_prong << "," << n_prongx_electron_prong
            << "\t\t" << n_bpfx_electron_prong << "," << n_bpfy_electron_prong << "," << n_bpfz_electron_prong
            << "\t\t" << n_bpfx_electron_prong_cut << "," << n_bpfy_electron_prong_cut << "," << n_bpfz_electron_prong_cut << std::endl;

  // Print some validity stuff
  bpfprotonvalid_proton_prong.OverridePOT(1);
  TH1* h_bpfprotonvalid_proton_prong = bpfprotonvalid_proton_prong.ToTH1(bpfprotonvalid_proton_prong.POT());
  int n_bpfprotonvalid_proton_prong = h_bpfprotonvalid_proton_prong->Integral();
  int n0_bpfprotonvalid_proton_prong = h_bpfprotonvalid_proton_prong->GetBinContent(1);
  int n1_bpfprotonvalid_proton_prong = h_bpfprotonvalid_proton_prong->GetBinContent(2);
  bpfprotonvalid_pimu_prong.OverridePOT(1);
  TH1* h_bpfprotonvalid_pimu_prong = bpfprotonvalid_pimu_prong.ToTH1(bpfprotonvalid_pimu_prong.POT());
  int n_bpfprotonvalid_pimu_prong = h_bpfprotonvalid_pimu_prong->Integral();
  int n0_bpfprotonvalid_pimu_prong = h_bpfprotonvalid_pimu_prong->GetBinContent(1);
  int n1_bpfprotonvalid_pimu_prong = h_bpfprotonvalid_pimu_prong->GetBinContent(2);
  bpfprotonvalid_electron_prong.OverridePOT(1);
  TH1* h_bpfprotonvalid_electron_prong = bpfprotonvalid_electron_prong.ToTH1(bpfprotonvalid_electron_prong.POT());
  int n_bpfprotonvalid_electron_prong = h_bpfprotonvalid_electron_prong->Integral();
  int n0_bpfprotonvalid_electron_prong = h_bpfprotonvalid_electron_prong->GetBinContent(1);
  int n1_bpfprotonvalid_electron_prong = h_bpfprotonvalid_electron_prong->GetBinContent(2);
  bpfpionvalid_proton_prong.OverridePOT(1);
  TH1* h_bpfpionvalid_proton_prong = bpfpionvalid_proton_prong.ToTH1(bpfpionvalid_proton_prong.POT());
  int n_bpfpionvalid_proton_prong = h_bpfpionvalid_proton_prong->Integral();
  int n0_bpfpionvalid_proton_prong = h_bpfpionvalid_proton_prong->GetBinContent(1);
  int n1_bpfpionvalid_proton_prong = h_bpfpionvalid_proton_prong->GetBinContent(2);
  bpfpionvalid_pimu_prong.OverridePOT(1);
  TH1* h_bpfpionvalid_pimu_prong = bpfpionvalid_pimu_prong.ToTH1(bpfpionvalid_pimu_prong.POT());
  int n_bpfpionvalid_pimu_prong = h_bpfpionvalid_pimu_prong->Integral();
  int n0_bpfpionvalid_pimu_prong = h_bpfpionvalid_pimu_prong->GetBinContent(1);
  int n1_bpfpionvalid_pimu_prong = h_bpfpionvalid_pimu_prong->GetBinContent(2);
  bpfpionvalid_electron_prong.OverridePOT(1);
  TH1* h_bpfpionvalid_electron_prong = bpfpionvalid_electron_prong.ToTH1(bpfpionvalid_electron_prong.POT());
  int n_bpfpionvalid_electron_prong = h_bpfpionvalid_electron_prong->Integral();
  int n0_bpfpionvalid_electron_prong = h_bpfpionvalid_electron_prong->GetBinContent(1);
  int n1_bpfpionvalid_electron_prong = h_bpfpionvalid_electron_prong->GetBinContent(2);
  bpfmuonvalid_proton_prong.OverridePOT(1);
  TH1* h_bpfmuonvalid_proton_prong = bpfmuonvalid_proton_prong.ToTH1(bpfmuonvalid_proton_prong.POT());
  int n_bpfmuonvalid_proton_prong = h_bpfmuonvalid_proton_prong->Integral();
  int n0_bpfmuonvalid_proton_prong = h_bpfmuonvalid_proton_prong->GetBinContent(1);
  int n1_bpfmuonvalid_proton_prong = h_bpfmuonvalid_proton_prong->GetBinContent(2);
  bpfmuonvalid_pimu_prong.OverridePOT(1);
  TH1* h_bpfmuonvalid_pimu_prong = bpfmuonvalid_pimu_prong.ToTH1(bpfmuonvalid_pimu_prong.POT());
  int n_bpfmuonvalid_pimu_prong = h_bpfmuonvalid_pimu_prong->Integral();
  int n0_bpfmuonvalid_pimu_prong = h_bpfmuonvalid_pimu_prong->GetBinContent(1);
  int n1_bpfmuonvalid_pimu_prong = h_bpfmuonvalid_pimu_prong->GetBinContent(2);
  bpfmuonvalid_electron_prong.OverridePOT(1);
  TH1* h_bpfmuonvalid_electron_prong = bpfmuonvalid_electron_prong.ToTH1(bpfmuonvalid_electron_prong.POT());
  int n_bpfmuonvalid_electron_prong = h_bpfmuonvalid_electron_prong->Integral();
  int n0_bpfmuonvalid_electron_prong = h_bpfmuonvalid_electron_prong->GetBinContent(1);
  int n1_bpfmuonvalid_electron_prong = h_bpfmuonvalid_electron_prong->GetBinContent(2);
  std::cout << std::endl << "BPF validity..." << std::endl
            << "\t\tProton Hypothesis\tPion Hypothesis\t\tMuon Hypothesis" << std::endl
            << "Proton\t\t" << n_bpfprotonvalid_proton_prong << " (" << n0_bpfprotonvalid_proton_prong << "/" << n1_bpfprotonvalid_proton_prong << ")" << "\t\t" << n_bpfpionvalid_proton_prong << " (" << n0_bpfpionvalid_proton_prong << "/" << n1_bpfpionvalid_proton_prong << ")" << "\t\t" << n_bpfmuonvalid_proton_prong << " (" << n0_bpfmuonvalid_proton_prong << "/" << n1_bpfmuonvalid_proton_prong << ")" << std::endl
            << "Pi/Mu\t\t" << n_bpfprotonvalid_pimu_prong << " (" << n0_bpfprotonvalid_pimu_prong << "/" << n1_bpfprotonvalid_pimu_prong << ")" << "\t" << n_bpfpionvalid_pimu_prong << " (" << n0_bpfpionvalid_pimu_prong << "/" << n1_bpfpionvalid_pimu_prong << ")" << "\t\t" << n_bpfmuonvalid_pimu_prong << " (" << n0_bpfmuonvalid_pimu_prong << "/" << n1_bpfmuonvalid_pimu_prong << ")" << std::endl
            << "Electron\t" << n_bpfprotonvalid_electron_prong << " (" << n0_bpfprotonvalid_electron_prong << "/" << n1_bpfprotonvalid_electron_prong << ")" << "\t\t" << n_bpfpionvalid_electron_prong << " (" << n0_bpfpionvalid_electron_prong << "/" << n1_bpfpionvalid_electron_prong << ")" << "\t\t" << n_bpfmuonvalid_electron_prong << " (" << n0_bpfmuonvalid_electron_prong << "/" << n1_bpfmuonvalid_electron_prong << ")" << std::endl;

  // Single prong plots
  // x
  canv->cd();
  canv->Clear();
  leg->Clear();
  singleprongx_pimu_bl.OverridePOT(1);
  TH1* h_singleprongx_pimu_bl = singleprongx_pimu_bl.ToTH1(singleprongx_pimu_bl.POT());
  h_singleprongx_pimu_bl->SetLineColor(kRed);
  h_singleprongx_pimu_bl->SetLineStyle(kSolid);
  h_singleprongx_pimu_bl->Draw("hist");
  leg->AddEntry(h_singleprongx_pimu_bl, "Pi/Mu", "l");
  singleprongbpfprotonx_pimu_bl.OverridePOT(1);
  TH1* h_singleprongbpfprotonx_pimu_bl = singleprongbpfprotonx_pimu_bl.ToTH1(singleprongbpfprotonx_pimu_bl.POT());
  h_singleprongbpfprotonx_pimu_bl->SetLineColor(kRed);
  h_singleprongbpfprotonx_pimu_bl->SetLineStyle(kDashed);
  h_singleprongbpfprotonx_pimu_bl->Draw("hist same");
  singleprongbpfpionx_pimu_bl.OverridePOT(1);
  TH1* h_singleprongbpfpionx_pimu_bl = singleprongbpfpionx_pimu_bl.ToTH1(singleprongbpfpionx_pimu_bl.POT());
  h_singleprongbpfpionx_pimu_bl->SetLineColor(kRed);
  h_singleprongbpfpionx_pimu_bl->SetLineStyle(kDotted);
  h_singleprongbpfpionx_pimu_bl->Draw("hist same");
  singleprongbpfmuonx_pimu_bl.OverridePOT(1);
  TH1* h_singleprongbpfmuonx_pimu_bl = singleprongbpfmuonx_pimu_bl.ToTH1(singleprongbpfmuonx_pimu_bl.POT());
  h_singleprongbpfmuonx_pimu_bl->SetLineColor(kRed);
  h_singleprongbpfmuonx_pimu_bl->SetLineStyle(kDashDotted);
  h_singleprongbpfmuonx_pimu_bl->Draw("hist same");
  singleprongx_electron_bl.OverridePOT(1);
  singleprongx_proton_bl.OverridePOT(1);
  TH1* h_singleprongx_proton_bl = singleprongx_proton_bl.ToTH1(singleprongx_proton_bl.POT());
  h_singleprongx_proton_bl->SetLineColor(kBlack);
  h_singleprongx_proton_bl->SetLineStyle(kSolid);
  h_singleprongx_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongx_proton_bl, "Proton (Prong)", "l");
  singleprongbpfprotonx_proton_bl.OverridePOT(1);
  TH1* h_singleprongbpfprotonx_proton_bl = singleprongbpfprotonx_proton_bl.ToTH1(singleprongbpfprotonx_proton_bl.POT());
  h_singleprongbpfprotonx_proton_bl->SetLineColor(kBlack);
  h_singleprongbpfprotonx_proton_bl->SetLineStyle(kDashed);
  h_singleprongbpfprotonx_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongbpfprotonx_proton_bl, "Proton (BPF Proton)", "l");
  singleprongbpfpionx_proton_bl.OverridePOT(1);
  TH1* h_singleprongbpfpionx_proton_bl = singleprongbpfpionx_proton_bl.ToTH1(singleprongbpfpionx_proton_bl.POT());
  h_singleprongbpfpionx_proton_bl->SetLineColor(kBlack);
  h_singleprongbpfpionx_proton_bl->SetLineStyle(kDotted);
  h_singleprongbpfpionx_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongbpfpionx_proton_bl, "Proton (BPF Pion)", "l");
  singleprongbpfmuonx_proton_bl.OverridePOT(1);
  TH1* h_singleprongbpfmuonx_proton_bl = singleprongbpfmuonx_proton_bl.ToTH1(singleprongbpfmuonx_proton_bl.POT());
  h_singleprongbpfmuonx_proton_bl->SetLineColor(kBlack);
  h_singleprongbpfmuonx_proton_bl->SetLineStyle(kDashDotted);
  h_singleprongbpfmuonx_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongbpfmuonx_proton_bl, "Proton (BPF Muon)", "l");
  TH1* h_singleprongx_electron_bl = singleprongx_electron_bl.ToTH1(singleprongx_electron_bl.POT());
  h_singleprongx_electron_bl->SetLineColor(kBlue);
  h_singleprongx_electron_bl->SetLineStyle(kSolid);
  h_singleprongx_electron_bl->Draw("hist same");
  leg->AddEntry(h_singleprongx_electron_bl, "Electron", "l");
  singleprongbpfprotonx_electron_bl.OverridePOT(1);
  TH1* h_singleprongbpfprotonx_electron_bl = singleprongbpfprotonx_electron_bl.ToTH1(singleprongbpfprotonx_electron_bl.POT());
  h_singleprongbpfprotonx_electron_bl->SetLineColor(kBlue);
  h_singleprongbpfprotonx_electron_bl->SetLineStyle(kDashed);
  h_singleprongbpfprotonx_electron_bl->Draw("hist same");
  singleprongbpfpionx_electron_bl.OverridePOT(1);
  TH1* h_singleprongbpfpionx_electron_bl = singleprongbpfpionx_electron_bl.ToTH1(singleprongbpfpionx_electron_bl.POT());
  h_singleprongbpfpionx_electron_bl->SetLineColor(kBlue);
  h_singleprongbpfpionx_electron_bl->SetLineStyle(kDotted);
  h_singleprongbpfpionx_electron_bl->Draw("hist same");
  singleprongbpfmuonx_electron_bl.OverridePOT(1);
  TH1* h_singleprongbpfmuonx_electron_bl = singleprongbpfmuonx_electron_bl.ToTH1(singleprongbpfmuonx_electron_bl.POT());
  h_singleprongbpfmuonx_electron_bl->SetLineColor(kBlue);
  h_singleprongbpfmuonx_electron_bl->SetLineStyle(kDashDotted);
  h_singleprongbpfmuonx_electron_bl->Draw("hist same");
  leg->Draw();
  canv->Write("SingleProngX");

  // y
  canv->cd();
  canv->Clear();
  leg->Clear();
  singleprongy_pimu_bl.OverridePOT(1);
  TH1* h_singleprongy_pimu_bl = singleprongy_pimu_bl.ToTH1(singleprongy_pimu_bl.POT());
  h_singleprongy_pimu_bl->SetLineColor(kRed);
  h_singleprongy_pimu_bl->SetLineStyle(kSolid);
  h_singleprongy_pimu_bl->Draw("hist");
  leg->AddEntry(h_singleprongy_pimu_bl, "Pi/Mu", "l");
  singleprongbpfprotony_pimu_bl.OverridePOT(1);
  TH1* h_singleprongbpfprotony_pimu_bl = singleprongbpfprotony_pimu_bl.ToTH1(singleprongbpfprotony_pimu_bl.POT());
  h_singleprongbpfprotony_pimu_bl->SetLineColor(kRed);
  h_singleprongbpfprotony_pimu_bl->SetLineStyle(kDashed);
  h_singleprongbpfprotony_pimu_bl->Draw("hist same");
  singleprongbpfpiony_pimu_bl.OverridePOT(1);
  TH1* h_singleprongbpfpiony_pimu_bl = singleprongbpfpiony_pimu_bl.ToTH1(singleprongbpfpiony_pimu_bl.POT());
  h_singleprongbpfpiony_pimu_bl->SetLineColor(kRed);
  h_singleprongbpfpiony_pimu_bl->SetLineStyle(kDotted);
  h_singleprongbpfpiony_pimu_bl->Draw("hist same");
  singleprongbpfmuony_pimu_bl.OverridePOT(1);
  TH1* h_singleprongbpfmuony_pimu_bl = singleprongbpfmuony_pimu_bl.ToTH1(singleprongbpfmuony_pimu_bl.POT());
  h_singleprongbpfmuony_pimu_bl->SetLineColor(kRed);
  h_singleprongbpfmuony_pimu_bl->SetLineStyle(kDashDotted);
  h_singleprongbpfmuony_pimu_bl->Draw("hist same");
  singleprongy_proton_bl.OverridePOT(1);
  TH1* h_singleprongy_proton_bl = singleprongy_proton_bl.ToTH1(singleprongy_proton_bl.POT());
  h_singleprongy_proton_bl->SetLineColor(kBlack);
  h_singleprongy_proton_bl->SetLineStyle(kSolid);
  h_singleprongy_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongy_proton_bl, "Proton (Prong)", "l");
  singleprongbpfprotony_proton_bl.OverridePOT(1);
  TH1* h_singleprongbpfprotony_proton_bl = singleprongbpfprotony_proton_bl.ToTH1(singleprongbpfprotony_proton_bl.POT());
  h_singleprongbpfprotony_proton_bl->SetLineColor(kBlack);
  h_singleprongbpfprotony_proton_bl->SetLineStyle(kDashed);
  h_singleprongbpfprotony_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongbpfprotony_proton_bl, "Proton (BPF Proton)", "l");
  singleprongbpfpiony_proton_bl.OverridePOT(1);
  TH1* h_singleprongbpfpiony_proton_bl = singleprongbpfpiony_proton_bl.ToTH1(singleprongbpfpiony_proton_bl.POT());
  h_singleprongbpfpiony_proton_bl->SetLineColor(kBlack);
  h_singleprongbpfpiony_proton_bl->SetLineStyle(kDotted);
  h_singleprongbpfpiony_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongbpfpiony_proton_bl, "Proton (BPF Pion)", "l");
  singleprongbpfmuony_proton_bl.OverridePOT(1);
  TH1* h_singleprongbpfmuony_proton_bl = singleprongbpfmuony_proton_bl.ToTH1(singleprongbpfmuony_proton_bl.POT());
  h_singleprongbpfmuony_proton_bl->SetLineColor(kBlack);
  h_singleprongbpfmuony_proton_bl->SetLineStyle(kDashDotted);
  h_singleprongbpfmuony_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongbpfmuony_proton_bl, "Proton (BPF Muon)", "l");
  singleprongy_electron_bl.OverridePOT(1);
  TH1* h_singleprongy_electron_bl = singleprongy_electron_bl.ToTH1(singleprongy_electron_bl.POT());
  h_singleprongy_electron_bl->SetLineColor(kBlue);
  h_singleprongy_electron_bl->SetLineStyle(kSolid);
  h_singleprongy_electron_bl->Draw("hist same");
  leg->AddEntry(h_singleprongy_electron_bl, "Electron", "l");
  singleprongbpfprotony_electron_bl.OverridePOT(1);
  TH1* h_singleprongbpfprotony_electron_bl = singleprongbpfprotony_electron_bl.ToTH1(singleprongbpfprotony_electron_bl.POT());
  h_singleprongbpfprotony_electron_bl->SetLineColor(kBlue);
  h_singleprongbpfprotony_electron_bl->SetLineStyle(kDashed);
  h_singleprongbpfprotony_electron_bl->Draw("hist same");
  singleprongbpfpiony_electron_bl.OverridePOT(1);
  TH1* h_singleprongbpfpiony_electron_bl = singleprongbpfpiony_electron_bl.ToTH1(singleprongbpfpiony_electron_bl.POT());
  h_singleprongbpfpiony_electron_bl->SetLineColor(kBlue);
  h_singleprongbpfpiony_electron_bl->SetLineStyle(kDotted);
  h_singleprongbpfpiony_electron_bl->Draw("hist same");
  singleprongbpfmuony_electron_bl.OverridePOT(1);
  TH1* h_singleprongbpfmuony_electron_bl = singleprongbpfmuony_electron_bl.ToTH1(singleprongbpfmuony_electron_bl.POT());
  h_singleprongbpfmuony_electron_bl->SetLineColor(kBlue);
  h_singleprongbpfmuony_electron_bl->SetLineStyle(kDashDotted);
  h_singleprongbpfmuony_electron_bl->Draw("hist same");
  leg->Draw();
  canv->Write("SingleProngY");

  // z
  canv->cd();
  canv->Clear();
  leg->Clear();
  singleprongz_pimu_bl.OverridePOT(1);
  TH1* h_singleprongz_pimu_bl = singleprongz_pimu_bl.ToTH1(singleprongz_pimu_bl.POT());
  h_singleprongz_pimu_bl->SetLineColor(kRed);
  h_singleprongz_pimu_bl->SetLineStyle(kSolid);
  h_singleprongz_pimu_bl->Draw("hist");
  leg->AddEntry(h_singleprongz_pimu_bl, "Pi/Mu", "l");
  singleprongbpfprotonz_pimu_bl.OverridePOT(1);
  TH1* h_singleprongbpfprotonz_pimu_bl = singleprongbpfprotonz_pimu_bl.ToTH1(singleprongbpfprotonz_pimu_bl.POT());
  h_singleprongbpfprotonz_pimu_bl->SetLineColor(kRed);
  h_singleprongbpfprotonz_pimu_bl->SetLineStyle(kDashed);
  h_singleprongbpfprotonz_pimu_bl->Draw("hist same");
  singleprongbpfpionz_pimu_bl.OverridePOT(1);
  TH1* h_singleprongbpfpionz_pimu_bl = singleprongbpfpionz_pimu_bl.ToTH1(singleprongbpfpionz_pimu_bl.POT());
  h_singleprongbpfpionz_pimu_bl->SetLineColor(kRed);
  h_singleprongbpfpionz_pimu_bl->SetLineStyle(kDotted);
  h_singleprongbpfpionz_pimu_bl->Draw("hist same");
  singleprongbpfmuonz_pimu_bl.OverridePOT(1);
  TH1* h_singleprongbpfmuonz_pimu_bl = singleprongbpfmuonz_pimu_bl.ToTH1(singleprongbpfmuonz_pimu_bl.POT());
  h_singleprongbpfmuonz_pimu_bl->SetLineColor(kRed);
  h_singleprongbpfmuonz_pimu_bl->SetLineStyle(kDashDotted);
  h_singleprongbpfmuonz_pimu_bl->Draw("hist same");
  singleprongz_proton_bl.OverridePOT(1);
  TH1* h_singleprongz_proton_bl = singleprongz_proton_bl.ToTH1(singleprongz_proton_bl.POT());
  h_singleprongz_proton_bl->SetLineColor(kBlack);
  h_singleprongz_proton_bl->SetLineStyle(kSolid);
  h_singleprongz_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongz_proton_bl, "Proton (Prong)", "l");
  singleprongbpfprotonz_proton_bl.OverridePOT(1);
  TH1* h_singleprongbpfprotonz_proton_bl = singleprongbpfprotonz_proton_bl.ToTH1(singleprongbpfprotonz_proton_bl.POT());
  h_singleprongbpfprotonz_proton_bl->SetLineColor(kBlack);
  h_singleprongbpfprotonz_proton_bl->SetLineStyle(kDashed);
  h_singleprongbpfprotonz_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongbpfprotonz_proton_bl, "Proton (BPF Proton)", "l");
  singleprongbpfpionz_proton_bl.OverridePOT(1);
  TH1* h_singleprongbpfpionz_proton_bl = singleprongbpfpionz_proton_bl.ToTH1(singleprongbpfpionz_proton_bl.POT());
  h_singleprongbpfpionz_proton_bl->SetLineColor(kBlack);
  h_singleprongbpfpionz_proton_bl->SetLineStyle(kDotted);
  h_singleprongbpfpionz_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongbpfpionz_proton_bl, "Proton (BPF Pion)", "l");
  singleprongbpfmuonz_proton_bl.OverridePOT(1);
  TH1* h_singleprongbpfmuonz_proton_bl = singleprongbpfmuonz_proton_bl.ToTH1(singleprongbpfmuonz_proton_bl.POT());
  h_singleprongbpfmuonz_proton_bl->SetLineColor(kBlack);
  h_singleprongbpfmuonz_proton_bl->SetLineStyle(kDashDotted);
  h_singleprongbpfmuonz_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongbpfmuonz_proton_bl, "Proton (BPF Muon)", "l");
  singleprongz_electron_bl.OverridePOT(1);
  TH1* h_singleprongz_electron_bl = singleprongz_electron_bl.ToTH1(singleprongz_electron_bl.POT());
  h_singleprongz_electron_bl->SetLineColor(kBlue);
  h_singleprongz_electron_bl->SetLineStyle(kSolid);
  h_singleprongz_electron_bl->Draw("hist same");
  leg->AddEntry(h_singleprongz_electron_bl, "Electron", "l");
  singleprongbpfprotonz_electron_bl.OverridePOT(1);
  TH1* h_singleprongbpfprotonz_electron_bl = singleprongbpfprotonz_electron_bl.ToTH1(singleprongbpfprotonz_electron_bl.POT());
  h_singleprongbpfprotonz_electron_bl->SetLineColor(kBlue);
  h_singleprongbpfprotonz_electron_bl->SetLineStyle(kDashed);
  h_singleprongbpfprotonz_electron_bl->Draw("hist same");
  singleprongbpfpionz_electron_bl.OverridePOT(1);
  TH1* h_singleprongbpfpionz_electron_bl = singleprongbpfpionz_electron_bl.ToTH1(singleprongbpfpionz_electron_bl.POT());
  h_singleprongbpfpionz_electron_bl->SetLineColor(kBlue);
  h_singleprongbpfpionz_electron_bl->SetLineStyle(kDotted);
  h_singleprongbpfpionz_electron_bl->Draw("hist same");
  singleprongbpfmuonz_electron_bl.OverridePOT(1);
  TH1* h_singleprongbpfmuonz_electron_bl = singleprongbpfmuonz_electron_bl.ToTH1(singleprongbpfmuonz_electron_bl.POT());
  h_singleprongbpfmuonz_electron_bl->SetLineColor(kBlue);
  h_singleprongbpfmuonz_electron_bl->SetLineStyle(kDashDotted);
  h_singleprongbpfmuonz_electron_bl->Draw("hist same");
  leg->Draw();
  canv->Write("SingleProngZ");

  // nhit
  canv->cd();
  canv->Clear();
  leg->Clear();
  singleprongnhit_pimu_bl.OverridePOT(1);
  TH1* h_singleprongnhit_pimu_bl = singleprongnhit_pimu_bl.ToTH1(singleprongnhit_pimu_bl.POT());
  h_singleprongnhit_pimu_bl->SetLineColor(kRed);
  h_singleprongnhit_pimu_bl->SetLineStyle(kSolid);
  h_singleprongnhit_pimu_bl->Draw("hist");
  leg->AddEntry(h_singleprongnhit_pimu_bl, "Pi/Mu", "l");
  singleprongbpfprotonnhit_pimu_bl.OverridePOT(1);
  TH1* h_singleprongbpfprotonnhit_pimu_bl = singleprongbpfprotonnhit_pimu_bl.ToTH1(singleprongbpfprotonnhit_pimu_bl.POT());
  h_singleprongbpfprotonnhit_pimu_bl->SetLineColor(kRed);
  h_singleprongbpfprotonnhit_pimu_bl->SetLineStyle(kDashed);
  h_singleprongbpfprotonnhit_pimu_bl->Draw("hist same");
  singleprongbpfpionnhit_pimu_bl.OverridePOT(1);
  TH1* h_singleprongbpfpionnhit_pimu_bl = singleprongbpfpionnhit_pimu_bl.ToTH1(singleprongbpfpionnhit_pimu_bl.POT());
  h_singleprongbpfpionnhit_pimu_bl->SetLineColor(kRed);
  h_singleprongbpfpionnhit_pimu_bl->SetLineStyle(kDotted);
  h_singleprongbpfpionnhit_pimu_bl->Draw("hist same");
  singleprongbpfmuonnhit_pimu_bl.OverridePOT(1);
  TH1* h_singleprongbpfmuonnhit_pimu_bl = singleprongbpfmuonnhit_pimu_bl.ToTH1(singleprongbpfmuonnhit_pimu_bl.POT());
  h_singleprongbpfmuonnhit_pimu_bl->SetLineColor(kRed);
  h_singleprongbpfmuonnhit_pimu_bl->SetLineStyle(kDashDotted);
  h_singleprongbpfmuonnhit_pimu_bl->Draw("hist same");
  singleprongnhit_proton_bl.OverridePOT(1);
  TH1* h_singleprongnhit_proton_bl = singleprongnhit_proton_bl.ToTH1(singleprongnhit_proton_bl.POT());
  h_singleprongnhit_proton_bl->SetLineColor(kBlack);
  h_singleprongnhit_proton_bl->SetLineStyle(kSolid);
  h_singleprongnhit_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongnhit_proton_bl, "Proton (Prong)", "l");
  singleprongbpfprotonnhit_proton_bl.OverridePOT(1);
  TH1* h_singleprongbpfprotonnhit_proton_bl = singleprongbpfprotonnhit_proton_bl.ToTH1(singleprongbpfprotonnhit_proton_bl.POT());
  h_singleprongbpfprotonnhit_proton_bl->SetLineColor(kBlack);
  h_singleprongbpfprotonnhit_proton_bl->SetLineStyle(kDashed);
  h_singleprongbpfprotonnhit_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongbpfprotonnhit_proton_bl, "Proton (BPF Proton)", "l");
  singleprongbpfpionnhit_proton_bl.OverridePOT(1);
  TH1* h_singleprongbpfpionnhit_proton_bl = singleprongbpfpionnhit_proton_bl.ToTH1(singleprongbpfpionnhit_proton_bl.POT());
  h_singleprongbpfpionnhit_proton_bl->SetLineColor(kBlack);
  h_singleprongbpfpionnhit_proton_bl->SetLineStyle(kDotted);
  h_singleprongbpfpionnhit_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongbpfpionnhit_proton_bl, "Proton (BPF Pion)", "l");
  singleprongbpfmuonnhit_proton_bl.OverridePOT(1);
  TH1* h_singleprongbpfmuonnhit_proton_bl = singleprongbpfmuonnhit_proton_bl.ToTH1(singleprongbpfmuonnhit_proton_bl.POT());
  h_singleprongbpfmuonnhit_proton_bl->SetLineColor(kBlack);
  h_singleprongbpfmuonnhit_proton_bl->SetLineStyle(kDashDotted);
  h_singleprongbpfmuonnhit_proton_bl->Draw("hist same");
  leg->AddEntry(h_singleprongbpfmuonnhit_proton_bl, "Proton (BPF Muon)", "l");
  singleprongnhit_electron_bl.OverridePOT(1);
  TH1* h_singleprongnhit_electron_bl = singleprongnhit_electron_bl.ToTH1(singleprongnhit_electron_bl.POT());
  h_singleprongnhit_electron_bl->SetLineColor(kBlue);
  h_singleprongnhit_electron_bl->SetLineStyle(kSolid);
  h_singleprongnhit_electron_bl->Draw("hist same");
  leg->AddEntry(h_singleprongnhit_electron_bl, "Electron", "l");
  singleprongbpfprotonnhit_electron_bl.OverridePOT(1);
  TH1* h_singleprongbpfprotonnhit_electron_bl = singleprongbpfprotonnhit_electron_bl.ToTH1(singleprongbpfprotonnhit_electron_bl.POT());
  h_singleprongbpfprotonnhit_electron_bl->SetLineColor(kBlue);
  h_singleprongbpfprotonnhit_electron_bl->SetLineStyle(kDashed);
  h_singleprongbpfprotonnhit_electron_bl->Draw("hist same");
  singleprongbpfpionnhit_electron_bl.OverridePOT(1);
  TH1* h_singleprongbpfpionnhit_electron_bl = singleprongbpfpionnhit_electron_bl.ToTH1(singleprongbpfpionnhit_electron_bl.POT());
  h_singleprongbpfpionnhit_electron_bl->SetLineColor(kBlue);
  h_singleprongbpfpionnhit_electron_bl->SetLineStyle(kDotted);
  h_singleprongbpfpionnhit_electron_bl->Draw("hist same");
  singleprongbpfmuonnhit_electron_bl.OverridePOT(1);
  TH1* h_singleprongbpfmuonnhit_electron_bl = singleprongbpfmuonnhit_electron_bl.ToTH1(singleprongbpfmuonnhit_electron_bl.POT());
  h_singleprongbpfmuonnhit_electron_bl->SetLineColor(kBlue);
  h_singleprongbpfmuonnhit_electron_bl->SetLineStyle(kDashDotted);
  h_singleprongbpfmuonnhit_electron_bl->Draw("hist same");
  leg->Draw();
  canv->Write("SingleProngNHit");

  outFile->Close();

}
