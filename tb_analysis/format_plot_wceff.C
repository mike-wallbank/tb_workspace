{
  TFile* inFile = TFile::Open("/pnfs/nova/scratch/users/bacharya/TestBeamGrid/MergedOutput.root", "READ");

  TProfile* wcEff = (TProfile*)inFile->Get("bishnuana/WCEff");

  wcEff->SetStats(0); // remove stats box
  wcEff->GetXaxis()->CenterTitle();
  wcEff->GetYaxis()->CenterTitle();

  TCanvas* canv = new TCanvas("canv", "", 800, 600);
  wcEff->Draw("hist text");
  canv->SetGridx();
  canv->SaveAs("WCEff.png");
}
