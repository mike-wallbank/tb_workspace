// execute as >> root 'drawSpillCounters.C("<file>.root")'

#include "MCenterDeviceMgr.h"
#include <string>

void drawSpillCounters(std::string inFileName) {

  MCenterDeviceMgr mgr(inFileName, "spillana/spills");
  //MCenterDeviceMgr mgr(inFileName, "spills");
  mgr.SetOutputDir("plots/");

  //mgr.SetStartTime(2021, 03, 03, 20, 00, 00);
  mgr.SetStartTime(2021, 06, 12, 00, 00, 00);
  mgr.SetEndTime(2021, 06, 26, 00, 00, 00);

  // arguments: device name (from tree), axis label, min, max, num spills/bin, option - average over total spills, plot note, option - display integral
  mgr.AddDevice("FTSDF", "FTSDF", 0, 100, 5, true);
  // mgr.AddDevice("S230MH", "S230MH");
  // mgr.AddDevice("S230MV", "S230MV");
  // mgr.AddDevice("S230SH", "S230SH");
  // mgr.AddDevice("S230SV", "S230SV");
  mgr.AddDevice("SM01HI", "SM01HI");
  mgr.AddDevice("SM01HM", "SM01HM", -10, 20, 2, true);
  mgr.AddDevice("SM01HS", "SM01HS");
  mgr.AddDevice("SM01VI", "SM01VI", 0, 2e5, 2, true);
  mgr.AddDevice("SM01VM", "SM01VM", -10, 20, 2, true);
  mgr.AddDevice("SM01VS", "SM01VS");
  mgr.AddDevice("SM11HI", "SM11HI");
  mgr.AddDevice("SM11HM", "SM11HM", -10, 10, 2, true);
  mgr.AddDevice("SM11HS", "SM11HS");
  mgr.AddDevice("SM11VI", "SM11VI", 0, 8e4, 2, true);
  mgr.AddDevice("SM11VM", "SM11VM", -10, 50, 2, true);
  mgr.AddDevice("SM11VS", "SM11VS");
  mgr.AddDevice("MC1SEM", "MC1SEM", 0, 3e11);
  mgr.AddDevice("SMC1HI", "SMC1HI", 0, 20, 2, true);
  mgr.AddDevice("SMC1HM", "SMC1HM", -5, 5, 2, true);
  mgr.AddDevice("SMC1HS", "SMC1HS", 0, 20, 2, true);
  mgr.AddDevice("SMC1VI", "SMC1VI", 0, 20, 2, true);
  mgr.AddDevice("SMC1VM", "SMC1VM", -5, 20, 2, true);
  mgr.AddDevice("SMC1VS", "SMC1VS", 0, 20, 2, true);
  mgr.AddDevice("MC1D", "MC1D", 0, 200, 5, true);
  mgr.AddDevice("MC2H", "MC2H", 0, 10, 5, true);
  mgr.AddDevice("MC2V", "MC2V", 0, 5, 5, true);
  mgr.AddDevice("MC2Q1", "MC2Q1", 0, 10, 5, true);
  mgr.AddDevice("MC2Q2", "MC2Q2", 0, 10, 5, true);
  mgr.AddDevice("MC2WCHM", "#splitline{MC2WC}{HM}", -10, 10, 2, true);
  mgr.AddDevice("MC2WCVM", "#splitline{MC2WC}{VM}", -10, 10, 2, true);
  mgr.AddDevice("MC2WCHS", "#splitline{MC2WC}{HS}", 0, 20, 2, true);
  mgr.AddDevice("MC2WCVS", "#splitline{MC2WC}{VS}", 0, 20, 2, true);
  mgr.AddDevice("MC2WCHI", "#splitline{MC2WC}{HI}", 0, 20, 2, true);
  mgr.AddDevice("MC2WCVI", "#splitline{MC2WC}{VI}", 0, 20, 2, true);
  mgr.AddDevice("MC3CV", "MC3CV", 0, 50, 5, true);
  mgr.AddDevice("MC3CH", "MC3CH", 0, 20, 5, true);
  mgr.AddDevice("MC4WCHM", "#splitline{MC4WC}{HM}", -5, 20, 2, true);
  mgr.AddDevice("MC4WCVM", "#splitline{MC4WC}{VM}", -5, 20, 2, true);
  mgr.AddDevice("MC4WCHS", "#splitline{MC4WC}{HS}", -5, 20, 2, true);
  mgr.AddDevice("MC4WCVS", "#splitline{MC4WC}{VS}", -5, 20, 2, true);
  mgr.AddDevice("MC4WCHI", "#splitline{MC4WC}{HI}", -5, 1e5, 2, true);
  mgr.AddDevice("MC4WCVI", "#splitline{MC4WC}{VI}", -5, 1e5, 2, true);
  mgr.AddDevice("MC5H1", "MC5H1", 0, 30, 5, true);
  mgr.AddDevice("MC5V1", "MC5V1", 0, 30, 5, true);
  mgr.AddDevice("MC5Q1", "MC5Q1", 0, 150, 5, true);
  mgr.AddDevice("MC5Q2", "MC5Q2", 0, 150, 5, true);
  mgr.AddDevice("MC5WCHM", "#splitline{MC5WC}{HM}", -5, 20, 2, true);
  mgr.AddDevice("MC5WCVM", "#splitline{MC5WC}{VM}", -10, 20, 2, true);
  mgr.AddDevice("MC5WCHS", "#splitline{MC5WC}{HS}", 0, 20, 2, true);
  mgr.AddDevice("MC5WCVS", "#splitline{MC5WC}{VS}", 0, 20, 2, true);
  mgr.AddDevice("MC5WCHI", "#splitline{MC5WC}{HI}", 0, 1e5, 2, true);
  mgr.AddDevice("MC5WCVI", "#splitline{MC5WC}{VI}", 0, 1e5, 2, true);
  mgr.AddDevice("MC6IC", "MC6IC", 0, 7e9); //7e9
  mgr.AddDevice("MC6WC1HM", "#splitline{MC6WC1}{HM}", -40, 30, 2, true);
  mgr.AddDevice("MC6WC1VM", "#splitline{MC6WC1}{VM}", -50, 20, 2, true);
  mgr.AddDevice("MC6WC1HS", "#splitline{MC6WC1}{HS}", 0, 40, 2, true);
  mgr.AddDevice("MC6WC1VS", "#splitline{MC6WC1}{VS}", 0, 20, 2, true);
  mgr.AddDevice("MC6WC1HI", "#splitline{MC6WC1}{HI}", 0, 1e6, 2, true);
  mgr.AddDevice("MC6WC1VI", "#splitline{MC6WC1}{VI}", 0, 1e6, 2, true);
  mgr.AddDevice("MC6SC", "MC6SC", 0, 5e6);
  mgr.AddDevice("MC6Col", "MC6Col", 0, 20, 5, true);
  mgr.AddDevice("MC6D", "MC6D", 0, 200, 5, true);
  mgr.AddDevice("MC6H1", "MC6H1", 0, 100, 5, true);
  mgr.AddDevice("MC6H2", "MC6H2", 0, 100, 5, true);
  mgr.AddDevice("MC6V1", "MC6V1", 0, 100, 5, true);
  mgr.AddDevice("MC6V2", "MC6V2", 0, 100, 5, true);
  mgr.AddDevice("MC6Q1", "MC6Q1", 0, 50, 5, true);
  mgr.AddDevice("MC6Q2", "MC6Q2", 0, 1000, 5, true);
  mgr.AddDevice("MC6Q3", "MC6Q3", 0, 100, 5, true);
  mgr.AddDevice("MC6Q4", "MC6Q4", 0, 100, 5, true);
  mgr.AddDevice("MC6Q5", "MC6Q5", 0, 200, 5, true);
  mgr.AddDevice("MC6Q6", "MC6Q6", 0, 200, 5, true);
  mgr.AddDevice("MC7SC1", "MC7SC1", 0, 2e6);
  mgr.AddDevice("MC7WC1HM", "#splitline{MC7WC1}{HM}", -5, 5, 2, true);
  mgr.AddDevice("MC7WC1VM", "#splitline{MC7WC1}{VM}", -5, 5, 2, true);
  mgr.AddDevice("MC7WC1HS", "#splitline{MC7WC1}{HS}", 0, 20, 2, true);
  mgr.AddDevice("MC7WC1VS", "#splitline{MC7WC1}{VS}", 0, 20, 2, true);
  mgr.AddDevice("MC7WC1HI", "#splitline{MC7WC1}{HI}", 0, 1e5, 2, true);
  mgr.AddDevice("MC7WC1VI", "#splitline{MC7WC1}{VI}", 0, 1e5, 2, true);
  mgr.AddDevice("MC7WC2HM", "#splitline{MC7WC2}{HM}", -5, 5, 2, true);
  mgr.AddDevice("MC7WC2VM", "#splitline{MC7WC2}{VM}", -5, 5, 2, true);
  mgr.AddDevice("MC7WC2HS", "#splitline{MC7WC2}{HS}", 0, 20, 2, true);
  mgr.AddDevice("MC7WC2VS", "#splitline{MC7WC2}{VS}", 0, 20, 2, true);
  mgr.AddDevice("MC7WC2HI", "#splitline{MC7WC2}{HI}", 0, 1e5, 2, true);
  mgr.AddDevice("MC7WC2VI", "#splitline{MC7WC2}{VI}", 0, 1e5, 2, true);
  mgr.AddDevice("MC7Target", "MC7Tgt", 0, 4e5);
  mgr.AddDevice("MC7SC2", "MC7SC2", 0, 1e5);//1e6
  mgr.AddDevice("MC7Target90Deg", "Tgt90Deg", 0, 1e3);//1e4
  mgr.AddDevice("MC7ShieldBlock", "MC7Shield", 0, 3e4);//3e5
  mgr.AddDevice("MC7D", "MC7D", 0, 2000);
  mgr.AddDevice("MC7Trig", "Triggers", 0, 10, 1, false, "All triggers", true);
  mgr.AddDevice("DetFace1", "Top-West", 0, 1800);//18000);
  mgr.AddDevice("DetFace2", "Bot-West", 0, 1800);//14000);
  mgr.AddDevice("DetFace3", "Top-East", 0, 1800);//10000);
  mgr.AddDevice("DetFace4", "Bot-East", 0, 1800);//7000);
  mgr.AddDevice("DAQGood", "DAQ Good", 0, 1, 60, true);
  mgr.AddDevice("TrigDetOnBit", "Triggers", 0, 1e3, 60, false, "Triggers with detector fully on (shut-off bit)", true);
  mgr.AddDevice("TrigDetOnHits", "Triggers", 0, 1e3, 60, false, "Triggers with detector fully on (hit method)", true);
  mgr.AddDevice("TrigSel", "Particles", 0, 40, 60, false, "Triggers passing particle selection", true);
  mgr.AddDevice("TrigSelDetOnBit", "Particles", 0, 40, 60, false, "Triggers with detector fully on (shut-off bit) passing particle selection", true);
  mgr.AddDevice("TrigSelDetOnHits", "Particles", 0, 40, 60, false, "Triggers with detector fully on (hit method) passing particle selection", true);
  mgr.AddDevice("ProtonSelDetOnBit", "Protons", 0, 10, 60, false);
  mgr.AddDevice("ElectronSelDetOnBit", "Electrons", 0, 10, 60, false);
  mgr.AddDevice("KaonSelDetOnBit", "Kaons", 0, 10, 60, false);
  mgr.AddDevice("MuPiOtherSelDetOnBit", "Pi/Mu", 0, 40, 60, false);

  // arguments: ratio name, device1, device2, axis label, min, max, plot note, number of spills/bin
  // mgr.AddDeviceRatio("MC7SC2/DetFace1", "MC7SC2", "DetFace1", "#splitline{MC7SC2/}{Top-West}", 0, 0.5, "On-axis/Off-axis (F:MC7SC2/Z:NOVTSC16^2)");
  mgr.AddDeviceRatio("MC7SC2/DetFace1", "MC7SC2", "DetFace1", "#splitline{MC7SC2/}{Top-West}", 0, 200, "On-axis/Off-axis (F:MC7SC2/Z:NOVTSC16)");
  mgr.AddDeviceRatio("MC7SC2/DetFace2", "MC7SC2", "DetFace2", "#splitline{MC7SC2/}{Bot-West}", 0, 250, "On-axis/Off-axis (F:MC7SC2/Z:NOVTSC17)");
  mgr.AddDeviceRatio("MC7SC2/DetFace3", "MC7SC2", "DetFace3", "#splitline{MC7SC2/}{Top-East}", 0, 300, "On-axis/Off-axis (F:MC7SC2/Z:NOVTSC18)");
  mgr.AddDeviceRatio("MC7SC2/DetFace4", "MC7SC2", "DetFace4", "#splitline{MC7SC2/}{Bot-East}", 0, 450, "On-axis/Off-axis (F:MC7SC2/Z:NOVTSC19)");
  mgr.AddDeviceRatio("TrigSel/MC6IC", "TrigSel", "MC6IC", "Trig/MC6IC", 0, 2e-8);

  mgr.AddDeviceFromFile("MW1SEM", "/nova/ana/users/wallbank/TestBeam/BackFill/data/MW1SEM_Data.txt", "MW1SEM", 0, 1e12);
  mgr.AddDeviceFromFile("F1SEM", "/nova/ana/users/wallbank/TestBeam/BackFill/data/F1SEM_Data.txt", "F1SEM", 0, 2e12);

  mgr.FillPlots();

  // arguments: name, vector of devices
  // mgr.DrawPlots("SpillCounters_MTest",
  // 		{"F1SEM", "MW1SEM", "MC1SEM", "MC6IC", "MC7SC2", "MC7Trig", "TrigSel"});
  // mgr.DrawPlots("SpillCounters_US",
  // 		{"FTSDF", "SM01HM", "SM01VM", "SM01VI", "SM11HM", "SM11VM", "SM11VI", "MC7Trig", "TrigSel"});
  // mgr.DrawPlots("SpillCounters_MC1",
  // 		{"MC1SEM", "SMC1HM", "SMC1HS", "SMC1VM", "SMC1VS", "MC1D", "MC7Trig", "TrigSel"});
  // mgr.DrawPlots("SpillCounters_MC2_Steer",
  // 		{"MC1SEM", "MC2H", "MC2V", "MC2Q1", "MC2Q2", "MC7Trig", "TrigSel"});
  // mgr.DrawPlots("SpillCounters_MC2_Monitor",
  // 		{"MC1SEM", "MC2WCHM", "MC2WCHS", "MC2WCVM", "MC2WCVS", "MC7Trig", "TrigSel"});
  // mgr.DrawPlots("SpillCounters_MC3&4",
  // 		{"MC1SEM", "MC3CV", "MC3CH", "MC4WCHM", "MC4WCHS", "MC4WCVM", "MC4WCVS", "MC7Trig", "TrigSel"});
  // mgr.DrawPlots("SpillCounters_MC5_Steer",
  // 		{"MC1SEM", "MC5H1", "MC5V1", "MC5Q1", "MC5Q2", "MC7Trig", "TrigSel"});
  // mgr.DrawPlots("SpillCounters_MC5_Monitor",
  // 		{"MC1SEM", "MC5WCHM", "MC5WCHS", "MC5WCVM", "MC5WCVS", "MC7Trig", "TrigSel"});
  // mgr.DrawPlots("SpillCounters_MC6_Focus",
  // 		{"MC1SEM", "MC6IC", "MC6Q1", "MC6Q2", "MC6Q3", "MC6Q4", "MC7Trig", "TrigSel"});
  // mgr.DrawPlots("SpillCounters_MC6_Steer",
  // 		{"MC1SEM", "MC6IC", "MC6D", "MC6H1", "MC6V1", "MC6Col", "MC6H2", "MC6V2", "MC7Trig", "TrigSel"});
  // mgr.DrawPlots("SpillCounters_MC6_Monitor",
  // 		{"MC1SEM", "MC6IC", "MC6SC", "MC6WC1HM", "MC6WC1HS", "MC6WC1HI", "MC6WC1VM", "MC6WC1VS", "MC6WC1VI", "MC7Trig", "TrigSel"});
  // mgr.DrawPlots("SpillCounters_MC7a",
  // 		{"MC6IC", "MC7SC1", "MC7WC1HM", "MC7WC1HS", "MC7WC1VM", "MC7WC1VS", "MC7WC2HM", "MC7WC2HS", "MC7WC2VM", "MC7WC2VS", "MC7SC2", "MC7Target"});
  // mgr.DrawPlots("SpillCounters_Secondary",
  // 		{"MC6IC", "MC6SC", "MC7SC1", "MC7SC2", "MC7Trig", "TrigSel"});
  // mgr.DrawPlots("SpillCounters_MC7b",
  // 		{"MC6IC", "MC7Target", "MC7Target90Deg", "MC7ShieldBlock", "DetFace1", "DetFace2", "DetFace3", "DetFace4", "TrigSel"});
  // mgr.DrawPlots("SpillCounters_Trigger",
  // 		{"MC6IC", "MC6Col", "MC7Target", "DAQGood", "MC7Trig", "TrigSel", "TrigSelDetOnBit", "TrigSelDetOnHits"});
  // mgr.DrawPlots("SpillCounters_TrigShutOffs",
  // 		{"MC6IC", "MC6SC", "MC7SC2", "MC7Trig", "DetFace1", "MC7SC2/DetFace1", "TrigSel"});
  // mgr.DrawPlots("SpillCounters_Counters",
  // 		{"MC1SEM", "MC6IC", "MC6SC", "MC7SC1", "MC7Target", "DetFace1", "MC7Trig", "TrigSel"});
  mgr.DrawPlots("SpillCounters_Backgrounds",
  		{"MC6IC", "MC7Target", "MC7Target90Deg", "MC7ShieldBlock", "DetFace1", "MC7Trig", "TrigSel", "TrigSelDetOnBit"});
  // mgr.DrawPlots("SpillCounters_Particles",
  // 		{"MC6IC", "DAQGood", "TrigSelDetOnBit", "ProtonSelDetOnBit", "ElectronSelDetOnBit", "KaonSelDetOnBit", "MuPiOtherSelDetOnBit"});
  // mgr.DrawPlots("SpillCounters_DetFace",
  // 		{"MC6IC", "MC7SC2", "MC7Trig", "MC7SC2/DetFace1", "MC7SC2/DetFace2", "MC7SC2/DetFace3", "MC7SC2/DetFace4", "TrigSel"});

}
