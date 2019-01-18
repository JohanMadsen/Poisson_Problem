import matplotlib.pyplot as plt

threads = [1, 2, 4, 8, 12, 16]
mem_fps = []
mflops = []
markers = ['o','x','+','v','s','*']
colors = ['b', 'g', 'r', 'y', 'c', 'm', 'w']
plt.figure(figsize=(13, 8))
plt.xlabel("Memory footprint in KB", fontsize=16)
plt.ylabel("MFlop/s", fontsize=16)
plt.title("Performance for different number of threads, for the advanced parallel version", fontsize=22)


for i in range(len(threads)):
    program = threads[i]
    with open ("adv_par/par_jacobi_advanced_%s.txt" % program, "r") as f:
        for line in f.readlines():
            mflop, _, mem_fp, _, _ = line.split()
            mem_fps.append(float(mem_fp))
            mflops.append(float(mflop))

    plt.semilogx(mem_fps, mflops, marker=markers[i], label="%s threads" % program, color=colors[i])
    plt.vlines(x=(32*program+1024*program), ymin=max(mflops)-10000, ymax=max(mflops)+10000, label="L1+L2-cache " + str(program) + " threads", color=colors[i], linewidth=2)
    mflops.clear()
    mem_fps.clear()

plt.axvline(x=(19712*2), label="L3-cache (with prefetch)", color="black", linewidth=2)
plt.legend(fontsize="x-large")
plt.tight_layout()
plt.savefig("jacobi_par_advanced.png")
plt.show()
