#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"

void compareP3KeepUpAndProdReco() {

  TFile* keepUpFile
    = TFile::Open("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period3/R21-01-28-testbeam-production.a/TBRecoAna_r100985-r101483.root",
		  "READ");
  TFile* prodFile
    = TFile::Open("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period3/R21-07-27-testbeam-production.a/TBRecoAna_r100985-r101483.root",
		  "READ");

  TTree* keepUpTree = (TTree*)keepUpFile->Get("tbrecoana/evts");
  TTree* prodTree = (TTree*)prodFile->Get("tbrecoana/evts");

  Double_t kWCMom = 0, pWCMom = 0;
  keepUpTree->SetBranchAddress("wcmom", &kWCMom);
  prodTree->SetBranchAddress("wcmom", &pWCMom);

  Double_t kToF = 0, pToF = 0;
  keepUpTree->SetBranchAddress("toftime", &kToF);
  prodTree->SetBranchAddress("toftime", &pToF);

  Double_t kMagDist = 0, pMagDist = 0;
  keepUpTree->SetBranchAddress("wcMagDist", &kMagDist);
  prodTree->SetBranchAddress("wcMagDist", &pMagDist);

  std::vector<Double_t> *kBPFTrackStrtX = nullptr, *kBPFTrackStrtY = nullptr, *kBPFTrackStrtZ = nullptr, *kBPFTrackMinTime = nullptr,
    *pBPFTrackStrtX = nullptr, *pBPFTrackStrtY = nullptr, *pBPFTrackStrtZ = nullptr, *pBPFTrackMinTime = nullptr;
  keepUpTree->SetBranchAddress("bpfStrtX", &kBPFTrackStrtX);
  keepUpTree->SetBranchAddress("bpfStrtY", &kBPFTrackStrtY);
  keepUpTree->SetBranchAddress("bpfStrtZ", &kBPFTrackStrtZ);
  keepUpTree->SetBranchAddress("bpfTrkMinTime", &kBPFTrackMinTime);
  prodTree->SetBranchAddress("bpfStrtX", &pBPFTrackStrtX);
  prodTree->SetBranchAddress("bpfStrtY", &pBPFTrackStrtY);
  prodTree->SetBranchAddress("bpfStrtZ", &pBPFTrackStrtZ);
  prodTree->SetBranchAddress("bpfTrkMinTime", &pBPFTrackMinTime);

  std::vector<Double_t> *kWinTrackStrtX = nullptr, *kWinTrackStrtY = nullptr, *kWinTrackStrtZ = nullptr, *kWinTrackMinTime = nullptr,
    *pWinTrackStrtX = nullptr, *pWinTrackStrtY = nullptr, *pWinTrackStrtZ = nullptr, *pWinTrackMinTime = nullptr;
  keepUpTree->SetBranchAddress("winTrkStrtX", &kWinTrackStrtX);
  keepUpTree->SetBranchAddress("winTrkStrtY", &kWinTrackStrtY);
  keepUpTree->SetBranchAddress("winTrkStrtZ", &kWinTrackStrtZ);
  keepUpTree->SetBranchAddress("winTrkMinTime", &kWinTrackMinTime);
  prodTree->SetBranchAddress("winTrkStrtX", &pWinTrackStrtX);
  prodTree->SetBranchAddress("winTrkStrtY", &pWinTrackStrtY);
  prodTree->SetBranchAddress("winTrkStrtZ", &pWinTrackStrtZ);
  prodTree->SetBranchAddress("winTrkMinTime", &pWinTrackMinTime);

  TH1* kNumBPFTracks = new TH1F("kNumBPFTracks", ";Number of BPF Tracks in Beamline Window;", 5, 0, 5);
  TH1* pNumBPFTracks = new TH1F("pNumBPFTracks", ";Number of BPF Tracks in Beamline Window;", 5, 0, 5);
  TH1* kNumWinTracks = new TH1F("kNumWinTracks", ";Number of Win Tracks in Beamline Window;", 5, 0, 5);
  TH1* pNumWinTracks = new TH1F("pNumWinTracks", ";Number of Win Tracks in Beamline Window;", 5, 0, 5);

  for (unsigned int kentry = 0; kentry < keepUpTree->GetEntriesFast(); ++kentry) {
    keepUpTree->GetEntry(kentry);
    if (kWCMom > 0 and kToF > 30 and kToF < 80 and kMagDist < 5) {
      unsigned int nbpf = 0, nwin = 0;
      for (unsigned int bpf = 0; bpf < kBPFTrackStrtX->size(); ++bpf)
	if (abs(kBPFTrackStrtX->at(bpf)) < 20 and kBPFTrackStrtY->at(bpf) > -25 and kBPFTrackStrtY->at(bpf) < 15 and
	    kBPFTrackStrtZ->at(bpf) < 18 and kBPFTrackMinTime->at(bpf) > 45000 and kBPFTrackMinTime->at(bpf) < 55000)
	  ++nbpf;
      for (unsigned int win = 0; win < kWinTrackStrtX->size(); ++win)
	if (abs(kWinTrackStrtX->at(win)) < 20 and kWinTrackStrtY->at(win) > -25 and kWinTrackStrtY->at(win) < 15 and
	    kWinTrackStrtZ->at(win) < 18 and kWinTrackMinTime->at(win) > 45000 and kWinTrackMinTime->at(win) < 55000)
	  ++nwin;
      kNumBPFTracks->Fill(nbpf);
      kNumWinTracks->Fill(nwin);
    }
  }

  for (unsigned int pentry = 0; pentry < prodTree->GetEntriesFast(); ++pentry) {
    prodTree->GetEntry(pentry);
    if (pWCMom > 0 and pToF > 30 and pToF < 80 and pMagDist < 5) {
      unsigned int nbpf = 0, nwin = 0;
      for (unsigned int bpf = 0; bpf < pBPFTrackStrtX->size(); ++bpf)
	if (abs(pBPFTrackStrtX->at(bpf)) < 20 and pBPFTrackStrtY->at(bpf) > -25 and pBPFTrackStrtY->at(bpf) < 15 and
	    pBPFTrackStrtZ->at(bpf) < 18 and pBPFTrackMinTime->at(bpf) > 45000 and pBPFTrackMinTime->at(bpf) < 55000)
	  ++nbpf;
      for (unsigned int win = 0; win < pWinTrackStrtX->size(); ++win)
	if (abs(pWinTrackStrtX->at(win)) < 20 and pWinTrackStrtY->at(win) > -25 and pWinTrackStrtY->at(win) < 15 and
	    pWinTrackStrtZ->at(win) < 18 and pWinTrackMinTime->at(win) > 45000 and pWinTrackMinTime->at(win) < 55000)
	  ++nwin;
      pNumBPFTracks->Fill(nbpf);
      pNumWinTracks->Fill(nwin);
    }
  }

  TFile* outFile = new TFile("P3RecoComparisons.root", "RECREATE");

  TCanvas* canv = new TCanvas("canv", "", 800, 600);
  kNumBPFTracks->SetLineColor(kBlack);
  kNumBPFTracks->Draw("hist");
  pNumBPFTracks->SetLineColor(kRed);
  pNumBPFTracks->Draw("hist same");
  outFile->cd();
  kNumBPFTracks->Write();
  pNumBPFTracks->Write();
  canv->Write("NumBPFTracks");
  
  canv->cd();
  canv->Clear();
  kNumWinTracks->SetLineColor(kBlack);
  kNumWinTracks->Draw("hist");
  pNumWinTracks->SetLineColor(kRed);
  pNumWinTracks->Draw("hist same");
  outFile->cd();
  kNumWinTracks->Write();
  pNumWinTracks->Write();
  canv->Write("NumWinTracks");

  outFile->Close();

}
