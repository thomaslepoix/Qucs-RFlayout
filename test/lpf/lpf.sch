<Qucs Schematic 0.0.19>
<Properties>
  <View=0,-60,1548,1443,1,0,660>
  <Grid=10,10,1>
  <DataSet=lpf.dat>
  <DataDisplay=lpf.sch>
  <OpenDisplay=1>
  <Script=lpf.m>
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
  <Pac P1 1 230 350 18 -26 0 1 "1" 1 "50 Ohm" 1 "0 dBm" 0 "1 GHz" 0 "26.85" 0>
  <GND *1 5 230 380 0 0 0 0>
  <MLIN MS1 1 290 200 -26 15 0 0 "Sub1" 1 "500 um" 1 "4.5 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MSTEP MS8 1 350 200 -26 -109 1 0 "Sub1" 1 "500 um" 1 "20.5 mm" 1 "Hammerstad" 0 "Kirschning" 0>
  <MLIN MS2 1 410 200 -26 15 0 0 "Sub1" 1 "20.5 mm" 1 "1.5 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MSTEP MS9 1 470 200 -26 -109 1 0 "Sub1" 1 "20.5 mm" 1 "500 um" 1 "Hammerstad" 0 "Kirschning" 0>
  <MLIN MS3 1 530 200 -26 15 0 0 "Sub1" 1 "500 um" 1 "18 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MSTEP MS10 1 590 200 -26 -109 1 0 "Sub1" 1 "500 um" 1 "20.5 mm" 1 "Hammerstad" 0 "Kirschning" 0>
  <MLIN MS4 1 650 200 -26 15 0 0 "Sub1" 1 "20.5 mm" 1 "2.5 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MSTEP MS11 1 710 200 -26 -109 1 0 "Sub1" 1 "20.5 mm" 1 "500 um" 1 "Hammerstad" 0 "Kirschning" 0>
  <MLIN MS5 1 770 200 -26 15 0 0 "Sub1" 1 "500 um" 1 "18 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MSTEP MS12 1 830 200 -26 -109 1 0 "Sub1" 1 "500 um" 1 "20.5 mm" 1 "Hammerstad" 0 "Kirschning" 0>
  <MLIN MS6 1 890 200 -26 15 0 0 "Sub1" 1 "20.5 mm" 1 "1.5 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <MSTEP MS13 1 950 200 -26 -109 1 0 "Sub1" 1 "20.5 mm" 1 "500 um" 1 "Hammerstad" 0 "Kirschning" 0>
  <MLIN MS7 1 1010 200 -26 15 0 0 "Sub1" 1 "500 um" 1 "4.5 mm" 1 "Hammerstad" 0 "Kirschning" 0 "26.85" 0>
  <Pac P2 1 1090 350 18 -26 0 1 "2" 1 "50 Ohm" 1 "0 dBm" 0 "1 GHz" 0 "26.85" 0>
  <GND *2 5 1090 380 0 0 0 0>
  <SUBST Sub1 1 660 380 -30 24 0 0 "4.2" 1 "800 um" 1 "35 um" 1 "0.035" 1 "1e-10" 1 "0" 1>
  <.SP SP1 1 420 340 0 77 0 0 "lin" 1 "20 MHz" 1 "5 GHz" 1 "499" 1 "no" 0 "1" 0 "2" 0 "no" 0 "no" 0>
  <Eqn Eqn1 1 790 450 -28 15 0 0 "Qucs_S11=dB(S[1,1])" 1 "Qucs_S21=dB(S[2,1])" 1 "yes" 0>
  <Pac P3 1 230 800 18 -26 0 1 "3" 1 "50 Ohm" 1 "0 dBm" 0 "1 GHz" 0 "26.85" 0>
  <GND * 1 230 830 0 0 0 0>
  <Pac P6 1 1090 800 18 -26 0 1 "6" 1 "50 Ohm" 1 "0 dBm" 0 "1 GHz" 0 "26.85" 0>
  <GND * 1 1090 830 0 0 0 0>
  <GND * 1 300 720 0 0 0 0>
  <Pac P4 1 370 800 18 -26 0 1 "4" 1 "50 Ohm" 1 "0 dBm" 0 "1 GHz" 0 "26.85" 0>
  <GND * 1 370 830 0 0 0 0>
  <GND * 1 1020 720 0 0 0 0>
  <Pac P5 1 950 800 18 -26 0 1 "5" 1 "50 Ohm" 1 "0 dBm" 0 "1 GHz" 0 "26.85" 0>
  <GND * 1 950 830 0 0 0 0>
  <Eqn Eqn2 1 630 690 -28 15 0 0 "OpenEMS_S11=dB(S[3,3])" 1 "OpenEMS_S21=dB(S[4,3])" 1 "Measure_S11=dB(S[5,5])" 1 "Measure_S21=dB(S[6,5])" 1 "yes" 0>
  <SPfile X1 1 300 690 -26 -67 0 0 "lpf_openems.s2p" 1 "rectangular" 0 "linear" 0 "open" 0 "2" 0>
  <SPfile X2 1 1020 690 -26 -67 0 0 "lpf_measure.s2p" 1 "rectangular" 0 "linear" 0 "open" 0 "2" 0>
</Components>
<Wires>
  <230 200 230 320 "" 0 0 0 "">
  <230 200 260 200 "" 0 0 0 "">
  <1090 200 1090 320 "" 0 0 0 "">
  <1040 200 1090 200 "" 0 0 0 "">
  <230 690 230 770 "" 0 0 0 "">
  <230 690 270 690 "" 0 0 0 "">
  <330 690 370 690 "" 0 0 0 "">
  <370 690 370 770 "" 0 0 0 "">
  <1090 690 1090 770 "" 0 0 0 "">
  <1050 690 1090 690 "" 0 0 0 "">
  <950 690 990 690 "" 0 0 0 "">
  <950 690 950 770 "" 0 0 0 "">
</Wires>
<Diagrams>
  <Rect 230 1235 450 300 3 #c0c0c0 1 00 0 0 1e+09 5e+09 1 -60 20 5.04775 1 -1 0.5 1 315 0 225 "Frequency (Hz)" "" "S11 (dB)" "">
	<"Qucs_S11" #00ffff 2 3 0 0 0>
	<"Measure_S11" #00ff00 2 3 0 0 0>
	<"OpenEMS_S11" #ff00ff 2 3 0 0 0>
  </Rect>
  <Rect 750 1235 450 300 3 #c0c0c0 1 00 0 0 1e+09 5e+09 1 -80 20 6.9719 1 -1 0.5 1 315 0 225 "Frequency (Hz)" " " "S21 (dB)" "">
	<"Qucs_S21" #00ffff 2 3 0 0 0>
	<"Measure_S21" #00ff00 2 3 0 0 0>
	<"OpenEMS_S21" #ff00ff 2 3 0 0 0>
  </Rect>
</Diagrams>
<Paintings>
  <Text 760 340 12 #000000 0 "stepped-impedance lowpass filter \n Butterworth 1.8 GHz...2 GHz \n impedance matching 50 Ohm">
</Paintings>
