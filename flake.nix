{
  description = "Export Qucs RF schematics to KiCad layouts & OpenEMS scripts";

  nixConfig.bash-prompt-suffix = "(qucsrflayout) ";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";

    flake-utils.url = "github:numtide/flake-utils";

    nixGL = {
      url = "github:nix-community/nixGL";
      inputs.nixpkgs.follows = "nixpkgs";
      inputs.flake-utils.follows = "flake-utils";
    };
  };

  outputs = { self
  , nixpkgs
  , flake-utils
  , nixGL
  , ...
  }@args:
  flake-utils.lib.eachDefaultSystem (system:
  let
    pkgs = nixpkgs.legacyPackages.${system};

    nixGLWrapper = package: pkgs.stdenvNoCC.mkDerivation {
      inherit (package) pname version meta;
      doCheck = false;
      dontUnpack = true;
      dontBuild = true;
      installPhase =
      let
        script = ''
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

    this-package = pkgs.qt6.callPackage ./default.nix {};

  in {
    packages = rec {
      default = qucsrflayoutNixGL;
      qucsrflayout = this-package;
      qucsrflayoutNixGL = nixGLWrapper this-package;
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
