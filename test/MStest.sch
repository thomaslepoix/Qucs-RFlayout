<Qucs Schematic 0.0.19>
<Properties>
  <View=0,-144,1574,1119,1,26,420>
  <Grid=10,10,1>
  <DataSet=MStest.dat>
  <DataDisplay=MStest.dpl>
  <OpenDisplay=1>
  <Script=MStest.m>
  <RunScript=0>
  <showFrame=0>
  <FrameText0=Titre>
  <FrameText1=Auteur :>
  <FrameText2=Date :>
  <FrameText3=Version :>
</Properties>
<Symbol>
</Symbol>
<Components>
  <SUBST Subst1 1 160 630 -30 24 0 0 "9.8" 1 "1 mm" 1 "35 um" 1 "2e-4" 1 "0.022e-6" 1 "0.15e-6" 1>
  <Pac P1 1 140 260 18 -26 0 1 "1" 1 "50 Ohm" 1 "0 dBm" 0 "1 GHz" 0 "26.85" 0>
  <GND * 1 140 290 0 0 0 0>
  <MLIN MS1 1 210 150 -26 15 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MSTEP MS3 1 320 150 -26 17 0 0 "Subst1" 1 "1 mm" 1 "2 mm" 1 "Hammerstad" 0 "Kirschning" 0>
  <MLIN MS2 1 430 150 -26 15 0 0 "Subst1" 1 "2 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MLIN MS7 1 550 240 15 -26 0 1 "Subst1" 1 "4 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MLIN MS6 1 710 150 -26 15 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <Pac P2 1 820 210 18 -26 0 1 "2" 1 "50 Ohm" 1 "0 dBm" 0 "1 GHz" 0 "26.85" 0>
  <GND * 1 820 260 0 0 0 0>
  <MLIN MS10 1 820 50 15 -26 0 1 "Subst1" 1 "2 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MLIN MS9 1 950 150 -26 15 0 0 "Subst1" 1 "2 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MCORN MS13 1 820 -40 -7 -84 0 1 "Subst1" 1 "2 mm" 1>
  <MCORN MS15 1 1050 150 -26 15 0 3 "Subst1" 1 "2 mm" 1>
  <MCORN MS14 1 1050 -40 15 -7 0 0 "Subst1" 1 "2 mm" 1>
  <MLIN MS16 1 970 -40 -26 15 0 0 "Subst1" 1 "2 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MLIN MS17 1 1050 70 15 -26 0 1 "Subst1" 1 "2 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MTEE MS4 1 550 150 -26 -130 0 0 "Subst1" 1 "2 mm" 1 "1 mm" 1 "4 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0 "showNumbers" 0>
  <MCROSS MS5 1 820 150 -146 -167 0 0 "Subst1" 1 "1 mm" 1 "2 mm" 1 "2 mm" 1 "1 mm" 1 "Hammerstad" 0 "Kirschning" 0 "showNumbers" 0>
  <MCROSS MS18 1 550 350 -148 143 0 0 "Subst1" 1 "1 mm" 1 "4 mm" 1 "1 mm" 1 "2 mm" 1 "Hammerstad" 0 "Kirschning" 0 "showNumbers" 0>
  <MOPEN MS12 1 760 350 -26 15 0 0 "Subst1" 1 "1 mm" 1 "Hammerstad" 0 "Kirschning" 0 "Kirschning" 0>
  <MOPEN MS21 1 380 350 -12 -84 0 2 "Subst1" 1 "1 mm" 1 "Hammerstad" 0 "Kirschning" 0 "Kirschning" 0>
  <MRSTUB MS22 1 550 490 -26 46 1 0 "Subst1" 1 "1 mm" 0 "10 mm" 1 "90" 1>
  <MLIN MS19 1 660 350 -26 15 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MLIN MS20 1 460 350 -26 15 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MLIN MS25 1 850 540 -26 15 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MRSTUB MS26 1 760 540 -58 25 0 1 "Subst1" 1 "1 mm" 0 "10 mm" 1 "90" 1>
  <MMBEND MS28 1 960 540 15 -7 0 0 "Subst1" 1 "1 mm" 1>
  <MMBEND MS29 1 960 760 -115 -26 0 2 "Subst1" 1 "1 mm" 1>
  <MLIN MS24 1 1070 760 -26 15 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MLIN MS23 1 960 650 15 -26 0 1 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MMBEND MS35 1 1180 760 -26 15 0 3 "Subst1" 1 "1 mm" 1>
  <MLIN MS33 1 1180 650 15 -26 0 1 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MMBEND MS36 1 1180 540 -115 -7 1 2 "Subst1" 1 "1 mm" 1>
  <MLIN MS31 1 1290 540 -26 15 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MRSTUB MS32 1 1380 540 -38 -117 0 3 "Subst1" 1 "1 mm" 0 "10 mm" 1 "90" 1>
  <MMBEND MS37 1 490 840 15 -7 0 0 "Subst1" 1 "1 mm" 1>
  <MMBEND MS41 1 820 880 -115 -7 1 2 "Subst1" 1 "1 mm" 1>
  <MMBEND MS40 1 490 900 -26 15 0 3 "Subst1" 1 "1 mm" 1>
  <MMBEND MS39 1 430 900 -115 -26 0 2 "Subst1" 1 "1 mm" 1>
  <MMBEND MS38 1 430 840 -7 -84 0 1 "Subst1" 1 "1 mm" 1>
  <MMBEND MS42 1 880 880 -26 -84 1 1 "Subst1" 1 "1 mm" 1>
  <MMBEND MS43 1 820 940 -7 15 1 3 "Subst1" 1 "1 mm" 1>
  <MMBEND MS44 1 880 940 15 -26 1 0 "Subst1" 1 "1 mm" 1>
</Components>
<Wires>
  <140 150 140 230 "" 0 0 0 "">
  <140 150 180 150 "" 0 0 0 "">
  <240 150 290 150 "" 0 0 0 "">
  <350 150 400 150 "" 0 0 0 "">
  <460 150 520 150 "" 0 0 0 "">
  <550 180 550 210 "" 0 0 0 "">
  <580 150 680 150 "" 0 0 0 "">
  <740 150 790 150 "" 0 0 0 "">
  <820 240 820 260 "" 0 0 0 "">
  <820 80 820 120 "" 0 0 0 "">
  <850 150 920 150 "" 0 0 0 "">
  <820 -10 820 20 "" 0 0 0 "">
  <980 150 1020 150 "" 0 0 0 "">
  <1000 -40 1020 -40 "" 0 0 0 "">
  <850 -40 940 -40 "" 0 0 0 "">
  <1050 -10 1050 40 "" 0 0 0 "">
  <1050 100 1050 120 "" 0 0 0 "">
  <550 270 550 320 "" 0 0 0 "">
  <550 380 550 480 "" 0 0 0 "">
  <690 350 730 350 "" 0 0 0 "">
  <580 350 630 350 "" 0 0 0 "">
  <490 350 520 350 "" 0 0 0 "">
  <410 350 430 350 "" 0 0 0 "">
  <770 540 820 540 "" 0 0 0 "">
  <880 540 930 540 "" 0 0 0 "">
  <990 760 1040 760 "" 0 0 0 "">
  <960 570 960 620 "" 0 0 0 "">
  <960 680 960 730 "" 0 0 0 "">
  <1100 760 1150 760 "" 0 0 0 "">
  <1180 680 1180 730 "" 0 0 0 "">
  <1180 570 1180 620 "" 0 0 0 "">
  <1210 540 1260 540 "" 0 0 0 "">
  <1320 540 1370 540 "" 0 0 0 "">
</Wires>
<Diagrams>
</Diagrams>
<Paintings>
</Paintings>
