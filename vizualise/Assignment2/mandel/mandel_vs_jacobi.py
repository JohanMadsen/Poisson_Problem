import matplotlib.pyplot as plt

threads = [1, 2, 4, 8, 12, 16]
speedups = []
times = []
programs = ["../par/advanced/speedup_no_opt", "../par/advanced/speedup"]
labels = ["Jacobi optimized simple, no flags", "Jacobi optimized simple"]
plt.figure(figsize=(13, 8))
plt.xlabel("threads", fontsize=16)
plt.ylabel("Speedup", fontsize=16)
plt.title("Speedup for Jacobi vs. mandelbrot", fontsize=22)

for i in range(len(programs)):
    program = programs[i]
    label = labels[i]
    with open ("%s.txt" % program, "r") as f:
        for line in f.readlines():
            _, time , _, _, _ = line.split()
            print(float(time))
            times.append(float(time))
            speedups.append(times[0] / float(time))

    plt.plot(threads, speedups, label=label, marker='o')
    speedups.clear()
    times.clear()

with open ("par_mandelbrot.txt", "r") as f:
    for line in f.readlines():
        time, _  = line.split()
        print(float(time))
        times.append(float(time))
        speedups.append(times[0] / float(time))

plt.plot(threads, speedups, label="Mandelbrot", marker='o')


plt.plot(threads, threads, label="linear")
plt.legend()
plt.savefig("mandel_vs_jacobi.png")
plt.show()
