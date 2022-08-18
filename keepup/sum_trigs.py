from ROOT import *

inFile = TFile("/nova/ana/users/wallbank/TestBeam/KeepUpAna/SpillAna_r100986-r101249.root", "READ")
inTree = inFile.Get("spillana/spills")

runtree = inTree.CopyTree("SpillTime>=1611435873&&SpillTime<=1611478472")

ntrig = 0
ntrigsel = 0
ntrigseldeton = 0
for entry in runtree:

    ntrig += entry.MC7Trig
    ntrigsel += entry.TrigSel
    ntrigseldeton += entry.TrigSelDetOnBit

print "Number triggers", ntrig, ", selected", ntrigsel, ", deton ", ntrigseldeton
