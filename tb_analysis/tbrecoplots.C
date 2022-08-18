// Some NOvA style functions
void Preliminary() {
  TLatex* prelim = new TLatex(.9, .95, "NOvA Preliminary");
  prelim->SetTextColor(kBlue);
  prelim->SetNDC();
  prelim->SetTextSize(2/30.);
  prelim->SetTextAlign(32);
  prelim->Draw();
}

void PreliminarySide() {
  TLatex* prelim = new TLatex(.93, .9, "NOvA Preliminary");
  prelim->SetTextColor(kBlue);
  prelim->SetNDC();
  prelim->SetTextSize(2/30.);
  prelim->SetTextAngle(270);
  prelim->SetTextAlign(12);
  prelim->Draw();
}

void CenterTitles(TH1* histo) {
  histo->GetXaxis()->CenterTitle();
  histo->GetYaxis()->CenterTitle();
  histo->GetZaxis()->CenterTitle();  
}

// Macro to create pretty plots from tbrecoana files.
void tbrecoplots()
{
  TFile* inFile = new TFile("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period3/R21-07-27-testbeam-production.a/TBRecoAna_r100985-r101483.root",
			    "READ");
  TTree* evts = (TTree*)inFile->Get("tbrecoana/evts");
  
  const std::string outdir = "plots/";
  char filename[128];

  // Find time from first and last files manually for now and update here.
  int t0 = 1610409600;
  int t1 = 1624856400; // 23 March 2020 00:00 UTC makes full period plots prettier
  int nday = 167;

  gSystem->Setenv("TZ","UTC");
  gStyle->SetTimeOffset(0);
  gStyle->SetPalette(kBird);

  //gStyle->SetOptStat(1);

  // Define cuts
  TCut wcX("wcmom>=0");
  TCut tofc("toftime>=30");
  TCut tofX("toftime>=0");
  TCut magdist("abs(wcMagDist)<10");
  TCut blcuts(wcX&&tofX&&magdist);
  TCut nhit("winTrkNhit>5");
  TCut centralVtx("abs(winTrkStrtX)<20&&winTrkStrtY>-25&&winTrkStrtY<15&&winTrkStrtZ<18");
  TCut hittime("winTrkMinTime>45000&&winTrkMinTime<55000");
  TCut detcuts(centralVtx&&hittime&&nhit);
  TCut selection(blcuts&&detcuts);

  TCut electrontof("toftime>30&&toftime<36");
  TCut protontof("(mc7mag>900&&mc7mag<1100&&toftime>39&&toftime<50)||(mc7mag>650&&mc7mag<850&&toftime>42&&toftime<60)||(mc7mag>400&&mc7mag<600&&toftime>56&&toftime<80)");
  TCut kaontof("(mc7mag>900&&mc7mag<1100&&toftime>34&&toftime<39)||(mc7mag>650&&mc7mag<850&&toftime>36&&toftime<42)||(mc7mag>400&&mc7mag<600&&toftime>40&&toftime<56)");
  TCut pimutof("(mc7mag>900&&mc7mag<1100&&toftime>30&&toftime<34)||(mc7mag>650&&mc7mag<850&&toftime>30&&toftime<36)||(mc7mag>400&&mc7mag<600&&toftime>30&&toftime<40)");
  
  TCut electron(selection&&electrontof&&"ckovadc>0");
  TCut proton(selection&&protontof&&"ckovadc<0");
  //TCut deuteron(selection&&"ckovadc<0&&toftime>70&&(run<100827||toftime>120)");
  TCut kaon(selection&&kaontof&&"ckovadc<0");
  TCut pimu(selection&&pimutof&&"ckovadc<0");

  TCut particle(electron||proton||kaon||pimu);//deuteron);

  TCanvas *c1 = new TCanvas("c1","c1");

  /* // Read in spill file to get recorded spills per day */
  /* // If you want smaller bins, script that creates spill file will need changing */
  /* TFile* spillFile = TFile::Open("/nova/ana/users/tlackey/testbeam/spills/MCenterSpills.root"); */
  /* TTree* spillTree = dynamic_cast<TTree*>(spillFile->Get("BeamMetrics")); */
  /* double timestamp; */
  /* int    spills_rec; */
  /* double pot_rec; */
  /* spillTree->SetBranchAddress("Date", &timestamp); */
  /* spillTree->SetBranchAddress("spills_rec", &spills_rec); */
  /* spillTree->SetBranchAddress("pot_rec", &pot_rec); */
  /* TH1F *hSpillsRecorded = 0; */
  /* hSpillsRecorded = new TH1F("hSpillsRecorded","hSpillsRecorded",nday,t0,t1); */
  /* for (int entryid=0; entryid<spillTree->GetEntries(); entryid++){ */
  /*   spillTree->GetEntry(entryid); */
  /*   if (timestamp > t0 && timestamp < t1){ */
  /*     int binid = hSpillsRecorded->GetXaxis()->FindBin(timestamp); */
  /*     hSpillsRecorded->SetBinContent(binid,spills_rec); */
  /*   } */
  /* } */
  /* hSpillsRecorded->SetTitle("Recorded spills per day (UTC)"); */
  /* hSpillsRecorded->GetYaxis()->SetTitle("recorded spills / day"); */
  /* hSpillsRecorded->GetXaxis()->SetTitle("time"); */
  /* hSpillsRecorded->GetXaxis()->SetTimeDisplay(1); */
  /* hSpillsRecorded->GetXaxis()->SetTimeFormat("%d %b%F1970-01-01 00:00:00"); */
  /* CenterTitles(hSpillsRecorded); */
  /* hSpillsRecorded->Draw(); */
  /* PreliminarySide(); */
  /* sprintf(filename,"%s/recspills.png",outdir.c_str()); */
  /* c1->Print(filename); */
  

  // Make plots
  TH1F* hevtTime = 0;
  hevtTime = new TH1F("hevtTime","hevtTime",4*nday,t0,t1);
  evts->Draw("evtTime>>hevtTime");
  CenterTitles(hevtTime);
  PreliminarySide();
  hevtTime->SetTitle("Event Time - no cuts");
  hevtTime->GetYaxis()->SetTitle("events / 6 hours");
  hevtTime->GetXaxis()->SetTitle("event time");
  hevtTime->GetXaxis()->SetTimeDisplay(1);
  hevtTime->GetXaxis()->SetTimeFormat("%d %b%F1970-01-01 00:00:00");
  sprintf(filename,"%s/evtTimeNoCuts.png",outdir.c_str());
  c1->Print(filename);

  evts->Draw("evtTime",particle,"same ap hist");
  evts->GetHistogram()->SetMarkerStyle(2);
  evts->GetHistogram()->SetMarkerColor(kRed);
  evts->GetHistogram()->Scale(50);
  sprintf(filename,"%s/evtTimeRecoOverlay.png",outdir.c_str());
  c1->Print(filename);

  TH1F* hevtsPerDay = 0;
  hevtsPerDay = new TH1F("hevtsPerDay","hevtsPerDay",nday,t0,t1);
  //evts->Draw("evtTime>>hevtsPerDay",particle,"p");
  evts->Draw("evtTime>>hevtsPerDay",particle,"hist");
  CenterTitles(hevtsPerDay);
  PreliminarySide();
  //hevtsPerDay->SetMarkerStyle(2);
  //hevtsPerDay->SetMarkerColor(kRed);
  hevtsPerDay->SetTitle("Selected events per day (UTC)");
  hevtsPerDay->GetYaxis()->SetTitle("events / day");
  hevtsPerDay->GetXaxis()->SetTimeDisplay(1);
  hevtsPerDay->GetXaxis()->SetTimeFormat("%d %b%F1970-01-01 00:00:00");  
  sprintf(filename,"%s/evtsPerDay.png",outdir.c_str());
  c1->Print(filename);

  /* hevtsPerDay->Divide(hSpillsRecorded); */
  /* hevtsPerDay->SetTitle("Selected events per spill"); */
  /* hevtsPerDay->GetYaxis()->SetTitle("events / spill"); */
  /* hevtsPerDay->Draw("hist"); */
  /* PreliminarySide(); */
  /* sprintf(filename,"%s/evtsPerSpillPerDay.png",outdir.c_str()); */
  /* c1->Print(filename); */

  TH1F* helecPerDay = 0;
  helecPerDay = new TH1F("helecPerDay","helecPerDay",nday,t0,t1);
  evts->Draw("evtTime>>helecPerDay",electron,"p");
  helecPerDay->SetMarkerStyle(21);
  helecPerDay->SetMarkerColor(kRed);
  helecPerDay->SetLineColor(kRed);

  TH1F* hprotPerDay = 0;
  hprotPerDay = new TH1F("hprotPerDay","hprotPerDay",nday,t0,t1);
  evts->Draw("evtTime>>hprotPerDay",proton,"p");
  hprotPerDay->SetMarkerStyle(22);
  hprotPerDay->SetMarkerColor(kBlue+1);
  hprotPerDay->SetLineColor(kBlue+1);

  TH1F* hkaonPerDay = 0;
  hkaonPerDay = new TH1F("hkaonPerDay","hkaonPerDay",nday,t0,t1);
  evts->Draw("evtTime>>hkaonPerDay",kaon,"p");
  hkaonPerDay->SetMarkerStyle(24);
  hkaonPerDay->SetMarkerColor(kGreen+3);
  hkaonPerDay->SetLineColor(kGreen+3);

  TH1F* hothPerDay = 0;
  hothPerDay = new TH1F("hothPerDay","hothPerDay",nday,t0,t1);
  evts->Draw("evtTime>>hothPerDay",pimu,"p");
  CenterTitles(hothPerDay);
  hothPerDay->SetMarkerStyle(3);
  //hothPerDay->SetMarkerSize(2);
  hothPerDay->SetMarkerColor(kMagenta+1);
  hothPerDay->SetLineColor(kMagenta+1);
  hothPerDay->SetTitle("Selected particles per day (UTC)");
  hothPerDay->GetYaxis()->SetTitle("events / day");
  hothPerDay->GetXaxis()->SetTimeDisplay(1);
  hothPerDay->GetXaxis()->SetTimeFormat("%d %b%F1970-01-01 00:00:00");  

  // hothPerDay->Draw("p");
  // hprotPerDay->Draw("ap same");
  // helecPerDay->Draw("ap same");
  // hkaonPerDay->Draw("ap same");
  hothPerDay->Draw("");
  hprotPerDay->Draw("a hist same");
  helecPerDay->Draw("a hist same");
  hkaonPerDay->Draw("a hist same");
  
  //auto legend = new TLegend(0.75,0.72,0.91,0.88);
  auto legend =  new TLegend(0.14,0.68,0.3,0.84);
  gStyle->SetLegendBorderSize(1);
  // legend->AddEntry(helecPerDay,"Electron","p");
  // legend->AddEntry(hprotPerDay,"Proton","p");
  // legend->AddEntry(hkaonPerDay,"Kaon","p");
  // legend->AddEntry(hothPerDay,"Muon, Pion","p");
  legend->AddEntry(helecPerDay,"Electron","l");
  legend->AddEntry(hprotPerDay,"Proton","l");
  legend->AddEntry(hkaonPerDay,"Kaon","l");
  legend->AddEntry(hothPerDay,"Muon, Pion","l");
  legend->Draw();
  PreliminarySide();

  sprintf(filename,"%s/partPerDay.png",outdir.c_str());
  c1->Print(filename);

  TH1F* hwcmom = 0;
  hwcmom = new TH1F("hwcmom","hwcmom",100,0,2000);
  evts->Draw("wcmom>>hwcmom",wcX);
  CenterTitles(hwcmom);
  PreliminarySide();
  hwcmom->SetTitle("WC momentum");
  hwcmom->GetYaxis()->SetTitle("events / 20 MeV");
  hwcmom->GetXaxis()->SetTitle("momentum [MeV/c]");
  sprintf(filename,"%s/wcmom.png",outdir.c_str());
  c1->Print(filename);

  TH1F* htoftime = 0;
  htoftime = new TH1F("htoftime","htoftime",100,0,200);
  evts->Draw("toftime>>htoftime",tofX);
  CenterTitles(htoftime);
  PreliminarySide();
  htoftime->SetTitle("Time of flight");
  htoftime->GetYaxis()->SetTitle("events / 2 ns");
  htoftime->GetXaxis()->SetTitle("time of flight [ns]");
  sprintf(filename,"%s/toftime.png",outdir.c_str());
  c1->Print(filename);
  
  TH1F* hckovadc = 0;
  hckovadc = new TH1F("hckovadc","hckovadc",100,0,6000);
  evts->Draw("ckovadc>>hckovadc","ckovadc!=-5");
  CenterTitles(hckovadc);
  PreliminarySide();
  hckovadc->SetTitle("Cherenkov");
  hckovadc->GetYaxis()->SetTitle("events / 60 ADC");
  hckovadc->GetXaxis()->SetTitle("cherenkov signal [ADC]");
  sprintf(filename,"%s/ckovadc.png",outdir.c_str());
  c1->Print(filename);

  TH1F* hwcmomcuts = 0;
  hwcmomcuts = new TH1F("hwcmomcuts","hwcmomcuts",100,0,2000);
  evts->Draw("wcmom>>hwcmomcuts",particle);
  CenterTitles(hwcmomcuts);
  PreliminarySide();
  hwcmomcuts->SetTitle("WC momentum - selected particles");
  hwcmomcuts->GetYaxis()->SetTitle("events / 20 MeV");
  hwcmomcuts->GetXaxis()->SetTitle("momentum [MeV/c]");
  sprintf(filename,"%s/wcmomCuts.png",outdir.c_str());
  c1->Print(filename);

  TH1F* htoftimecuts = 0;
  htoftimecuts = new TH1F("htoftimecuts","htoftimecuts",100,0,100);
  evts->Draw("toftime>>htoftimecuts",particle);
  CenterTitles(htoftimecuts);
  PreliminarySide();
  htoftimecuts->SetTitle("Time of flight - selected particles");
  htoftimecuts->GetYaxis()->SetTitle("events / 1 ns");
  htoftimecuts->GetXaxis()->SetTitle("time of flight [ns]");
  sprintf(filename,"%s/toftimeCuts.png",outdir.c_str());
  c1->Print(filename);
  
  TH1F* hckovadccuts = 0;
  hckovadccuts = new TH1F("hckovadccuts","hckovadccuts",100,0,6000);
  evts->Draw("ckovadc>>hckovadccuts",particle&&"ckovadc!=-5");
  CenterTitles(hckovadccuts);
  PreliminarySide();
  hckovadccuts->SetTitle("Cherenkov - selected electrons");
  hckovadccuts->GetYaxis()->SetTitle("events / 60 ADC");
  hckovadccuts->GetXaxis()->SetTitle("cherenkov signal [ADC]");
  sprintf(filename,"%s/ckovadcCuts.png",outdir.c_str());
  c1->Print(filename);

  TH2F* htofwc = 0;
  htofwc = new TH2F("htofwc","htofwc",100,0,2000,120,0,120);
  evts->Draw("toftime:wcmom>>htofwc",blcuts,"colz");
  CenterTitles(htofwc);
  htofwc->SetTitle("TOF vs. WC momentum - all events");
  htofwc->GetXaxis()->SetTitle("momentum [MeV/c]");
  htofwc->GetYaxis()->SetTitle("time of flight [ns]");
  sprintf(filename,"%s/tofVwcmom.png",outdir.c_str());
  c1->Print(filename);

  TH2F* htofwcCuts = 0;
  htofwcCuts = new TH2F("htofwcCuts","htofwcCuts",100,0,2000,120,0,120);
  evts->Draw("toftime:wcmom>>htofwcCuts",particle,"colz");
  CenterTitles(htofwcCuts);
  htofwcCuts->SetTitle("TOF vs. WC momentum - selected particles");
  htofwcCuts->GetXaxis()->SetTitle("momentum [MeV/c]");
  htofwcCuts->GetYaxis()->SetTitle("time of flight [ns]");
  sprintf(filename,"%s/tofVwcmomAllCuts.png",outdir.c_str());
  c1->Print(filename);

  TH2F* htofwcCutsZoom = 0;
  htofwcCutsZoom = new TH2F("htofwcCutsZoom","htofwcCutsZoom",130,300,1600,90,30,120);
  evts->Draw("toftime:wcmom>>htofwcCutsZoom",blcuts&&tofc,"colz");
  CenterTitles(htofwcCutsZoom);
  htofwcCutsZoom->SetTitle("TOF vs. WC momentum");
  htofwcCutsZoom->GetXaxis()->SetTitle("momentum [MeV/c]");
  htofwcCutsZoom->GetYaxis()->SetTitle("time of flight [ns]");
  sprintf(filename,"%s/tofVwcmomAllCutsZoom.png",outdir.c_str());
  c1->Print(filename);

  TH2F* htofwcElec = 0;
  htofwcElec = new TH2F("htofwcElec","htofwcElec",130,300,1600,50,30,80);
  evts->Draw("toftime:wcmom>>htofwcElec",tofc&&"ckovadc>0&&toftime<50","colz"); 
  CenterTitles(htofwcElec);
  htofwcElec->SetTitle("TOF vs. WC momentum - electrons");
  htofwcElec->GetXaxis()->SetTitle("momentum [MeV/c]");
  htofwcElec->GetYaxis()->SetTitle("time of flight [ns]");
  sprintf(filename,"%s/tofVwcmomElectrons.png",outdir.c_str());
  c1->Print(filename);

  TH2F* htofwcPro = 0;
  htofwcPro = new TH2F("htofwcPro","htofwcPro",130,300,1600,50,30,80);
  evts->Draw("toftime:wcmom>>htofwcPro","ckovadc<0&&toftime>50","colz");
  CenterTitles(htofwcPro);
  htofwcPro->SetTitle("TOF vs. WC momentum - protons");
  htofwcPro->GetXaxis()->SetTitle("momentum [MeV/c]");
  htofwcPro->GetYaxis()->SetTitle("time of flight [ns]");
  sprintf(filename,"%s/tofVwcmomProtons.png",outdir.c_str());
  c1->Print(filename);

  TH2F* htofwcKaon = 0;
  htofwcKaon = new TH2F("htofwcKaon","htofwcKaon",130,300,1600,50,30,80);
  evts->Draw("toftime:wcmom>>htofwcKaon","ckovadc<0&&toftime>45&&toftime<50","colz");
  CenterTitles(htofwcKaon);
  htofwcKaon->SetTitle("TOF vs. WC momentum - kaons");
  htofwcKaon->GetXaxis()->SetTitle("momentum [MeV/c]");
  htofwcKaon->GetYaxis()->SetTitle("time of flight [ns]");
  sprintf(filename,"%s/tofVwcmomKaons.png",outdir.c_str());
  c1->Print(filename);

  TH2F* htofwcOth = 0;
  htofwcOth = new TH2F("htofwcOth","htofwcOth",130,300,1600,50,30,80);
  evts->Draw("toftime:wcmom>>htofwcOth",tofc&&"ckovadc<0&&toftime<=45","colz");
  CenterTitles(htofwcOth);
  htofwcOth->SetTitle("TOF vs. WC momentum - muons, pions");
  htofwcOth->GetXaxis()->SetTitle("momentum [MeV/c]");
  htofwcOth->GetYaxis()->SetTitle("time of flight [ns]");
  sprintf(filename,"%s/tofVwcmomPiMus.png",outdir.c_str());
  c1->Print(filename);

  TH1F* hwinTrkStrtX = 0;
  hwinTrkStrtX = new TH1F("hwinTrkStrtX","hwinTrkStrtX",70,-140,140);
  evts->Draw("winTrkStrtX>>hwinTrkStrtX",hittime);
  CenterTitles(hwinTrkStrtX);
  hwinTrkStrtX->SetTitle("Window track start posistion - in-time tracks");
  hwinTrkStrtX->GetXaxis()->SetTitle("X [cm]");
  hwinTrkStrtX->GetYaxis()->SetTitle("tracks / 4 cm");
  sprintf(filename,"%s/winTrkStrtXinTime.png",outdir.c_str());
  c1->Print(filename);

  TH1F* hwinTrkStrtY = 0;
  hwinTrkStrtY = new TH1F("hwinTrkStrtY","hwinTrkStrtY",70,-140,140);
  evts->Draw("winTrkStrtY>>hwinTrkStrtY",hittime);
  CenterTitles(hwinTrkStrtY);
  hwinTrkStrtY->SetTitle("Window track start posistion - in-time tracks");
  hwinTrkStrtY->GetXaxis()->SetTitle("Y [cm]");
  hwinTrkStrtY->GetYaxis()->SetTitle("tracks / 4 cm");
  sprintf(filename,"%s/winTrkStrtYinTime.png",outdir.c_str());
  c1->Print(filename);

  TH2F* hxyprof = 0;
  hxyprof = new TH2F("hxyprof","hxyprof",70,-140,140,70,-140,140);
  evts->Draw("winTrkStrtY:winTrkStrtX>>hxyprof","","colz");
  CenterTitles(hxyprof);
  hxyprof->SetTitle("Track start position - XY view");
  hxyprof->GetXaxis()->SetTitle("X [cm]");
  hxyprof->GetYaxis()->SetTitle("Y [cm]");
  sprintf(filename,"%s/XYprofile.png",outdir.c_str());
  c1->Print(filename);

  TH2F* hxyprofcut = 0;
  hxyprofcut = new TH2F("hxyprofcut","hxyprofcut",30,-30,30,30,-30,30);
  evts->Draw("winTrkStrtY:winTrkStrtX>>hxyprofcut",particle,"colz");
  CenterTitles(hxyprofcut);
  hxyprofcut->SetTitle("Track start position - XY view - selection cuts applied");
  hxyprofcut->GetXaxis()->SetTitle("X [cm]");
  hxyprofcut->GetYaxis()->SetTitle("Y [cm]");
  sprintf(filename,"%s/XYprofileCuts.png",outdir.c_str());
  c1->Print(filename);
  

  evts->SetScanField(0);
  ((TTreePlayer*)(evts->GetPlayer()))->SetScanRedirect(true);
  sprintf(filename,"%s/event-list-all_to_date.txt",outdir.c_str());
  ((TTreePlayer*)(evts->GetPlayer()))->SetScanFileName(filename);
  evts->Scan("run:subrun:event:toftime:wcmom:ckovadc:evtTime",particle,"col=::::::17f");

  sprintf(filename,"%s/event-list-electron.txt",outdir.c_str());
  ((TTreePlayer*)(evts->GetPlayer()))->SetScanFileName(filename);
  evts->Scan("run:subrun:event:toftime:wcmom:ckovadc:evtTime",electron,"col=::::::17f");

  sprintf(filename,"%s/event-list-proton.txt",outdir.c_str());
  ((TTreePlayer*)(evts->GetPlayer()))->SetScanFileName(filename);
  evts->Scan("run:subrun:event:toftime:wcmom:ckovadc:evtTime",proton,"col=::::::17f");

  sprintf(filename,"%s/event-list-kaon.txt",outdir.c_str());
  ((TTreePlayer*)(evts->GetPlayer()))->SetScanFileName(filename);
  evts->Scan("run:subrun:event:toftime:wcmom:ckovadc:evtTime",kaon,"col=::::::17f");

  sprintf(filename,"%s/event-list-other.txt",outdir.c_str());
  ((TTreePlayer*)(evts->GetPlayer()))->SetScanFileName(filename);
  evts->Scan("run:subrun:event:toftime:wcmom:ckovadc:evtTime",pimu,"col=::::::17f");
}
