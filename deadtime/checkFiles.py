#!/bin/python

import sys, os

run = sys.argv[1]

nbeamline = os.popen("samweb count-files \"defname: pid_testbeam_beamlinestream_period3_R21-07-27-testbeam-production.a and run_number {}\"".format(run)).read()
beamlinefiles = os.popen("samweb list-files \"defname: pid_testbeam_beamlinestream_period3_R21-07-27-testbeam-production.a and run_number {}\"".format(run)).read().split()
nspill = os.popen("samweb count-files \"defname: pid_testbeam_detector_spill_period3_R21-01-28-testbeam-production.a and run_number {}\"".format(run)).read()
spillfiles = os.popen("samweb list-files \"defname: pid_testbeam_detector_spill_period3_R21-01-28-testbeam-production.a and run_number {}\"".format(run)).read().split()

for subrun in range(64):
    thisbeamlinesubrun = False
    for beamlinefile in beamlinefiles:
        if int(beamlinefile.strip().split('_')[2][1:]) == subrun:
               thisbeamlinesubrun = True
    thisspillsubrun = False
    for spillfile in spillfiles:
        if int(spillfile.strip().split('_')[2][1:]) == subrun:
               thisspillsubrun = True
    if thisbeamlinesubrun != thisspillsubrun:
        print("Subrun {}: beamline {}, spill {}".format(subrun, thisbeamlinesubrun, thisspillsubrun))
