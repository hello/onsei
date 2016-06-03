#!/usr/bin/python
import numpy as np
N = 400

h = np.hanning(N) * 1.0
x = np.round(h * 32767)

print ','.join(x.astype(int).astype(str).tolist())
