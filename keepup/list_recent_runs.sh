PERIOD=4
TAG=R21-07-27-testbeam-production.a

count_files() {
    beamlineraw=$(samweb count-files "defname: raw_testbeam_detector_beamlinestream_period${PERIOD} and run_number $1")
    beamlineartdaq=$(samweb count-files "defname: artdaq_testbeam_beamlinestream_period${PERIOD}_${TAG} and run_number $1")
    beamlinepid=$(samweb count-files "defname: pid_testbeam_beamlinestream_period${PERIOD}_${TAG} and run_number $1")
    spillraw=$(samweb count-files "defname: raw_testbeam_detector_spill_period${PERIOD} and run_number $1")
    spillartdaq=$(samweb count-files "defname: artdaq_testbeam_detector_spill_period${PERIOD}_${TAG} and run_number $1")
    spillpid=$(samweb count-files "defname: pid_testbeam_detector_spill_period${PERIOD}_${TAG} and run_number $1")
}

recentdir=`ls -Art /pnfs/nova/rawdata/TestBeam/ | tail -1`
run=`ls -Art /pnfs/nova/rawdata/TestBeam/$recentdir | tail -1`

count_files $run
echo "Run $run has $beamlineraw raw, $beamlineartdaq artdaq and $beamlinepid pid beamline files; $spillraw raw, $spillartdaq artdaq and $spillpid pid spill files"
for (( i=0; i<$1; ++i )); do
    run=$(($run-1))
    count_files $run
    echo "Run $run has $beamlineraw raw, $beamlineartdaq artdaq and $beamlinepid pid beamline files; $spillraw raw, $spillartdaq artdaq and $spillpid pid spill files"
done
