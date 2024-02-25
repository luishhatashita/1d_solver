import numpy as np
import matplotlib
font  = {'family'       : 'sans-serif',
         'weight'       : 'normal',
         'size'         :  14,}
xtick = {'direction'    : 'in',
         'minor.visible': True,
         'top'          : True,}
ytick = {'direction'    : 'in',
         'minor.visible': True,
         'right'        : True,}
text  = {'usetex'       : True,}
matplotlib.rc('font' , **font )
matplotlib.rc('xtick', **xtick)
matplotlib.rc('ytick', **ytick)
matplotlib.rc('text' , **text )
import matplotlib.pyplot as plt

if __name__ == '__main__':
    y      = np.fromfile("./out/time-accurate/y_00000.bin", dtype=np.double)
    y      = y.reshape((101,))
    flows  = [0, 2500, 5000, 7500, 10000]
    trests = [0, 0.125, 0.25, 0.375, 0.5]
    fig, ax = plt.subplots(figsize=(8,6)) 
    for i, flow in enumerate(flows):
        fname = f"./out/time-accurate/flow_{flow:05d}.bin"
        data  = np.fromfile(fname, dtype=np.double)
        data  = data.reshape((101,))
        label = f"$t = {trests[i]:1.3f}$"
        ax.plot(data, y, label=label)
    ax.set(
        xlabel = r'$u \; [-]$',
        ylabel = r'$y \; [-]$',
    )
    ax.legend()
    fig.savefig('./out/time-accurate/solution.png', dpi=300)
    plt.close(fig)
