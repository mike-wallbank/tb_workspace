
#include "CAFAna/Core/EventList.h"
#include "CAFAna/Vars/Vars.h"
#include "TestBeamAna/Vars/BeamVars.h"

#include "TFile.h"

using namespace ana;

void AnalyzePolarity() {
  
  std::vector<const Var*> vars = {&kRun, &kMC7MagPol};
  MakeTextListFile("testbeam_r00101853_s00_beamline_R21-07-27-testbeam-production.caf.root",
                   {kNoCut},
                   {"caf_polarity_1853.txt"},
		   vars);
  MakeTextListFile("testbeam_r00101858_s00_beamline_R21-07-27-testbeam-production.caf.root",
                   {kNoCut},
                   {"caf_polarity_1858.txt"},
		   vars);

  return;


}
