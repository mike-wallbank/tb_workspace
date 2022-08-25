import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import numpy as np

def draw_map(maps, name):

    fig = plt.figure(constrained_layout=True)

    width=3; height=2
    #subfigs = fig.subfigures(width, height)
    event_grid = gridspec.GridSpec(width, height)

    for i in range(width*height):
        map_i = maps[i]
        if map_i.shape[0] == 16000:
            map_i_shape = map_i.reshape(2, 100, 80)
            map_i_shape = map_i_shape[:,0:32,24:56]
        else:
            map_i_shape = map_i

        #axs = subfigs[i%width][int(i/width)].subplots(2, 1)
        view_grid = gridspec.GridSpecFromSubplotSpec(2, 1,
                                                     subplot_spec = event_grid[i],
                                                     wspace=0.1, hspace=0.1)
        axs = list()
        axs.append(plt.Subplot(fig, view_grid[0]))
        axs.append(plt.Subplot(fig, view_grid[1]))

        axs[0].imshow(map_i_shape[0].T, cmap='gray_r', aspect='auto')
        axs[0].set_ylabel('X')
        axs[0].set_xlabel('Z Pixel No.')
        axs[0].set_xlim(0,20)
        axs[0].set_ylim(0,32) if map_i_shape[0].shape[1] == 32 else axs[0].set_ylim(20,60)
        fig.add_subplot(axs[0])
        if map_i_shape.shape[0] == 2:
            axs[1].imshow(map_i_shape[1].T, cmap='gray_r', aspect='auto')
            axs[1].set_ylabel('Y')
            axs[1].set_xlabel('Z Pixel No.')
            axs[1].set_xlim(0,20)
            axs[1].set_ylim(0,32) if map_i_shape[1].shape[1] == 32 else axs[1].set_ylim(20,60)
            fig.add_subplot(axs[1])

    plt.savefig('figs/{}.png'.format(name))
