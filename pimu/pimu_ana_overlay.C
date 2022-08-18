#include "pimu_drawing.h"

void pimu_ana_overlay() {

  gStyle->SetOptStat("i");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.937);
  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.15);
  gStyle->SetHistLineColor(1);
  TGaxis::SetMaxDigits(3);

  TFile* pi_infile = TFile::Open("pi_ana.root", "READ");
  TFile* mu_infile = TFile::Open("mu_ana.root", "READ");

  // get histograms
  TH1* pi_picvn = (TH1*)pi_infile->Get("pimusep/PiCVN");
  TH1* pi_mucvn = (TH1*)pi_infile->Get("pimusep/MuCVN");
  TH1* mu_picvn = (TH1*)mu_infile->Get("pimusep/PiCVN");
  TH1* mu_mucvn = (TH1*)mu_infile->Get("pimusep/MuCVN");
  TH1* pi_pibpfchi2 = (TH1*)pi_infile->Get("pimusep/PiBPFChi2");
  TH1* pi_pibpfchi2hit = (TH1*)pi_infile->Get("pimusep/PiBPFChi2Hit");
  TH1* pi_pibpfchi2scat = (TH1*)pi_infile->Get("pimusep/PiBPFChi2Scat");
  TH1* pi_mubpfchi2 = (TH1*)pi_infile->Get("pimusep/MuBPFChi2");
  TH1* pi_mubpfchi2hit = (TH1*)pi_infile->Get("pimusep/MuBPFChi2Hit");
  TH1* pi_mubpfchi2scat = (TH1*)pi_infile->Get("pimusep/MuBPFChi2Scat");
  TH1* mu_pibpfchi2 = (TH1*)mu_infile->Get("pimusep/PiBPFChi2");
  TH1* mu_pibpfchi2hit = (TH1*)mu_infile->Get("pimusep/PiBPFChi2Hit");
  TH1* mu_pibpfchi2scat = (TH1*)mu_infile->Get("pimusep/PiBPFChi2Scat");
  TH1* mu_mubpfchi2 = (TH1*)mu_infile->Get("pimusep/MuBPFChi2");
  TH1* mu_mubpfchi2hit = (TH1*)mu_infile->Get("pimusep/MuBPFChi2Hit");
  TH1* mu_mubpfchi2scat = (TH1*)mu_infile->Get("pimusep/MuBPFChi2Scat");

  // out
  TFile* outFile = new TFile("pimu_ana_overlay.root", "RECREATE");

  // CVN
  Overlay(pi_picvn, mu_picvn, "PiCVN", outFile);
  Overlay(pi_mucvn, mu_mucvn, "MuCVN", outFile);

  // BPF -chi2
  Overlay(pi_pibpfchi2, mu_pibpfchi2, "PiBPFChi2", outFile);
  Overlay(pi_mubpfchi2, mu_mubpfchi2, "MuBPFChi2", outFile);

  // BPF -chi2hit
  Overlay(pi_pibpfchi2hit, mu_pibpfchi2hit, "PiBPFChi2Hit", outFile);
  Overlay(pi_mubpfchi2hit, mu_mubpfchi2hit, "MuBPFChi2Hit", outFile);

  // BPF -chi2scat
  Overlay(pi_pibpfchi2scat, mu_pibpfchi2scat, "PiBPFChi2Scat", outFile);
  Overlay(pi_mubpfchi2scat, mu_mubpfchi2scat, "MuBPFChi2Scat", outFile);

}
