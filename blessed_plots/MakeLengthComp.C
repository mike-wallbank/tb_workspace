// framework
#include "CAFAna/Core/Spectrum.h"
#include "TestBeamAna/Analysis/TestBeamLoaders.h"
#include "TestBeamAna/Cuts/Cuts.h"
#include "TestBeamAna/Vars/Vars.h"

// root
#include "TFile.h"

using namespace ana;

void MakeLengthComp() {

  TestBeamPeriod3Loader* loader = new TestBeamPeriod3Loader();

  Spectrum pronglen_proton_prong(*loader, HistAxis("Length (cm)", Binning::Simple(100,0,500), kSelProngLength), kProton);
  Spectrum pronglen_pimu_prong(*loader, HistAxis("Length (cm)", Binning::Simple(100,0,500), kSelProngLength), kPiMu);
  Spectrum pronglen_electron_prong(*loader, HistAxis("Length (cm)", Binning::Simple(100,0,500), kSelProngLength), kElectron);
  Spectrum bpfprotonlen_proton_prong(*loader, HistAxis("Length (cm)", Binning::Simple(100,0,500), kSelProngBPFProtonLength), kProton);
  Spectrum bpfprotonlen_pimu_prong(*loader, HistAxis("Length (cm)", Binning::Simple(100,0,500), kSelProngBPFProtonLength), kPiMu);
  Spectrum bpfprotonlen_electron_prong(*loader, HistAxis("Length (cm)", Binning::Simple(100,0,500), kSelProngBPFProtonLength), kElectron);
  Spectrum bpfpionlen_proton_prong(*loader, HistAxis("Length (cm)", Binning::Simple(100,0,500), kSelProngBPFPionLength), kProton);
  Spectrum bpfpionlen_pimu_prong(*loader, HistAxis("Length (cm)", Binning::Simple(100,0,500), kSelProngBPFPionLength), kPiMu);
  Spectrum bpfpionlen_electron_prong(*loader, HistAxis("Length (cm)", Binning::Simple(100,0,500), kSelProngBPFPionLength), kElectron);
  Spectrum bpfmuonlen_proton_prong(*loader, HistAxis("Length (cm)", Binning::Simple(100,0,500), kSelProngBPFMuonLength), kProton);
  Spectrum bpfmuonlen_pimu_prong(*loader, HistAxis("Length (cm)", Binning::Simple(100,0,500), kSelProngBPFMuonLength), kPiMu);
  Spectrum bpfmuonlen_electron_prong(*loader, HistAxis("Length (cm)", Binning::Simple(100,0,500), kSelProngBPFMuonLength), kElectron);
  Spectrum bpfprotonlendiff_proton_prong(*loader, HistAxis("Length (cm)", Binning::Simple(500,0,500), kSelProngBPFProtonLengthDiff), kProton);
  Spectrum bpfprotonlendiff_pimu_prong(*loader, HistAxis("Length (cm)", Binning::Simple(500,0,500), kSelProngBPFProtonLengthDiff), kPiMu);
  Spectrum bpfprotonlendiff_electron_prong(*loader, HistAxis("Length (cm)", Binning::Simple(500,0,500), kSelProngBPFProtonLengthDiff), kElectron);
  Spectrum bpfpionlendiff_proton_prong(*loader, HistAxis("Length (cm)", Binning::Simple(500,0,500), kSelProngBPFPionLengthDiff), kProton);
  Spectrum bpfpionlendiff_pimu_prong(*loader, HistAxis("Length (cm)", Binning::Simple(500,0,500), kSelProngBPFPionLengthDiff), kPiMu);
  Spectrum bpfpionlendiff_electron_prong(*loader, HistAxis("Length (cm)", Binning::Simple(500,0,500), kSelProngBPFPionLengthDiff), kElectron);
  Spectrum bpfmuonlendiff_proton_prong(*loader, HistAxis("Length (cm)", Binning::Simple(500,0,500), kSelProngBPFMuonLengthDiff), kProton);
  Spectrum bpfmuonlendiff_pimu_prong(*loader, HistAxis("Length (cm)", Binning::Simple(500,0,500), kSelProngBPFMuonLengthDiff), kPiMu);
  Spectrum bpfmuonlendiff_electron_prong(*loader, HistAxis("Length (cm)", Binning::Simple(500,0,500), kSelProngBPFMuonLengthDiff), kElectron);

  loader->Go();

  TFile* outFile = new TFile("LengthComp.root", "RECREATE");

  pronglen_proton_prong.SaveTo(outFile->mkdir("pronglen_proton_prong"), "pronglen_proton_prong");
  pronglen_pimu_prong.SaveTo(outFile->mkdir("pronglen_pimu_prong"), "pronglen_pimu_prong");
  pronglen_electron_prong.SaveTo(outFile->mkdir("pronglen_electron_prong"), "pronglen_electron_prong");
  bpfprotonlen_proton_prong.SaveTo(outFile->mkdir("bpfprotonlen_proton_prong"), "bpfprotonlen_proton_prong");
  bpfprotonlen_pimu_prong.SaveTo(outFile->mkdir("bpfprotonlen_pimu_prong"), "bpfprotonlen_pimu_prong");
  bpfprotonlen_electron_prong.SaveTo(outFile->mkdir("bpfprotonlen_electron_prong"), "bpfprotonlen_electron_prong");
  bpfpionlen_proton_prong.SaveTo(outFile->mkdir("bpfpionlen_proton_prong"), "bpfpionlen_proton_prong");
  bpfpionlen_pimu_prong.SaveTo(outFile->mkdir("bpfpionlen_pimu_prong"), "bpfpionlen_pimu_prong");
  bpfpionlen_electron_prong.SaveTo(outFile->mkdir("bpfpionlen_electron_prong"), "bpfpionlen_electron_prong");
  bpfmuonlen_proton_prong.SaveTo(outFile->mkdir("bpfmuonlen_proton_prong"), "bpfmuonlen_proton_prong");
  bpfmuonlen_pimu_prong.SaveTo(outFile->mkdir("bpfmuonlen_pimu_prong"), "bpfmuonlen_pimu_prong");
  bpfmuonlen_electron_prong.SaveTo(outFile->mkdir("bpfmuonlen_electron_prong"), "bpfmuonlen_electron_prong");
  bpfprotonlendiff_proton_prong.SaveTo(outFile->mkdir("bpfprotonlendiff_proton_prong"), "bpfprotonlendiff_proton_prong");
  bpfprotonlendiff_pimu_prong.SaveTo(outFile->mkdir("bpfprotonlendiff_pimu_prong"), "bpfprotonlendiff_pimu_prong");
  bpfprotonlendiff_electron_prong.SaveTo(outFile->mkdir("bpfprotonlendiff_electron_prong"), "bpfprotonlendiff_electron_prong");
  bpfpionlendiff_proton_prong.SaveTo(outFile->mkdir("bpfpionlendiff_proton_prong"), "bpfpionlendiff_proton_prong");
  bpfpionlendiff_pimu_prong.SaveTo(outFile->mkdir("bpfpionlendiff_pimu_prong"), "bpfpionlendiff_pimu_prong");
  bpfpionlendiff_electron_prong.SaveTo(outFile->mkdir("bpfpionlendiff_electron_prong"), "bpfpionlendiff_electron_prong");
  bpfmuonlendiff_proton_prong.SaveTo(outFile->mkdir("bpfmuonlendiff_proton_prong"), "bpfmuonlendiff_proton_prong");
  bpfmuonlendiff_pimu_prong.SaveTo(outFile->mkdir("bpfmuonlendiff_pimu_prong"), "bpfmuonlendiff_pimu_prong");
  bpfmuonlendiff_electron_prong.SaveTo(outFile->mkdir("bpfmuonlendiff_electron_prong"), "bpfmuonlendiff_electron_prong");

  outFile->Close();

}
