#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct 16 17:51:12 2021

@author: simon
"""

import matplotlib.pyplot as plt
import numpy as np

xpoints = np.array([0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000])
ypoints = np.array([0, 0, 50, 133, 250, 400, 583, 800, 1050, 1333, 1650])

plt.plot(xpoints, ypoints)
plt.ylabel("AVG-Response Time")
plt.xlabel("Länge letzter Job")
plt.show()