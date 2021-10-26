#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Oct 25 14:37:56 2021

@author: simon
"""

#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct 16 17:51:12 2021

@author: simon
"""

import matplotlib.pyplot as plt
import numpy as np

ypoints = np.array([0, 0, 0, 17.5, 47.5, 100])
xpoints = np.array([0, 1, 10, 100, 500, 1000])

axes = plt.subplot()
axes.set_xscale("log")
axes.set_xlabel("Limit")
axes.set_ylabel("Hitrate in %")
axes.plot(xpoints, ypoints)