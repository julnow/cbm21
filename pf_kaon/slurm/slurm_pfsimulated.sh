#!/bin/bash

source /lustre/cbm/users/lubynets/soft/root-6/install-cpp11/bin/thisroot.sh
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lustre/cbm/users/$USER/AnalysisTree/install/lib/
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:/lustre/cbm/users/$USER/AnalysisTree/install/include/AnalysisTree/
#for Pf_simple
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lustre/cbm/users/$USER/pf_simple/install/external/lib/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lustre/cbm/users/$USER/pf_simple/install/lib/

WORK=/lustre/cbm/users/$USER/pf_kaon
#slurm taks id
INDEX=${SLURM_ARRAY_TASK_ID}
#INDEX=1
mkdir -p $PWD/kaons_simulated
path=/lustre/cbm/users/lubynets/cbm2atree/outputs/apr20_fr_18.2.1_fs_jun19p1/dcmqgsm_smm_pluto/auau/12agev/mbias/sis100_electron_target_25_mkm/AT2/$INDEX/${INDEX}.analysistree.root
#create root histograms file with folder name from pfinput
output=$PWD/kaons_simulated/histogram${INDEX}.root
root -l -b -q "$WORK/newpfSimulated.c(\"$path\", \"$output\")" >& log_${INDEX}.txt
#run compareRootFiles
