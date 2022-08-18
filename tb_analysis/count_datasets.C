#include "TFile.h"
#include "TTree.h"
#include "TCut.h"

#include <iostream>

void count_datasets() {

  TFile* p2_file
    = TFile::Open("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period2/R21-07-27-testbeam-production.a/TBRecoAna_r100224-r100856.root",
		  "READ");
  TFile* p3_file
    = TFile::Open("/nova/ana/users/wallbank/TestBeam/FlatTreeData/Period3/R21-07-27-testbeam-production.a/TBRecoAna_r100985-r101483.root",
		  "READ");

  TTree* p2_tree = (TTree*)p2_file->Get("tbrecoana/evts");
  TTree* p3_tree = (TTree*)p3_file->Get("tbrecoana/evts");

  // Define cuts
  TCut wcX("wcmom>=0");
  TCut tofX("toftime>=0");
  TCut magdist("abs(wcMagDist)<5");
  TCut blcuts(wcX&&tofX&&magdist);
  TCut nhit("winTrkNhit>5");
  TCut centralVtx("abs(winTrkStrtX)<20&&winTrkStrtY>-25&&winTrkStrtY<15&&winTrkStrtZ<18");
  TCut hittime("winTrkMinTime>45000&&winTrkMinTime<55000");
  TCut detcuts(centralVtx&&hittime&&nhit);
  TCut selection(blcuts&&detcuts);

  TCut electrontof_p2("toftime>40&&toftime<50");
  TCut protontof_p2("toftime>50&&(toftime<70||(run>100826&&toftime>70))");
  TCut kaontof_p2("toftime>45&&((toftime<=50&&run<100827)||(toftime>50&&toftime<=70&&run>=100827))");
  TCut pimutof_p2("toftime>40&&((toftime<=45&&run<100827)||(toftime<=50&&run>=100827))");

  TCut electron_p2(selection&&electrontof_p2&&"ckovadc>0");
  TCut proton_p2(selection&&protontof_p2&&"ckovadc<0");
  TCut kaon_p2(selection&&kaontof_p2&&"ckovadc<0");
  TCut pimu_p2(selection&&pimutof_p2&&"ckovadc<0");

  TCut electrontof_p3("toftime>30&&toftime<36");
  TCut protontof_p3
    ("(mc7mag>900&&mc7mag<1100&&toftime>39&&toftime<50)||(mc7mag>650&&mc7mag<850&&toftime>42&&toftime<60)||(mc7mag>400&&mc7mag<600&&toftime>56&&toftime<80)");
  TCut kaontof_p3
    ("(mc7mag>900&&mc7mag<1100&&toftime>34&&toftime<39)||(mc7mag>650&&mc7mag<850&&toftime>36&&toftime<42)||(mc7mag>400&&mc7mag<600&&toftime>40&&toftime<56)");
  TCut pimutof_p3
    ("(mc7mag>900&&mc7mag<1100&&toftime>30&&toftime<34)||(mc7mag>650&&mc7mag<850&&toftime>30&&toftime<36)||(mc7mag>400&&mc7mag<600&&toftime>30&&toftime<40)");

  TCut electron_p3(selection&&electrontof_p3&&"ckovadc>0");
  TCut proton_p3(selection&&protontof_p3&&"ckovadc<0");
  TCut kaon_p3(selection&&kaontof_p3&&"ckovadc<0");
  TCut pimu_p3(selection&&pimutof_p3&&"ckovadc<0");

  TCut p2_1GeV("run<=100826");
  TCut p2_500MeV("run>=100827");

  TCut p3_1GeV("mc7mag>900&&mc7mag<1100");
  TCut p3_750MeV("mc7mag>650&&mc7mag<850");
  TCut p3_500MeV("mc7mag>400&&mc7mag<600");
  TCut p3_underfill("run<101357");
  TCut p3_neg("run>=101452&&run<=101483");

  // count up!

  // Period 2
  // all
  int n_electron_p2 = p2_tree->GetEntries(electron_p2);
  int n_proton_p2 = p2_tree->GetEntries(proton_p2);
  int n_kaon_p2 = p2_tree->GetEntries(kaon_p2);
  int n_pimu_p2 = p2_tree->GetEntries(pimu_p2);
  // 1 GeV/c
  int n1GeV_electron_p2 = p2_tree->GetEntries(electron_p2&&p2_1GeV);
  int n1GeV_proton_p2 = p2_tree->GetEntries(proton_p2&&p2_1GeV);
  int n1GeV_kaon_p2 = p2_tree->GetEntries(kaon_p2&&p2_1GeV);
  int n1GeV_pimu_p2 = p2_tree->GetEntries(pimu_p2&&p2_1GeV);
  // 0.5 GeV/c
  int n500MeV_electron_p2 = p2_tree->GetEntries(electron_p2&&p2_500MeV);
  int n500MeV_proton_p2 = p2_tree->GetEntries(proton_p2&&p2_500MeV);
  int n500MeV_kaon_p2 = p2_tree->GetEntries(kaon_p2&&p2_500MeV);
  int n500MeV_pimu_p2 = p2_tree->GetEntries(pimu_p2&&p2_500MeV);

  // Period 3
  // all
  int n_electron_p3 = p3_tree->GetEntries(electron_p3);
  int n_proton_p3 = p3_tree->GetEntries(proton_p3);
  int n_kaon_p3 = p3_tree->GetEntries(kaon_p3);
  int n_pimu_p3 = p3_tree->GetEntries(pimu_p3);
  // 1 GeV/c
  int n1GeV_electron_p3 = p3_tree->GetEntries(electron_p3&&p3_1GeV);
  int n1GeV_proton_p3 = p3_tree->GetEntries(proton_p3&&p3_1GeV);
  int n1GeV_kaon_p3 = p3_tree->GetEntries(kaon_p3&&p3_1GeV);
  int n1GeV_pimu_p3 = p3_tree->GetEntries(pimu_p3&&p3_1GeV);
  // 750 MeV/c
  int n750MeV_electron_p3 = p3_tree->GetEntries(electron_p3&&p3_750MeV&&!p3_neg);
  int n750MeV_proton_p3 = p3_tree->GetEntries(proton_p3&&p3_750MeV&&!p3_neg);
  int n750MeV_kaon_p3 = p3_tree->GetEntries(kaon_p3&&p3_750MeV&&!p3_neg);
  int n750MeV_pimu_p3 = p3_tree->GetEntries(pimu_p3&&p3_750MeV&&!p3_neg);
  // -750 MeV/c
  int nneg750MeV_electron_p3 = p3_tree->GetEntries(electron_p3&&p3_750MeV&&p3_neg);
  int nneg750MeV_proton_p3 = p3_tree->GetEntries(proton_p3&&p3_750MeV&&p3_neg);
  int nneg750MeV_kaon_p3 = p3_tree->GetEntries(kaon_p3&&p3_750MeV&&p3_neg);
  int nneg750MeV_pimu_p3 = p3_tree->GetEntries(pimu_p3&&p3_750MeV&&p3_neg);
  // 0.5 GeV/c
  int n500MeV_electron_p3 = p3_tree->GetEntries(electron_p3&&p3_500MeV);
  int n500MeV_proton_p3 = p3_tree->GetEntries(proton_p3&&p3_500MeV);
  int n500MeV_kaon_p3 = p3_tree->GetEntries(kaon_p3&&p3_500MeV);
  int n500MeV_pimu_p3 = p3_tree->GetEntries(pimu_p3&&p3_500MeV);
  // underfilled
  // all
  int n_electron_p3_underfill = p3_tree->GetEntries(electron_p3&&p3_underfill);
  int n_proton_p3_underfill = p3_tree->GetEntries(proton_p3&&p3_underfill);
  int n_kaon_p3_underfill = p3_tree->GetEntries(kaon_p3&&p3_underfill);
  int n_pimu_p3_underfill = p3_tree->GetEntries(pimu_p3&&p3_underfill);
  // 1 GeV/c
  int n1GeV_electron_p3_underfill = p3_tree->GetEntries(electron_p3&&p3_1GeV&&p3_underfill);
  int n1GeV_proton_p3_underfill = p3_tree->GetEntries(proton_p3&&p3_1GeV&&p3_underfill);
  int n1GeV_kaon_p3_underfill = p3_tree->GetEntries(kaon_p3&&p3_1GeV&&p3_underfill);
  int n1GeV_pimu_p3_underfill = p3_tree->GetEntries(pimu_p3&&p3_1GeV&&p3_underfill);
  // 750 MeV/c
  int n750MeV_electron_p3_underfill = p3_tree->GetEntries(electron_p3&&p3_750MeV&&!p3_neg&&p3_underfill);
  int n750MeV_proton_p3_underfill = p3_tree->GetEntries(proton_p3&&p3_750MeV&&!p3_neg&&p3_underfill);
  int n750MeV_kaon_p3_underfill = p3_tree->GetEntries(kaon_p3&&p3_750MeV&&!p3_neg&&p3_underfill);
  int n750MeV_pimu_p3_underfill = p3_tree->GetEntries(pimu_p3&&p3_750MeV&&!p3_neg&&p3_underfill);
  // -750 MeV/c
  int nneg750MeV_electron_p3_underfill = p3_tree->GetEntries(electron_p3&&p3_750MeV&&p3_neg&&p3_underfill);
  int nneg750MeV_proton_p3_underfill = p3_tree->GetEntries(proton_p3&&p3_750MeV&&p3_neg&&p3_underfill);
  int nneg750MeV_kaon_p3_underfill = p3_tree->GetEntries(kaon_p3&&p3_750MeV&&p3_neg&&p3_underfill);
  int nneg750MeV_pimu_p3_underfill = p3_tree->GetEntries(pimu_p3&&p3_750MeV&&p3_neg&&p3_underfill);
  // 0.5 GeV/c
  int n500MeV_electron_p3_underfill = p3_tree->GetEntries(electron_p3&&p3_500MeV&&p3_underfill);
  int n500MeV_proton_p3_underfill = p3_tree->GetEntries(proton_p3&&p3_500MeV&&p3_underfill);
  int n500MeV_kaon_p3_underfill = p3_tree->GetEntries(kaon_p3&&p3_500MeV&&p3_underfill);
  int n500MeV_pimu_p3_underfill = p3_tree->GetEntries(pimu_p3&&p3_500MeV&&p3_underfill);

  std::cout << "Period 2" << std::endl;
  std::cout << "\t\t1 GeV/c\t0.5 GeV/c\tAll" << std::endl
	    << "Proton\t\t" << n1GeV_proton_p2 << "\t" << n500MeV_proton_p2 << "\t\t" << n_proton_p2 << std::endl
	    << "Electron\t" << n1GeV_electron_p2 << "\t" << n500MeV_electron_p2 << "\t\t" << n_electron_p2 << std::endl
	    << "Kaon\t\t" << n1GeV_kaon_p2 << "\t" << n500MeV_kaon_p2 << "\t\t" << n_kaon_p2 << std::endl
	    << "Pi/Mu\t\t" << n1GeV_pimu_p2 << "\t" << n500MeV_pimu_p2 << "\t\t" << n_pimu_p2 << std::endl << std::endl;

  std::cout << "Period 3" << std::endl;
  std::cout << "\t\t1 GeV/c\t0.75 GeV/c\t0.5 GeV/c\t-0.75 GeV/c\tAll" << std::endl
  	    << "Proton\t\t" << n1GeV_proton_p3 << "\t" << n750MeV_proton_p3 << "\t\t"
	    << n500MeV_proton_p3 << "\t\t" << nneg750MeV_proton_p3 << "\t\t" << n_proton_p3 << std::endl
  	    << "Electron\t" << n1GeV_electron_p3 << "\t" << n750MeV_electron_p3 << "\t\t"
	    << n500MeV_electron_p3 << "\t\t" << nneg750MeV_electron_p3 << "\t\t" << n_electron_p3 << std::endl
  	    << "Kaon\t\t" << n1GeV_kaon_p3 << "\t" << n750MeV_kaon_p3 << "\t\t"
	    << n500MeV_kaon_p3 << "\t\t" << nneg750MeV_kaon_p3 << "\t\t" << n_kaon_p3 << std::endl
  	    << "Pi/Mu\t\t" << n1GeV_pimu_p3 << "\t" << n750MeV_pimu_p3 << "\t\t"
	    << n500MeV_pimu_p3 << "\t\t" << nneg750MeV_pimu_p3 << "\t\t" << n_pimu_p3 << std::endl << std::endl;

  std::cout << "DQ scaling (20% shut-off, 15% underfilled)" << std::endl << std::endl;

  std::cout << "Period 2" << std::endl;
  float p2_scaling = 0.8*0.85;
  std::cout << "\t\t1 GeV/c\t0.5 GeV/c\tAll" << std::endl
	    << "Proton\t\t" << n1GeV_proton_p2*p2_scaling << "\t" << n500MeV_proton_p2*p2_scaling << "\t\t" << n_proton_p2*p2_scaling << std::endl
	    << "Electron\t" << n1GeV_electron_p2*p2_scaling << "\t" << n500MeV_electron_p2*p2_scaling << "\t\t" << n_electron_p2*p2_scaling << std::endl
	    << "Kaon\t\t" << n1GeV_kaon_p2*p2_scaling << "\t" << n500MeV_kaon_p2*p2_scaling << "\t\t" << n_kaon_p2*p2_scaling << std::endl
	    << "Pi/Mu\t\t" << n1GeV_pimu_p2*p2_scaling << "\t" << n500MeV_pimu_p2*p2_scaling << "\t\t" << n_pimu_p2*p2_scaling << std::endl << std::endl;

  float p3_scaling_underfill = 0.8*0.85;
  float p3_scaling_overfill = 0.8;

  int n_proton_p3_underfill_scaled            = n_proton_p3_underfill*p3_scaling_underfill;
  int n_electron_p3_underfill_scaled          = n_electron_p3_underfill*p3_scaling_underfill;
  int n_kaon_p3_underfill_scaled              = n_kaon_p3_underfill*p3_scaling_underfill;
  int n_pimu_p3_underfill_scaled              = n_pimu_p3_underfill*p3_scaling_underfill;
  int n1GeV_proton_p3_underfill_scaled        = n1GeV_proton_p3_underfill*p3_scaling_underfill;
  int n1GeV_electron_p3_underfill_scaled      = n1GeV_electron_p3_underfill*p3_scaling_underfill;
  int n1GeV_kaon_p3_underfill_scaled          = n1GeV_kaon_p3_underfill*p3_scaling_underfill;
  int n1GeV_pimu_p3_underfill_scaled          = n1GeV_pimu_p3_underfill*p3_scaling_underfill;
  int n750MeV_proton_p3_underfill_scaled      = n750MeV_proton_p3_underfill*p3_scaling_underfill;
  int n750MeV_electron_p3_underfill_scaled    = n750MeV_electron_p3_underfill*p3_scaling_underfill;
  int n750MeV_kaon_p3_underfill_scaled        = n750MeV_kaon_p3_underfill*p3_scaling_underfill;
  int n750MeV_pimu_p3_underfill_scaled        = n750MeV_pimu_p3_underfill*p3_scaling_underfill;
  int nneg750MeV_proton_p3_underfill_scaled   = nneg750MeV_proton_p3_underfill*p3_scaling_underfill;
  int nneg750MeV_electron_p3_underfill_scaled = nneg750MeV_electron_p3_underfill*p3_scaling_underfill;
  int nneg750MeV_kaon_p3_underfill_scaled     = nneg750MeV_kaon_p3_underfill*p3_scaling_underfill;
  int nneg750MeV_pimu_p3_underfill_scaled     = nneg750MeV_pimu_p3_underfill*p3_scaling_underfill;
  int n500MeV_proton_p3_underfill_scaled      = n500MeV_proton_p3_underfill*p3_scaling_underfill;
  int n500MeV_electron_p3_underfill_scaled    = n500MeV_electron_p3_underfill*p3_scaling_underfill;
  int n500MeV_kaon_p3_underfill_scaled        = n500MeV_kaon_p3_underfill*p3_scaling_underfill;
  int n500MeV_pimu_p3_underfill_scaled        = n500MeV_pimu_p3_underfill*p3_scaling_underfill;

  int n_proton_p3_overfill_scaled            = p3_scaling_overfill*(n_proton_p3-n_proton_p3_underfill);
  int n_electron_p3_overfill_scaled          = p3_scaling_overfill*(n_electron_p3-n_electron_p3_underfill);
  int n_kaon_p3_overfill_scaled              = p3_scaling_overfill*(n_kaon_p3-n_kaon_p3_underfill);
  int n_pimu_p3_overfill_scaled              = p3_scaling_overfill*(n_pimu_p3-n_pimu_p3_underfill);
  int n1GeV_proton_p3_overfill_scaled        = p3_scaling_overfill*(n1GeV_proton_p3-n1GeV_proton_p3_underfill);
  int n1GeV_electron_p3_overfill_scaled      = p3_scaling_overfill*(n1GeV_electron_p3-n1GeV_electron_p3_underfill);
  int n1GeV_kaon_p3_overfill_scaled          = p3_scaling_overfill*(n1GeV_kaon_p3-n1GeV_kaon_p3_underfill);
  int n1GeV_pimu_p3_overfill_scaled          = p3_scaling_overfill*(n1GeV_pimu_p3-n1GeV_pimu_p3_underfill);
  int n750MeV_proton_p3_overfill_scaled      = p3_scaling_overfill*(n750MeV_proton_p3-n750MeV_proton_p3_underfill);
  int n750MeV_electron_p3_overfill_scaled    = p3_scaling_overfill*(n750MeV_electron_p3-n750MeV_electron_p3_underfill);
  int n750MeV_kaon_p3_overfill_scaled        = p3_scaling_overfill*(n750MeV_kaon_p3-n750MeV_kaon_p3_underfill);
  int n750MeV_pimu_p3_overfill_scaled        = p3_scaling_overfill*(n750MeV_pimu_p3-n750MeV_pimu_p3_underfill);
  int nneg750MeV_proton_p3_overfill_scaled   = p3_scaling_overfill*(nneg750MeV_proton_p3-nneg750MeV_proton_p3_underfill);
  int nneg750MeV_electron_p3_overfill_scaled = p3_scaling_overfill*(nneg750MeV_electron_p3-nneg750MeV_electron_p3_underfill);
  int nneg750MeV_kaon_p3_overfill_scaled     = p3_scaling_overfill*(nneg750MeV_kaon_p3-nneg750MeV_kaon_p3_underfill);
  int nneg750MeV_pimu_p3_overfill_scaled     = p3_scaling_overfill*(nneg750MeV_pimu_p3-nneg750MeV_pimu_p3_underfill);
  int n500MeV_proton_p3_overfill_scaled      = p3_scaling_overfill*(n500MeV_proton_p3-n500MeV_proton_p3_underfill);
  int n500MeV_electron_p3_overfill_scaled    = p3_scaling_overfill*(n500MeV_electron_p3-n500MeV_electron_p3_underfill);
  int n500MeV_kaon_p3_overfill_scaled        = p3_scaling_overfill*(n500MeV_kaon_p3-n500MeV_kaon_p3_underfill);
  int n500MeV_pimu_p3_overfill_scaled        = p3_scaling_overfill*(n500MeV_pimu_p3-n500MeV_pimu_p3_underfill);

  std::cout << "Period 3" << std::endl;
  std::cout << "\t\t1 GeV/c\t0.75 GeV/c\t0.5 GeV/c\t-0.75 GeV/cAll" << std::endl
	    << "Proton\t\t" << n1GeV_proton_p3_underfill_scaled+n1GeV_proton_p3_overfill_scaled
	    << "\t" << n750MeV_proton_p3_underfill_scaled+n750MeV_proton_p3_overfill_scaled
	    << "\t\t" << n500MeV_proton_p3_underfill_scaled+n500MeV_proton_p3_overfill_scaled
	    << "\t\t" << nneg750MeV_proton_p3_underfill_scaled+nneg750MeV_proton_p3_overfill_scaled
	    << "\t\t" << n_proton_p3_underfill_scaled+n_proton_p3_overfill_scaled << std::endl
	    << "Electron\t" << n1GeV_electron_p3_underfill_scaled+n1GeV_electron_p3_overfill_scaled
	    << "\t" << n750MeV_electron_p3_underfill_scaled+n750MeV_electron_p3_overfill_scaled
	    << "\t\t" << n500MeV_electron_p3_underfill_scaled+n500MeV_electron_p3_overfill_scaled
	    << "\t\t" << nneg750MeV_electron_p3_underfill_scaled+nneg750MeV_electron_p3_overfill_scaled
	    << "\t\t" << n_electron_p3_underfill_scaled+n_electron_p3_overfill_scaled << std::endl
	    << "Kaon\t\t" << n1GeV_kaon_p3_underfill_scaled+n1GeV_kaon_p3_overfill_scaled
	    << "\t" << n750MeV_kaon_p3_underfill_scaled+n750MeV_kaon_p3_overfill_scaled
	    << "\t\t" << n500MeV_kaon_p3_underfill_scaled+n500MeV_kaon_p3_overfill_scaled
	    << "\t\t" << nneg750MeV_kaon_p3_underfill_scaled+nneg750MeV_kaon_p3_overfill_scaled
	    << "\t\t" << n_kaon_p3_underfill_scaled+n_kaon_p3_overfill_scaled << std::endl
	    << "Pi/Mu\t\t" << n1GeV_pimu_p3_underfill_scaled+n1GeV_pimu_p3_overfill_scaled
	    << "\t" << n750MeV_pimu_p3_underfill_scaled+n750MeV_pimu_p3_overfill_scaled
	    << "\t\t" << n500MeV_pimu_p3_underfill_scaled+n500MeV_pimu_p3_overfill_scaled
	    << "\t\t" << nneg750MeV_pimu_p3_underfill_scaled+nneg750MeV_pimu_p3_overfill_scaled
	    << "\t\t" << n_pimu_p3_underfill_scaled+n_pimu_p3_overfill_scaled << std::endl << std::endl;

}
