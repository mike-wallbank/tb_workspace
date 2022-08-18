{
TCut wcX("wcmom>=0");
TCut tofc("toftime>=30");
TCut tofX("toftime>=0");
TCut magdist("abs(wcMagDist)<5");
TCut blcuts(wcX&&tofX&&magdist);
TCut nhit("prongNhit>5");
TCut centralVtx("abs(prongStrtX)<20&&prongStrtY>-25&&prongStrtY<15&&prongStrtZ<18");
TCut hittime("prongMinTime>45000&&prongMinTime<55000");
TCut detcuts(centralVtx&&hittime&&nhit);
TCut selection(blcuts&&detcuts);

TCut electrontof("toftime>30&&toftime<36");
TCut protontof("(mc7mag>900&&mc7mag<1100&&toftime>39&&toftime<50)||(mc7mag>650&&mc7mag<850&&toftime>42&&toftime<60)||(mc7mag>400&&mc7mag<600&&toftime>56&&toftime<80)");
TCut kaontof("(mc7mag>900&&mc7mag<1100&&toftime>34&&toftime<39)||(mc7mag>650&&mc7mag<850&&toftime>36&&toftime<42)||(mc7mag>400&&mc7mag<600&&toftime>40&&toftime<56)");
TCut pimutof("(mc7mag>900&&mc7mag<1100&&toftime>30&&toftime<34)||(mc7mag>650&&mc7mag<850&&toftime>30&&toftime<36)||(mc7mag>400&&mc7mag<600&&toftime>30&&toftime<40)");

TCut electron(selection&&electrontof&&"ckovadc>0");
TCut proton(selection&&protontof&&"ckovadc<0");
//TCut deuteron(selection&&"ckovadc<0&&toftime>70&&(run<100827||toftime>120)");                                                                          
TCut kaon(selection&&kaontof&&"ckovadc<0");
TCut pimu(selection&&pimutof&&"ckovadc<0");

TCut particle(electron||proton||kaon||pimu);//deuteron);
}
