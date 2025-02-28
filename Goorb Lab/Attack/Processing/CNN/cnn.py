"""
MIT License

Copyright (c) 2024 bistoyek(21)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

"""
import numpy as np
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Input, Dense, LSTM, Conv1D, MaxPooling1D, Flatten, Reshape

import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

class BinaryClassifier:
    def __init__(self, input_size):
        self.model = Sequential([
            Input(shape=(input_size,)),
            Reshape((input_size, 1)),
            Conv1D(32, 3, activation='relu'),
            MaxPooling1D(2),
            Flatten(),
            Dense(16, activation='relu'),
            Dense(1, activation='sigmoid')
        ])
        self._compile()
    
    def _compile(self):
        self.model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
    
    def train(self, X_train, y_train, epochs=10, batch_size=32):
        #X_train = tf.reshape(X_train, [-1, X_train.shape[1], 1])
        self.history = self.model.fit(X_train, y_train, epochs=epochs, batch_size=batch_size, verbose=0)
    
    def predict(self, X):
        X = tf.reshape(X, [-1, X.shape[1], 1])
        return self.model.predict(X, verbose=0)


class CombinedClassifier:
    def __init__(self, input_size, output_size):
        self.input_size = input_size
        self.output_size = output_size
        self.classifiers = [BinaryClassifier(input_size) for _ in range(output_size)]
    
    def train(self, X_train, y_train, epochs=10, batch_size=32):
        X_train = tf.convert_to_tensor(X_train)
        y_train = tf.convert_to_tensor(y_train)
        for i, clf in enumerate(self.classifiers):
            clf.train(X_train, y_train[i], epochs=epochs, batch_size=batch_size)
    
    def predict(self, X):
        X = tf.convert_to_tensor(X)
        predictions = np.zeros(shape=(X.shape[0], self.output_size))
        for i, clf in enumerate(self.classifiers):
            predictions[i] = clf.predict(X).flatten()
        return predictions


if __name__ == '__main__':
    processor = CombinedClassifier(5, 5)
    X = np.random.randint(0, 2, size=(5, 5)).astype(float)
    Y = np.random.randint(0, 2, size=(5, 5)).astype(float)
    X = tf.convert_to_tensor(X)
    print(X, flush=True)
    print(X[0])
    print('=' * 40)
    processor.train(X_train=X, y_train=Y)
    print('=' * 40)
    print(processor.predict(X))