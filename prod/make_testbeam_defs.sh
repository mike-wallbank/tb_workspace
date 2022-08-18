# Script to make all the relevant test beam definitions

# This assumes the base definitions (with run numbers) have been updated
# -- base_testbeam_detector_epochXX
# -- base_testbeam_beamline_epochXX

echo
echo "Making definitions for $1, tag $2"

# # base
# echo
# samweb create-definition base_testbeam_detector_beamlinestream_$1 "defname: base_testbeam_detector_$1 and online.stream beamline"
# echo "base_testbeam_detector_beamlinestream_$1 created; number of files"
# samweb count-definition-files base_testbeam_detector_beamlinestream_$1

# echo
# samweb create-definition base_testbeam_detector_activity_$1 "defname: base_testbeam_detector_$1 and online.stream ddactivity1"
# echo "base_testbeam_detector_activity_$1 created; number of files"
# samweb count-definition-files base_testbeam_detector_activity_$1

# echo
# samweb create-definition base_testbeam_detector_axisactivity_$1 "defname: base_testbeam_detector_$1 and online.stream ddactivity2"
# echo "base_testbeam_detector_axisactivity_$1 created; number of files"
# samweb count-definition-files base_testbeam_detector_axisactivity_$1

# echo
# samweb create-definition base_testbeam_detector_spill_$1 "defname: base_testbeam_detector_$1 and online.stream spill"
# echo "base_testbeam_detector_spill_$1 created; number of files"
# samweb count-definition-files base_testbeam_detector_spill_$1

# # raw
# echo
# samweb create-definition raw_testbeam_detector_beamlinestream_$1 "defname: base_testbeam_detector_beamlinestream_$1 and data_tier raw"
# echo "raw_testbeam_detector_beamlinestream_$1 created; number of files"
# samweb count-definition-files raw_testbeam_detector_beamlinestream_$1

# echo
# samweb create-definition raw_testbeam_detector_activity_$1 "defname: base_testbeam_detector_activity_$1 and data_tier raw"
# echo "raw_testbeam_detector_activity_$1 created; number of files"
# samweb count-definition-files raw_testbeam_detector_activity_$1

# echo
# samweb create-definition raw_testbeam_detector_axisactivity_$1 "defname: base_testbeam_detector_axisactivity_$1 and data_tier raw"
# echo "raw_testbeam_detector_axisactivity_$1 created; number of files"
# samweb count-definition-files raw_testbeam_detector_axisactivity_$1

# echo
# samweb create-definition raw_testbeam_detector_spill_$1 "defname: base_testbeam_detector_spill_$1 and data_tier raw"
# echo "raw_testbeam_detector_spill_$1 created; number of files"
# samweb count-definition-files raw_testbeam_detector_spill_$1

# echo
# samweb create-definition raw_testbeam_beamline_$1 "defname: base_testbeam_beamline_$1 and data_tier raw"
# echo "raw_testbeam_beamline_$1 created; number of files"
# samweb count-definition-files raw_testbeam_beamline_$1

# # artdaq
# echo
# samweb create-definition artdaq_testbeam_beamlinestream_$1_$2 "defname: base_testbeam_detector_beamlinestream_$1 and data_tier artdaq and nova.release $2"
# echo "artdaq_testbeam_beamlinestream_$1_$2 created; number of files"
# samweb count-definition-files artdaq_testbeam_beamlinestream_$1_$2

# echo
# samweb create-definition artdaq_testbeam_detector_activity_$1_$2 "defname: base_testbeam_detector_activity_$1 and data_tier artdaq and nova.release $2"
# echo "artdaq_testbeam_detector_activity_$1_$2 created; number of files"
# samweb count-definition-files artdaq_testbeam_detector_activity_$1_$2

# echo
# samweb create-definition artdaq_testbeam_detector_axisactivity_$1_$2 "defname: base_testbeam_detector_axisactivity_$1 and data_tier artdaq and nova.release $2"
# echo "artdaq_testbeam_detector_axisactivity_$1_$2 created; number of files"
# samweb count-definition-files artdaq_testbeam_detector_axisactivity_$1_$2

# echo
# samweb create-definition artdaq_testbeam_detector_spill_$1_$2 "defname: base_testbeam_detector_spill_$1 and data_tier artdaq and nova.release $2"
# echo "artdaq_testbeam_detector_spill_$1_$2 created; number of files"
# samweb count-definition-files artdaq_testbeam_detector_spill_$1_$2

# echo
# samweb create-definition artdaq_testbeam_beamline_$1_$2 "defname: base_testbeam_beamline_$1 and data_tier artdaq and nova.release $2"
# echo "artdaq_testbeam_beamline_$1_$2 created; number of files"
# samweb count-definition-files artdaq_testbeam_beamline_$1_$2

# # reco
# echo
# samweb create-definition pid_testbeam_beamlinestream_$1_$2 "defname: base_testbeam_detector_beamlinestream_$1 and data_tier tbreco and nova.release $2"
# echo "pid_testbeam_beamlinestream_$1_$2 created; number of files"
# samweb count-definition-files pid_testbeam_beamlinestream_$1_$2

# echo
# samweb create-definition pid_testbeam_detector_spill_$1_$2 "defname: base_testbeam_detector_spill_$1 and data_tier tbreco and nova.release $2"
# echo "pid_testbeam_detector_spill_$1_$2 created; number of files"
# samweb count-definition-files pid_testbeam_detector_spill_$1_$2

# echo
# samweb create-definition pid_testbeam_beamline_$1_$2 "defname: base_testbeam_beamline_$1 and data_tier tbblreco and nova.release $2"
# echo "pid_testbeam_beamline_$1_$2 created; number of files"
# samweb count-definition-files pid_testbeam_beamline_$1_$2

# # pclist
# echo
# samweb create-definition pclist_testbeam_detector_activity_$1_$2 "defname: base_testbeam_detector_activity_$1 and data_tier pclist and nova.release $2"
# echo "pclist_testbeam_detector_activity_$1_$2 created; number of files"
# samweb count-definition-files pclist_testbeam_detector_activity_$1_$2

# echo
# samweb create-definition pcliststop_testbeam_detector_activity_$1_$2 "defname: base_testbeam_detector_activity_$1 and data_tier pcliststop and nova.release $2"
# echo "pcliststop_testbeam_detector_activity_$1_$2 created; number of files"
# samweb count-definition-files pcliststop_testbeam_detector_activity_$1_$2

# caf
echo
samweb create-definition caf_testbeam_$1_$2 "defname: base_testbeam_detector_$1 and data_tier caf and nova.release $2"
echo "caf_testbeam_$1_$2 created; number of files"
samweb count-definition-files caf_testbeam_$1_$2
