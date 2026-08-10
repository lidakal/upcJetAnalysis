#!/usr/bin/env python3

# Usage:
# python3 list_file_collections.py /path/to/base_dir -o output.txt

import argparse
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(
        description="List paths of collections of ROOT files in a directory and write them to a text file."
    )
    parser.add_argument(
        "base_dir",
        nargs="?",
        default=Path.home() / "SE_UserHome",
        type=Path,
        help="Base directory to search for ROOT file collections. Defaults to the SE_UserHome directory.",
    )
    parser.add_argument(
        "-o",
        "--output",
        default=Path(__file__).resolve().parent / "files.txt",
        type=Path,
        help="Output text file path. Defaults to files.txt next to this script.",
    )
    args = parser.parse_args()

    base_dir = args.base_dir.expanduser().resolve()
    out_path = args.output.expanduser().resolve()

    if not base_dir.is_dir():
        raise SystemExit(f"Base directory does not exist: {base_dir}")

    merged_paths = []
    for directory in base_dir.glob("HIForward*/*16Jan2024*/*/*/"):
        merged_paths.append(directory / "HiForestMiniAOD_*.root")

    if not merged_paths:
        print(f"No paths found under {base_dir}")
        return 0

    out_path.parent.mkdir(parents=True, exist_ok=True)
    with out_path.open("w", encoding="utf-8") as fp:
        for path in merged_paths:
            fp.write(f"{path}\n")

    print(f"Wrote {len(merged_paths)} paths to {out_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
