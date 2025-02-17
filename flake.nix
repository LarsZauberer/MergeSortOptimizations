{
  description = "A simple nix packaged merge sort cpp program";

  inputs = { nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable"; };

  outputs = inputs:
    let
      eachSystem = f:
        inputs.nixpkgs.lib.mapAttrs f inputs.nixpkgs.legacyPackages;
      pname = "sorter";
      version = "1.0";
    in {
      packages = eachSystem (system: pkgs: {
        sorter = pkgs.callPackage ./package.nix {
          inherit pkgs;
          inherit pname;
          inherit version;
        };
        default = inputs.self.packages.${system}.sorter;
      });

      devShells = eachSystem (system: pkgs: {
        default = pkgs.callPackage ./shell.nix {
          inherit pkgs;
          inherit (inputs.self.packages.${system}) sorter;
        };
      });
    };
}
