export fname=testbeam_r00$1_s$2_beamline_R21-07-27-testbeam-production.a_v1_data.tbreco.root

ifdh_fetch $fname
../test_testbeam/novaprod/NovaGridUtils/bin/testbeam_beamline_spill_mix.sh 
