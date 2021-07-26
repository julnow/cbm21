#!/bin/bash

#remote work on AnalysisTree
source /lustre/cbm/users/lubynets/soft/root-6/install-cpp11/bin/thisroot.sh
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lustre/cbm/users/$USER/AnalysisTree/install/lib/
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:/lustre/cbm/users/$USER/AnalysisTree/install/include/AnalysisTree
#for Pf_simple
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lustre/cbm/users/$USER/pf_simple/install/external/lib/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lustre/cbm/users/$USER/pf_simple/install/lib/
export AnalysisTree_DIR=/lustre/cbm/users/$USER/AnalysisTree/install/lib/cmake/AnalysisTree

INDEX=${SLURM_ARRAY_TASK_ID}
WORK=/lustre/cbm/users/$USER/pf_kaon

path=$WORK/pfsimple/${INDEX}/analysis_tree.root
output=$WORK/pfsimple/${INDEX}/read_init_all.root
#run pf_Read_init over each file from pfsimple
root -l -b -q "$WORK/pfRead_initial_all.c(\"$path\", \"$output\")" >& log_${INDEX}.txt
