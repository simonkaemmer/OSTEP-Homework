#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct 16 17:51:12 2021

@author: simon
"""

import matplotlib.pyplot as plt
import numpy as np

ypoints = np.array([0.5, 0.5, 0.75, 0.8, 0.93, 0.99])
xpoints = np.array([1, 2, 4, 10, 100, 1000])

axes = plt.subplot()
axes.set_xscale("log")
axes.plot(xpoints, ypoints)