// MCenterDeviceMgr.h
// Helper class to analyze spill information from MCenter devices

// -----------------------------------------------------------------------
struct MCenterDevice {
  std::string Name;
  std::string Title;
  float LowerLimit;
  float UpperLimit;
  unsigned int Rebin;
  TGraph* Plot;
};

// -----------------------------------------------------------------------
class MCenterDeviceMgr {
public:

  MCenterDeviceMgr();

  void AddDevice(std::string name, std::string title,
		 float low, float high, unsigned int rebin);
  void DrawPlots(std::string name,
		 std::vector<std::string> devices);
  void DrawPlot(MCenterDevice device, TCanvas* canv,
		unsigned int num, unsigned int num_tot);
  void FillPlots();
  void SetupInput(std::string file, std::string tree);
  void SetStartTime(unsigned int year, unsigned int month, unsigned int day,
		    unsigned int hour, unsigned int min, unsigned int sec);
  void SetEndTime(unsigned int year, unsigned int month, unsigned int day,
		  unsigned int hour, unsigned int min, unsigned int sec);

private:

  TFile* fFile;
  TTree* fTree;
  time_t fStartTime;
  time_t fEndTime;

  std::map<std::string, MCenterDevice> fDevices;
  
};

// -----------------------------------------------------------------------
MCenterDeviceMgr::MCenterDeviceMgr() {
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::SetupInput(std::string file, std::string tree) {
  fFile = TFile::Open(file.c_str(), "READ");
  fTree = (TTree*)fFile->Get(tree.c_str());
  if (!fTree)
    std::cout << "Error: cannot read tree " << tree << std::endl;
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::SetStartTime(unsigned int year, unsigned int month, unsigned int day,
				    unsigned int hour, unsigned int min, unsigned int sec) {
  struct tm start_tm, end_tm;
  if (strptime(Form("%d-%d-%d_%d:%d:%d", year, month, day, hour, min, sec),
	       "%Y-%m-%d_%H:%M:%S", &start_tm) != NULL)
    fStartTime = mktime(&start_tm);
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::SetEndTime(unsigned int year, unsigned int month, unsigned int day,
				  unsigned int hour, unsigned int min, unsigned int sec) {
  struct tm end_tm;
  if (strptime(Form("%d-%d-%d_%d:%d:%d", year, month, day, hour, min, sec),
	       "%Y-%m-%d_%H:%M:%S", &end_tm) != NULL)
    fEndTime = mktime(&end_tm);
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::AddDevice(std::string name, std::string title,
				 float low = 0., float high = 0., unsigned int rebin = 0) {
  MCenterDevice device;
  device.Name = name;
  device.Title = title;
  device.UpperLimit = high;
  device.LowerLimit = low;
  device.Rebin = rebin;
  device.Plot = new TGraph();
  device.Plot->GetXaxis()->SetTimeDisplay(1);
  device.Plot->GetXaxis()->SetTimeFormat("%b-%d %H:%M %F 1970-01-01 00:00:00");
  fDevices[name] = device;
  return;
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::FillPlots() {
  double spillTime;
  fTree->SetBranchAddress("SpillTime", &spillTime);
  std::map<std::string, double> deviceMap;
  for (std::map<std::string, MCenterDevice>::const_iterator deviceIt = fDevices.begin(); deviceIt != fDevices.end(); ++deviceIt) {
    deviceMap[deviceIt->first] = 0.;
    fTree->SetBranchAddress(deviceIt->first.c_str(), &deviceMap[deviceIt->first]);
  }
  for (int spill = 0; spill < fTree->GetEntriesFast(); ++spill) {
    fTree->GetEntry(spill);
    for (std::map<std::string, MCenterDevice>::iterator deviceIt = fDevices.begin(); deviceIt != fDevices.end(); ++deviceIt)
      deviceIt->second.Plot->SetPoint(deviceIt->second.Plot->GetN(), spillTime, deviceMap[deviceIt->first]);
  }
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::DrawPlots(std::string name,
				 std::vector<std::string> devices) {
  TCanvas* canv = new TCanvas(Form("canv_%s", name.c_str()), "", 800, 800);
  for (unsigned int deviceIt = 0; deviceIt < devices.size(); ++deviceIt)
    DrawPlot(fDevices[devices[deviceIt]], canv, deviceIt, devices.size());
  canv->SaveAs(Form("plots/%s.png", name.c_str()));
  delete canv;
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::DrawPlot(MCenterDevice device, TCanvas* canv,
				unsigned int num, unsigned int num_tot) {
  float lowery = (float)num/(float)num_tot;
  float uppery = (float)(num+1.)/(float)num_tot;
  std::cout << "Num " << num << ", lowery " << lowery << ", uppery " << uppery << std::endl;
  canv->cd();
  TPad *p = new TPad(Form("p_%s_%s",canv->GetName(),device.Name.c_str()),"p",0.,lowery,1.,uppery);
  p->SetFillColor(0);
  p->SetFrameLineColor(0);
  p->SetTopMargin(0.2);
  p->SetBottomMargin(0.2);
  p->SetRightMargin(0.05);
  p->Draw();
  if (num == 0)
    device.Plot->GetXaxis()->SetLabelSize(0.2);
  else
    device.Plot->GetXaxis()->SetLabelSize(0.);
  device.Plot->GetXaxis()->SetRangeUser(fStartTime, fEndTime);
  if (device.LowerLimit > 0. and device.UpperLimit > 0.)
    device.Plot->GetYaxis()->SetRangeUser(device.LowerLimit, device.UpperLimit);
  device.Plot->GetYaxis()->SetTitle(device.Title.c_str());
  device.Plot->GetYaxis()->SetNdivisions(4);
  device.Plot->GetYaxis()->SetLabelSize(0.15);
  device.Plot->GetYaxis()->SetTitleSize(0.2);
  device.Plot->GetYaxis()->SetTitleOffset(0.2);
  device.Plot->GetYaxis()->CenterTitle();
  p->cd();
  device.Plot->Draw("APL");
}
