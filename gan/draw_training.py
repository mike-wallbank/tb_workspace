# draw training examples

import sys
import h5py
from draw_pixelmaps import draw_map

if len(sys.argv) != 2:
    print("Usage: python draw_training.py <h5 training-formatted file>")
    exit()

inFile = h5py.File(sys.argv[1])
maps = inFile['cvnmap'][:]

draw_map(maps, "training_examples")
