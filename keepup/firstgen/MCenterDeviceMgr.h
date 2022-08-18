// MCenterDeviceMgr.h
// Helper class to analyze spill information from MCenter devices

// -----------------------------------------------------------------------
struct MCenterDevice {
  MCenterDevice(std::string name, std::string text) { Name = name; Text = text; }
  virtual ~MCenterDevice() = default;
  std::string Name;
  std::string Text;
  float Low;
  float High;
  int NSpills;
  bool Average;
  bool Integral;
  TH1* Plot;
};

// -----------------------------------------------------------------------
struct MCenterDeviceRatio : public MCenterDevice {
 MCenterDeviceRatio(std::string name, std::string text) : MCenterDevice(name, text) { }
  std::string Device1;
  std::string Device2;
};

// -----------------------------------------------------------------------
struct MCenterDeviceFromFile : public MCenterDevice {
 MCenterDeviceFromFile(std::string name, std::string text) : MCenterDevice(name, text) { }
  std::string File;
};

// -----------------------------------------------------------------------
class MCenterDeviceMgr {
public:

  MCenterDeviceMgr(std::string file, std::string tree);
  ~MCenterDeviceMgr();

  void AddDevice(std::string device, std::string label,
		 float low, float high,
		 unsigned int nspills, bool average,
		 std::string text, bool integral);
  void AddDeviceRatio(std::string name, std::string device1, std::string device2,
		      std::string label,
		      float low, float high,
		      std::string text,
		      unsigned int nspills);
  void AddDeviceFromFile(std::string name, std::string file, std::string label,
			 float low, float high,
			 unsigned int nspills, bool average,
			 std::string text, bool integral);
  void DrawPlots(std::string name,
		 std::vector<std::string> devices);
  void DrawPlot(MCenterDevice* device, TCanvas* canv,
		unsigned int num, unsigned int num_tot);
  void FillPlots();
  TH1* MakePlot(std::string name, std::string label,
		unsigned int nspills, bool average);
  void SetStartTime(unsigned int year, unsigned int month, unsigned int day,
		    unsigned int hour, unsigned int min, unsigned int sec);
  void SetEndTime(unsigned int year, unsigned int month, unsigned int day,
		  unsigned int hour, unsigned int min, unsigned int sec);
  void SetOutputDir(std::string dir);

private:

  TFile* fFile;
  TTree* fTree;
  time_t fStartTime;
  time_t fEndTime;
  std::string fOutputDir;

  std::map<std::string, MCenterDevice*> fDevices;
  
};

// -----------------------------------------------------------------------
MCenterDeviceMgr::MCenterDeviceMgr(std::string file, std::string tree) {
  TGaxis::SetMaxDigits(3);
  fFile = TFile::Open(file.c_str(), "READ");
  fTree = (TTree*)fFile->Get(tree.c_str());
  if (!fTree)
    std::cout << "Error: cannot read tree " << tree << std::endl;
  fTree->Draw("SpillTime>>h","","goff");
  TH1* h = (TH1*)gDirectory->Get("h");
  fStartTime = h->GetXaxis()->GetBinLowEdge(1);
  fEndTime = h->GetXaxis()->GetBinLowEdge(h->GetNbinsX());
  return;
}

// -----------------------------------------------------------------------
MCenterDeviceMgr::~MCenterDeviceMgr() {
  for (std::map<std::string, MCenterDevice*>::iterator deviceIt = fDevices.begin();
       deviceIt != fDevices.end(); ++deviceIt)
    delete deviceIt->second;
  return;
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::AddDevice(std::string devicename, std::string label,
				 float low = std::numeric_limits<float>::max(), float high = std::numeric_limits<float>::max(),
				 unsigned int nspills = 1, bool average = false,
				 std::string text = "", bool integral = false) {
  MCenterDevice* device = new MCenterDevice(devicename, text);
  device->Plot = MakePlot(devicename, label, nspills, average);
  device->Low = low;
  device->High = high;
  device->NSpills = nspills;
  device->Average = average;
  device->Integral = integral;
  fDevices[devicename] = device;
  return;
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::AddDeviceRatio(std::string name, std::string device1, std::string device2,
				      std::string label,
				      float low = std::numeric_limits<float>::max(), float high = std::numeric_limits<float>::max(),
				      std::string text = "",
				      unsigned int nspills = 1) {
  MCenterDeviceRatio* device = new MCenterDeviceRatio(name, text);
  device->Plot = MakePlot(name, label, nspills, false);
  device->Low = low;
  device->High = high;
  device->NSpills = nspills;
  device->Device1 = device1;
  device->Device2 = device2;
  device->Integral = false;
  fDevices[name] = device;
  return;
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::AddDeviceFromFile(std::string devicename, std::string file, std::string label,
					 float low = std::numeric_limits<float>::max(), float high = std::numeric_limits<float>::max(),
					 unsigned int nspills = 1, bool average = false,
					 std::string text = "", bool integral = false) {
  MCenterDeviceFromFile* device = new MCenterDeviceFromFile(devicename, text);
  device->Plot = MakePlot(devicename, label, nspills, average);
  device->File = file;
  device->Low = low;
  device->High = high;
  device->NSpills = nspills;
  device->Average = average;
  device->Integral = integral;
  fDevices[devicename] = device;
  return;
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::DrawPlots(std::string name,
				 std::vector<std::string> devices) {
  TCanvas* canv = new TCanvas(Form("canv_%s", name.c_str()), "", 800, 800);
  for (unsigned int deviceIt = 0; deviceIt < devices.size(); ++deviceIt) {
    if (!fDevices.count(devices[deviceIt]))
      std::cout << "Error: device " << devices[deviceIt] << " requested for plotting does not exist" << std::endl;
    DrawPlot(fDevices[devices[deviceIt]], canv, deviceIt, devices.size());
  }
  canv->SaveAs(Form("%s/%s.png", fOutputDir.c_str(), name.c_str()));
  delete canv;
  return;
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::DrawPlot(MCenterDevice* device, TCanvas* canv,
				unsigned int num, unsigned int num_tot) {
  float lowery = (float)num/(float)num_tot;
  float uppery = (float)(num+1.)/(float)num_tot;
  canv->cd();
  TPad *p = new TPad(Form("p_%s_%s",canv->GetName(),device->Name.c_str()),"p",0.,lowery,1.,uppery);
  p->SetFillColor(0);
  p->SetFrameLineColor(0);
  p->SetTopMargin(0.2);
  p->SetBottomMargin(0.2);
  p->SetRightMargin(0.05);
  p->Draw();
  if (num == 0)
    device->Plot->GetXaxis()->SetLabelSize(0.2);
  else {
    device->Plot->GetXaxis()->SetLabelSize(0.);
    device->Plot->GetXaxis()->SetAxisColor(0);
  }
  p->cd();
  device->Plot->Draw("hist");
  TText text;
  std::stringstream plottext; plottext << device->Text;
  if (device->Integral) plottext << " (" << device->Plot->Integral() << ")";
  text.SetTextFont(42);
  text.SetTextSize(0.1);
  text.DrawTextNDC(0.15, 0.8, plottext.str().c_str());
  return;
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::FillPlots() {
  double spillTime;
  fTree->SetBranchAddress("SpillTime", &spillTime);
  std::map<std::string, double> deviceMap;

  // set branch addresses for the single variables
  for (std::map<std::string, MCenterDevice*>::const_iterator deviceIt = fDevices.begin(); deviceIt != fDevices.end(); ++deviceIt) {
    if (dynamic_cast<MCenterDeviceRatio*>(deviceIt->second) or dynamic_cast<MCenterDeviceFromFile*>(deviceIt->second))
      continue;
    deviceMap[deviceIt->first] = 0.;
    fTree->SetBranchAddress(deviceIt->first.c_str(), &deviceMap[deviceIt->first]);
  }

  // fill plots from the tree
  for (int spill = 0; spill < fTree->GetEntriesFast(); ++spill) {
    fTree->GetEntry(spill);
    for (std::map<std::string, MCenterDevice*>::iterator deviceIt = fDevices.begin(); deviceIt != fDevices.end(); ++deviceIt) {
      if (dynamic_cast<MCenterDeviceFromFile*>(deviceIt->second))
	continue;
      if (dynamic_cast<MCenterDeviceRatio*>(deviceIt->second)) {
	MCenterDeviceRatio* ratio = dynamic_cast<MCenterDeviceRatio*>(deviceIt->second);
	if (deviceMap[ratio->Device2] > 0)
	  //ratio->Plot->Fill(spillTime, deviceMap[ratio->Device1]/pow(deviceMap[ratio->Device2],2));
	  ratio->Plot->Fill(spillTime, deviceMap[ratio->Device1]/deviceMap[ratio->Device2]);
      }
      else if (!isinf(deviceMap[deviceIt->first]) and deviceMap[deviceIt->first] != -999)
	deviceIt->second->Plot->Fill(spillTime, deviceMap[deviceIt->first]);
    }
  }

  // fill plots from the files
  for (std::map<std::string, MCenterDevice*>::const_iterator deviceIt = fDevices.begin(); deviceIt != fDevices.end(); ++deviceIt) {
    if (dynamic_cast<MCenterDeviceFromFile*>(deviceIt->second)) {
      std::ifstream file((dynamic_cast<MCenterDeviceFromFile*>(deviceIt->second))->File);
      std::string str, buf;
      while (std::getline(file, str)) {
	std::stringstream ss(str);
	std::vector<double> line;
	while (ss >> buf)
	  line.push_back(stod(buf));
	deviceIt->second->Plot->Fill(line[0], line[1]);
      }
    }
  }

  // formatting
  for (std::map<std::string, MCenterDevice*>::const_iterator deviceIt = fDevices.begin(); deviceIt != fDevices.end(); ++deviceIt) {
    if (deviceIt->second->Average)
      deviceIt->second->Plot->Scale(1./deviceIt->second->NSpills);
    if (deviceIt->second->Low < std::numeric_limits<float>::max())
      deviceIt->second->Plot->SetMinimum(deviceIt->second->Low);
    if (deviceIt->second->High < std::numeric_limits<float>::max())
      deviceIt->second->Plot->SetMaximum(deviceIt->second->High);
  }

  return;
}

// -----------------------------------------------------------------------
TH1* MCenterDeviceMgr::MakePlot(std::string name, std::string label,
				unsigned int nspills, bool average = false) {
  TH1* plot = new TH1D(name.c_str(), "", (fEndTime-fStartTime)/(60*nspills), fStartTime, fEndTime);
  plot->SetStats(0);
  plot->SetLineColor(kBlack);
  if (nspills > 1 and !average)
    plot->GetYaxis()->SetTitle(Form("#splitline{%s}{(%d spills)}", label.c_str(), nspills));
  else
    plot->GetYaxis()->SetTitle(label.c_str());
  plot->GetYaxis()->SetNdivisions(4);
  plot->GetYaxis()->SetLabelSize(0.15);
  plot->GetYaxis()->SetTitleSize(0.2);
  plot->GetYaxis()->SetTitleOffset(0.2);
  plot->GetYaxis()->CenterTitle();
  plot->GetXaxis()->SetTimeDisplay(1);
  //plot->GetXaxis()->SetTimeFormat("%b-%d %H:%M %F 1970-01-01 00:00:00");
  plot->GetXaxis()->SetTimeFormat("%b-%d %F 1970-01-01 00:00:00");
  return plot;
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::SetStartTime(unsigned int year, unsigned int month, unsigned int day,
				    unsigned int hour, unsigned int min, unsigned int sec) {
  struct tm start_tm;
  if (strptime(Form("%d-%d-%d_%d:%d:%d", year, month, day, hour, min, sec),
	       "%Y-%m-%d_%H:%M:%S", &start_tm) != NULL)
    fStartTime = mktime(&start_tm);
  return;
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::SetEndTime(unsigned int year, unsigned int month, unsigned int day,
				  unsigned int hour, unsigned int min, unsigned int sec) {
  struct tm end_tm;
  if (strptime(Form("%d-%d-%d_%d:%d:%d", year, month, day, hour, min, sec),
	       "%Y-%m-%d_%H:%M:%S", &end_tm) != NULL)
    fEndTime = mktime(&end_tm);
  return;
}

// -----------------------------------------------------------------------
void MCenterDeviceMgr::SetOutputDir(std::string dir) {
  fOutputDir = dir;
  return;
}
