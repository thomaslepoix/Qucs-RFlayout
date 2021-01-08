[![Liberapay patrons](https://img.shields.io/liberapay/patrons/thomaslepoix.svg?logo=liberapay)](https://liberapay.com/thomaslepoix/donate)
[![Discord](https://img.shields.io/discord/616889479298547722?logo=discord)](https://discord.gg/P82fEmE)
[![License](https://img.shields.io/github/license/thomaslepoix/Qucs-RFlayout)](LICENSE)
[![Version](https://img.shields.io/github/v/release/thomaslepoix/Qucs-RFlayout)](https://github.com/thomaslepoix/Qucs-RFlayout/releases/latest)

[![Travis build Status](https://travis-ci.org/thomaslepoix/Qucs-RFlayout.svg?branch=master)](https://travis-ci.org/thomaslepoix/Qucs-RFlayout)
[![LGTM alerts](https://img.shields.io/lgtm/alerts/g/thomaslepoix/Qucs-RFlayout.svg?logo=lgtm)](https://lgtm.com/projects/g/thomaslepoix/Qucs-RFlayout/alerts/)
[![LGTM grade](https://img.shields.io/lgtm/grade/cpp/g/thomaslepoix/Qucs-RFlayout.svg?logo=lgtm)](https://lgtm.com/projects/g/thomaslepoix/Qucs-RFlayout/context:cpp)

# Qucs-RFlayout

A tool to produce layouts from Qucs RF schematic (microstrip only for now)

`qucs-schematic.sch` -> `kicad-layout.kicad_pcb` [OK]

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
-> `kicad-module.kicad_mod` [OK]

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
-> `pcb-rnd-layout.lht` [OK]

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
-> `openEMS-script.m` [Beta]

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
-> `gmsh.geo` [ASAP]

<br>

French documentation [here](https://github.com/thomaslepoix/ESTEI/blob/master/M2_CPP_Qucs-RFlayout/Qucs-RFlayout.pdf)

This software is a part of the [Open-RFlab](https://github.com/Open-RFlab/Open-RFlab) project, if you are interrested in contributing or involved in an other `somewhat -> openems` converter please take a look.

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
    - Feed point VSWR
    - Phase response (wrapped and unwrapped)
    - Phase delay and group delay
    - Azimuth & elevation far field radiation pattern (polar and orthogonal, normalized and in dBi)
    - 3D far field radiation pattern for multiple frequencies (animated `.gif`)
    - Electric & magnetic fields, current and current density in time domain (visible with Paraview)

- [Here](doc/tutorials/openems.md) is a tutorial.

<br>

## Installation

### Dependencies

- [Qucs](https://github.com/Qucs/qucs) is needed (even if you want to convert QucsStudio files), be sure it is installed and accessible from your `PATH` variable.
- OpenEMS scripts dependencies :
  - [OpenEMS](https://openems.de/index.php/OpenEMS#Installation) (`octave-openems` package available on Debian 10 based distros, `octave-openEMS` on openSUSE)
  - [ImageMagick](https://imagemagick.org/script/download.php) (packages available on most distros)

### Binary installation

- For Debian based distributions, a repository is available :

```sh
curl -s https://bintray.com/user/downloadSubjectPublicKey?username=bintray | sudo apt-key --keyring /etc/apt/trusted.gpg.d/open-rflab.gpg add -
echo "deb https://dl.bintray.com/open-rflab/debian $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/open-rflab.list

sudo apt-get update
sudo apt-get install qucsrflayout
```

- For RPM based distributions and Windows, you can download packages [here](https://github.com/thomaslepoix/Qucs-RFlayout/releases).

### Build from sources

- Install build dependencies :

```sh
sudo apt-get install qt5-default libqt5opengl5-dev texlive-xetex fonts-lato    # Debian
```

- Build :

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
- QucsStudio schematics are supported (2.x versions only) but it is closed source and there are some incompatibilities so please prefer using Qucs.

<br>

Work in progress... thomas.lepoix@protonmail.ch
