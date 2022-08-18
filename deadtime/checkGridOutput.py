#!/bin/python

import sys, os, glob, datetime

definition = sys.argv[1]
directory = sys.argv[2]
identifier = sys.argv[3]

def_files = os.popen("samweb list-definition-files {}".format(definition)).read().split()
dir_files = [os.path.basename(filename) for filename in glob.glob("{}/testbeam_*.root".format(directory))]

print("Definition {} has {} files; directory {} contains {}".format(definition, len(def_files), directory, len(dir_files)))

missing_runs = []
for i,def_file in enumerate(def_files):
    if i % 100 == 0:
        print("Analyzing file {} of {}".format(i, len(def_files)))
    def_run = def_file.split('_')[1]
    def_subrun = def_file.split('_')[2]
    def_file_in_dir = False
    for dir_file in dir_files:
        dir_run = dir_file.split('_')[1]
        dir_subrun = dir_file.split('_')[2]
        if dir_run == def_run and dir_subrun == def_subrun:
            def_file_in_dir = True;
    if not def_file_in_dir:
        print("Run {}, subrun {} missing in directory {}".format(def_run, def_subrun, directory))
        missing_runs.append([def_run, def_subrun])

missing_runs_string = ""
for i,missing_run in enumerate(missing_runs):
    missing_runs_string += "(run_number "+missing_run[0][1:]+" and online.subrun "+missing_run[1][1:]+")"
    if i < len(missing_runs)-1:
        missing_runs_string += " or "

print("Making definition for missing files...")
os.system("samweb create-definition wallbank_{}_deadtime-{}-drain_{} \"defname: {} and ({})\""
          .format(definition, identifier, datetime.date.today(), definition, missing_runs_string))
