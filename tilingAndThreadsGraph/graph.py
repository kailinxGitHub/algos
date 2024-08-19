import matplotlib.pyplot as plt
import numpy as np

file = open("./cmake-build-debug/threadScaling.csv", "r")

threads = []
time = []

for line_number, line in enumerate(file):
    if line_number == 0:
        continue
    
    parts = line.split(",")
    thread_count = int(parts[0])
    if thread_count % 2 == 0:
        threads.append(thread_count)
        time.append(float(parts[1]))

fig, ax = plt.subplots()
ax.plot(threads, time)
plt.title("Threads vs Time")
plt.xlabel("Threads")
plt.ylabel("Time (s)")
ax.set_aspect(aspect='auto')
plt.xscale('log', base=2)
plt.show()
