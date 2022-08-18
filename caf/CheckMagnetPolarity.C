#include "CAFAna/Core/EventList.h"
#include "CAFAna/Cuts/Cuts.h"
#include "TestBeamAna/Analysis/TestBeamLoaders.h"
#include "TestBeamAna/Vars/BeamVars.h"

#include <string>
#include <vector>

using namespace ana;

void CheckMagnetPolarity() {

  std::string fileName = "r101861_oldspillinfo.caf.root";

  std::vector<const Var*> vars = {&kMC7MagPol, &kMC7Magnet};
  MakeTextListFile(fileName,
  		   {kNoCut},
                   {"polarity_check.txt"},
                   vars);

}
