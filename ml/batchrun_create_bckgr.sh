#!/bin/bash
LOGDIR=/lustre/cbm/users/$USER/ml/log
mkdir -p $LOGDIR
mkdir -p $LOGDIR/out
mkdir -p $LOGDIR/error

sbatch --job-name=pfsimplecreate \
        -t 00:20:00 \
        --partition main \
        --output=$LOGDIR/out/%j.out.log \
        --error=$LOGDIR/error/%j.err.log \
        --array 1-500 \
        -- $PWD/slurm_pfsimplecreate_bckgr.sh
