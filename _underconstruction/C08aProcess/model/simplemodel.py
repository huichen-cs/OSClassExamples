import numpy as np
import os
from matplotlib import pyplot as plt

def compute_cpu_utilization(io_waits, process_numbers):
    utilization = [];
    for w in io_waits:
        utilization.append(1 - w**process_numbers)
    return np.array(utilization)

def setup_font_sizes():
    SMALL_SIZE = 14
    MEDIUM_SIZE = 16
    BIG_SIZE = 20
    plt.rc('font', size=SMALL_SIZE)          # controls default text sizes
    plt.rc('axes', titlesize=SMALL_SIZE)     # fontsize of the axes title
    plt.rc('axes', labelsize=MEDIUM_SIZE)    # fontsize of the x and y labels

    plt.rc('xtick', labelsize=SMALL_SIZE)    # fontsize of the tick labels
    plt.rc('ytick', labelsize=SMALL_SIZE)    # fontsize of the tick labels
    plt.rc('legend', fontsize=SMALL_SIZE)    # legend fontsize
    plt.rc('figure', titlesize=BIG_SIZE)     # fontsize of the figure title

def save_graph(graph_fn):
    figure_dir = 'figures'
    try:
        os.makedirs(figure_dir)
    except:
        pass
    plt.savefig(os.path.join(figure_dir, graph_fn + '.pdf'))
    plt.savefig(os.path.join(figure_dir, graph_fn + '.pdf'))
    
def plot_graph(utilization, io_waits, process_numbers, graph_fn):
    setup_font_sizes()
    _, ax = plt.subplots(figsize=(8, 6))
    linestyles = ['-', '--', '-.']
    linewidths = [1, 1, 1]
    colors = ['k', 'k', 'k']
    markers = ['o', '*', '.']
    markersizes = [6, 8, 6]
    markerfacecolors = ['none', 'none', 'k']
    legends = []
    for io_wait,row,style,color,width,marker,size,facecolor in zip(io_waits, utilization, linestyles, colors, linewidths, markers, markersizes, markerfacecolors):
        ax.plot(process_numbers, row, linestyle=style, color=color, linewidth=width, marker=marker, markersize=size, markerfacecolor=facecolor)
        legends.append('I/O Wait={0:2d}%'.format(int(io_wait*100)))
    ax.legend(legends)
    ax.set_xlabel('Degree of Multiprogramming')
    ax.set_ylabel('CPU Utilization')
    plt.tight_layout()
    save_graph(graph_fn)
    plt.show()

if __name__ == '__main__':
    io_waits = np.array([0.2, 0.5, 0.8])
    process_numbers = np.array(range(0, 13))
    utilization = compute_cpu_utilization(io_waits, process_numbers)
    plot_graph(utilization, io_waits, process_numbers, 'multiprogramming')
    