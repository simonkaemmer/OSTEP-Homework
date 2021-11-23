#!/usr/bin/env python3


# Author: Simon Kaemmer


import matplotlib.pyplot as plt

# Plotting data
xax = [1, 2, 4, 8, 16, 32]
yaxLRU = [50.52, 85.27, 94.06, 97.35, 98.52, 99.73]
yaxOPT = [50.77, 85.53, 95.71, 98.16, 99.18, 99.87]
yaxFIFO = [50.77, 79.04, 92.32, 96.54, 98.09, 99.49]
yaxCLOCK = [50.77, 80.94, 93.06, 96.92, 98.41, 99.66]
axes = plt.subplot()
axes.set_xscale("symlog", base=2)
axes.set_xlabel("Number of Cache-Pages")
axes.set_ylabel("HitRate")
axes.plot(xax, yaxLRU, "r", label="LRU")
axes.plot(xax, yaxOPT, "g", label="OPT")
axes.plot(xax, yaxFIFO, "b", label="FIFO")
axes.plot(xax, yaxCLOCK, "y", label="CLOCK")
axes.legend()
plt.savefig('plot.png')
plt.show()
