import matplotlib.pyplot as plt

threads = [1, 2, 4, 8, 12, 16]
mem_fps = []
mflops = []
plt.figure(figsize=(13, 8))
plt.xlabel("Memory footprint in KB")
plt.ylabel("MFlop/s")
plt.title("Performance for different number of threads for the simple parallel version")


for program in threads:
    with open ("par_jacobi_%s.txt" % program, "r") as f:
        for line in f.readlines():
            mflop, _, mem_fp, _, _ = line.split()
            mem_fps.append(float(mem_fp))
            mflops.append(float(mflop))

    plt.semilogx(mem_fps, mflops, marker='o', label="%s threads" % program)
    mflops.clear()
    mem_fps.clear()


plt.axvline(x=1024, label="L2-cache", color="black")
plt.legend(fontsize="x-large")
plt.savefig("jacobi_par_simple.png")
plt.show()
