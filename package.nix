{ pkgs, pname, version, }:
pkgs.stdenv.mkDerivation {
  inherit pname version;

  src = ./.;

  buildInputs = with pkgs; [
    gcc
    cmake
    catch2_3
    hyperfine
    linuxKernel.packages.linux_6_12.perf
  ];

  installPhase = ''
    mkdir -p $out/bin
    cp main $out/bin/${pname}
  '';
}
