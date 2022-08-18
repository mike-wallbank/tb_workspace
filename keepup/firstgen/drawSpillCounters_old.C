// execute as >> root 'drawSpillCounters.C("<file>.root")'

#include <string>

void drawSpillCounters(std::string inFileName) {

  // time range
  bool useTimeRange = false;

  int start_year = 2021;
  int start_month = 01;
  int start_day = 26;
  int start_hour = 00;
  int start_min = 00;
  int start_sec = 00;

  int end_year = 2021;
  int end_month = 01;
  int end_day = 28;
  int end_hour = 00;
  int end_min = 00;
  int end_sec = 00;

  // counter ranges
  // period3
  float mc7count = 1e6;
  float mc7target = 2e6;
  float mc7trig = 60;
  float mc7trignorm = 0.5;

  // period2
  // float mc7count = 1e5;
  // float mc7target = 2e5;
  // float mc7trig = 5;
  // float mc7trignorm = 0.1;

  // format time into structure
  struct tm start_tm, end_tm;
  time_t start_time, end_time;
  if (useTimeRange) {
    if (strptime(Form("%d-%d-%d_%d:%d:%d", start_year, start_month, start_day, start_hour, start_min, start_sec),
		 "%Y-%m-%d_%H:%M:%S", &start_tm) != NULL)
      start_time = mktime(&start_tm);
    if (strptime(Form("%d-%d-%d_%d:%d:%d", end_year, end_month, end_day, end_hour, end_min, end_sec),
		 "%Y-%m-%d_%H:%M:%S", &end_tm) != NULL)
      end_time = mktime(&end_tm);
  }

  TFile* inFile = new TFile(inFileName.c_str(), "READ");

  TGraph* hMC6IC                 = (TGraph*)inFile->Get("spillana/MC6IC");
  TGraph* hMC6SC                 = (TGraph*)inFile->Get("spillana/MC6SC");
  TGraph* hMC6Col                = (TGraph*)inFile->Get("spillana/MC6Col");
  TGraph* hMC6D                  = (TGraph*)inFile->Get("spillana/MC6D");
  TGraph* hMC7SC1                = (TGraph*)inFile->Get("spillana/MC7SC1");
  TGraph* hMC7SC1Norm            = (TGraph*)inFile->Get("spillana/MC7SC1Norm");
  TGraph* hMC7Target             = (TGraph*)inFile->Get("spillana/MC7Target");
  TGraph* hMC7TargetNorm         = (TGraph*)inFile->Get("spillana/MC7TargetNorm");
  TGraph* hMC7D                  = (TGraph*)inFile->Get("spillana/MC7D");
  TGraph* hMC7Trig               = (TGraph*)inFile->Get("spillana/MC7Trig");
  TGraph* hMC7TrigNorm           = (TGraph*)inFile->Get("spillana/MC7TrigNorm");
  TGraph* hTrigDetOn             = (TGraph*)inFile->Get("spillana/TrigDetOn");
  TGraph* hTrigDetOnNorm         = (TGraph*)inFile->Get("spillana/TrigDetOnNorm");
  TGraph* hGoodTrigFrac          = (TGraph*)inFile->Get("spillana/GoodTrigFrac");
  TGraph* hShutOffs              = (TGraph*)inFile->Get("spillana/ShutOffs");
  TGraph* hShutOffsNorm          = (TGraph*)inFile->Get("spillana/ShutOffsNorm");
  TGraph* hTrigOverShutOffs      = (TGraph*)inFile->Get("spillana/TrigOverShutOffs");
  TGraph* hTrigDetOnOverShutOffs = (TGraph*)inFile->Get("spillana/TrigDetOnOverShutOffs");

  TCanvas* canv = new TCanvas("canv", "", 800, 800);

  TPad *p1 = new TPad("p1","p1",0.,0.,1.,0.14);
  p1->SetFillColor(0);
  p1->SetFrameLineColor(0);
  p1->SetTopMargin(0.2);
  p1->SetBottomMargin(0.2);
  p1->SetRightMargin(0.05);
  p1->Draw();
  p1->cd();
  hMC6IC->GetXaxis()->SetLabelSize(0.2);
  hMC6IC->GetXaxis()->SetRangeUser(start_time, end_time);
  hMC6IC->GetYaxis()->SetRangeUser(1e8, 5e9);
  hMC6IC->GetYaxis()->SetTitle("MC6IC");
  hMC6IC->GetYaxis()->SetNdivisions(4);
  hMC6IC->GetYaxis()->SetLabelSize(0.15);
  hMC6IC->GetYaxis()->SetTitleSize(0.2);
  hMC6IC->GetYaxis()->SetTitleOffset(0.2);
  hMC6IC->GetYaxis()->CenterTitle();
  hMC6IC->Draw("APL");

  canv->cd();
  TPad *p2 = new TPad("p2","p2",0.,0.14,1.,0.28);
  p2->SetFillColor(0);
  p2->SetFrameLineColor(0);
  p2->SetTopMargin(0.2);
  p2->SetBottomMargin(0.2);
  p2->SetRightMargin(0.05);
  p2->Draw();
  hMC6SC->GetXaxis()->SetLabelSize(0);
  hMC6SC->GetXaxis()->SetTickLength(0);
  hMC6SC->GetXaxis()->SetAxisColor(0);
  hMC6SC->GetXaxis()->SetRangeUser(start_time, end_time);
  hMC6SC->GetYaxis()->SetRangeUser(0, 2e6);
  hMC6SC->GetYaxis()->SetTitle("MC6SC");
  hMC6SC->GetYaxis()->SetNdivisions(4);
  hMC6SC->GetYaxis()->SetLabelSize(0.15);
  hMC6SC->GetYaxis()->SetTitleSize(0.2);
  hMC6SC->GetYaxis()->SetTitleOffset(0.2);
  hMC6SC->GetYaxis()->CenterTitle();
  p2->cd();
  hMC6SC->Draw("APL");

  canv->cd();
  TPad *p3 = new TPad("p3","p3",0.,0.28,1.,0.42);
  p3->SetFillColor(0);
  p3->SetFrameLineColor(0);
  p3->SetTopMargin(0.2);
  p3->SetBottomMargin(0.2);
  p3->SetRightMargin(0.05);
  p3->Draw();
  hMC7SC1->GetXaxis()->SetLabelSize(0);
  hMC7SC1->GetXaxis()->SetTickLength(0);
  hMC7SC1->GetXaxis()->SetAxisColor(0);
  hMC7SC1->GetXaxis()->SetRangeUser(start_time, end_time);
  hMC7SC1->GetYaxis()->SetRangeUser(0, mc7count);
  hMC7SC1->GetYaxis()->SetTitle("MC7SC1");
  hMC7SC1->GetYaxis()->SetNdivisions(4);
  hMC7SC1->GetYaxis()->SetLabelSize(0.15);
  hMC7SC1->GetYaxis()->SetTitleSize(0.2);
  hMC7SC1->GetYaxis()->SetTitleOffset(0.2);
  hMC7SC1->GetYaxis()->CenterTitle();
  p3->cd();
  hMC7SC1->Draw("APL");

  canv->cd();
  TPad *p4 = new TPad("p4","p4",0.,0.42,1.,0.56);
  p4->SetFillColor(0);
  p4->SetFrameLineColor(0);
  p4->SetTopMargin(0.2);
  p4->SetBottomMargin(0.2);
  p4->SetRightMargin(0.05);
  p4->Draw();
  hMC7Target->GetXaxis()->SetLabelSize(0);
  hMC7Target->GetXaxis()->SetTickLength(0);
  hMC7Target->GetXaxis()->SetAxisColor(0);
  hMC7Target->GetXaxis()->SetRangeUser(start_time, end_time);
  hMC7Target->GetYaxis()->SetRangeUser(0, mc7target);
  hMC7Target->GetYaxis()->SetTitle("MC7Target");
  hMC7Target->GetYaxis()->SetNdivisions(4);
  hMC7Target->GetYaxis()->SetLabelSize(0.15);
  hMC7Target->GetYaxis()->SetTitleSize(0.2);
  hMC7Target->GetYaxis()->SetTitleOffset(0.2);
  hMC7Target->GetYaxis()->CenterTitle();
  p4->cd();
  hMC7Target->Draw("APL");

  canv->cd();
  TPad *p5 = new TPad("p5","p5",0.,0.56,1.,0.7);
  p5->SetFillColor(0);
  p5->SetFrameLineColor(0);
  p5->SetTopMargin(0.2);
  p5->SetBottomMargin(0.2);
  p5->SetRightMargin(0.05);
  p5->Draw();
  hMC7Trig->GetXaxis()->SetLabelSize(0);
  hMC7Trig->GetXaxis()->SetTickLength(0);
  hMC7Trig->GetXaxis()->SetAxisColor(0);
  hMC7Trig->GetXaxis()->SetRangeUser(start_time, end_time);
  hMC7Trig->GetYaxis()->SetRangeUser(0, mc7trig);
  hMC7Trig->GetYaxis()->SetTitle("MC7Trig");
  hMC7Trig->GetYaxis()->SetNdivisions(4);
  hMC7Trig->GetYaxis()->SetLabelSize(0.15);
  hMC7Trig->GetYaxis()->SetTitleSize(0.2);
  hMC7Trig->GetYaxis()->SetTitleOffset(0.2);
  hMC7Trig->GetYaxis()->CenterTitle();
  p5->cd();
  hMC7Trig->Draw("APL");

  canv->cd();
  TPad *p6 = new TPad("p6","p6",0.,0.7,1.,0.84);
  p6->SetFillColor(0);
  p6->SetFrameLineColor(0);
  p6->SetTopMargin(0.2);
  p6->SetBottomMargin(0.2);
  p6->SetRightMargin(0.05);
  p6->Draw();
  hTrigDetOn->GetXaxis()->SetLabelSize(0);
  hTrigDetOn->GetXaxis()->SetTickLength(0);
  hTrigDetOn->GetXaxis()->SetAxisColor(0);
  hTrigDetOn->GetXaxis()->SetRangeUser(start_time, end_time);
  hTrigDetOn->GetYaxis()->SetRangeUser(0, mc7trig);
  hTrigDetOn->GetYaxis()->SetTitle("TrigDetOn");
  hTrigDetOn->GetYaxis()->SetNdivisions(4);
  hTrigDetOn->GetYaxis()->SetLabelSize(0.15);
  hTrigDetOn->GetYaxis()->SetTitleSize(0.2);
  hTrigDetOn->GetYaxis()->SetTitleOffset(0.2);
  hTrigDetOn->GetYaxis()->CenterTitle();
  p6->cd();
  hTrigDetOn->Draw("APL");

  canv->cd();
  TPad *p7 = new TPad("p7","p7",0.,0.84,1.,0.98);
  p7->SetFillColor(0);
  p7->SetFrameLineColor(0);
  p7->SetTopMargin(0.2);
  p7->SetBottomMargin(0.2);
  p7->SetRightMargin(0.05);
  p7->Draw();
  hTrigDetOnOverShutOffs->GetXaxis()->SetLabelSize(0);
  hTrigDetOnOverShutOffs->GetXaxis()->SetTickLength(0);
  hTrigDetOnOverShutOffs->GetXaxis()->SetAxisColor(0);
  hTrigDetOnOverShutOffs->GetXaxis()->SetRangeUser(start_time, end_time);
  hTrigDetOnOverShutOffs->GetYaxis()->SetRangeUser(0, mc7trignorm);
  hTrigDetOnOverShutOffs->GetYaxis()->SetTitle("#splitline{TrigDetOn/}{ShutOff}");
  hTrigDetOnOverShutOffs->GetYaxis()->SetNdivisions(4);
  hTrigDetOnOverShutOffs->GetYaxis()->SetLabelSize(0.15);
  hTrigDetOnOverShutOffs->GetYaxis()->SetTitleSize(0.2);
  hTrigDetOnOverShutOffs->GetYaxis()->SetTitleOffset(0.2);
  hTrigDetOnOverShutOffs->GetYaxis()->CenterTitle();
  p7->cd();
  hTrigDetOnOverShutOffs->Draw("APL");

}
