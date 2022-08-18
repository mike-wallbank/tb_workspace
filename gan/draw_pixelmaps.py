import h5py
import matplotlib.pyplot as plt
import numpy as np

inFile = h5py.File('gan_reco_1000.h5caf.h5', 'r')

maps = inFile['rec.training.cvnmaps']['cvnmap']

fig = plt.figure(constrained_layout=True)
width=3; height=2
subfigs = fig.subfigures(width, height)
for i in range(width*height):
    map_i = maps[i]
    map_i_shape = map_i.reshape(2, 100, 80)

    axs = subfigs[i%width][int(i/width)].subplots(2, 1)
    axs[0].imshow(map_i_shape[0].T, cmap='gray_r', aspect='auto')
    axs[0].set_ylabel('X Pixel No.')
    axs[0].set_xlabel('Z Pixel No.')
    axs[0].set_xlim(0,20)
    axs[0].set_ylim(20,60)
    axs[1].imshow(map_i_shape[1].T, cmap='gray_r', aspect='auto')
    axs[1].set_ylabel('Y Pixel No.')
    axs[1].set_xlabel('Z Pixel No.')
    axs[1].set_xlim(0,20)
    axs[1].set_ylim(20,60)

plt.show()
