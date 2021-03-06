#!/bin/bash
LOGDIR=/lustre/cbm/users/$USER/pf_kaon/log
mkdir -p $LOGDIR
mkdir -p $LOGDIR/out
mkdir -p $LOGDIR/error

sbatch --job-name=pfreadcutall \
        -t 00:20:00 \
        --partition main \
        --output=$LOGDIR/out/%j.out.log \
        --error=$LOGDIR/error/%j.err.log \
        --array 1-1000 \
        -- $PWD/slurm_pfread_cut_all.sh
