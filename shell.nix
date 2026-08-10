{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
    gdb
    gnumake
    clang-tools
    valgrind
    man-pages
    man-pages-dev
    pkgconf
    bear
  ];
}
