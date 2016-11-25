#!/bin/bash

EXEC="../../cmake-build-Release/bin/neurostr_benchmark"
OUTDIR="."

if [[ $# -lt 1 ]] ; then
    echo "Usage: xxx <input folder>"
    exit 1
fi

# Take data dir and discard argument
DATA_DIR=$1
shift

mkdir $OUTDIR

for file in $(find $DATA_DIR -type f) ; do

    # Extract filename
    filename=$(basename "$file")
    extension="${filename##*.}"
    filename="${filename%.*}"
    

    # Call script
    echo -n "Executing ${filename}..."
    $EXEC -i $file | python -m json.tool > "${OUTDIR}/${filename}_${extension}_benchmark.json"
    echo "Done. Output: ${OUTDIR}/${filename}_${extension}_benchmark.json"

done
