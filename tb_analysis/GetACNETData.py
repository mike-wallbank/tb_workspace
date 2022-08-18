#!/usr/bin/env python
"""
  Return spill information for variety of MC7 devices.
  Teresa Lackey (lackey32@fnal.gov)
"""

import urllib.request as urllib2
import sys
import getopt
import csv
from datetime import date, datetime, timedelta
from operator import itemgetter

#.......................................................................
def unix_timestamp(input):
  """
    Convert a datetime to a unix timestamp
    Args:
    input : A datetime object

    Returns:
    difference : A unix timestamp
  """

  t0 = datetime(year = 1970, month = 1, day = 1)
  difference = input - t0

  # Return unix timestamp
  return difference.total_seconds()

#.......................................................................
def merge_max_mappings(*dicts):
    """ 
      Merges an arbitrary number of dictionaries based on the
      maximum value in a given mapping.

      Parameters
      ----------
      dicts : Dict[Any, Comparable]
      
      Returns
      -------
      Dict[Any, Comparable]
      The merged dictionary
    """

    merged = {}
    for d in dicts:  # `dicts` is a tuple storing the input dictionaries
        for key in d:
            if key not in merged or d[key] > merged[key]:
                merged[key] = d[key]
    return merged

#.......................................................................

def main():

  spills = {}

  # define times for query
  t0 = datetime(2021,5,2,0)
  t1 = datetime(2020,5,5,0)

  t0 = unix_timestamp(t0)
  t1 = unix_timestamp(t1)

  # device list you want to query
  #devices = {"F:MC6IC":"e,36", "F:MC7SC1":"e,36", "Z:NOVTSC01":"e,36"}
  devices = {"F:MC7AN1":"e,36"}
#  event = ["e,36,s,200", "e,36,e,0", "e,37,e,0"]
  
  print (("Querying database from {} to {}").format(datetime.utcfromtimestamp(t0).strftime('%Y-%m-%d %H:%M:%S UTC'),
                                                    datetime.utcfromtimestamp(t1).strftime('%Y-%m-%d %H:%M:%S UTC')))

  # loop over devices
  for device,event in devices.items():

    print (("Querying {} at event {}").format(device, event))

    # query IF Beam DB
    url = ('http://ifb-data.fnal.gov:8099/ifbeam/data/data?'\
        'v={}&e={}&t0={}&t1={}&f=csv').format(device,event,t0,t1)

    print(url)

    response = None
    try:
      response = urllib2.urlopen(url, None, 200)
    except:
      try:
        response = urllib2.urlopen(url, None, 200)
      except:
        try:
          response = urllib2.urlopen(url, None, 200)
        except:
          return spills

    csvdata = csv.reader(response)
    print (csvdata)

    # write value into dictionary
    for row in csvdata:
      if (row.count(device)>0):
        if (row[4] != 'null'):
          spill_time = float(row[2]) / 1000.
          if (spill_time in spills.keys()):
            time_array = spills[spill_time]
          else:
            time_array = []
          
          time_array.append( {'device': device, 'value': float(row[4])} )
          spills[spill_time] = time_array

  # Reformat dictionary to list of times and device values
  spill_array = []  
  for key in spills.keys():
    tmp_row = {}
    tmp_row['unix time [s]'] = key
    for device in spills[key]:
      tmp_row[device['device']] = device['value']
    spill_array.append(tmp_row)

  # sort by time
  spill_array = sorted(spill_array, key=itemgetter('unix time [s]'))

  # merge lines that are from the same spill
  # (Sets of devices recorded at slightly different times, 
  #  usually within 10s of ns of each other)
  spill_array_merged = []
  skipNextRow = False
  for i in range(len(spill_array)-1):
    if skipNextRow:
      skipNextRow = False
      continue

    row1 = spill_array[i]
    row2 = spill_array[i+1]
    
    if row2['unix time [s]'] - row1['unix time [s]'] < 1:
      spill_array_merged.append(merge_max_mappings(row1,row2))
      skipNextRow = True
    else:
      spill_array_merged.append(row1)
                                

  # write out info to csv
  csv_cols = devices.keys()
  csv_cols.insert(0,'unix time [s]')
  csv_file = "MC7_scalars.csv"

  try:
    with open (csv_file, 'w') as csvfile:
      writer = csv.DictWriter(csvfile, fieldnames=csv_cols)
      writer.writeheader()
      for data in spill_array_merged:
        writer.writerow(data)
  except IOError:
    print("I/O error")


#.......................................................................

if __name__ == "__main__":
  main()
