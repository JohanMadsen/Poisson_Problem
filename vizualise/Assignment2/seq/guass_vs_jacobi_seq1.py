import matplotlib.pyplot as plt

times = []
iterations = []
programs = ["jacobi", "gauss"]
ns = []

plt.figure(figsize=(13, 8))
plt.xlabel("N")
plt.ylabel("Iterations")
plt.title("Iterations needed for converging (Sequential)")

for program in programs:
    with open ("seq_%s.txt" % program, "r") as f:
        for line in f.readlines():
            _, time, _, iteration, n = line.split()
            iterations.append(float(iteration))
            ns.append(int(n))
        plt.plot(ns, iterations, label=program, marker='o')
        iterations.clear()
        ns.clear()

plt.legend(fontsize="xx-large")
plt.savefig("gauss_vs_jacobi_seq2.png")
plt.show()
