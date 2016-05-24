from __future__ import absolute_import
from keras.utils import np_utils
from keras.models import model_from_json
import numpy as np
import os
from scipy.io import loadmat
import pdb

def load_model(defFile, weightFile):
    # as per http://keras.io/faq/#how-can-i-save-a-keras-model

    model = model_from_json(open(defFile).read())
    model.load_weights(weightFile)

    return model

def load_batch(filePath, var='mfc'):
    data = loadmat(filePath)
    data = data[var]
    data = np.rollaxis(data, 2)
    data = data.reshape(data.shape[0], 1, data.shape[1], data.shape[2])

    return data

def load_sequence_batch(filePath, var='features'):
    data = loadmat(filePath)
    data = data[var]
    data = data.swapaxes(1,2)

    return data

def permute_pair(X, y):

    perm = np.random.permutation(X.shape[0])
    X = X[perm, ...]
    y = y[perm]

    return X, y

def split_pair(X, y, testSplit):

    splitIdx = np.int(X.shape[0] * (1-testSplit))
    (feaTrain, feaTest) = np.array_split(X, [splitIdx], axis=0)
    (labelTrain, labelTest) = np.array_split(y, [splitIdx], axis=0)

    return feaTrain, labelTrain, feaTest, labelTest

def load_training(inFiles, dataVar, modelType, testSplit=0.1, negRatioTrain=10, negRatioTest=1, normalize=False, permuteBeforeSplit=(True,True)):

    if modelType=='convnet':
        data_loader = load_batch
    elif modelType=='sequence':
        data_loader = load_sequence_batch

    # pos
    feaTrainPos = data_loader(inFiles[0], dataVar)
    labelTrainPos = np.ones((feaTrainPos.shape[0],), dtype='uint8')

    # neg
    feaTrainNeg = data_loader(inFiles[1], dataVar)
    labelTrainNeg = np.zeros((feaTrainNeg.shape[0],), dtype='uint8')

    # permute before split
    if permuteBeforeSplit[0]: # pos
        (feaTrainPos, labelTrainPos) = permute_pair(feaTrainPos, labelTrainPos)
    if permuteBeforeSplit[1]: # neg
        (feaTrainNeg, labelTrainNeg) = permute_pair(feaTrainNeg, labelTrainNeg)

    # trim negatives to a given multiple of the number of positives
    numNeg = np.min((np.int(feaTrainPos.shape[0] * negRatioTrain), feaTrainNeg.shape[0]))
    feaTrainNeg = feaTrainNeg[:numNeg, ...]
    labelTrainNeg = labelTrainNeg[:numNeg]

    # split
    # . pos
    (feaTrainPos, labelTrainPos, feaTestPos, labelTestPos) = split_pair(feaTrainPos, labelTrainPos, testSplit)
    # . neg
    (feaTrainNeg, labelTrainNeg, feaTestNeg, labelTestNeg) = split_pair(feaTrainNeg, labelTrainNeg, testSplit)

    # rebalance for test set
    numNegTest = np.min((np.int(feaTestPos.shape[0] * negRatioTest), feaTestNeg.shape[0]))
    feaTestNeg = feaTestNeg[:numNegTest, ...]
    labelTestNeg = labelTestNeg[:numNegTest]

    # join pos & neg into train & test sets
    feaTrain = np.concatenate((feaTrainPos, feaTrainNeg), axis=0)
    labelTrain = np.concatenate((labelTrainPos, labelTrainNeg), axis=0)
    feaTest = np.concatenate((feaTestPos, feaTestNeg), axis=0)
    labelTest = np.concatenate((labelTestPos, labelTestNeg), axis=0)

    labelTrain = np.reshape(labelTrain, (len(labelTrain), 1))
    labelTest = np.reshape(labelTest, (len(labelTest), 1))

    # convert class vectors to binary class matrices
    labelTrain = np_utils.to_categorical(labelTrain, 2)
    labelTest = np_utils.to_categorical(labelTest, 2)

    # normalization
    if normalize:
        feaTrain = np.float64(feaTrain)

        feaMean = np.mean(feaTrain)
        feaTrain -= feaMean
        feaTrain = np.float32(feaTrain)
        feaMax = np.max(np.abs(feaTrain))
        feaTrain /= feaMax

        feaTest = np.float64(feaTest)
        feaTest -= feaMean
        feaTest = np.float32(feaTest)
        feaTest /= feaMax
	pdb.set_trace()
    else:
        feaTrain = (np.float32(feaTrain)+6)/10# / 255
        feaTest = (np.float32(feaTest)+5)/10# / 255

    return (feaTrain, labelTrain), (feaTest, labelTest)
