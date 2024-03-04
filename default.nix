{ lib
, stdenv
, cmake
, git
, qtbase
, wrapQtAppsHook
, texlive
, lato
, withDoc ? true
}:

stdenv.mkDerivation {
  pname = "qucsrflayout";
  version = "2.0.0";

  src = ./.;

  nativeBuildInputs = [
    cmake
    git
    wrapQtAppsHook
  ] ++ lib.optionals withDoc [
    lato
    (texlive.combine {
      inherit (texlive) scheme-small standalone pgfplots;
    })
  ];

  buildInputs = [
    qtbase
  ];

  cmakeFlags = [
    "-DCPM_DISABLE=ON"
  ];

  postBuild = lib.optionals withDoc ''
    export XDG_CACHE_HOME=$TMPDIR
    make doc
  '';

  enableParallelBuilding = true;

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
