# Qucs-RFlayout
A tool to produce layout from qucs RF schematic (microstrip only for now)

`qucs-schematic.sch` -> `kicad-layout.kicad_pcb` [OK]

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
-> `kicad-module.kicad_mod` [Work in progress]

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
-> `pcb-rnd-layout.lht` [Work in progress]

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

![Qucs](https://raw.githubusercontent.com/thomaslepoix/Qucs-RFlayout/master/bitmaps/testqucs.png)
![Kicad](https://raw.githubusercontent.com/thomaslepoix/Qucs-RFlayout/master/bitmaps/testkicad.png)

<br>

Work in progress... thomas.lepoix@gmail.com
