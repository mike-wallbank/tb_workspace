#!/bin/env python

import os
import string

for config_file in os.listdir("/nova/ana/users/wallbank/TestBeamConfig/"):

	run = config_file.strip().split('novabeamline_config_r')[1].split('.xml')[0]

        with open('/pnfs/nova/archived_logs/testbeam/beamlineconfig/tmp_{}.json'.format(run), 'w') as jsonfile:
                jsonfile.write("""
{{
    \"file_name\" : \"{}\",
    \"file_size\": {},
    \"file_type\" : \"nonPhysicsGeneric\",
    \"file_format\" : \"text\",
    \"data_tier\" : \"configuration\",
    \"online.detector\" : \"testbeam-beamline\",
    \"online.runnumber\" : {},
    \"runs\": [ [ {}, \"online\" ] ]
}}
                """.format(config_file.strip(), os.path.getsize("/nova/ana/users/wallbank/TestBeamConfig/{}".format(config_file.strip())), int(run), int(run)))

## for file in `ls tmp_*.json`; do run=$(echo $file | cut -d'_' -f 2 | cut -d'.' -f 1); samweb declare-file $file; samweb add-file-location novabeamline_config_r${run}.xml `pwd`; done
