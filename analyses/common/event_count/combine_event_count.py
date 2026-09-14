#!/usr/bin/env python3
"""
Combine the '% of previous' row from several per-dataset selection CSVs
(each produced by event_count.py, named e.g. event_count_<jobid>.csv)
into one summary CSV.

Step 1: build a table with
            rows    = dataset (jobid, taken from the filename)
            columns = selection category (Total entries, Passing HLT, ...)
            cells   = the percentage from that dataset's last row
Step 2: transpose it, so the final CSV has
            rows    = selection category
            columns = dataset (jobid)

Usage:
    python3 combine_event_count.py
"""

import csv
import glob
import os
import re
import sys


# The label used for the percentage row by event_count.py
SUM_ROW_LABEL = "SUM"
PCT_ROW_LABEL = "% of previous"

def read_row_by_label(path, label):
    """Return (category_names, {category: value_string}) for the row in
    `path` whose first cell matches `label`."""
    with open(path, newline="") as f:
        rows = list(csv.reader(f))

    if not rows:
        raise ValueError(f"{path} is empty")

    header = rows[0]
    categories = header[1:]

    target_row = None
    for r in rows[1:]:
        if r and r[0].strip() == label:
            target_row = r
            break
    if target_row is None:
        raise ValueError(f"Could not find a '{label}' row in {path}")

    values = target_row[1:]
    values += [""] * (len(categories) - len(values))

    return categories, dict(zip(categories, values))


def main():

    data_id = 242337
    beamA_id = 242335
    beamB_id = 242336
    jobids = [data_id, beamA_id, beamB_id]

    all_categories = None
    dataset_sum = {}  # jobid -> {category: sum_string}
    dataset_pct = {}  # jobid -> {category: pct_string}

    for jobid in jobids:
        path = "event_count_" + str(jobid) + ".csv"

        categories, pct = read_row_by_label(path, PCT_ROW_LABEL)
        _, summed = read_row_by_label(path, SUM_ROW_LABEL)

        if all_categories is None:
            all_categories = categories
        elif categories != all_categories:
            # Categories differ between files; keep the union, preserving
            # first-seen order, so nothing silently gets dropped.
            for c in categories:
                if c not in all_categories:
                    all_categories.append(c)

        dataset_pct[jobid] = pct
        dataset_sum[jobid] = summed

    # jobids = list(dataset_pct.keys())  # dataset order = file order

    # ---- transpose -> rows = category, columns = dataset --------
    sum_output = "event_count_summary.csv"
    with open(sum_output, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["category"] + jobids)
        for category in all_categories:
            row = [category] + [dataset_sum[j].get(category, "") for j in jobids]
            writer.writerow(row)

    print(f"Combined {len(jobids)} dataset(s) x {len(all_categories)} categories into {sum_output}")

    pct_output = "event_count_summary_percentage.csv"
    with open(pct_output, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["category"] + jobids)
        for category in all_categories:
            row = [category] + [dataset_pct[j].get(category, "") for j in jobids]
            writer.writerow(row)

    print(f"Combined {len(jobids)} dataset(s) x {len(all_categories)} categories into {pct_output}")


if __name__ == "__main__":
    main()