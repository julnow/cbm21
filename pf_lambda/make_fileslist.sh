#!/bin/bash

#list of files from simulation
#/lustre/cbm/users/lubynets/cbm2atree/outputs/apr21_fr_18.2.1_fs_jun19p1/dcmqgsm_smm_pluto_w/auau/12agev/mbias/sis100_electron_apr20_target_25_mkm/TGeant4/

: > fileslist.txt
for i in {1..100}
do
  echo /lustre/cbm/users/lubynets/cbm2atree/outputs_at2/apr20_fr_18.2.1_fs_jun19p1/dcmqgsm_smm_pluto_w/auau/12agev/mbias/sis100_electron_target_25_mkm/$i/$i.analysistree.root >> fileslist.txt
done
