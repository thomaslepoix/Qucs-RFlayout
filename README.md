[![Travis build Status](https://travis-ci.org/thomaslepoix/Qucs-RFlayout.svg?branch=master)](https://travis-ci.org/thomaslepoix/Qucs-RFlayout)
[![Liberapay patrons](https://img.shields.io/liberapay/patrons/thomaslepoix.svg?logo=liberapay)](https://liberapay.com/thomaslepoix/donate)

# Qucs-RFlayout

A tool to produce layouts from Qucs RF schematic (microstrip only for now)

`qucs-schematic.sch` -> `kicad-layout.kicad_pcb` [OK]

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
-> `kicad-module.kicad_mod` [OK]

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
-> `pcb-rnd-layout.lht` [OK]

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
-> `openEMS-script.m` [Alpha]

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
-> `gmsh.geo` [ASAP]

<br>

French documentation [here](https://github.com/thomaslepoix/ESTEI/blob/master/M2_CPP_Qucs-RFlayout/Qucs-RFlayout.pdf)

<br>

## Screenshots

### Qucs : schematic.sch
![qucs_sch](res/preview_qucs_sch.png)

### Qucs-RFlayout : preview
![qucsrflayout_preview](res/preview_qucsrflayout.png)

### Pcbnew : layout.kicad_pcb
![pcbnew_kicad_pcb](res/preview_pcbnew_kicad_pcb.png)

### Pcbnew : module.kicad_mod
![pcbnew_kicad_mod](res/preview_pcbnew_kicad_mod.png)

### Pcb-rnd : layout.lht
![pcb-rnd_lht](res/preview_pcb-rnd_lht.png)

### OpenEMS : simulation.m
![appcsxcad_m](res/preview_appcsxcad_m.png)

- Better example : A low pass filter designed, produced and measured by [F4HDG](https://wiki.rfporn.org/doku.php/wiki:projects:filtres:lpf_23cm_microstrip). Thanks to him!

<img src="doc/tutorials/res/lpf_sch.svg" width="100%" title="lpf_sch"/>

<img src="res/lpf_csx.png" style="float:left;" width="360" title="lpf_csx"/> <img src="res/lpf_pcb.png" style="float:right;" width="440" title="lpf_pcb"/>

<img src="doc/tutorials/res/lpf_ff_3d_vm.gif" style="float:right;" width="410" title="lpf_ff_3d_vm"/> <img src="res/lpf_paraview_et.gif" style="float:left;" width="410" title="lpf_paraview_et"/>

<img src="doc/tutorials/res/lpf_dpl.svg" width="100%" title="lpf_dpl"/>

- Generated scripts outputs :
    - Touchstone file (`.sxp`)
    - S parameters (Smith chart and orthogonal)
    - Feed point impedance
    - Azimuth & elevation far field radiation pattern (polar and orthogonal, normalized and in dBi)
    - 3D far field radiation pattern for multiple frequencies (animated `.gif`)
    - Electric & magnetic fields, current and current density in time domain (visible with Paraview)

- [Here](doc/tutorials/openems.md) is a tutorial.

<br>

## Build & Install

- Install dependencies :

```sh
sudo apt-get install qt5-default libqt5opengl5-dev texlive-xetex fonts-lato    # Debian
```

- OpenEMS scripts dependencies :

  - [OpenEMS](https://github.com/thliebig/openEMS-Project) (CTB is required, be sure to add the `addpath` lines to your `.octaverc` / `startup.m` file)
  - ImageMagick

- With CMake (You must use a modern version >= 3.11) :

```sh
Qucs-RFlayout $

    mkdir build && cd build

    cmake ..
    make
    make doc

    # Prefered way : use your packet manager
    make package
    sudo apt-get install ./qucsrflayout_*.deb    # Debian
    sudo dnf install ./qucsrflayout-*.rpm        # Fedora

    # Classic way : install manually
    sudo make install
```

- Or if you don't have CMake, you can use QMake (Incomplete installation) :

```sh
Qucs-RFlayout $

    mkdir build && cd build

    qmake ..
    make
    sudo make install
```

<br>

## Usage

```sh
qucsrflayout -i qucs-schematic.sch -o output-directory -f .output-format
```

<br>

## Limitations

- Microstrip only for now, coplanar waveguide ASAP.
- Any other component cannot be converted into a geometric shape of metal by this tool.
- Use one wire to connect only two components ports, use apropriate components to make tees or crosses.
- Equations are not supported yet, avoid using variables in component fields.
- QucsStudio schematics are supported but it is closed source and there are some incompatibilities so please prefer using Qucs.

<br>

Work in progress... thomas.lepoix@protonmail.ch
