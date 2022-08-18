#!/bin/bash

FILES="testbeam*Beamline.raw" 

for file in $FILES
do
    export fname=$file
    fetch_tb_beamline_files.py
done