import numpy as np
import matplotlib
font  = {'family'       : 'serif',
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
    VNN_case = "VNN_05"
    y      = np.fromfile(f"./out/time-marching/{VNN_case}/y_00000.bin", dtype=np.double)
    y      = y.reshape((101,))
    flows  = [0, 20000, 40000, 60000, 80000]
    trests = [0, 1.0, 2.0, 3.0, 4.0]
    fig1, ax1 = plt.subplots(figsize=(8,6)) 
    for i, flow in enumerate(flows):
        fname = f"./out/time-marching/{VNN_case}/flow_{flow:05d}.bin"
        data  = np.fromfile(fname, dtype=np.double)
        data  = data.reshape((101,))
        label = f"$t = {trests[i]:1.3f}$"
        ax1.plot(data, y, label=label)
    ax1.set(
        xlabel = r'$u \; [-]$',
        ylabel = r'$y \; [-]$',
    )
    ax1.legend()
    fig1.savefig(f'./out/time-marching/{VNN_case}/solution.png', dpi=300)
    plt.close(fig1)

    fig2, ax2 = plt.subplots(figsize=(8,6))
    L2     = np.fromfile(f"./out/time-marching/{VNN_case}/L2_80000.bin", dtype=np.double)
    Linfty = np.fromfile(f"./out/time-marching/{VNN_case}/Linfty_80000.bin", dtype=np.double)
    L2nonan = L2[~np.isnan(L2)]
    L2nonannoinf = L2nonan[~np.isinf(L2nonan)]
    Linftynonan = Linfty[~np.isnan(Linfty)]
    Linftynonannoinf = Linftynonan[~np.isinf(Linftynonan)]
    if VNN_case == "VNN_06":
        Linftynonannoinf = Linftynonannoinf[np.nonzero(Linftynonannoinf)]
    #print(L2nonannoinf.size, Linftynonannoinf.size)
    ax2.plot(L2nonannoinf, 'k')
    ax2.plot(Linftynonannoinf, 'k--')
    ax2.set(
        xlabel = 'Iteration', 
        ylabel = r'$\parallel u_j^{q+1} - u_j^{q} \parallel_2 \;, \parallel u_j^{q+1} - u_j^{q} \parallel_\infty$', 
        yscale = 'log',
        ylim   = (1e-16, 1e5),
    )
    fig2.savefig(f'./out/time-marching/{VNN_case}/error_norms.png', dpi=300)
    plt.close(fig2)

    VNN_cases = ["VNN_01", "VNN_03", "VNN_05", "VNN_06"]
    VNNs      = [0.1, 0.3, 0.5, 0.6]
    fig3, ax3 = plt.subplots(figsize=(8,6))
    for i, VNN_case in enumerate(VNN_cases):
        L2     = np.fromfile(f"./out/time-marching/{VNN_case}/L2_80000.bin", dtype=np.double)
        L2nonan = L2[~np.isnan(L2)]
        L2nonannoinf = L2nonan[~np.isinf(L2nonan)]
        ax3.plot(L2nonannoinf, label=f'VNN = {VNNs[i]}')
    ax3.set(
        xlabel = 'Iteration', 
        ylabel = r'$\parallel u_j^{q+1} - u_j^{q} \parallel_2$', 
        yscale = 'log',
        ylim   = (1e-16, 1e5),
    )
    ax3.legend()
    fig3.savefig(f'./out/time-marching/L2_norms.png', dpi=300)
    plt.close(fig3)

    fig4, ax4 = plt.subplots(figsize=(8,6))
    for i, VNN_case in enumerate(VNN_cases):
        Linfty = np.fromfile(f"./out/time-marching/{VNN_case}/Linfty_80000.bin", dtype=np.double)
        Linftynonan = Linfty[~np.isnan(Linfty)]
        Linftynonannoinf = Linftynonan[~np.isinf(Linftynonan)]
        if VNNs[i] == 0.6:
            Linftynonannoinf = Linftynonannoinf[np.nonzero(Linftynonannoinf)]
        ax4.plot(Linftynonannoinf, label=f'VNN = {VNNs[i]}')
    ax4.set(
        xlabel = 'Iteration', 
        ylabel = r'$\parallel u_j^{q+1} - u_j^{q} \parallel_\infty$', 
        yscale = 'log',
        ylim   = (1e-16, 1e5),
    )
    ax4.legend()
    fig4.savefig(f'./out/time-marching/Linfty_norms.png', dpi=300)
    plt.close(fig4)
