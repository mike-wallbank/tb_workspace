{
  TFile* inFile = new TFile("RateShutOffAna_31.25ns.root", "READ");

  TH1* rawProfile = (TH1*)inFile->Get("rateshutoffana/HitProfile");
  int integral = rawProfile->Integral();
  float scale = 5300000./integral;
  TH1I* modProfile = new TH1I("modProfile", "", rawProfile->GetNbinsX(), 0, 5e9);
  for (Int_t bin = 1; bin <= rawProfile->GetNbinsX(); ++bin)
    modProfile->SetBinContent(bin, (int)((float)rawProfile->GetBinContent(bin)*scale));
  //profile->Scale(2264600./profile->Integral());
  //profile->Scale(5300000./profile->Integral());

  // TH1I* modProfile = new TH1I("modProfile", "", profile->GetNbinsX(), 0, 5e9);
  // for (Int_t bin = 1; bin <= profile->GetNbinsX(); ++bin)
  //   modProfile->SetBinContent(bin, (int)profile->GetBinContent(bin));

  std::cout << "Modified integral (c.f. 2264600) " << modProfile->Integral() << std::endl;

}
