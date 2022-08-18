#!/bin/env python

import os
import string
import samweb_client

SAM = samweb_client.SAMWebClient("nova")

# Open each of the files and save a dictionary of trigger condition for each run
trig_conditions = {}

for config_file in os.listdir("/nova/ana/users/wallbank/TestBeamConfig/"):

	run = config_file.strip().split('novabeamline_config_r')[1].split('.xml')[0]

    	ondict = {}
    	offdict = {}

        ff=open("/nova/ana/users/wallbank/TestBeamConfig/"+config_file,"r")
        trigcount=-1
        flag=0
        for line in ff:
            onlist=[]
            offlist=[]
            if string.count(line,"<trigpat")>0:
                flag=1
                trigcount+=1
                continue
            #                                                                                                                                          
            if string.count(line,"</trigpat")>0:
                flag=0
                continue
            #                                                                                                                                          
            if flag==0: continue
            #                                                                                                                                          
            line=string.lstrip(line)
            while string.count(line,"  ")>0: line=line.replace("  "," ")
            if string.find(line,"<on>")==0:
                line=line.replace("<on>","").replace("</on>","")
                line=string.lstrip(line); line=string.rstrip(line)
                linedata=line.split(" ")
                for item in linedata: onlist.append(item)
                if len(onlist)>0 and onlist[0]!="SPARE": ondict[trigcount]=onlist
            #                                                                                                                                          
            if string.find(line,"<off>")==0:
                line=line.replace("<off>","").replace("</off>","")
                line=string.lstrip(line); line=string.rstrip(line)
                linedata=line.split(" ")
                for item in linedata: offlist.append(item)
                if len(offlist)>0: offdict[trigcount]=offlist
            #                                                                                                                                          
        ff.close()

	pats=ondict.keys()
	pats.sort()

	if len(pats) == 1:
		trigger_condition = ""
		if len(ondict[0]) == 6 and "PADDLE1" in ondict[0] and "PADDLE2" in ondict[0] and "PADDLE3" in ondict[0] and "PADDLE4" in ondict[0]:
			trigger_condition = "Paddle4of4"
		elif len(ondict[0]) == 6 and "PAD1" in ondict[0] and "PAD2" in ondict[0] and "PAD3" in ondict[0] and "PAD4" in ondict[0]: 
			trigger_condition = "Paddle4of4"
		elif len(ondict[0]) == 3 and "PADDLECOINC4" in ondict[0]: 
			trigger_condition = "Paddle4of4"
		elif len(ondict[0]) == 3 and "PADDLES" in ondict[0]: 
			trigger_condition = "Paddle4of4"
		elif len(ondict[0]) == 3 and "TOFUS" in ondict[0]:
			trigger_condition = "ToFUS"
		elif len(ondict[0]) == 3 and "TOFDS1" in ondict[0]:
			trigger_condition = "ToFDS1"
		elif len(ondict[0]) == 3 and "TOFDS2" in ondict[0]:
			trigger_condition = "ToFDS2"
		elif len(ondict[0]) == 4 and "PADDLE3" in ondict[0] and "PADDLE4" in ondict[0]:
			trigger_condition = "Paddle3and4"
		elif len(ondict[0]) == 4 and "PADDLE2" in ondict[0] and "PADDLE3" in ondict[0]:
			trigger_condition = "Paddle2and3"
		elif len(ondict[0]) == 4 and "PADDLE1" in ondict[0] and "PADDLE2" in ondict[0]:
			trigger_condition = "Paddle1and2"
		elif len(ondict[0]) == 5 and "PADDLE2" in ondict[0] and "PADDLE3" in ondict[0] and "PADDLE4" in ondict[0]:
			trigger_condition = "Paddle2and3and4"
		elif len(ondict[0]) == 5 and "PADDLE1" in ondict[0] and "PADDLE3" in ondict[0] and "PADDLE4" in ondict[0]:
			trigger_condition = "Paddle1and3and4"
		elif len(ondict[0]) == 3 and "PADDLECOINC3" in ondict[0]:
			trigger_condition = "Paddle3of4"
		elif len(ondict[0]) == 3 and "WCCOINC3" in ondict[0]:
			trigger_condition = "WC3of4"
		elif len(ondict[0]) == 3 and "WCCOINC" in ondict[0]:
			trigger_condition = "WC3of4"
		elif len(ondict[0]) == 3 and "TOFPROMPT" in ondict[0]:
			trigger_condition = "ToFPrompt"
		elif len(ondict[0]) == 1 and "CKOV" in ondict[0]:
			trigger_condition = "Ckov"
		elif "FWPULSER" in ondict[0]:
			trigger_condition = "FWPulser"
		elif len(ondict[0]) == 3 and "TOFSLOW" in ondict[0]:
			trigger_condition = "ToFSlow"
		elif len(ondict[0]) == 3 and "WC1" in ondict[0]:
			trigger_condition = "WC1"
		elif len(ondict[0]) == 2 and "WC1" in ondict[0]:
			trigger_condition = "WC1"
		elif "TOFUS" in ondict[0]:
			trigger_condition = "ToFUS"
		elif len(ondict[0]) == 4 and "DSTOF1" in ondict[0] and "DSTOF2" in ondict[0]:
			trigger_condition = "ToFDS1and2"
		elif len(ondict[0]) == 3 and "TC" in ondict[0]:
			trigger_condition = "TargetScin"
		if trigger_condition == "":
			print ondict[0]
	else:
		trigger_condition = "ToFPromptORToFSlow"

	trig_conditions[int(run)] = trigger_condition
	#

for run in trig_conditions:
	print "Run", run, ":", trig_conditions[run]

# for f in SAM.listFiles(dimensions="defname: base_testbeam_beamline_period2"):

# 	print f

# 	metadata = SAM.getMetadata(f)
# 	run = metadata['Online.RunNumber']

# 	UPDATED_METADATA = {
# 		"Beamline.BeamlineTrigger": trig_conditions[run],
# 	}

# 	SAM.modifyFileMetadata(f, UPDATED_METADATA)
