#!/bin/bash
LOGDIR=/lustre/cbm/users/$USER/pf_results/log
mkdir -p $LOGDIR
mkdir -p $LOGDIR/out
mkdir -p $LOGDIR/error

sbatch --job-name=pfsimpleread \
        -t 00:20:00 \
        --partition main \
        --output=$LOGDIR/out/%j.out.log \
        --error=$LOGDIR/error/%j.err.log \
        --array 1-4 \
        -- $PWD/slurm_pfsimpleread.sh
