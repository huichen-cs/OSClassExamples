"""Simple multiprogramming model"""

import os

import numpy as np
from matplotlib import pyplot as plt


def compute_cpu_utilization(io_waits, process_numbers):
    utilization = []
    for w in io_waits:
        utilization.append(1 - w**process_numbers)
    return np.array(utilization)


def setup_font_sizes():
    small_size = 14
    medium_size = 16
    big_size = 20
    plt.rc("font", size=small_size)  # controls default text sizes
    plt.rc("axes", titlesize=small_size)  # fontsize of the axes title
    plt.rc("axes", labelsize=medium_size)  # fontsize of the x and y labels

    plt.rc("xtick", labelsize=small_size)  # fontsize of the tick labels
    plt.rc("ytick", labelsize=small_size)  # fontsize of the tick labels
    plt.rc("legend", fontsize=small_size)  # legend fontsize
    plt.rc("figure", titlesize=big_size)  # fontsize of the figure title


def save_graph(graph_fn):
    figure_dir = "figures"
    os.makedirs(figure_dir, exist_ok=True)
    plt.savefig(os.path.join(figure_dir, graph_fn + ".pdf"))
    plt.savefig(os.path.join(figure_dir, graph_fn + ".pdf"))


def plot_graph(utilization, io_waits, process_numbers, graph_fn):
    setup_font_sizes()
    _, ax = plt.subplots(figsize=(8, 6))
    linestyles = ["-", "--", "-."]
    linewidths = [1, 1, 1]
    colors = ["k", "k", "k"]
    markers = ["o", "*", "."]
    markersizes = [6, 8, 6]
    markerfacecolors = ["none", "none", "k"]
    legends = []
    for io_wait, row, style, color, width, marker, size, facecolor in zip(
        io_waits,
        utilization,
        linestyles,
        colors,
        linewidths,
        markers,
        markersizes,
        markerfacecolors,
    ):
        ax.plot(
            process_numbers,
            row,
            linestyle=style,
            color=color,
            linewidth=width,
            marker=marker,
            markersize=size,
            markerfacecolor=facecolor,
        )
        legends.append(f"I/O Wait={int(io_wait * 100):2d}%")
    ax.legend(legends)
    ax.set_xlabel("Degree of Multiprogramming")
    ax.set_ylabel("CPU Utilization")
    plt.tight_layout()
    save_graph(graph_fn)
    plt.show()


if __name__ == "__main__":
    io_wait_list = np.array([0.2, 0.5, 0.8])
    num_process_range = np.array(range(0, 13))
    cpu_utilization = compute_cpu_utilization(io_wait_list, num_process_range)
    plot_graph(cpu_utilization, io_wait_list, num_process_range, "multiprogramming")
