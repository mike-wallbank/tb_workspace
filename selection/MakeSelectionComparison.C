// -----------------------------------------------
// MakeSelectionComparison.C
// Mike Wallbank (July 2022)
//
// Produce comparison plots between various
// selections.
// -----------------------------------------------

// framework
#include "CAFAna/Core/Spectrum.h"
#include "TestBeamAna/Analysis/TestBeamLoaders.h"
#include "TestBeamAna/Cuts/Cuts.h"
#include "TestBeamAna/Vars/HistAxes.h"
#include "TestBeamAna/Vars/Vars.h"

// root
#include "TFile.h"

using namespace ana;

// -----------------------------------------------
void MakeSelectionComparison() {

  TestBeamPeriod3Loader* loader = new TestBeamPeriod3Loader();

  Spectrum p_proton_prong   = Spectrum(*loader, kMomAxis, kProton);
  Spectrum p_pimu_prong     = Spectrum(*loader, kMomAxis, kPiMu);
  Spectrum p_electron_prong = Spectrum(*loader, kMomAxis, kElectron);
  Spectrum p_proton_bpf     = Spectrum(*loader, kMomAxis, kProtonCutBPFTrk);
  Spectrum p_pimu_bpf       = Spectrum(*loader, kMomAxis, kPiMuCutBPFTrk);
  Spectrum p_electron_bpf   = Spectrum(*loader, kMomAxis, kElectronCutBPFTrk);
  Spectrum p_proton_win     = Spectrum(*loader, kMomAxis, kProtonCutWinTrk);
  Spectrum p_pimu_win       = Spectrum(*loader, kMomAxis, kPiMuCutWinTrk);
  Spectrum p_electron_win   = Spectrum(*loader, kMomAxis, kElectronCutWinTrk);
  Spectrum p_proton_cos     = Spectrum(*loader, kMomAxis, kProtonCutCosTrk);
  Spectrum p_pimu_cos       = Spectrum(*loader, kMomAxis, kPiMuCutCosTrk);
  Spectrum p_electron_cos   = Spectrum(*loader, kMomAxis, kElectronCutCosTrk);

  HistAxis bpfprotonvalid_axis("BPF Proton-Hypothesis", Binning::Simple(2,0,2), kSelProngBPFProtonValid);
  Spectrum bpfprotonvalid_proton_prong = Spectrum(*loader, bpfprotonvalid_axis, kProton);
  Spectrum bpfprotonvalid_pimu_prong = Spectrum(*loader, bpfprotonvalid_axis, kPiMu);
  Spectrum bpfprotonvalid_electron_prong = Spectrum(*loader, bpfprotonvalid_axis, kElectron);
  HistAxis bpfpionvalid_axis("BPF Pion-Hypothesis", Binning::Simple(2,0,2), kSelProngBPFPionValid);
  Spectrum bpfpionvalid_proton_prong = Spectrum(*loader, bpfpionvalid_axis, kProton);
  Spectrum bpfpionvalid_pimu_prong = Spectrum(*loader, bpfpionvalid_axis, kPiMu);
  Spectrum bpfpionvalid_electron_prong = Spectrum(*loader, bpfpionvalid_axis, kElectron);
  HistAxis bpfmuonvalid_axis("BPF Muon-Hypothesis", Binning::Simple(2,0,2), kSelProngBPFMuonValid);
  Spectrum bpfmuonvalid_proton_prong = Spectrum(*loader, bpfmuonvalid_axis, kProton);
  Spectrum bpfmuonvalid_pimu_prong = Spectrum(*loader, bpfmuonvalid_axis, kPiMu);
  Spectrum bpfmuonvalid_electron_prong = Spectrum(*loader, bpfmuonvalid_axis, kElectron);

  const HistAxis pronge_prong_axis("Prong Energy (Prong Selected) (GeV)", Binning::Simple(100,0,2), kSelProngTotE);
  Spectrum pronge_proton_prong   = Spectrum(*loader, pronge_prong_axis, kProton);
  Spectrum pronge_pimu_prong     = Spectrum(*loader, pronge_prong_axis, kPiMu);
  Spectrum pronge_electron_prong = Spectrum(*loader, pronge_prong_axis, kElectron);
  const HistAxis pronge_bpf_axis("Prong Energy (BPF Selected) (GeV)", Binning::Simple(100,0,2), kSelBPFProngTotE);
  Spectrum pronge_proton_bpf     = Spectrum(*loader, pronge_bpf_axis, kProtonCutBPFTrk);
  Spectrum pronge_pimu_bpf       = Spectrum(*loader, pronge_bpf_axis, kPiMuCutBPFTrk);
  Spectrum pronge_electron_bpf   = Spectrum(*loader, pronge_bpf_axis, kElectronCutBPFTrk);

  const HistAxis bpfpione_prong_axis("BPF Energy (Prong Selected) (GeV)", Binning::Simple(100,0,2), kSelProngBPFPionTotE);
  const HistAxis bpfprotone_prong_axis("BPF Energy (Prong Selected) (GeV)", Binning::Simple(100,0,2), kSelProngBPFProtonTotE);
  Spectrum bpfe_proton_prong   = Spectrum(*loader, bpfprotone_prong_axis, kProton);
  Spectrum bpfe_pimu_prong     = Spectrum(*loader, bpfpione_prong_axis, kPiMu);
  Spectrum bpfe_electron_prong = Spectrum(*loader, bpfpione_prong_axis, kElectron);
  const HistAxis bpfpione_bpf_axis("BPF Energy (BPF Selected) (GeV)", Binning::Simple(100,0,2), kSelBPFPionTotE);
  const HistAxis bpfprotone_bpf_axis("BPF Energy (BPF Selected) (GeV)", Binning::Simple(100,0,2), kSelBPFProtonTotE);
  Spectrum bpfe_proton_bpf     = Spectrum(*loader, bpfprotone_bpf_axis, kProtonCutBPFTrk);
  Spectrum bpfe_pimu_bpf       = Spectrum(*loader, bpfpione_bpf_axis, kPiMuCutBPFTrk);
  Spectrum bpfe_electron_bpf   = Spectrum(*loader, bpfpione_bpf_axis, kElectronCutBPFTrk);

  const HistAxis prongx_prong_axis("Prong X (Prong Selected) (cm)", Binning::Simple(100,-200,200), kSelProngStrtX);
  const HistAxis prongy_prong_axis("Prong Y (Prong Selected) (cm)", Binning::Simple(100,-200,200), kSelProngStrtY);
  const HistAxis prongz_prong_axis("Prong Z (Prong Selected) (cm)", Binning::Simple(100,-50,50), kSelProngStrtZ);
  const HistAxis bpfpionx_prong_axis("BPF X (Prong Selected) (cm)", Binning::Simple(100,-200,200), kSelProngBPFPionStrtX);
  const HistAxis bpfpiony_prong_axis("BPF Y (Prong Selected) (cm)", Binning::Simple(100,-200,200), kSelProngBPFPionStrtY);
  const HistAxis bpfpionz_prong_axis("BPF Z (Prong Selected) (cm)", Binning::Simple(100,-50,50), kSelProngBPFPionStrtZ);
  const HistAxis bpfprotonx_prong_axis("BPF X (Prong Selected) (cm)", Binning::Simple(100,-200,200), kSelProngBPFProtonStrtX);
  const HistAxis bpfprotony_prong_axis("BPF Y (Prong Selected) (cm)", Binning::Simple(100,-200,200), kSelProngBPFProtonStrtY);
  const HistAxis bpfprotonz_prong_axis("BPF Z (Prong Selected) (cm)", Binning::Simple(100,-50,50), kSelProngBPFProtonStrtZ);
  Spectrum prongx_proton_prong   = Spectrum(*loader, prongx_prong_axis, kProton);
  Spectrum prongy_proton_prong   = Spectrum(*loader, prongy_prong_axis, kProton);
  Spectrum prongz_proton_prong   = Spectrum(*loader, prongz_prong_axis, kProton);
  Spectrum prongx_pimu_prong     = Spectrum(*loader, prongx_prong_axis, kPiMu);
  Spectrum prongy_pimu_prong     = Spectrum(*loader, prongy_prong_axis, kPiMu);
  Spectrum prongz_pimu_prong     = Spectrum(*loader, prongz_prong_axis, kPiMu);
  Spectrum prongx_electron_prong = Spectrum(*loader, prongx_prong_axis, kElectron);
  Spectrum prongy_electron_prong = Spectrum(*loader, prongy_prong_axis, kElectron);
  Spectrum prongz_electron_prong = Spectrum(*loader, prongz_prong_axis, kElectron);
  Spectrum bpfx_proton_prong   = Spectrum(*loader, bpfprotonx_prong_axis, kProton);
  Spectrum bpfy_proton_prong   = Spectrum(*loader, bpfprotony_prong_axis, kProton);
  Spectrum bpfz_proton_prong   = Spectrum(*loader, bpfprotonz_prong_axis, kProton);
  Spectrum bpfx_pimu_prong     = Spectrum(*loader, bpfpionx_prong_axis, kPiMu);
  Spectrum bpfy_pimu_prong     = Spectrum(*loader, bpfpiony_prong_axis, kPiMu);
  Spectrum bpfz_pimu_prong     = Spectrum(*loader, bpfpionz_prong_axis, kPiMu);
  Spectrum bpfx_electron_prong = Spectrum(*loader, bpfpionx_prong_axis, kElectron);
  Spectrum bpfy_electron_prong = Spectrum(*loader, bpfpiony_prong_axis, kElectron);
  Spectrum bpfz_electron_prong = Spectrum(*loader, bpfpionz_prong_axis, kElectron);
  Spectrum prongvbpfx_proton_prong   = Spectrum(*loader, prongx_prong_axis, bpfprotonx_prong_axis, kProton);
  Spectrum prongvbpfy_proton_prong   = Spectrum(*loader, prongy_prong_axis, bpfprotony_prong_axis, kProton);
  Spectrum prongvbpfz_proton_prong   = Spectrum(*loader, prongz_prong_axis, bpfprotonz_prong_axis, kProton);
  Spectrum prongvbpfx_pimu_prong     = Spectrum(*loader, prongx_prong_axis, bpfpionx_prong_axis, kPiMu);
  Spectrum prongvbpfy_pimu_prong     = Spectrum(*loader, prongy_prong_axis, bpfpiony_prong_axis, kPiMu);
  Spectrum prongvbpfz_pimu_prong     = Spectrum(*loader, prongz_prong_axis, bpfpionz_prong_axis, kPiMu);
  Spectrum prongvbpfx_electron_prong = Spectrum(*loader, prongx_prong_axis, bpfpionx_prong_axis, kElectron);
  Spectrum prongvbpfy_electron_prong = Spectrum(*loader, prongy_prong_axis, bpfpiony_prong_axis, kElectron);
  Spectrum prongvbpfz_electron_prong = Spectrum(*loader, prongz_prong_axis, bpfpionz_prong_axis, kElectron);

  const HistAxis bpfpionlen_prong_axis("BPF Length (Prong Selected) (cm)", Binning::Simple(100,0,500), kSelProngBPFPionLength);
  const HistAxis bpfprotonlen_prong_axis("BPF Length (Prong Selected) (cm)", Binning::Simple(100,0,500), kSelProngBPFProtonLength);
  Spectrum bpflen_proton_prong   = Spectrum(*loader, bpfprotonlen_prong_axis, kProton);
  Spectrum bpflen_pimu_prong     = Spectrum(*loader, bpfpionlen_prong_axis, kPiMu);
  Spectrum bpflen_electron_prong = Spectrum(*loader, bpfpionlen_prong_axis, kElectron);
  const HistAxis bpfpionlen_bpf_axis("BPF Length (BPF Selected) (cm)", Binning::Simple(100,0,500), kSelBPFPionLength);
  const HistAxis bpfprotonlen_bpf_axis("BPF Length (BPF Selected) (cm)", Binning::Simple(100,0,500), kSelBPFProtonLength);
  Spectrum bpflen_proton_bpf     = Spectrum(*loader, bpfprotonlen_bpf_axis, kProtonCutBPFTrk);
  Spectrum bpflen_pimu_bpf       = Spectrum(*loader, bpfpionlen_bpf_axis, kPiMuCutBPFTrk);
  Spectrum bpflen_electron_bpf   = Spectrum(*loader, bpfpionlen_bpf_axis, kElectronCutBPFTrk);

  const HistAxis wintrklen_axis("Window Track Length (cm)", Binning::Simple(100,0,500), kSelWinTrkLength);
  Spectrum wintrklen_proton   = Spectrum(*loader, wintrklen_axis, kProtonCutWinTrk);
  Spectrum wintrklen_pimu     = Spectrum(*loader, wintrklen_axis, kPiMuCutWinTrk);
  Spectrum wintrklen_electron = Spectrum(*loader, wintrklen_axis, kElectronCutWinTrk);
  const HistAxis costrklen_axis("Cosmic Track Length (cm)", Binning::Simple(100,0,500), kSelCosTrkLength);
  Spectrum costrklen_proton   = Spectrum(*loader, costrklen_axis, kProtonCutCosTrk);
  Spectrum costrklen_pimu     = Spectrum(*loader, costrklen_axis, kPiMuCutCosTrk);
  Spectrum costrklen_electron = Spectrum(*loader, costrklen_axis, kElectronCutCosTrk);

  const HistAxis bpfprotonlen_axis("BPF Proton-Hypothesis Length (BPF Selected)", Binning::Simple(100,0,500), kSelBPFProtonLength);
  const HistAxis bpfpionlen_axis("BPF Pion-Hypothesis Length (BPF Selected)", Binning::Simple(100,0,500), kSelBPFPionLength);
  const HistAxis bpfmuonlen_axis("BPF Muon-Hypothesis Length (BPF Selected)", Binning::Simple(100,0,500), kSelBPFMuonLength);
  Spectrum bpfprotonlen_proton_bpf = Spectrum(*loader, bpfprotonlen_axis, kProtonCutBPFTrk);
  Spectrum bpfprotonlen_pimu_bpf = Spectrum(*loader, bpfprotonlen_axis, kPiMuCutBPFTrk);
  Spectrum bpfprotonlen_electron_bpf = Spectrum(*loader, bpfprotonlen_axis, kElectronCutBPFTrk);
  Spectrum bpfpionlen_proton_bpf = Spectrum(*loader, bpfpionlen_axis, kProtonCutBPFTrk);
  Spectrum bpfpionlen_pimu_bpf = Spectrum(*loader, bpfpionlen_axis, kPiMuCutBPFTrk);
  Spectrum bpfpionlen_electron_bpf = Spectrum(*loader, bpfpionlen_axis, kElectronCutBPFTrk);
  Spectrum bpfmuonlen_proton_bpf = Spectrum(*loader, bpfmuonlen_axis, kProtonCutBPFTrk);
  Spectrum bpfmuonlen_pimu_bpf = Spectrum(*loader, bpfmuonlen_axis, kPiMuCutBPFTrk);
  Spectrum bpfmuonlen_electron_bpf = Spectrum(*loader, bpfmuonlen_axis, kElectronCutBPFTrk);
  Spectrum bpfprotonlen_proton_prong = Spectrum(*loader, bpfprotonlen_axis, kProton);
  Spectrum bpfprotonlen_pimu_prong = Spectrum(*loader, bpfprotonlen_axis, kPiMu);
  Spectrum bpfprotonlen_electron_prong = Spectrum(*loader, bpfprotonlen_axis, kElectron);
  Spectrum bpfpionlen_proton_prong = Spectrum(*loader, bpfpionlen_axis, kProton);
  Spectrum bpfpionlen_pimu_prong = Spectrum(*loader, bpfpionlen_axis, kPiMu);
  Spectrum bpfpionlen_electron_prong = Spectrum(*loader, bpfpionlen_axis, kElectron);
  Spectrum bpfmuonlen_proton_prong = Spectrum(*loader, bpfmuonlen_axis, kProton);
  Spectrum bpfmuonlen_pimu_prong = Spectrum(*loader, bpfmuonlen_axis, kPiMu);
  Spectrum bpfmuonlen_electron_prong = Spectrum(*loader, bpfmuonlen_axis, kElectron);

  const HistAxis singleprongx("X (cm)", Binning::Simple(100,-200,200), kSingleProngStrtX);
  const HistAxis singleprongy("Y (cm)", Binning::Simple(100,-200,200), kSingleProngStrtY);
  const HistAxis singleprongz("Z (cm)", Binning::Simple(100,0,400), kSingleProngStrtZ);
  const HistAxis singleprongnhit("Number of Hits", Binning::Simple(100,0,100), kSingleProngNHit);
  const HistAxis singleprongbpfprotonx("X (cm)", Binning::Simple(100,-200,200), kSingleProngBPFProtonStrtX);
  const HistAxis singleprongbpfprotony("Y (cm)", Binning::Simple(100,-200,200), kSingleProngBPFProtonStrtY);
  const HistAxis singleprongbpfprotonz("Z (cm)", Binning::Simple(100,0,400), kSingleProngBPFProtonStrtZ);
  const HistAxis singleprongbpfprotonnhit("Number of Hits", Binning::Simple(100,0,100), kSingleProngBPFProtonNHit);
  const HistAxis singleprongbpfpionx("X (cm)", Binning::Simple(100,-200,200), kSingleProngBPFPionStrtX);
  const HistAxis singleprongbpfpiony("Y (cm)", Binning::Simple(100,-200,200), kSingleProngBPFPionStrtY);
  const HistAxis singleprongbpfpionz("Z (cm)", Binning::Simple(100,0,400), kSingleProngBPFPionStrtZ);
  const HistAxis singleprongbpfpionnhit("Number of Hits", Binning::Simple(100,0,100), kSingleProngBPFPionNHit);
  const HistAxis singleprongbpfmuonx("X (cm)", Binning::Simple(100,-200,200), kSingleProngBPFMuonStrtX);
  const HistAxis singleprongbpfmuony("Y (cm)", Binning::Simple(100,-200,200), kSingleProngBPFMuonStrtY);
  const HistAxis singleprongbpfmuonz("Z (cm)", Binning::Simple(100,0,400), kSingleProngBPFMuonStrtZ);
  const HistAxis singleprongbpfmuonnhit("Number of Hits", Binning::Simple(100,0,100), kSingleProngBPFMuonNHit);
  Spectrum singleprongx_proton_bl = Spectrum(*loader, singleprongx, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongy_proton_bl = Spectrum(*loader, singleprongy, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongz_proton_bl = Spectrum(*loader, singleprongz, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongnhit_proton_bl = Spectrum(*loader, singleprongnhit, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongx_pimu_bl = Spectrum(*loader, singleprongx, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongy_pimu_bl = Spectrum(*loader, singleprongy, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongz_pimu_bl = Spectrum(*loader, singleprongz, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongnhit_pimu_bl = Spectrum(*loader, singleprongnhit, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongx_electron_bl = Spectrum(*loader, singleprongx, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongy_electron_bl = Spectrum(*loader, singleprongy, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongz_electron_bl = Spectrum(*loader, singleprongz, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongnhit_electron_bl = Spectrum(*loader, singleprongnhit, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongbpfprotonx_proton_bl = Spectrum(*loader, singleprongbpfprotonx, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongbpfprotony_proton_bl = Spectrum(*loader, singleprongbpfprotony, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongbpfprotonz_proton_bl = Spectrum(*loader, singleprongbpfprotonz, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongbpfprotonnhit_proton_bl = Spectrum(*loader, singleprongbpfprotonnhit, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongbpfprotonx_pimu_bl = Spectrum(*loader, singleprongbpfprotonx, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongbpfprotony_pimu_bl = Spectrum(*loader, singleprongbpfprotony, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongbpfprotonz_pimu_bl = Spectrum(*loader, singleprongbpfprotonz, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongbpfprotonnhit_pimu_bl = Spectrum(*loader, singleprongbpfprotonnhit, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongbpfprotonx_electron_bl = Spectrum(*loader, singleprongbpfprotonx, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongbpfprotony_electron_bl = Spectrum(*loader, singleprongbpfprotony, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongbpfprotonz_electron_bl = Spectrum(*loader, singleprongbpfprotonz, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongbpfprotonnhit_electron_bl = Spectrum(*loader, singleprongbpfprotonnhit, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongbpfpionx_proton_bl = Spectrum(*loader, singleprongbpfpionx, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongbpfpiony_proton_bl = Spectrum(*loader, singleprongbpfpiony, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongbpfpionz_proton_bl = Spectrum(*loader, singleprongbpfpionz, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongbpfpionnhit_proton_bl = Spectrum(*loader, singleprongbpfpionnhit, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongbpfpionx_pimu_bl = Spectrum(*loader, singleprongbpfpionx, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongbpfpiony_pimu_bl = Spectrum(*loader, singleprongbpfpiony, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongbpfpionz_pimu_bl = Spectrum(*loader, singleprongbpfpionz, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongbpfpionnhit_pimu_bl = Spectrum(*loader, singleprongbpfpionnhit, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongbpfpionx_electron_bl = Spectrum(*loader, singleprongbpfpionx, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongbpfpiony_electron_bl = Spectrum(*loader, singleprongbpfpiony, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongbpfpionz_electron_bl = Spectrum(*loader, singleprongbpfpionz, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongbpfpionnhit_electron_bl = Spectrum(*loader, singleprongbpfpionnhit, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongbpfmuonx_proton_bl = Spectrum(*loader, singleprongbpfmuonx, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongbpfmuony_proton_bl = Spectrum(*loader, singleprongbpfmuony, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongbpfmuonz_proton_bl = Spectrum(*loader, singleprongbpfmuonz, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongbpfmuonnhit_proton_bl = Spectrum(*loader, singleprongbpfmuonnhit, kBeamlineProton&&kSingleProngSlice);
  Spectrum singleprongbpfmuonx_pimu_bl = Spectrum(*loader, singleprongbpfmuonx, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongbpfmuony_pimu_bl = Spectrum(*loader, singleprongbpfmuony, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongbpfmuonz_pimu_bl = Spectrum(*loader, singleprongbpfmuonz, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongbpfmuonnhit_pimu_bl = Spectrum(*loader, singleprongbpfmuonnhit, kBeamlinePiMu&&kSingleProngSlice);
  Spectrum singleprongbpfmuonx_electron_bl = Spectrum(*loader, singleprongbpfmuonx, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongbpfmuony_electron_bl = Spectrum(*loader, singleprongbpfmuony, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongbpfmuonz_electron_bl = Spectrum(*loader, singleprongbpfmuonz, kBeamlineElectron&&kSingleProngSlice);
  Spectrum singleprongbpfmuonnhit_electron_bl = Spectrum(*loader, singleprongbpfmuonnhit, kBeamlineElectron&&kSingleProngSlice);

  loader->Go();

  TFile* outFile = new TFile("SelectionComparison.root", "RECREATE");

  p_proton_prong.SaveTo(outFile->mkdir("p_proton_prong"), "p_proton_prong");
  p_pimu_prong.SaveTo(outFile->mkdir("p_pimu_prong"), "p_pimu_prong");
  p_electron_prong.SaveTo(outFile->mkdir("p_electron_prong"), "p_electron_prong");
  p_proton_bpf.SaveTo(outFile->mkdir("p_proton_bpf"), "p_proton_bpf");
  p_pimu_bpf.SaveTo(outFile->mkdir("p_pimu_bpf"), "p_pimu_bpf");
  p_electron_bpf.SaveTo(outFile->mkdir("p_electron_bpf"), "p_electron_bpf");
  p_proton_win.SaveTo(outFile->mkdir("p_proton_win"), "p_proton_win");
  p_pimu_win.SaveTo(outFile->mkdir("p_pimu_win"), "p_pimu_win");
  p_electron_win.SaveTo(outFile->mkdir("p_electron_win"), "p_electron_win");
  p_proton_cos.SaveTo(outFile->mkdir("p_proton_cos"), "p_proton_cos");
  p_pimu_cos.SaveTo(outFile->mkdir("p_pimu_cos"), "p_pimu_cos");
  p_electron_cos.SaveTo(outFile->mkdir("p_electron_cos"), "p_electron_cos");

  bpfprotonvalid_proton_prong.SaveTo(outFile->mkdir("bpfprotonvalid_proton_prong"), "bpfprotonvalid_proton_prong");
  bpfprotonvalid_pimu_prong.SaveTo(outFile->mkdir("bpfprotonvalid_pimu_prong"), "bpfprotonvalid_pimu_prong");
  bpfprotonvalid_electron_prong.SaveTo(outFile->mkdir("bpfprotonvalid_electron_prong"), "bpfprotonvalid_electron_prong");
  bpfpionvalid_proton_prong.SaveTo(outFile->mkdir("bpfpionvalid_proton_prong"), "bpfpionvalid_proton_prong");
  bpfpionvalid_pimu_prong.SaveTo(outFile->mkdir("bpfpionvalid_pimu_prong"), "bpfpionvalid_pimu_prong");
  bpfpionvalid_electron_prong.SaveTo(outFile->mkdir("bpfpionvalid_electron_prong"), "bpfpionvalid_electron_prong");
  bpfmuonvalid_proton_prong.SaveTo(outFile->mkdir("bpfmuonvalid_proton_prong"), "bpfmuonvalid_proton_prong");
  bpfmuonvalid_pimu_prong.SaveTo(outFile->mkdir("bpfmuonvalid_pimu_prong"), "bpfmuonvalid_pimu_prong");
  bpfmuonvalid_electron_prong.SaveTo(outFile->mkdir("bpfmuonvalid_electron_prong"), "bpfmuonvalid_electron_prong");

  pronge_proton_prong.SaveTo(outFile->mkdir("pronge_proton_prong"), "pronge_proton_prong");
  pronge_pimu_prong.SaveTo(outFile->mkdir("pronge_pimu_prong"), "pronge_pimu_prong");
  pronge_electron_prong.SaveTo(outFile->mkdir("pronge_electron_prong"), "pronge_electron_prong");
  pronge_proton_bpf.SaveTo(outFile->mkdir("pronge_proton_bpf"), "pronge_proton_bpf");
  pronge_pimu_bpf.SaveTo(outFile->mkdir("pronge_pimu_bpf"), "pronge_pimu_bpf");
  pronge_electron_bpf.SaveTo(outFile->mkdir("pronge_electron_bpf"), "pronge_electron_bpf");

  bpfe_proton_prong.SaveTo(outFile->mkdir("bpfe_proton_prong"), "bpfe_proton_prong");
  bpfe_pimu_prong.SaveTo(outFile->mkdir("bpfe_pimu_prong"), "bpfe_pimu_prong");
  bpfe_electron_prong.SaveTo(outFile->mkdir("bpfe_electron_prong"), "bpfe_electron_prong");
  bpfe_proton_bpf.SaveTo(outFile->mkdir("bpfe_proton_bpf"), "bpfe_proton_bpf");
  bpfe_pimu_bpf.SaveTo(outFile->mkdir("bpfe_pimu_bpf"), "bpfe_pimu_bpf");
  bpfe_electron_bpf.SaveTo(outFile->mkdir("bpfe_electron_bpf"), "bpfe_electron_bpf");

  bpflen_proton_prong.SaveTo(outFile->mkdir("bpflen_proton_prong"), "bpflen_proton_prong");
  bpflen_pimu_prong.SaveTo(outFile->mkdir("bpflen_pimu_prong"), "bpflen_pimu_prong");
  bpflen_electron_prong.SaveTo(outFile->mkdir("bpflen_electron_prong"), "bpflen_electron_prong");
  bpflen_proton_bpf.SaveTo(outFile->mkdir("bpflen_proton_bpf"), "bpflen_proton_bpf");
  bpflen_pimu_bpf.SaveTo(outFile->mkdir("bpflen_pimu_bpf"), "bpflen_pimu_bpf");
  bpflen_electron_bpf.SaveTo(outFile->mkdir("bpflen_electron_bpf"), "bpflen_electron_bpf");

  prongx_proton_prong.SaveTo(outFile->mkdir("prongx_proton_prong"), "prongx_proton_prong");
  prongy_proton_prong.SaveTo(outFile->mkdir("prongy_proton_prong"), "prongy_proton_prong");
  prongz_proton_prong.SaveTo(outFile->mkdir("prongz_proton_prong"), "prongz_proton_prong");
  prongx_pimu_prong.SaveTo(outFile->mkdir("prongx_pimu_prong"), "prongx_pimu_prong");
  prongy_pimu_prong.SaveTo(outFile->mkdir("prongy_pimu_prong"), "prongy_pimu_prong");
  prongz_pimu_prong.SaveTo(outFile->mkdir("prongz_pimu_prong"), "prongz_pimu_prong");
  prongx_electron_prong.SaveTo(outFile->mkdir("prongx_electron_prong"), "prongx_electron_prong");
  prongy_electron_prong.SaveTo(outFile->mkdir("prongy_electron_prong"), "prongy_electron_prong");
  prongz_electron_prong.SaveTo(outFile->mkdir("prongz_electron_prong"), "prongz_electron_prong");

  bpfx_proton_prong.SaveTo(outFile->mkdir("bpfx_proton_prong"), "bpfx_proton_prong");
  bpfy_proton_prong.SaveTo(outFile->mkdir("bpfy_proton_prong"), "bpfy_proton_prong");
  bpfz_proton_prong.SaveTo(outFile->mkdir("bpfz_proton_prong"), "bpfz_proton_prong");
  bpfx_pimu_prong.SaveTo(outFile->mkdir("bpfx_pimu_prong"), "bpfx_pimu_prong");
  bpfy_pimu_prong.SaveTo(outFile->mkdir("bpfy_pimu_prong"), "bpfy_pimu_prong");
  bpfz_pimu_prong.SaveTo(outFile->mkdir("bpfz_pimu_prong"), "bpfz_pimu_prong");
  bpfx_electron_prong.SaveTo(outFile->mkdir("bpfx_electron_prong"), "bpfx_electron_prong");
  bpfy_electron_prong.SaveTo(outFile->mkdir("bpfy_electron_prong"), "bpfy_electron_prong");
  bpfz_electron_prong.SaveTo(outFile->mkdir("bpfz_electron_prong"), "bpfz_electron_prong");

  prongvbpfx_proton_prong.SaveTo(outFile->mkdir("prongvbpfx_proton_prong"), "prongvbpfx_proton_prong");
  prongvbpfy_proton_prong.SaveTo(outFile->mkdir("prongvbpfy_proton_prong"), "prongvbpfy_proton_prong");
  prongvbpfz_proton_prong.SaveTo(outFile->mkdir("prongvbpfz_proton_prong"), "prongvbpfz_proton_prong");
  prongvbpfx_pimu_prong.SaveTo(outFile->mkdir("prongvbpfx_pimu_prong"), "prongvbpfx_pimu_prong");
  prongvbpfy_pimu_prong.SaveTo(outFile->mkdir("prongvbpfy_pimu_prong"), "prongvbpfy_pimu_prong");
  prongvbpfz_pimu_prong.SaveTo(outFile->mkdir("prongvbpfz_pimu_prong"), "prongvbpfz_pimu_prong");
  prongvbpfx_electron_prong.SaveTo(outFile->mkdir("prongvbpfx_electron_prong"), "prongvbpfx_electron_prong");
  prongvbpfy_electron_prong.SaveTo(outFile->mkdir("prongvbpfy_electron_prong"), "prongvbpfy_electron_prong");
  prongvbpfz_electron_prong.SaveTo(outFile->mkdir("prongvbpfz_electron_prong"), "prongvbpfz_electron_prong");

  wintrklen_proton.SaveTo(outFile->mkdir("wintrklen_proton"), "wintrklen_proton");
  wintrklen_pimu.SaveTo(outFile->mkdir("wintrklen_pimu"), "wintrklen_pimu");
  wintrklen_electron.SaveTo(outFile->mkdir("wintrklen_electron"), "wintrklen_electron");
  costrklen_proton.SaveTo(outFile->mkdir("costrklen_proton"), "costrklen_proton");
  costrklen_pimu.SaveTo(outFile->mkdir("costrklen_pimu"), "costrklen_pimu");
  costrklen_electron.SaveTo(outFile->mkdir("costrklen_electron"), "costrklen_electron");

  bpfprotonlen_proton_bpf.SaveTo(outFile->mkdir("bpfprotonlen_proton_bpf"), "bpfprotonlen_proton_bpf");
  bpfprotonlen_pimu_bpf.SaveTo(outFile->mkdir("bpfprotonlen_pimu_bpf"), "bpfprotonlen_pimu_bpf");
  bpfprotonlen_electron_bpf.SaveTo(outFile->mkdir("bpfprotonlen_electron_bpf"), "bpfprotonlen_electron_bpf");
  bpfpionlen_proton_bpf.SaveTo(outFile->mkdir("bpfpionlen_proton_bpf"), "bpfpionlen_proton_bpf");
  bpfpionlen_pimu_bpf.SaveTo(outFile->mkdir("bpfpionlen_pimu_bpf"), "bpfpionlen_pimu_bpf");
  bpfpionlen_electron_bpf.SaveTo(outFile->mkdir("bpfpionlen_electron_bpf"), "bpfpionlen_electron_bpf");
  bpfmuonlen_proton_bpf.SaveTo(outFile->mkdir("bpfmuonlen_proton_bpf"), "bpfmuonlen_proton_bpf");
  bpfmuonlen_pimu_bpf.SaveTo(outFile->mkdir("bpfmuonlen_pimu_bpf"), "bpfmuonlen_pimu_bpf");
  bpfmuonlen_electron_bpf.SaveTo(outFile->mkdir("bpfmuonlen_electron_bpf"), "bpfmuonlen_electron_bpf");
  bpfprotonlen_proton_prong.SaveTo(outFile->mkdir("bpfprotonlen_proton_prong"), "bpfprotonlen_proton_prong");
  bpfprotonlen_pimu_prong.SaveTo(outFile->mkdir("bpfprotonlen_pimu_prong"), "bpfprotonlen_pimu_prong");
  bpfprotonlen_electron_prong.SaveTo(outFile->mkdir("bpfprotonlen_electron_prong"), "bpfprotonlen_electron_prong");
  bpfpionlen_proton_prong.SaveTo(outFile->mkdir("bpfpionlen_proton_prong"), "bpfpionlen_proton_prong");
  bpfpionlen_pimu_prong.SaveTo(outFile->mkdir("bpfpionlen_pimu_prong"), "bpfpionlen_pimu_prong");
  bpfpionlen_electron_prong.SaveTo(outFile->mkdir("bpfpionlen_electron_prong"), "bpfpionlen_electron_prong");
  bpfmuonlen_proton_prong.SaveTo(outFile->mkdir("bpfmuonlen_proton_prong"), "bpfmuonlen_proton_prong");
  bpfmuonlen_pimu_prong.SaveTo(outFile->mkdir("bpfmuonlen_pimu_prong"), "bpfmuonlen_pimu_prong");
  bpfmuonlen_electron_prong.SaveTo(outFile->mkdir("bpfmuonlen_electron_prong"), "bpfmuonlen_electron_prong");

  singleprongx_proton_bl.SaveTo(outFile->mkdir("singleprongx_proton_bl"), "singleprongx_proton_bl");
  singleprongy_proton_bl.SaveTo(outFile->mkdir("singleprongy_proton_bl"), "singleprongy_proton_bl");
  singleprongz_proton_bl.SaveTo(outFile->mkdir("singleprongz_proton_bl"), "singleprongz_proton_bl");
  singleprongnhit_proton_bl.SaveTo(outFile->mkdir("singleprongnhit_proton_bl"), "singleprongnhit_proton_bl");
  singleprongx_pimu_bl.SaveTo(outFile->mkdir("singleprongx_pimu_bl"), "singleprongx_pimu_bl");
  singleprongy_pimu_bl.SaveTo(outFile->mkdir("singleprongy_pimu_bl"), "singleprongy_pimu_bl");
  singleprongz_pimu_bl.SaveTo(outFile->mkdir("singleprongz_pimu_bl"), "singleprongz_pimu_bl");
  singleprongnhit_pimu_bl.SaveTo(outFile->mkdir("singleprongnhit_pimu_bl"), "singleprongnhit_pimu_bl");
  singleprongx_electron_bl.SaveTo(outFile->mkdir("singleprongx_electron_bl"), "singleprongx_electron_bl");
  singleprongy_electron_bl.SaveTo(outFile->mkdir("singleprongy_electron_bl"), "singleprongy_electron_bl");
  singleprongz_electron_bl.SaveTo(outFile->mkdir("singleprongz_electron_bl"), "singleprongz_electron_bl");
  singleprongnhit_electron_bl.SaveTo(outFile->mkdir("singleprongnhit_electron_bl"), "singleprongnhit_electron_bl");
  singleprongbpfprotonx_proton_bl.SaveTo(outFile->mkdir("singleprongbpfprotonx_proton_bl"), "singleprongbpfprotonx_proton_bl");
  singleprongbpfprotony_proton_bl.SaveTo(outFile->mkdir("singleprongbpfprotony_proton_bl"), "singleprongbpfprotony_proton_bl");
  singleprongbpfprotonz_proton_bl.SaveTo(outFile->mkdir("singleprongbpfprotonz_proton_bl"), "singleprongbpfprotonz_proton_bl");
  singleprongbpfprotonnhit_proton_bl.SaveTo(outFile->mkdir("singleprongbpfprotonnhit_proton_bl"), "singleprongbpfprotonnhit_proton_bl");
  singleprongbpfprotonx_pimu_bl.SaveTo(outFile->mkdir("singleprongbpfprotonx_pimu_bl"), "singleprongbpfprotonx_pimu_bl");
  singleprongbpfprotony_pimu_bl.SaveTo(outFile->mkdir("singleprongbpfprotony_pimu_bl"), "singleprongbpfprotony_pimu_bl");
  singleprongbpfprotonz_pimu_bl.SaveTo(outFile->mkdir("singleprongbpfprotonz_pimu_bl"), "singleprongbpfprotonz_pimu_bl");
  singleprongbpfprotonnhit_pimu_bl.SaveTo(outFile->mkdir("singleprongbpfprotonnhit_pimu_bl"), "singleprongbpfprotonnhit_pimu_bl");
  singleprongbpfprotonx_electron_bl.SaveTo(outFile->mkdir("singleprongbpfprotonx_electron_bl"), "singleprongbpfprotonx_electron_bl");
  singleprongbpfprotony_electron_bl.SaveTo(outFile->mkdir("singleprongbpfprotony_electron_bl"), "singleprongbpfprotony_electron_bl");
  singleprongbpfprotonz_electron_bl.SaveTo(outFile->mkdir("singleprongbpfprotonz_electron_bl"), "singleprongbpfprotonz_electron_bl");
  singleprongbpfprotonnhit_electron_bl.SaveTo(outFile->mkdir("singleprongbpfprotonnhit_electron_bl"), "singleprongbpfprotonnhit_electron_bl");
  singleprongbpfpionx_proton_bl.SaveTo(outFile->mkdir("singleprongbpfpionx_proton_bl"), "singleprongbpfpionx_proton_bl");
  singleprongbpfpiony_proton_bl.SaveTo(outFile->mkdir("singleprongbpfpiony_proton_bl"), "singleprongbpfpiony_proton_bl");
  singleprongbpfpionz_proton_bl.SaveTo(outFile->mkdir("singleprongbpfpionz_proton_bl"), "singleprongbpfpionz_proton_bl");
  singleprongbpfpionnhit_proton_bl.SaveTo(outFile->mkdir("singleprongbpfpionnhit_proton_bl"), "singleprongbpfpionnhit_proton_bl");
  singleprongbpfpionx_pimu_bl.SaveTo(outFile->mkdir("singleprongbpfpionx_pimu_bl"), "singleprongbpfpionx_pimu_bl");
  singleprongbpfpiony_pimu_bl.SaveTo(outFile->mkdir("singleprongbpfpiony_pimu_bl"), "singleprongbpfpiony_pimu_bl");
  singleprongbpfpionz_pimu_bl.SaveTo(outFile->mkdir("singleprongbpfpionz_pimu_bl"), "singleprongbpfpionz_pimu_bl");
  singleprongbpfpionnhit_pimu_bl.SaveTo(outFile->mkdir("singleprongbpfpionnhit_pimu_bl"), "singleprongbpfpionnhit_pimu_bl");
  singleprongbpfpionx_electron_bl.SaveTo(outFile->mkdir("singleprongbpfpionx_electron_bl"), "singleprongbpfpionx_electron_bl");
  singleprongbpfpiony_electron_bl.SaveTo(outFile->mkdir("singleprongbpfpiony_electron_bl"), "singleprongbpfpiony_electron_bl");
  singleprongbpfpionz_electron_bl.SaveTo(outFile->mkdir("singleprongbpfpionz_electron_bl"), "singleprongbpfpionz_electron_bl");
  singleprongbpfpionnhit_electron_bl.SaveTo(outFile->mkdir("singleprongbpfpionnhit_electron_bl"), "singleprongbpfpionnhit_electron_bl");
  singleprongbpfmuonx_proton_bl.SaveTo(outFile->mkdir("singleprongbpfmuonx_proton_bl"), "singleprongbpfmuonx_proton_bl");
  singleprongbpfmuony_proton_bl.SaveTo(outFile->mkdir("singleprongbpfmuony_proton_bl"), "singleprongbpfmuony_proton_bl");
  singleprongbpfmuonz_proton_bl.SaveTo(outFile->mkdir("singleprongbpfmuonz_proton_bl"), "singleprongbpfmuonz_proton_bl");
  singleprongbpfmuonnhit_proton_bl.SaveTo(outFile->mkdir("singleprongbpfmuonnhit_proton_bl"), "singleprongbpfmuonnhit_proton_bl");
  singleprongbpfmuonx_pimu_bl.SaveTo(outFile->mkdir("singleprongbpfmuonx_pimu_bl"), "singleprongbpfmuonx_pimu_bl");
  singleprongbpfmuony_pimu_bl.SaveTo(outFile->mkdir("singleprongbpfmuony_pimu_bl"), "singleprongbpfmuony_pimu_bl");
  singleprongbpfmuonz_pimu_bl.SaveTo(outFile->mkdir("singleprongbpfmuonz_pimu_bl"), "singleprongbpfmuonz_pimu_bl");
  singleprongbpfmuonnhit_pimu_bl.SaveTo(outFile->mkdir("singleprongbpfmuonnhit_pimu_bl"), "singleprongbpfmuonnhit_pimu_bl");
  singleprongbpfmuonx_electron_bl.SaveTo(outFile->mkdir("singleprongbpfmuonx_electron_bl"), "singleprongbpfmuonx_electron_bl");
  singleprongbpfmuony_electron_bl.SaveTo(outFile->mkdir("singleprongbpfmuony_electron_bl"), "singleprongbpfmuony_electron_bl");
  singleprongbpfmuonz_electron_bl.SaveTo(outFile->mkdir("singleprongbpfmuonz_electron_bl"), "singleprongbpfmuonz_electron_bl");
  singleprongbpfmuonnhit_electron_bl.SaveTo(outFile->mkdir("singleprongbpfmuonnhit_electron_bl"), "singleprongbpfmuonnhit_electron_bl");

  outFile->Close();

}
