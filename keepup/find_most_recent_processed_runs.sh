count_files() {
    beamlineraw=$(samweb count-files "defname: raw_testbeam_detector_beamlinestream_period3 and run_number $1")
    beamlinepid=$(samweb count-files "defname: pid_testbeam_beamlinestream_period3_R21-01-28-testbeam-production.a and run_number $1")
    spillraw=$(samweb count-files "defname: raw_testbeam_detector_spill_period3 and run_number $1")
    spillpid=$(samweb count-files "defname: pid_testbeam_detector_spill_period3_R21-01-28-testbeam-production.a and run_number $1")
}

recentdir=`ls -Art /pnfs/nova/rawdata/TestBeam/ | tail -1`
run=`ls -Art /pnfs/nova/rawdata/TestBeam/$recentdir | tail -1`

count_files $run
echo "Run $run has $beamlineraw raw and $beamlinepid pid beamline files; $spillraw raw and $spillpid pid spill files"
while [[ $beamlineraw -eq 0 || $spillraw -eq 0 || $beamlineraw -ne $beamlinepid || $spillraw -ne $spillpid ]]; do
    run=$(($run-1))
    count_files $run
    echo "Run $run has $beamlineraw raw and $beamlinepid pid beamline files; $spillraw raw and $spillpid pid spill files"
done

echo $run
