<Qucs Schematic 0.0.19>
<Properties>
  <View=126,28,2045,937,0.80667,0,0>
  <Grid=10,10,1>
  <DataSet=MStest2.dat>
  <DataDisplay=MStest2.dpl>
  <OpenDisplay=1>
  <Script=MStest2.m>
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
  <MLIN MS25 1 340 130 -26 15 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MRSTUB MS26 1 250 130 -58 25 0 1 "Subst1" 1 "1 mm" 0 "10 mm" 1 "130" 1>
  <MMBEND MS27 1 450 130 15 -7 0 0 "Subst1" 1 "1 mm" 1>
  <MMBEND MS28 1 450 350 -115 -33 0 2 "Subst1" 1 "1 mm" 1>
  <MLIN MS30 1 450 240 15 -26 0 1 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MMBEND MS31 1 670 350 20 -35 0 3 "Subst1" 1 "1 mm" 1>
  <MLIN MS32 1 670 240 15 -26 0 1 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MMBEND MS33 1 670 130 -102 -62 1 2 "Subst1" 1 "1 mm" 1>
  <MLIN MS34 1 780 130 -26 15 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MRSTUB MS35 1 870 130 1 46 0 3 "Subst1" 1 "1 mm" 0 "10 mm" 1 "60" 1>
  <MCOUPLED MS36 1 560 380 -26 37 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "1 mm" 1 "Kirschning" 0 "Kirschning" 0 "26.85" 0>
  <MGAP MS37 1 450 410 -26 15 0 0 "Subst1" 1 "1 mm" 1 "1 mm" 1 "1 mm" 1 "Hammerstad" 0 "Kirschning" 0>
  <MGAP MS38 1 670 410 -26 15 0 0 "Subst1" 1 "1 mm" 1 "1 mm" 1 "1 mm" 1 "Hammerstad" 0 "Kirschning" 0>
  <MCOUPLED MS40 1 780 440 -26 37 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "1 mm" 1 "Kirschning" 0 "Kirschning" 0 "26.85" 0>
  <MCOUPLED MS39 1 340 440 -26 37 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "1 mm" 1 "Kirschning" 0 "Kirschning" 0 "26.85" 0>
  <GND * 1 860 470 0 0 0 0>
  <GND * 1 860 410 0 0 0 0>
  <GND * 1 260 470 0 0 0 0>
  <Pac P2 1 260 440 -94 -26 1 1 "2" 1 "50 Ohm" 1 "0 dBm" 0 "1 GHz" 0 "26.85" 0>
  <Pac P1 1 980 530 18 -26 0 1 "1" 1 "50 Ohm" 1 "0 dBm" 0 "1 GHz" 0 "26.85" 0>
  <GND * 1 980 560 0 0 0 0>
  <MLIN MS1 1 1050 420 -26 15 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MSTEP MS2 1 1160 420 -26 17 0 0 "Subst1" 1 "1 mm" 1 "2 mm" 1 "Hammerstad" 0 "Kirschning" 0>
  <MLIN MS3 1 1270 420 -26 15 0 0 "Subst1" 1 "2 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MLIN MS6 1 1660 320 15 -26 0 1 "Subst1" 1 "2 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MLIN MS7 1 1790 420 -13 -116 0 0 "Subst1" 1 "2 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MCORN MS8 1 1660 230 -42 -84 0 1 "Subst1" 1 "2 mm" 1>
  <MCORN MS9 1 1890 420 -26 15 0 3 "Subst1" 1 "2 mm" 1>
  <MLIN MS12 1 1890 340 15 -26 0 1 "Subst1" 1 "2 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MTEE MS13 1 1390 420 -26 -130 0 0 "Subst1" 1 "2 mm" 1 "1 mm" 1 "4 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0 "showNumbers" 0>
  <MCROSS MS14 1 1660 420 -146 -167 0 0 "Subst1" 1 "1 mm" 1 "2 mm" 1 "2 mm" 1 "1 mm" 1 "Hammerstad" 0 "Kirschning" 0 "showNumbers" 0>
  <MRSTUB MS18 1 1390 760 -26 46 1 0 "Subst1" 1 "1 mm" 0 "10 mm" 1 "90" 1>
  <MLIN MS4 1 1390 530 15 -26 0 1 "Subst1" 1 "4 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MCROSS MS15 1 1390 640 -114 21 1 2 "Subst1" 1 "1 mm" 1 "4 mm" 1 "1 mm" 1 "2 mm" 1 "Hammerstad" 0 "Kirschning" 0 "showNumbers" 0>
  <MLIN MS19 1 1500 640 -26 15 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MOPEN MS16 1 1600 640 -26 15 0 0 "Subst1" 1 "1 mm" 1 "Hammerstad" 0 "Kirschning" 0 "Kirschning" 0>
  <MLIN MS20 1 1300 640 -34 -103 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MOPEN MS17 1 1220 640 -77 -87 0 2 "Subst1" 1 "1 mm" 1 "Hammerstad" 0 "Kirschning" 0 "Kirschning" 0>
  <MLIN MS5 1 1530 420 -26 15 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MMBEND MS22 1 1890 230 15 -7 0 0 "Subst1" 1 "2 mm" 1>
  <MMBEND MS23 1 1660 600 -115 -56 0 2 "Subst1" 1 "1 mm" 1>
  <MLIN MS21 1 1660 510 37 -52 0 1 "Subst1" 1 "1 mm" 1 "5.025 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MLIN MS11 1 1790 230 -36 -105 0 0 "Subst1" 1 "2 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MLIN MS24 1 1770 600 -26 15 0 0 "Subst1" 1 "1 mm" 1 "10 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <SUBST Subst1 1 1020 700 -30 24 0 0 "9.8" 1 "1 mm" 1 "35 um" 1 "2e-4" 1 "0.022e-6" 1 "0.15e-6" 1>
  <MVIA MS41 1 1870 600 20 0 0 0 "Subst1" 1 "1 mm" 1 "26.85" 0>
</Components>
<Wires>
  <260 130 310 130 "" 0 0 0 "">
  <370 130 420 130 "" 0 0 0 "">
  <480 350 530 350 "" 0 0 0 "">
  <450 160 450 210 "" 0 0 0 "">
  <450 270 450 320 "" 0 0 0 "">
  <590 350 640 350 "" 0 0 0 "">
  <670 270 670 320 "" 0 0 0 "">
  <670 160 670 210 "" 0 0 0 "">
  <700 130 750 130 "" 0 0 0 "">
  <810 130 860 130 "" 0 0 0 "">
  <480 410 530 410 "" 0 0 0 "">
  <590 410 640 410 "" 0 0 0 "">
  <700 410 750 410 "" 0 0 0 "">
  <370 410 420 410 "" 0 0 0 "">
  <810 470 860 470 "" 0 0 0 "">
  <810 410 860 410 "" 0 0 0 "">
  <260 410 310 410 "" 0 0 0 "">
  <980 420 980 500 "" 0 0 0 "">
  <980 420 1020 420 "" 0 0 0 "">
  <1080 420 1130 420 "" 0 0 0 "">
  <1190 420 1240 420 "" 0 0 0 "">
  <1300 420 1360 420 "" 0 0 0 "">
  <1660 350 1660 390 "" 0 0 0 "">
  <1690 420 1760 420 "" 0 0 0 "">
  <1820 420 1860 420 "" 0 0 0 "">
  <1890 370 1890 390 "" 0 0 0 "">
  <1390 450 1390 500 "" 0 0 0 "">
  <1390 670 1390 750 "" 0 0 0 "">
  <1390 560 1390 610 "" 0 0 0 "">
  <1420 640 1470 640 "" 0 0 0 "">
  <1530 640 1570 640 "" 0 0 0 "">
  <1330 640 1360 640 "" 0 0 0 "">
  <1250 640 1270 640 "" 0 0 0 "">
  <1560 420 1630 420 "" 0 0 0 "">
  <1420 420 1500 420 "" 0 0 0 "">
  <1660 450 1660 480 "" 0 0 0 "">
  <1660 540 1660 570 "" 0 0 0 "">
  <1690 600 1740 600 "" 0 0 0 "">
  <1800 600 1850 600 "" 0 0 0 "">
  <1660 260 1660 290 "" 0 0 0 "">
  <1690 230 1760 230 "" 0 0 0 "">
  <1820 230 1860 230 "" 0 0 0 "">
  <1890 260 1890 310 "" 0 0 0 "">
</Wires>
<Diagrams>
</Diagrams>
<Paintings>
</Paintings>
