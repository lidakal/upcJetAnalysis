#!/usr/bin/env python3

# Usage:
# python3 list_files.py /path/to/root_dir -o output.txt

import argparse
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(
        description="List full paths of merged_JRA.root files and write them to a text file."
    )
    parser.add_argument(
        "root_dir",
        nargs="?",
        default=Path.home() / "SE_UserHome" / "GNucleus-QCD_Pthat8_5p36TeV_pythia8" / "crab_GNucleus-QCD_Pthat8_UPC_5p36TeV_pythia8_JRA_v2" / "260406_082939",
        type=Path,
        help="Root directory to search for merged_JRA.root files. Defaults to the standard crab output directory.",
    )
    parser.add_argument(
        "-o",
        "--output",
        default=Path(__file__).resolve().parent / "merged_files.txt",
        type=Path,
        help="Output text file path. Defaults to merged_files.txt next to this script.",
    )
    args = parser.parse_args()

    root_dir = args.root_dir.expanduser().resolve()
    out_path = args.output.expanduser().resolve()

    if not root_dir.is_dir():
        raise SystemExit(f"Root directory does not exist: {root_dir}")

    merged_files = sorted(root_dir.rglob("merged_JRA.root"))

    if not merged_files:
        print(f"No merged_JRA.root files found under {root_dir}")
        return 0

    out_path.parent.mkdir(parents=True, exist_ok=True)
    with out_path.open("w", encoding="utf-8") as fp:
        for path in merged_files:
            fp.write(f"{path}\n")

    print(f"Wrote {len(merged_files)} files to {out_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
