from keras.models import Sequential
from keras.layers.core import Dense, Dropout, Activation, Flatten
from keras.layers.convolutional import Convolution2D, MaxPooling2D
from keras.layers.recurrent import LSTM
from keras.optimizers import SGD

def model_may25_lstm_small(inputShape, numClasses):

    optimizer = 'rmsprop'
    #optimizer = SGD(lr=0.1, decay=0.0, momentum=0.9, nesterov=True)
    loss = 'categorical_crossentropy'

    model = Sequential()

    model.add(LSTM(32, return_sequences=True, input_shape=inputShape))
    #model.add(Dropout(0.2))
    model.add(LSTM(16, return_sequences=False))
    #model.add(Dropout(0.2))
    model.add(Dense(numClasses))
    model.add(Activation('softmax'))

    return model, optimizer, loss

def model_may25_lstm_large(inputShape, numClasses):

    optimizer = 'rmsprop'
    loss = 'categorical_crossentropy'

    model = Sequential()

    model.add(LSTM(64, return_sequences=True, input_shape=inputShape))
    model.add(Dropout(0.2))
    model.add(LSTM(64, return_sequences=False))
    model.add(Dropout(0.2))
    model.add(Dense(numClasses))
    model.add(Activation('softmax'))

    return model, optimizer, loss

def model_may24_large(inputShape, numClasses):

    #optimizer = SGD(lr=0.01, decay=0.0, momentum=0.9, nesterov=True)
    optimizer = 'rmsprop'
    loss = 'categorical_crossentropy'

    model = Sequential()

    model.add(Convolution2D(16, 3, 5, border_mode='same', input_shape=inputShape))
    model.add(Activation('relu'))

    model.add(Convolution2D(16, 3, 5))
    model.add(Activation('relu'))

    model.add(MaxPooling2D(pool_size=(2, 3)))
    model.add(Dropout(0.25))

    model.add(Convolution2D(32, 1, 3)) # best 64 or 32
    model.add(Activation('relu'))

    model.add(Convolution2D(32, 1, 3)) # best 64 or 32
    model.add(Activation('relu'))

    model.add(MaxPooling2D(pool_size=(1, 3)))
    model.add(Dropout(0.25))

    # New part
    model.add(Convolution2D(64, 1, 3)) # best 64 or 32
    model.add(Activation('relu'))

    model.add(Convolution2D(64, 1, 3)) # best 64 or 32
    model.add(Activation('relu'))

    model.add(MaxPooling2D(pool_size=(1, 3)))
    model.add(Dropout(0.25))
    # end new part

    model.add(Flatten())

    model.add(Dense(1024))
    model.add(Activation('relu'))
    model.add(Dropout(0.5))

    model.add(Dense(1024))
    model.add(Activation('relu'))
    model.add(Dropout(0.5))

    model.add(Dense(numClasses))
    model.add(Activation('softmax'))

    return model, optimizer, loss

def model_may24_small(inputShape, numClasses):

    #optimizer = SGD(lr=0.003, decay=0.0, momentum=0.9, nesterov=True)
    optimizer = 'rmsprop'
    loss = 'categorical_crossentropy'

    model = Sequential()

    model.add(Convolution2D(16, 3, 5, border_mode='same', input_shape=inputShape))
    model.add(Activation('relu'))

    model.add(MaxPooling2D(pool_size=(2, 3)))
    model.add(Dropout(0.25))

    model.add(Convolution2D(32, 1, 3)) # best 64 or 32
    model.add(Activation('relu'))

    model.add(MaxPooling2D(pool_size=(1, 3)))
    model.add(Dropout(0.25))

    # New part
    model.add(Convolution2D(32, 1, 3)) # best 64 or 32
    model.add(Activation('relu'))

    model.add(MaxPooling2D(pool_size=(1, 3)))
    model.add(Dropout(0.25))
    # end new part

    model.add(Flatten())

    model.add(Dense(512))
    model.add(Activation('relu'))
    model.add(Dropout(0.5))

    model.add(Dense(512))
    model.add(Activation('relu'))
    model.add(Dropout(0.5))

    model.add(Dense(numClasses))
    model.add(Activation('softmax'))

    return model, optimizer, loss


def model_may31_small_sigm(inputShape, numClasses):

    #optimizer = SGD(lr=0.003, decay=0.0, momentum=0.9, nesterov=True)
    optimizer = 'rmsprop'
    loss = 'mse'

    model = Sequential()

    model.add(Convolution2D(16, 3, 5, border_mode='valid', input_shape=inputShape))
    model.add(Activation('relu'))

    model.add(MaxPooling2D(pool_size=(2, 3)))
    model.add(Dropout(0.25))

    model.add(Convolution2D(32, 1, 3, border_mode='valid')) # best 64 or 32
    model.add(Activation('relu'))

    model.add(MaxPooling2D(pool_size=(1, 3)))
    model.add(Dropout(0.25))

    # New part
    model.add(Convolution2D(32, 1, 3, border_mode='valid')) # best 64 or 32
    model.add(Activation('relu'))

    model.add(MaxPooling2D(pool_size=(1, 3)))
    model.add(Dropout(0.25))
    # end new part

    model.add(Flatten())

    model.add(Dense(512))
    model.add(Activation('relu'))
    model.add(Dropout(0.5))

    model.add(Dense(512))
    model.add(Activation('relu'))
    model.add(Dropout(0.5))

    model.add(Dense(numClasses))
    model.add(Activation('sigmoid'))

    return model, optimizer, loss

