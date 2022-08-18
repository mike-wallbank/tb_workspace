// Make a simple spectrum plot
#include "CAFAna/Core/Binning.h"
#include "CAFAna/Cuts/Cuts.h"
#include "CAFAna/Core/Spectrum.h"
#include "CAFAna/Core/SpectrumLoader.h"
#include "CAFAna/Vars/Vars.h"
#include "StandardRecord/Proxy/SRProxy.h"
#include "TCanvas.h"
#include "TH2.h"
using namespace ana;
void demo0()
{
  // Environment variables and wildcards work. Most commonly you want a SAM
  // dataset. Pass -ss --limit 1 on the cafe command line to make this take a
  // reasonable amount of time for demo purposes. 
  const std::string fname = "prod_sumdecaf_development_nd_genie_N1810j0211a_nonswap_fhc_nova_v08_full_ndphysics_contain_v1";
  SpectrumLoader loader(fname);

  // binning
  const Binning bins = Binning::Simple(100, 0, 1000);

  // Specify variables needed and arbitrary code to extract value from
  // SRProxy
  const Var kFirstTrackLen([](const caf::SRProxy* sr) {
      //often you need to include checks to make sure the object you want to look at exists 
      //and assign a value if it doesn't. otherwise you will get abort errors
      if (sr->trk.kalman.ntracks == 0)
        return 0.0f;
      return float(sr->trk.kalman.tracks[0].len);
    });

  // Spectrum to be filled from the loader
  Spectrum len("Track length (cm)", bins, loader, kFirstTrackLen, kIsNumuCC);
  //Spectrum energy("Energy (GeV)", Binning::Simple(100,0,5), loader, kFirstTrackLen, kNoCut);

  // Do it!
  loader.Go();

  // How to scale histograms
  const double pot = 18e20;

  // We have histograms
  len.ToTH1(pot)->Draw("hist");

  // TFile* outFile = new TFile("out_spectra.root", "RECREATE");
  // len.SaveTo(outFile->mkdir("len"), "len");
  // energy.SaveTo(outFile->mkdir("energy"), "energy");
  // outFile->Close();
}
