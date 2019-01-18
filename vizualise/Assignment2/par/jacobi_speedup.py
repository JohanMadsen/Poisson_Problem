import matplotlib.pyplot as plt

threads = [1, 2, 4, 8, 12, 16]
speedups = []
times = []
markers = ['o','x','+','v','s','*','P']
colors = ['b', 'g', 'r', 'y', 'c', 'm', 'k']

plt.figure(figsize=(13, 8))
plt.xlabel("threads", fontsize=16)
plt.ylabel("Speedup", fontsize=16)
plt.title("Speedup as function of number of threads", fontsize=22)


with open("advanced/speedup.txt", "r") as f:
    for line in f.readlines():
        _, time, _, _, _ = line.split()
        times.append(float(time))
        speedups.append(times[0] / float(time))

plt.plot(threads, speedups, label="Optimized simple", marker=markers[0], color=colors[0])
speedups.clear()
times.clear()

with open ("advanced/speedup_no_opt.txt", "r") as f:
    for line in f.readlines():
        _, time, _, _, _ = line.split()
        times.append(float(time))
        speedups.append(times[0] / float(time))

plt.plot(threads, speedups, label="Optimized simple. No compiler optimization", marker=markers[1], color=colors[1])
speedups.clear()
times.clear()

with open ("simple/speedup_jacobi.txt", "r") as f:
    for line in f.readlines():
        _, time, _, _, _ = line.split()
        times.append(float(time))
        speedups.append(times[0] / float(time))

plt.plot(threads, speedups, label="Naive", marker=markers[2], color=colors[2])
speedups.clear()
times.clear()

with open("advanced/sim/adv_par_jacobi_speed_up_un_optim.txt", "r") as f:
    for line in f.readlines():
        _, time, _, _, _ = line.split()
        times.append(float(time))
        speedups.append(times[0] / float(time))

plt.plot(threads, speedups, label="Optimized advanced. No compiler optimization", marker=markers[3], color=colors[3])
speedups.clear()
times.clear()

with open("advanced/sim/adv_par_jacobi_speed_up.txt", "r") as f:
    for line in f.readlines():
        _, time, _, _, _ = line.split()
        times.append(float(time))
        speedups.append(times[0] / float(time))

plt.plot(threads, speedups, label="Optimized advanced.", marker=markers[4], color=colors[4])
speedups.clear()
times.clear()

with open("../mandel/par_mandelbrot.txt", "r") as f:
    for line in f.readlines():
        time, _ = line.split()
        times.append(float(time))
        speedups.append(times[0] / float(time))

plt.plot(threads, speedups, label="Mandelbot", marker=markers[5], color=colors[5])
speedups.clear()
times.clear()

f = 0.99791553758285738108141910201359
amdahls = [1.0 / (f/i) + 1.0-f for i in threads]
plt.plot(threads, amdahls, label="Theoretical speedup", marker=markers[6], color=colors[6], linewidth=2.5)
plt.legend()
plt.tight_layout()
plt.savefig("jacobi_speedup.png")
plt.show()

