{
  description = "Export Qucs RF schematics to KiCad layouts & OpenEMS scripts";

  nixConfig.bash-prompt-suffix = "(qucsrflayout) ";
#    nixpkgs.url = "github:NixOS/nixpkgs/219951b495fc2eac67b1456824cc1ec1fd2ee659";
#    nixpkgs.url = "flake:nixpkgs";

  inputs = {
#    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    nixpkgs.url = "github:NixOS/nixpkgs";

    flake-utils.url = "github:numtide/flake-utils";

    nix-filter.url = "github:numtide/nix-filter";

#    zicross ={
#      url = github:flyx/Zicross;
#      inputs.nixpkgs.follows = "nixpkgs";
#      inputs.utils.follows = "flake-utils";
#      inputs.nix-filter.follows = "nix-filter";
#    };

    nixGL = {
      url = "github:nix-community/nixGL";
      inputs.nixpkgs.follows = "nixpkgs";
      inputs.flake-utils.follows = "flake-utils";
    };
  };

  outputs = { self
  , nixpkgs
  , flake-utils
  , nix-filter
  , nixGL
  #, zicross
  , ...
  }@args:
  flake-utils.lib.eachDefaultSystem (system:
  let
#    nixpkgs-patched = (import nixpkgs { inherit system; }).applyPatches {
#      name = "nixpkgs-patched";
#      src = nixpkgs;
#      patches = [
#        ((import nixpkgs { inherit system; }).fetchpatch {
#          url = "https://github.com/NixOS/nixpkgs/pull/298001.patch";
#          hash = "sha256-g3Anxe4LWP78HmP/QqvZLmpAptj+5oLNTYNQC/Xb2eI=";
#        })
#      ];
#    };
#    lib = (import nixpkgs-patched { inherit system; }).lib.extend nix-filter.overlays.default;
#    pkgs = ((import nixpkgs-patched { inherit system; }).extend (final: prev: {
    lib = nixpkgs.lib.extend nix-filter.overlays.default;
    pkgs = (nixpkgs.legacyPackages.${system}.extend (final: prev: {
      qucs-s = prev.qucs-s.overrideAttrs (old: rec {
        version = "d8bea98";
        src = pkgs.fetchFromGitHub {
          owner = "ra3xdh";
          repo = "qucs_s";
          rev = version;
          hash = "sha256-fx61Vn54J2UGjGbycYwSpmJJ618WVpBAym8d/GUgepk=";
        };
        cmakeFlags = [
          "-DWITH_QT6=ON"
        ];
        enableParallelBuilding = true;
      });
      # find `ls /nix/store | grep -E 'mingw32|wine' | awk '{print "/nix/store/" $0}'` -name qwindows.dll -or -name UxTheme.dll -or -name d3d11.dll -or -name dxgi.dll -or -name OPENGL32.dll -or -name USERENV.dll
      pe-util = pkgs.stdenv.mkDerivation rec {
        pname = "pe-util";
        version = "dc5dda5";
        src = pkgs.fetchFromGitHub {
          fetchSubmodules = true;
          owner = "gsauthof";
          repo = "pe-util";
          rev = version;
          hash = "sha256-ex2fQUn9lSh5Yh4XGMYkHaHkgGiKWa8T6BpXD8rR8qI=";
        };
        nativeBuildInputs = [
          pkgs.cmake
        ];
        enableParallelBuilding = true;
        meta = {
          homepage = "https://github.com/gsauthof/pe-util";
          description = "List shared object dependencies of a portable executable (PE)";
          license = lib.licenses.mit;
          mainProgram = "peldd";
          maintainers = [
            {
              email = "thomas.lepoix@protonmail.ch";
              github = "thomaslepoix";
              githubId = 26417323;
              name = "Thomas Lepoix";
            }
          ];
        };
      };
      openems = (prev.openems.overrideAttrs (new: old: {
        version = "0.0.36";
        src = pkgs.fetchFromGitHub {
          owner = "thliebig";
          repo = "openEMS";
          rev = "v${new.version}";
          hash = "sha256-wdH+Zw7G2ZigzBMX8p3GKdFVx/AhbTNL+P3w+YjI/dc=";
        };
#        prePatch = ''
#          substituteInPlace CMakeLists.txt --replace 'INSTALL( DIRECTORY matlab DESTINATION share/openEMS )' ""
#        '';
      })).override {
        stdenv = pkgs.fastStdenv;
      };
      csxcad = (prev.csxcad.overrideAttrs (new: old: {
        version = "0.6.3";
        src = pkgs.fetchFromGitHub {
          owner = "thliebig";
          repo = "CSXCAD";
          rev = "v${new.version}";
          hash = "sha256-SSV5ulx3rCJg99I/oOQbqe+gOSs+BfcCo6UkWHVhnSs=";
        };
        prePatch = ''
          substituteInPlace CMakeLists.txt --replace 'INSTALL(DIRECTORY matlab DESTINATION share/CSXCAD)' ""
        '';
      })).override {
        stdenv = pkgs.fastStdenv;
      };
    }));
#    })).extend zicross.overlays.windows;

    nixGLWrapper = package: pkgs.stdenvNoCC.mkDerivation {
      inherit (package) pname version meta;
      doCheck = false;
      dontUnpack = true;
      dontBuild = true;
      installPhase =
      let
        script = ''
          #!/bin/sh
          exec ${nixGL.packages.${system}.nixGLDefault}/bin/nixGL ${package}/bin/${package.pname} "$@"
        '';
      in ''
        mkdir -p $out/bin
        printf '${script}' > $out/bin/${package.pname}
        chmod +x $out/bin/${package.pname}
        mkdir -p $out/share
        ${pkgs.xorg.lndir}/bin/lndir -silent ${package}/share $out/share
      '';
    };

    wineWrapper = package: pkgs.stdenvNoCC.mkDerivation {
      inherit (package) pname version meta;
      doCheck = false;
      dontUnpack = true;
      dontBuild = true;
      installPhase =
      let
        script = ''
          #!/bin/sh
          exec ${pkgs.wine64}/bin/wine64 ${package}/bin/${package.pname}.exe "$@"
        '';
      in ''
        mkdir -p $out/bin
        printf '${script}' > $out/bin/${package.pname}
        chmod +x $out/bin/${package.pname}
        mkdir -p $out/share
        ${pkgs.xorg.lndir}/bin/lndir -silent ${package}/share $out/share
      '';
    };

    zipWrapper = package: pkgs.stdenvNoCC.mkDerivation {
      inherit (package) pname version meta;
      doCheck = false;
      dontUnpack = true;
      nativeBuildInputs = [ pkgs.zip ];
      buildPhase = ''
        cp -rL ${package} ${package.name}
        chmod -R ug+w ${package.name}
        zip -r ${package.name}.zip ${package.name}/*
      '';
      installPhase = ''
        mkdir -p $out
        mv ${package.name}.zip $out/
      '';
    };

    this-package = pkgs.qt6.callPackage ./default.nix { inherit lib; };
    this-package-clang = pkgs.qt6.callPackage ./default.nix { inherit lib; stdenv = pkgs.clangStdenv; };
    this-package-gcc = pkgs.qt6.callPackage ./default.nix { inherit lib; stdenv = pkgs.gccStdenv; };
    this-package-static = pkgs.pkgsStatic.qt6.callPackage ./default.nix { inherit lib; withDoc = false; };
    this-package-win = pkgs.pkgsCross.mingwW64.qt6.callPackage ./default.nix { inherit lib; inherit (pkgs) texlive; };

  in {
    packages = rec {
      default = qucsrflayoutNixGL;
      # Native
      qucsrflayout = this-package;
      qucsrflayoutClang = this-package-clang;
      qucsrflayoutGcc = this-package-gcc;
      # Cross compiled
      qucsrflayoutMingw64 = this-package-win;
      # Wrappers
      qucsrflayoutNixGL = nixGLWrapper this-package;
      qucsrflayoutWine64 = wineWrapper this-package-win;
      # Bundles
      qucsrflayoutMingw64Zip = zipWrapper this-package-win;
    };

    devShells = {
      default = pkgs.mkShell {
        inputsFrom = [
          this-package
        ];
        packages = [
          pkgs.qucs-s
#          pkgs.kicad-small
          pkgs.openems
          pkgs.csxcad
#          pkgs.pe-util
#          pkgs.wine64
          pkgs.appcsxcad
          pkgs.graphicsmagick
          this-package
          (let
            openems = pkgs.octavePackages.buildOctavePackage rec {
              inherit (pkgs.openems) pname version meta;
              src = pkgs.applyPatches {
                inherit (pkgs.openems) src;
                postPatch = ''
                  sed -i matlab/private/invoke_openEMS.m \
                    -e '29,35d'
                  substituteInPlace matlab/private/invoke_openEMS.m --replace \
                    "command = [openEMS_bin" \
                    "command = ['env openEMS'"
                  sed -i matlab/CalcNF2FF.m \
                    -e '101,107d' \
                    -e '124,126d'
                  substituteInPlace matlab/CalcNF2FF.m --replace \
                    "system(['export LD_LIBRARY_PATH=; ' nf2ff_bin" \
                    "system(['env nf2ff'"
                  cp ${self + "/patch/openems/DESCRIPTION"} .
                  mv ./matlab ./inst
                '';
              };
              buildInputs = [ pkgs.hdf5-cpp ];
              propagatedBuildInputs = [ pkgs.openems ];
#              preBuild = ''
              postBuild = ''
                mkoctfile --version
                echo $OCTAVE_FULLBPATH
                pwd ; ls
                cd inst
                CXXFLAGS="-g -O2 -fstack-protector-strong -Wformat -Werror=format-security" \
                mkoctfile \
                  -I${pkgs.hdf5-cpp}/include \
                  -L${pkgs.hdf5-cpp}/lib \
                  -lhdf5_cpp \
                  -DH5_USE_16_API \
                  h5readatt_octave.cc
                rm h5readatt_octave.cc
                ls
                cd ..
              '';
#              postInstall = ''
#                mv inst/h5readatt_octave.oct $out/lib/octave/<version>/oct/
#              '';
#	cd debian/tmp/usr/share/openEMS/matlab && CXXFLAGS="-g -O2 -fstack-protector-strong -Wformat -Werror=format-security" mkoctfile -L/usr/lib/$(DEB_HOST_MULTIARCH)/hdf5/serial -lhdf5_cpp -DH5_USE_16_API -I/usr/include/hdf5/serial h5readatt_octave.cc
#	mkdir -p debian/tmp/$(OCTAVE_FULLBPATH)
#	mv debian/tmp/usr/share/openEMS/matlab/h5readatt_octave.oct debian/tmp/$(OCTAVE_FULLBPATH)/
#	rm debian/tmp/usr/share/openEMS/matlab/h5readatt_octave.cc
            };
            csxcad = pkgs.octavePackages.buildOctavePackage rec {
              inherit (pkgs.csxcad) pname version meta;
              src = pkgs.applyPatches {
                inherit (pkgs.csxcad) src;
                postPatch = ''
                  sed -i matlab/CSXGeomPlot.m \
                    -e '30,36d'
                  substituteInPlace matlab/CSXGeomPlot.m --replace \
                    "command = [AppCSXCAD_bin" \
                    "command = ['env AppCSXCAD'"
                  cp ${self + "/patch/csxcad/DESCRIPTION"} .
                  mv ./matlab ./inst
                '';
              };
              propagatedBuildInputs = [ pkgs.openems ];
            };

          in pkgs.octaveFull.withPackages (p: [
            openems
            csxcad
            (pkgs.octavePackages.buildOctavePackage rec {
              pname = "openems-hll";
              version = "ec5e1c1";
              src = pkgs.fetchFromGitHub {
                owner = "Open-RFlab";
                repo = "octave-openems-hll";
                rev = version;
                hash = "sha256-/RITOhGOwVjUuttDdiYQ7IaDhD7j9NB24PRI1tZRFJY=";
              };
              requiredOctavePackages = [
                openems
                csxcad
              ];
              propagatedBuildInputs = [
                pkgs.imagemagick
                pkgs.graphicsmagick
                pkgs.ghostscript
              ];
            })
          ]))
        ];
      };

      winVM = pkgs.mkShell {
        packages = [
          pkgs.quickemu
        ];
      };

      nixGL = pkgs.mkShell {
        inputsFrom = [
          this-package
        ];
        packages = [
          nixGL.packages.${system}.nixGLDefault
        ];
      };
    };

#    checks = {
#      test = {};
#      run = {};
#      test-win = {};
#      run-win = {};
#      devshell = {};
#    };
  });
}
      # https://github.com/ralismark/nix-appimage
#      win-bundle =
 #     qucsrflayoutStatic = this-package-static;
      # https://functor.tokyo/blog/2021-10-20-nix-cross-static
      # https://ayats.org/blog/nix-cross/
      # https://flyx.org/cross-packaging/part1/
      # https://github.com/flyx/Zicross
      # https://github.com/pololu/nixcrpkgs
      # There’s also pkgs.pkgsStatic which automatically builds static binaries that are linked against musl instead of the GNU libc.


#      win64Zip = pkgs.packageForWindows this-package {
#        targetSystem = "x86_64-windows";
#        appendExe = [ "qucsrflayout" ];
#        deps = {
##          sdl2 = {
##            tail = "SDL2-2.0.22-1-any.pkg.tar.zst";
##            sha256 = "13v4wavbxzdnmg6b7qrv7031dmdbd1rn6wnsk9yn4kgs110gkk90";
##            postPatch = ''
##              ${pkgs.gnused}/bin/sed -i "s:-lSDL2main:$out/clang64/lib/libSDL2main.a:g" upstream/clang64/lib/pkgconfig/sdl2.pc
##            '';
##          };
##          iconv = {
##            tail = "libiconv-1.16-2-any.pkg.tar.zst";
##            sha256 = "0kwc5f60irrd5ayjr0f103f7qzll9wghcs9kw1v17rj5pax70bxf";
##          };
##          vulkan = {
##            tail = "vulkan-loader-1.3.211-1-any.pkg.tar.zst";
##            sha256 = "0n9wnrcclvxj7ay14ia679s2gcj5jyjgpg53j51yfdn48wlqi40l";
##          };
##          libcpp = {
##            tail = "libc++-14.0.3-1-any.pkg.tar.zst";
##            sha256 = "1r73zs9naislzzjn7mr3m8s6pikgg3y4mv550hg09gcsjc719kzz";
##          };
##          unwind = {
##            tail = "libunwind-14.0.3-1-any.pkg.tar.zst";
##            sha256 = "1lxb0qgnl9fbdmkmj53zjg8i9q5hv0pa83bkmraf2raflpm2yrs5";
##          };
#        };
#      };

