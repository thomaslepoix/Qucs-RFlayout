{
  description = "Export Qucs RF schematics to KiCad layouts & OpenEMS scripts";

  nixConfig.bash-prompt-suffix = "(qucsrflayout) ";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";

    flake-utils.url = "github:numtide/flake-utils";

    nix-filter.url = "github:numtide/nix-filter";

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
  , ...
  }@args:
  flake-utils.lib.eachDefaultSystem (system:
  let
    lib = nixpkgs.lib.extend nix-filter.overlays.default;
    pkgs = nixpkgs.legacyPackages.${system};

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
      qucsrflayoutWine64NixGL = nixGLWrapper qucsrflayoutWine64;
      # Bundles
      qucsrflayoutMingw64Zip = zipWrapper this-package-win;
    };

    devShells = {
      default = pkgs.mkShell {
        inputsFrom = [
          this-package
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
  });
}
