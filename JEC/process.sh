#!/bin/bash
set -e

echo "===== Job starting on $(hostname) ====="
date

echo "PWD: $(pwd)"
echo "Arguments:"
echo "  Input file : $1"
echo "  Output file: $2"

INPUTFILE=$1
OUTPUTFILE=$2

# ----------------------------------------------------------------------

source /cvmfs/sft.cern.ch/lcg/releases/LCG_106a/ROOT/6.32.06/x86_64-el9-gcc13-opt/ROOT-env.sh
cd /u/user/lidakal/UPC2023/upcJetAnalysis/JEC/

# ----------------------------------------------------------------------

echo "===== Running ROOT macro ====="
root -b -q plot_from_jra.C\(\"$INPUTFILE\",\"$OUTPUTFILE\"\)

EXITCODE=$?

echo "ROOT exit code: $EXITCODE"
date
echo "===== Job finished ====="

exit $EXITCODE