# Qucs-RFlayout
A tool to produce layout from qucs RF schematic (microstrip only for now)

`qucs-schematic.sch` -> `kicad-layout.kicad_pcb` [OK]

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
-> `kicad-module.kicad_mod` [OK]

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
-> `pcb-rnd-layout.lht` [OK]

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
-> `openEMS-script.m` [Work in progress]

<br>

## Build

```
make
```

<br>

## Usage

```
./qucsrflayout -i qucs-schematic.sch -o output-directory -f .output-format
```

<br>

## Screenshots

### Qucs : schematic.sch
![qucs_sch](https://raw.githubusercontent.com/thomaslepoix/Qucs-RFlayout/master/test/test_qucs_sch.png)

### Qucs-RFlayout : preview
![qucsrflayout_preview](https://raw.githubusercontent.com/thomaslepoix/Qucs-RFlayout/master/test/test_qucsrflayout_preview.png)

### Pcbnew : layout.kicad_pcb
![pcbnew_kicad_pcb](https://raw.githubusercontent.com/thomaslepoix/Qucs-RFlayout/master/test/test_pcbnew_kicad_pcb.png)

### Pcbnew : module.kicad_mod
![pcbnew_kicad_mod](https://raw.githubusercontent.com/thomaslepoix/Qucs-RFlayout/master/test/test_pcbnew_kicad_mod.png)

### Pcb-rnd : layout.lht
![pcb-rnd_lht](https://raw.githubusercontent.com/thomaslepoix/Qucs-RFlayout/master/test/test_pcb-rnd_lht.png)

<br>

Work in progress... thomas.lepoix@gmail.com
