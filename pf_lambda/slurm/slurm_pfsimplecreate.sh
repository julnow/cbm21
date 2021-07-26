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
WORK=/lustre/cbm/users/$USER
paths=($WORK/pf_simple/bin/main*)
path=${paths[$INDEX-1]}
filenr=${path#/lustre/cbm/users/$USER/pf_simple/bin/main}
#make directory for each cutcos parameter
mkdir -p $PWD/SetCutCos/$filenr
cd $PWD/SetCutCos/$filenr
#run pf_simple on each file
$path $WORK/fileslist.txt
