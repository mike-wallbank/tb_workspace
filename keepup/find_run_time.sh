# find time of a run from the raw file metadata

# get list of raw files
files=`samweb list-files "online.detector testbeam and data_tier raw and data_stream spill and run_number $1"`

starttime=1e10
endtime=0
for file in $files; do
    filestarttime=`samweb get-metadata $file | grep -i online.subrunstarttime | cut -d":" -f2`
    fileendtime=`samweb get-metadata $file | grep -i online.subrunendtime | cut -d":" -f 2`
    if [[ $filestarttime < $starttime ]]; then starttime=$filestarttime; fi
    if [[ $fileendtime > $endtime ]]; then endtime=$fileendtime; fi
done
echo "Run $1 start and end times:"
echo $starttime
echo $endtime
date -d "@$starttime"
date -d "@$endtime"
