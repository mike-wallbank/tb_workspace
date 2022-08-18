import sys, os, time, requests
from datetime import datetime, timedelta
from ROOT import *
import numpy as np

deviceName = "MC6IC"
deviceAddress = "F:MC6IC"
url='http://www-bd.fnal.gov/cgi-bin/acl.pl?acl=logger_get/double/start=12-JAN-2021/end=08-APR-2021/date_format=utc_seconds/device='+deviceAddress
print url
url_query = requests.get(url)
content = url_query.content

outFile = open("{}_Data.txt".format(deviceName), 'w')
for line in content.splitlines():
    line_split = line.split()
    tm = datetime.fromtimestamp(float(line_split[0]))
    outFile.write("{} {}\n".format(float(line_split[0]), float(line_split[1])))
outFile.close()
