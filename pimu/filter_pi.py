#!/bin/python

outfile = open("evts_pi_period3.txt", 'w')
event = 0
for line in open("evts_period3.txt", 'r'):
    line_split = line.strip().split(' ')
    if len(line_split) == 2 or int(line_split[1]) != 211:
        continue
    outfile.write("{} 1\n".format(event))
    outfile.write(line)
    event += 1
outfile.close()
