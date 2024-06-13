import matplotlib.pyplot as plt
import numpy as np

file = open("./cmake-build-debug/matrixGraph.csv", "r")


powers = []
time = []

for line in file:
    parts = line.split(",")
    powers.append(parts[0])
    time.append(parts[1])
    
fig, ax = plt.subplots()
ax.plot(powers, time)
plt.title("powers vs time")
plt.xlabel("Powers of 2")
plt.ylabel("Time (s)")
plt.show()