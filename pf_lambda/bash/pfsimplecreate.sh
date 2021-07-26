#!/bin/#!/usr/bin/env bash

#create inputfile from pfsimple
if [[ $# -eq 0 ]] ; then
    echo 'no name passed'
    exit 1
else
  mkdir -p ~/pf_results/lambda/$1
  cd ~/pf_results/lambda/$1
  ~/pf_simple/install/bin/main ~/fileslist.txt
fi
