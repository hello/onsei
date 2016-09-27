import sys, os, glob
from scipy.io import loadmat, savemat
import numpy as np
import pdb

"""
python collect_wavrunner_epochs.py inDir outFile
"""

inDir = sys.argv[1]
outFile = sys.argv[2]+'.mat'

allFiles = glob.glob(os.path.join(inDir,'*.mat'))
allFiles.sort()

prob = []
for fn in allFiles:
    data = loadmat(fn)['prob']
    prob.append(data)

#prob = np.rollaxis(np.array(prob), 0, 3)
prob = np.array(prob)
savemat(outFile, {'prob':prob})
