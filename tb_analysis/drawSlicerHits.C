// root
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TH1I.h"
#include "TH2I.h"
#include "TH2F.h"
#include "TVector3.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TText.h"

// stl
#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include "/nova/app/users/wallbank/test_testbeam/TestBeamAna/TestBeamCuts.h"

// --------------------------------------------------------------------------------------------------
std::vector<std::vector<TVector3> > BuildCellGeoMap();

// --------------------------------------------------------------------------------------------------
void FormatHist(TH1* hist);

// --------------------------------------------------------------------------------------------------
void drawSlicerHits(int nevents, bool geo = true) {

  gROOT->SetBatch(1);

  std::vector<std::vector<TVector3> > cellGeo = BuildCellGeoMap();

  TFile* inFile
    = new TFile("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period3/R21-07-27-testbeam-production.a/TBRecoAna_r101400-r101483.root",
		"READ");
  TTree* inTree = (TTree*)inFile->Get("tbrecoana/evts");

  TCanvas* canv = new TCanvas("canv", "", 1600, 600);
  TH2 *top_view = nullptr, *side_view = nullptr, *top_view_slice = nullptr, *side_view_slice = nullptr;
  if (geo) {
    top_view = new TH2F("TopEVD", ";z (cm);x (cm);", 75, 0, 420, 79, -140, 140);
    side_view = new TH2F("SideEVD", ";z (cm);y (cm);", 75, 0, 420, 79, -140, 140);
    top_view_slice = new TH2F("TopEVDSlice", ";z (cm);x (cm);", 75, 0, 420, 79, -140, 140);
    side_view_slice = new TH2F("SideEVDSlice", ";z (cm);y (cm);", 75, 0, 420, 79, -140, 140);
  } else {
    top_view = new TH2F("TopEVD", ";Plane;Cell;", 63, 0, 63, 64, 0, 64);
    side_view = new TH2F("SideEVD", ";Plane;Cell;", 63, 0, 63, 64, 0, 64);
    top_view_slice = new TH2F("TopEVDSlice", ";Plane;Cell;", 63, 0, 63, 64, 0, 64);
    side_view_slice = new TH2F("SideEVDSlice", ";Plane;Cell;", 63, 0, 63, 64, 0, 64);
  }
  FormatHist(top_view);
  FormatHist(side_view);
  FormatHist(top_view_slice);
  FormatHist(side_view_slice);

  gROOT->cd();
  TTree* evts_cuts = (TTree*)inTree->CopyTree(particle);

  Int_t run, subrun, event;
  evts_cuts->SetBranchAddress("run",    &run);
  evts_cuts->SetBranchAddress("subrun", &subrun);
  evts_cuts->SetBranchAddress("event",  &event);

  Double_t mc7mag;
  evts_cuts->SetBranchAddress("mc7mag", &mc7mag);

  Double_t toftime, wcmom, ckovadc;
  evts_cuts->SetBranchAddress("toftime", &toftime);
  evts_cuts->SetBranchAddress("wcmom", &wcmom);
  evts_cuts->SetBranchAddress("ckovadc", &ckovadc);

  std::vector<Int_t> *hitSlice = nullptr, *hitPlane = nullptr, *hitCell = nullptr;
  std::vector<Double_t> *hitTime = nullptr;
  evts_cuts->SetBranchAddress("hitSlice", &hitSlice);
  evts_cuts->SetBranchAddress("hitPlane", &hitPlane);
  evts_cuts->SetBranchAddress("hitCell", &hitCell);
  evts_cuts->SetBranchAddress("hitTime", &hitTime);

  std::vector<Int_t> *winTrkSlice = nullptr;
  std::vector<Double_t> *winTrkMinTime = nullptr, *winTrkNhit = nullptr,
    *winTrkStrtX = nullptr, *winTrkStrtY = nullptr, *winTrkStrtZ = nullptr,
    *winTrkStopX = nullptr, *winTrkStopY = nullptr, *winTrkStopZ = nullptr;
  evts_cuts->SetBranchAddress("winTrkSlice",   &winTrkSlice);
  evts_cuts->SetBranchAddress("winTrkMinTime", &winTrkMinTime);
  evts_cuts->SetBranchAddress("winTrkNhit",    &winTrkNhit);
  evts_cuts->SetBranchAddress("winTrkStrtX",   &winTrkStrtX);
  evts_cuts->SetBranchAddress("winTrkStrtY",   &winTrkStrtY);
  evts_cuts->SetBranchAddress("winTrkStrtZ",   &winTrkStrtZ);
  evts_cuts->SetBranchAddress("winTrkStopX",   &winTrkStopX);
  evts_cuts->SetBranchAddress("winTrkStopY",   &winTrkStopY);
  evts_cuts->SetBranchAddress("winTrkStopZ",   &winTrkStopZ);

  for (int event = 1; event < nevents && event < evts_cuts->GetEntriesFast(); ++event) {

    evts_cuts->GetEntry(event);

    // pid
    std::string pid = PID(toftime, ckovadc, mc7mag);

    // get the slice
    int slice = -1;
    TVector3 trackStrt, trackStop;
    for (unsigned int trackIt = 0; trackIt < winTrkSlice->size(); ++trackIt) {
      if (abs(winTrkStrtX->at(trackIt)) < 20 and winTrkStrtY->at(trackIt) > -25 and winTrkStrtY->at(trackIt) < 15 and
	  winTrkStrtZ->at(trackIt) < 18 and winTrkNhit->at(trackIt) >= 5 and
	  winTrkMinTime->at(trackIt) > 45000 and winTrkMinTime->at(trackIt) < 55000) {
	slice = winTrkSlice->at(trackIt);
	trackStrt = TVector3(winTrkStrtX->at(trackIt), winTrkStrtY->at(trackIt), winTrkStrtZ->at(trackIt));
	trackStop = TVector3(winTrkStopX->at(trackIt), winTrkStopY->at(trackIt), winTrkStopZ->at(trackIt));
	break;
      }
    }

    if (slice == -1)
      continue;

    top_view->Reset();
    side_view->Reset();
    top_view_slice->Reset();
    side_view_slice->Reset();

    // fill hits
    for (unsigned int hitIt = 0; hitIt < hitSlice->size(); ++hitIt) {

      if (hitTime->at(hitIt) < 45000 or hitTime->at(hitIt) > 55000)
	continue;

      TVector3 pos = cellGeo[hitPlane->at(hitIt)][hitCell->at(hitIt)];

      int z_bin = geo ? top_view->GetXaxis()->FindBin(pos.Z()) : hitPlane->at(hitIt);
      int x_bin = geo ? top_view->GetYaxis()->FindBin(pos.X()) : hitCell->at(hitIt);
      int y_bin = geo ? top_view->GetYaxis()->FindBin(pos.Y()) : hitCell->at(hitIt);

      if (hitPlane->at(hitIt) % 2 == 0) {
	if (hitSlice->at(hitIt) == slice)
	  top_view_slice->SetBinContent(z_bin, x_bin, 1);
	else
	  top_view->SetBinContent(z_bin, x_bin, 1.8);
      } else {
	if (hitSlice->at(hitIt) == slice)
	  side_view_slice->SetBinContent(z_bin, y_bin, 1);
	else
	  side_view->SetBinContent(z_bin, y_bin, 1.8);
      }

    }

    canv->cd();
    canv->Clear();
    canv->Divide(1, 2);

    TLine line;
    line.SetLineColor(kRed);
    line.SetLineStyle(kDashed);
    line.SetLineWidth(1);

    canv->cd(1);
    top_view->Draw("col");
    top_view_slice->Draw("col same");
    if (geo)
      line.DrawLine(trackStrt.Z(), trackStrt.X(), trackStop.Z(), trackStop.X());

    canv->cd(2);
    side_view->Draw("col");
    side_view_slice->Draw("col same");
    if (geo)
      line.DrawLine(trackStrt.Z(), trackStrt.Y(), trackStop.Z(), trackStop.Y());

    canv->cd();
    TText text;
    text.SetTextColor(kBlack);
    text.DrawText(0.03, 0.87, pid.c_str());

    canv->SaveAs(Form("SlicerHits/Run%dSubrun%dEvent%dSlice%d.png", run, subrun, event, slice));

  }

  return;

}

// --------------------------------------------------------------------------------------------------
std::vector<std::vector<TVector3> > BuildCellGeoMap() {

  std::vector<std::vector<TVector3> > cellGeo(63, std::vector<TVector3>(64));

  std::ifstream inFile("detgeo.txt", std::ifstream::in);
  std::string line;
  std::string plane, cell, x, y, z;

  while (getline(inFile, line)) {
    std::stringstream ss(line);
    ss >> plane;
    ss >> cell;
    ss >> x;
    ss >> y;
    ss >> z;
    TVector3 xyz(std::stof(x), std::stof(y), std::stof(z));
    cellGeo[std::stoi(plane)][std::stoi(cell)] = xyz;
  }

  return cellGeo;

}

// --------------------------------------------------------------------------------------------------
void FormatHist(TH1* hist) {

  hist->SetStats(0);
  hist->GetZaxis()->SetRangeUser(1,2);
  hist->GetXaxis()->SetTitleSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->CenterTitle();

  return;

}
