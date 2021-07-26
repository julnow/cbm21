#!/bin/bash

#list of files from simulation
#/lustre/cbm/users/lubynets/cbm2atree/outputs/apr20_fr_18.2.1_fs_jun19p1/dcmqgsm_smm_pluto/auau/12agev/mbias/sis100_electron_target_25_mkm/AT2

: > fileslist.txt
for i in {1..5000}
do
  echo /lustre/cbm/users/lubynets/cbm2atree/outputs/apr20_fr_18.2.1_fs_jun19p1/dcmqgsm_smm_pluto/auau/12agev/mbias/sis100_electron_target_25_mkm/AT2/$i/$i.analysistree.root >> fileslist.txt
done
