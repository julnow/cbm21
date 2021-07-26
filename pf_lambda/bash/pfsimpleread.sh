#!/bin/#!/usr/bin/env bash

#open root and its files
~/remote_AnalysisTree.sh
#slurm taks id
INDEX=${SLURM_ARRAY_TASK_ID}
#compare files in list
mkdir -p comparison
for path in ~/pf_results/lambda/*/pfinput.root
do
  #create root histograms file with folder name from pfinput
  folder=${path#~/pf_results/lambda/}
  folder=${folder%/pfinput.root}
  output=comparison/$folder".root"
  root -l -b -q "pfRead.c(\"$path\", \"$output\")" >& log_${INDEX}.txt
done
#run compareRootFiles
~/comparerootfiles/build/compareRootFiles -i comparison/*
