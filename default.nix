{ lib
, stdenv
, cmake
, qtbase
, wrapQtAppsHook
, texlive
, lato
, withDoc ? true
#, withTests ? false # TODO enableTests?
}:

#assert texlive.stdenv.hostPlatform == stdenv.buildPlatform;

let
#  texlive-native = texlive.override { stdenv = stdenv. }

in stdenv.mkDerivation {
  pname = "qucsrflayout";
  version = "2.0.0";

  src = lib.nix-filter {
    root = ./.;
    include = [
      "cmake"
      "src"
      "doc"
      "lib"
      "pack"
      "test"
      "CMakeLists.txt"
      "CHANGELOG"
    ];
  };

#  checkInputs = [
#    catch2
#  ];
#  doCheck = withTests;
#  cmakeFlags = lib.optional enableTests "-DCMAKE_BUILD_TYPE=Debug";
  cmakeFlags = [
    "-DCPM_DISABLE=ON"
  ];

  shellHook = ''
    export CPM_DISABLE=ON
  '';

  nativeBuildInputs = [
    cmake
    wrapQtAppsHook
#  ] ++ lib.optionals withDoc [
#    lato
#    (texlive.combine {
#      inherit (texlive) scheme-small standalone pgfplots;
#    })
#  ] ++ lib.optionals stdenv.hostPlatform.isWindows [
  ];

  depsBuildBuild = lib.optionals withDoc [
    lato
    (texlive.combine {
      inherit (texlive) scheme-small standalone pgfplots;
    })
  ];

  buildInputs = [
    qtbase
  ];

  postBuild = lib.optionals withDoc ''
    export XDG_CACHE_HOME=$TMPDIR
    make doc
  '';

  postInstall = lib.optionals stdenv.hostPlatform.isWindows ''
    mkdir -p $out/bin/platforms
    ln -t $out/bin/platforms -s ${qtbase}/lib/qt-6/plugins/platforms/qwindows.dll
  '';
#    ln -t $out/bin -s ${wine64Packages.base}/lib/wine/x86_64-windows/d3d11.dll
#    ln -t $out/bin -s ${wine64Packages.base}/lib/wine/x86_64-windows/dxgi.dll

  dontWrapQtApps = stdenv.hostPlatform.isWindows;

  QT_XCB_GL_INTEGRATION = "none";

  meta = {
    homepage = "https://github.com/thomaslepoix/Qucs-RFlayout";
    description = "Export Qucs RF schematics to KiCad layouts & OpenEMS scripts";
    license = lib.licenses.gpl3;
    maintainers = [
      {
        email = "thomas.lepoix@protonmail.ch";
        github = "thomaslepoix";
        githubId = 26417323;
        name = "Thomas Lepoix";
      }
    ];
  };
}
