import sys
from matplotlib import pyplot as plt

if len(sys.argv) != 3:
    print("""
Usage: python plot_properties.py <original file> <smeared file>
    exit
""")

prop = {}
prop['x'], prop['y'], prop['z'], prop['px'], prop['py'], prop['pz'], prop['e'] = {}, {}, {}, {}, {}, {}, {}

for i in range(2):

    prop['x'][i], prop['y'][i], prop['z'][i], prop['px'][i], prop['py'][i], prop['pz'][i], prop['e'][i] \
        = list(), list(), list(), list(), list(), list(), list()

    for line in open(sys.argv[i+1], 'r'):

        if line.startswith('#'):
            continue

        line_split = line.split()
        if len(line_split) == 2:
            continue

        prop['x'][i].append(float(line_split[11]))
        prop['y'][i].append(float(line_split[12]))
        prop['z'][i].append(float(line_split[13]))
        prop['px'][i].append(float(line_split[6]))
        prop['py'][i].append(float(line_split[7]))
        prop['pz'][i].append(float(line_split[8]))
        prop['e'][i].append(float(line_split[9]))

for property in prop:
    plt.hist(prop[property][0], color="black", histtype="step", label="original")
    plt.hist(prop[property][1], color="red", histtype="step", label="smeared")
    plt.xlabel(property)
    plt.legend()
    plt.savefig("plots/{}.png".format(property))
    plt.clf()
