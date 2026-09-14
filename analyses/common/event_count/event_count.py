#!/usr/bin/env python3
"""
Parse a directory of ROOT-macro log .txt files and collect the selection
numbers ("Total entries", "Entries passing HLT", etc.) into a single CSV.

Each row in the CSV = one input file.
Columns          = one selection category each.
Last two rows    = column-wise SUM, and the selection efficiency (%) of
                   each column relative to the column immediately to its
                   left (computed from the SUM row).

Usage:
    python3 event_count.py jobId
    eg. python3 event_count.py 242337
"""

import argparse
import csv
import glob
import os
import re
import sys

# Ordered list of (column_name, regex). Order matters: it defines both the
# column order in the CSV and the "previous column" used for the percentage
# row. Add/remove/edit entries here if your logs have different categories.
CATEGORY_PATTERNS = [
    ("Total entries",              r"Total entries:\s*(\d+)"),
    ("Passing HLT",                r"Entries passing HLT:\s*(\d+)"),
    ("Passing ZDC",                r"Entries passing ZDC:\s*(\d+)"),
    ("Passing Jet Kinematics",     r"Entries passing Jet Kinematics:\s*(\d+)"),
    ("Passing Jet ID",             r"Entries passing Jet ID:\s*(\d+)"),
    ("Passing Jet Veto Map",       r"Entries passing Jet Veto Map:\s*(\d+)"),
    ("Passing Additional Activity", r"Entries passing Additional Activity:\s*(\d+)"),
    ("Passing HF",                 r"Entries passing HF:\s*(\d+)"),
    ("Passing RG",                 r"Entries passing RG:\s*(\d+)"),
]


def parse_file(path):
    """Return a dict {category_name: int_value_or_None} for one log file."""
    with open(path, "r", errors="ignore") as f:
        text = f.read()

    row = {}
    for name, pattern in CATEGORY_PATTERNS:
        m = re.search(pattern, text)
        row[name] = int(m.group(1)) if m else None
    return row


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("jobId", help="Condor job id")
    args = ap.parse_args()

    jobId = str(args.jobId)
    files = sorted(glob.glob(os.path.join("../log/", "job_"+jobId+"_*.out")))
    if not files:
        print(f"No files matching '{jobId}' found in log/", file=sys.stderr)
        sys.exit(1)

    category_names = [name for name, _ in CATEGORY_PATTERNS]
    header = ["file"] + category_names

    rows = []  # list of dicts: {"file": ..., category: value_or_None}
    for path in files:
        parsed = parse_file(path)
        parsed["file"] = os.path.basename(path)
        rows.append(parsed)
        missing = [name for name in category_names if parsed[name] is None]
        if missing:
            print(f"Warning: {os.path.basename(path)} is missing: {', '.join(missing)}",
                  file=sys.stderr)

    # ---- Sum row -------------------------------------------------------
    sums = {}
    for name in category_names:
        vals = [r[name] for r in rows if r[name] is not None]
        sums[name] = sum(vals) if vals else None

    # ---- Percentage row (relative to previous column, using the sums) --
    pct = {}
    for i, name in enumerate(category_names):
        if i == 0:
            pct[name] = ""  # no "previous" column for the first one
            continue
        prev_name = category_names[i - 1]
        prev_val = sums[prev_name]
        cur_val = sums[name]
        if prev_val:  # avoid division by zero / None
            pct[name] = f"{100.0 * cur_val / prev_val:.2f}%"
        else:
            pct[name] = ""

    # ---- Write CSV -------------------------------------------------------
    output = "event_count_"+jobId + ".csv"
    with open(output, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(header)
        for r in rows:
            writer.writerow([r["file"]] + [r[name] if r[name] is not None else "" for name in category_names])
        writer.writerow(["SUM"] + [sums[name] if sums[name] is not None else "" for name in category_names])
        writer.writerow(["% of previous"] + [pct[name] for name in category_names])

    print(f"Wrote {len(rows)} file rows + SUM + % row to {output}")


if __name__ == "__main__":
    main()