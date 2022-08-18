#!/bin/python

# beam_ana.py
# Analyze the beam!

import ROOT
import sys

# Graphs for ratios
gMC7SC1Ratio = ROOT.TGraph()
gNOVTSC01Ratio = ROOT.TGraph()

with open(sys.argv[1], 'r') as csv_input:
    for line in csv_input:
        data = line.strip().split(',')
        if "unix" in data[0]: continue

        # Order of columns in file
        # unix time [s],F:MC6IC,Z:NOVTSC01,F:MC7SC1
        if not data[2]: continue
        if float(data[1]) == 0: continue

        gMC7SC1Ratio.SetPoint(gMC7SC1Ratio.GetN(), float(data[0]), float(data[3])/float(data[1]))
        gNOVTSC01Ratio.SetPoint(gNOVTSC01Ratio.GetN(), float(data[0]), float(data[2])/float(data[1]))

# Simulation
simMC7SC1Ratio = float(938)/float(5e6)
simNOVTSC01Ratio = float(847)/float(5e6)

gRatios = ROOT.TMultiGraph("Ratios",";Time (unix);Ratio to MC6IC;")
leg = ROOT.TLegend(0.7,0.7,0.85,0.85)
gMC7SC1Ratio.SetMarkerColor(ROOT.kBlack)
gMC7SC1Ratio.SetLineColor(ROOT.kBlack)
gRatios.Add(gMC7SC1Ratio)
leg.AddEntry(gMC7SC1Ratio, "MC7SC1", "l")
gNOVTSC01Ratio.SetMarkerColor(ROOT.kRed)
gNOVTSC01Ratio.SetLineColor(ROOT.kRed)
gRatios.Add(gNOVTSC01Ratio)
leg.AddEntry(gNOVTSC01Ratio, "NOVTSC01", "l")
gRatios.Draw("AP")
leg.Draw()

line = ROOT.TLine()
xmin = gMC7SC1Ratio.GetXaxis().GetXmin()
xmax = gMC7SC1Ratio.GetXaxis().GetXmax()
line.SetLineColor(ROOT.kBlack)
line.DrawLine(xmin, simMC7SC1Ratio, xmax, simMC7SC1Ratio)
line.SetLineColor(ROOT.kRed)
line.DrawLine(xmin, simNOVTSC01Ratio, xmax, simNOVTSC01Ratio)

raw_input()
