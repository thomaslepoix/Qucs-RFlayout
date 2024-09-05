{ lib
, stdenv
, cmake
, qtbase
, wrapQtAppsHook
, texlive
, lato
, withDoc ? true
, withGui ? true
}:

assert lib.asserts.assertMsg (! (stdenv.hostPlatform.isWindows && withGui == false))
  "Minimal mode is not compatible with Windows build";

stdenv.mkDerivation {
  pname = "qucsrflayout" + lib.strings.optionalString (! withGui) "-minimal";
  version =
  let
    firstLine = builtins.elemAt (lib.strings.split "\n" (builtins.readFile ./CHANGELOG)) 0;
  in builtins.elemAt (builtins.match "^qucsrflayout \\((.*)\\)$" firstLine) 0;

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

  cmakeFlags = lib.optionals (! withGui) [
    "-DQRFL_MINIMAL=ON"
  ];

  nativeBuildInputs = [
    cmake
  ] ++ lib.optionals withGui [
    wrapQtAppsHook
  ] ++ lib.optionals withDoc [
    lato
    (texlive.combine {
      inherit (texlive) scheme-small standalone pgfplots;
    })
  ];

  buildInputs = lib.optionals withGui [
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
