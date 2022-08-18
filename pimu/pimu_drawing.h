#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPaveStats.h"

void Overlay(TH1* pi, TH1* mu, const char* label, TFile* outFile, bool stats = false) {

  TCanvas* canv = new TCanvas("canv", "", 800, 600);
  TLegend* leg = new TLegend(0.7, 0.6, 0.85, 0.85);

  canv->cd();
  pi->SetLineColor(kRed);
  pi->SetLineWidth(2);
  pi->SetFillColor(kRed);
  pi->SetFillStyle(3002);
  leg->AddEntry(pi, "#pi", "lf");
  pi->SetMaximum(1.1*std::max(pi->GetMaximum(), mu->GetMaximum()));
  pi->Draw("hist");
  canv->Update();
  if (stats) {
    TPaveStats* pi_stat = (TPaveStats*)pi->GetListOfFunctions()->FindObject("stats");
    pi_stat->SetX1NDC(0.3); pi_stat->SetX2NDC(0.6);
    pi_stat->SetTextColor(kRed);
  }
  canv->Modified();
  mu->SetLineColor(kBlue);
  mu->SetLineWidth(2);
  mu->SetFillColor(kBlue);
  mu->SetFillStyle(3002);
  leg->AddEntry(mu, "#mu", "lf");
  mu->Draw("hist sames");
  canv->Update();
  if (stats) {
    TPaveStats* mu_stat = (TPaveStats*)mu->GetListOfFunctions()->FindObject("stats");
    mu_stat->SetTextColor(kBlue);
    mu_stat->SetX1NDC(0.6); mu_stat->SetX2NDC(0.9);
  }
  canv->Modified();
  leg->Draw();
  canv->Modified();
  canv->Update();
  canv->SaveAs(Form("plots/%s.png", label));
  outFile->WriteTObject(canv, label);

  delete leg;
  delete canv;

}
