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
#path to pf simpled
pfpath=$WORK/pf_simple/mainkaon
#path to simulated files

#splitting into 500 fileslist with 10 files
mkdir -p $PWD/mainkaon
list=$PWD/mainkaon/filelist_${INDEX}.txt
: >  $list
for ((i=1+10*(INDEX-1); i<=10*INDEX; i++)); do
  echo /lustre/cbm/users/lubynets/cbm2atree/outputs/apr20_fr_18.2.1_fs_jun19p1/dcmqgsm_smm_pluto/auau/12agev/mbias/sis100_electron_target_25_mkm/AT2/$i/$i.analysistree.root >>  $list
done
mkdir -p $PWD/pfsimple/${INDEX}
cd $PWD/pfsimple/${INDEX}
#run pf_simple on each file
$pfpath $WORK/pf_kaon/mainkaon/filelist_${INDEX}.txt
