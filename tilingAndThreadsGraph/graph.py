import matplotlib.pyplot as plt
import numpy as np

file = open("./cmake-build-debug/threadScaling.csv", "r")


threads = []
time = []

for line_number, line in enumerate(file):
    if line_number == 0:
        continue
    
    parts = line.split(",")
    threads.append(int(parts[0]))
    time.append(float(parts[1]))
    
fig, ax = plt.subplots()
ax.plot(threads, time)
plt.title("threads vs time")
plt.xlabel("threads")
plt.ylabel("Time (s)")
ax.set_aspect(aspect='auto')
plt.show()