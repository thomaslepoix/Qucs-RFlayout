<Qucs Schematic 0.0.19>
<Properties>
  <View=-120,-60,1550,1084,1,120,300>
  <Grid=10,10,1>
  <DataSet=TP3_0-patch.dat>
  <DataDisplay=TP3_0-patch.dpl>
  <OpenDisplay=1>
  <Script=TP3_0-patch.m>
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
  <SUBST Subst1 1 330 350 -30 24 0 0 "4.7" 1 "1.55 mm" 1 "35 um" 1 "0.02" 1 "16.78e-9" 1 "0.15e-6" 1>
  <Eqn Eqn1 1 480 440 -31 19 0 0 "S11_Patch=S[1,1]" 1 "dB_S11_Patch=dB(S11_Patch)" 1 "yes" 0>
  <.SP SP1 1 90 330 0 84 0 0 "log" 1 "2 GHz" 1 "3 GHz" 1 "400" 1 "no" 0 "1" 0 "2" 0 "no" 0 "no" 0>
  <Pac P1 1 740 410 -26 18 0 0 "1" 1 "50 Ohm" 1 "0 dBm" 0 "1 GHz" 0 "26.85" 0>
  <GND * 1 660 410 0 0 0 0>
  <MOPEN MS2 1 1180 410 -26 -84 1 0 "Subst1" 1 "37.0218 mm" 1 "Hammerstad" 0 "Kirschning" 0 "Kirschning" 0>
  <MLIN MS3 1 1070 410 -26 15 0 0 "Subst1" 1 "37.0218 mm" 1 "28.5288 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MLIN MS4 1 860 410 -26 15 0 0 "Subst1" 1 "2.78892 mm" 1 "16.621 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MSTEP MS5 1 970 410 -26 -109 0 2 "Subst1" 1 "37.0218 mm" 1 "2.78892 mm" 1 "Hammerstad" 0 "Kirschning" 0>
</Components>
<Wires>
  <660 410 710 410 "" 0 0 0 "">
  <1100 410 1150 410 "" 0 0 0 "">
  <770 410 830 410 "" 0 0 0 "">
  <890 410 940 410 "" 0 0 0 "">
  <1000 410 1040 410 "" 0 0 0 "">
</Wires>
<Diagrams>
  <Rect 160 810 240 160 3 #c0c0c0 1 00 1 0 0.2 1 1 -0.1 0.5 1.1 1 -0.1 0.5 1.1 315 0 225 "" "" "" "">
	<"dB_S11_Patch" #55ff00 0 3 0 0 0>
  </Rect>
  <Smith 510 830 200 200 3 #c0c0c0 1 00 1 0 1 1 1 0 4 1 1 0 1 1 315 0 225 "" "" "" "">
	<"S11_Patch" #55ff00 0 3 0 0 0>
  </Smith>
</Diagrams>
<Paintings>
</Paintings>
