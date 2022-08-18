#include <TTree.h>
#include <TLatex.h>
#include <TCut.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TFile.h>
#include <TLegend.h>
#include <TH2.h>
#include <TTreePlayer.h>
#include <iostream>
#include <TEntryList.h>
#include <vector>
#include <TProfile.h>

void CenterTitles(TH1* histo) {
  histo->GetXaxis()->CenterTitle();
  histo->GetYaxis()->CenterTitle();
  histo->GetZaxis()->CenterTitle();  
}

  void Preliminary() {
  TLatex* prelim = new TLatex(.9, .95, "NOvA Preliminary");
  prelim->SetTextColor(kBlue);
  prelim->SetNDC();
  prelim->SetTextSize(2/30.);
  prelim->SetTextAlign(32);
  prelim->Draw();
}

void PreliminarySide() {
  TLatex* prelim = new TLatex(.93, .7, "NOvA Preliminary");
  prelim->SetTextColor(kBlue);
  prelim->SetNDC();
  prelim->SetTextSize(2/30.);
  prelim->SetTextAngle(270);
  prelim->SetTextAlign(12);
  prelim->Draw();
}
//Standard Cuts
  TCut wcX("wcmom>=0");
  TCut tofc("toftime>=30");
  TCut tofX("toftime>=0");
  TCut magdist("abs(wcMagDist)<10");
  TCut blcuts(wcX&&tofX&&magdist);
  TCut nhitcut("winTrkNhit>5");
  TCut centralVtx("abs(winTrkStrtX)<20&&winTrkStrtY>-25&&winTrkStrtY<15&&winTrkStrtZ<18");
  TCut hittime("winTrkMinTime>45000&&winTrkMinTime<55000");
  TCut detcuts(centralVtx&&hittime&&nhitcut);
  TCut selection(blcuts&&detcuts);

//PiMu Cuts
  TCut pimutof("(mc7mag>900&&mc7mag<1100&&toftime>30&&toftime<34)||(mc7mag>650&&mc7mag<850&&toftime>30&&toftime<36)||(mc7mag>400&&mc7mag<600&&toftime>30&&toftime<40)");
  TCut pimuE("(mc7mag>400&&mc7mag<1100)");
  TCut pimutof1("(mc7mag>900&&mc7mag<1100&&toftime>30&&toftime<34)"); //1 GeV
  TCut pimutof2("(mc7mag>650&&mc7mag<850&&toftime>30&&toftime<36)");  //.75 GeV
  TCut pimutof3("(mc7mag>400&&mc7mag<600&&toftime>30&&toftime<40)");  //.5 GeV

  TCut pimu(selection&&pimutof&&"ckovadc<0"&&"sqrt((winTrkStopX - winTrkStrtX)^2+(winTrkStopY - winTrkStrtY)^2+(winTrkStopZ - winTrkStrtZ)^2)<380");

  TCut pimu1(selection&&pimutof1&&"ckovadc<0"); //blue
  TCut pimu2(selection&&pimutof2&&"ckovadc<0"); //red
  TCut pimu3(selection&&pimutof3&&"ckovadc<0"); //green

//Particle Cuts
  TCut electrontof("toftime>30&&toftime<36");
  TCut protontof("(mc7mag>900&&mc7mag<1100&&toftime>39&&toftime<50)||(mc7mag>650&&mc7mag<850&&toftime>42&&toftime<60)||(mc7mag>400&&mc7mag<600&&toftime>56&&toftime<80)");
  TCut kaontof("(mc7mag>900&&mc7mag<1100&&toftime>34&&toftime<39)||(mc7mag>650&&mc7mag<850&&toftime>36&&toftime<42)||(mc7mag>400&&mc7mag<600&&toftime>40&&toftime<56)");
  TCut electron(selection&&electrontof&&"ckoadc>0");
  TCut proton(selection&&protontof&&"ckovadc<0"&&"sqrt((winTrkStopX - winTrkStrtX)^2+(winTrkStopY - winTrkStrtY)^2+(winTrkStopZ - winTrkStrtZ)^2)<300");
  //TCut deuteron(selection&&"ckovadc<0&&toftime>70&&(run<100827||tof time>120)");
  TCut kaon(selection&&kaontof&&"ckovadc<0");
  TCut particle(electron||proton||kaon||pimu);//deuteron);

  
// Macro to create pretty plots from tbrecoana files.
void braggpeak_proton()
{
  TFile* inFile = new TFile("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period3/R21-07-27-testbeam-production.a/TBRecoAna_r100985-r101483.root", "READ");
  TTree* evts = (TTree*)inFile->Get("tbrecoana/evts");
  const std::string outdirE = ".";
  char filename[128]; 

  gSystem->Setenv("TZ","UTC");
  gStyle->SetTimeOffset(0);
  gStyle->SetPalette(kBird);

  //gStyle->SetOptStat(1);

  TCanvas *c1 = new TCanvas("c1","c1");
  TCanvas *c2 = new TCanvas("c2","c2");
  auto legend = new TLegend(.3,.68,.5,.84);

  //Bragg Peak Histo
  int nhit = -1;
  double mc7mag = -1;
  int event = -1;
  std::vector<int>* winTrkSlice = nullptr;
  std::vector<int>* winTrk = nullptr;
  //std::vector<double>* hitPlane = nullptr;
  std::vector<int>* hitPlane = nullptr;
  std::vector<int>* hitSlice = nullptr;
  std::vector<float>* hitGeV = nullptr;
  std::vector<int>* winTrkMaxPlane = nullptr;
  std::vector<int>* winTrkNhit = nullptr;
  std::vector<int>* winTrkStrtX = nullptr;
  std::vector<int>* winTrkStrtY = nullptr;
  std::vector<int>* winTrkStrtZ = nullptr;
  std::vector<int>* winTrkMinTime = nullptr;

  evts->SetBranchAddress("event",&event);
  evts->SetBranchAddress("nhit",&nhit);
  evts->SetBranchAddress("hitPlane",&hitPlane);
  evts->SetBranchAddress("hitSlice",&hitSlice);
  evts->SetBranchAddress("hitGeV",&hitGeV);
  evts->SetBranchAddress("winTrkMaxPlane",&winTrkMaxPlane);
  evts->SetBranchAddress("winTrkSlice",&winTrkSlice);
  evts->SetBranchAddress("winTrk",&winTrk);
  evts->SetBranchAddress("winTrkNhit",&winTrkNhit);
  evts->SetBranchAddress("winTrkStrtX",&winTrkStrtX);
  evts->SetBranchAddress("winTrkStrtY",&winTrkStrtY);
  evts->SetBranchAddress("winTrkStrtZ",&winTrkStrtZ);
  evts->SetBranchAddress("winTrkMinTime",&winTrkMinTime);
  evts->SetBranchAddress("mc7mag",&mc7mag);
  
  TH2F* hpimubraggpeakall = new TH2F("pimubraggpeakall","pimubraggpeakall", 63, 0, 63, 100, 0, 1);
  evts->Draw(">>entriesall",proton,"entrylist");
  TEntryList *entriesall = (TEntryList*)gDirectory->Get("entriesall");

  for(int event = 0; event<=entriesall->GetN();event++)
  {
    evts->GetEntry(entriesall->GetEntry(event));
    int slice = -1;
    int track = -1;
    int max_plane = -1;
    for (unsigned int trackIt = 0; trackIt < winTrkSlice->size(); ++trackIt) {
      if (winTrkNhit->at(trackIt)>5&&
        abs(winTrkStrtX->at(trackIt))<20&&
        winTrkStrtY->at(trackIt)>-25&&winTrkStrtY->at(trackIt)<15&&
        winTrkStrtZ->at(trackIt)<18&&
        winTrkMinTime->at(trackIt)>45000&&winTrkMinTime->at(trackIt)<55000
        )
      {

        slice = winTrkSlice->at(trackIt);
        track = winTrk->at(trackIt);
        max_plane = winTrkMaxPlane->at(trackIt);
        break;
      }//track cuts
    }//loop over trackIt

    std::vector<double> total_plane_energy(63, 0);

    for (int hitIt = 0; hitIt < nhit; ++hitIt)
    {
      if (hitSlice->at(hitIt) == slice)
      {
        if(hitGeV->at(hitIt)>-5)
        //cout << "hitGeV is " << hitGeV->at(hitIt) << endl;
          total_plane_energy.at(hitPlane->at(hitIt)) += hitGeV->at(hitIt);

      }
    }

    for (unsigned int planeIt = 0; planeIt < 63; ++planeIt)
    {
      //if(total_plane_energy[planeIt]>0)
      //cout << "total plane energy is " << total_plane_energy[planeIt] << endl;
      if(total_plane_energy.at(planeIt)>0)
        hpimubraggpeakall->Fill(max_plane-planeIt, total_plane_energy[planeIt]);
    }
    total_plane_energy.clear();
    }//loop over events

    
    c1->cd();
    hpimubraggpeakall->Draw("colz");
    CenterTitles(hpimubraggpeakall);
    //PreliminarySide();
    hpimubraggpeakall->SetTitle("PiMu Bragg Peak");
    hpimubraggpeakall->GetYaxis()->SetTitle("Plane GeV");
    hpimubraggpeakall->GetXaxis()->SetTitle("# Planes from Track End");
    sprintf(filename,"%s/pimubraggpeakall.png",outdirE.c_str());
    c1->Print(filename); 
    TProfile* profileall = hpimubraggpeakall->ProfileX();
    c2->cd();
    profileall->Draw();
    profileall->SetTitle("PiMu Bragg Peak Profile");
    profileall->GetYaxis()->SetTitle("Plane GeV");
    profileall->GetXaxis()->SetTitle("# Planes from Track End");
    sprintf(filename,"%s/pimubraggpeakprofileall.png",outdirE.c_str());
    c2->Print(filename); 
    TFile* outFileprofile = new TFile("pimubraggpeakall.root", "RECREATE");
    hpimubraggpeakall->Write("hpimubraggpeak");
    profileall->Write("peakprofile");
    outFileprofile->Close();
  }
