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
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, LSTM, Conv1D, MaxPooling1D, Flatten, Reshape

class BinaryClassifierRNN:
    def __init__(self, input_size):
        self.model = Sequential([
            Reshape((input_size, 1), input_shape=(input_size,)),
            LSTM(64),
            Dense(32, activation='relu'),
            Dense(1, activation='sigmoid')
        ])
        self._compile()
    
    def _compile(self):
        self.model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
    
    def train(self, X_train, y_train, epochs=10, batch_size=32):
        X_reshaped = X_train.reshape(-1, X_train.shape[1], 1)
        self.history = self.model.fit(X_reshaped, y_train, epochs=epochs, batch_size=batch_size, verbose=0)
    
    def predict(self, X):
        X_reshaped = X.reshape(-1, X.shape[1], 1)
        return self.model.predict(X_reshaped, verbose=0)


class CombinedClassifier:
    def __init__(self, input_size, num_classifiers):
        self.classifiers = [BinaryClassifierRNN(input_size) for _ in range(num_classifiers)]
    
    def train(self, X_train, y_train, epochs=10, batch_size=32):
        for i, clf in enumerate(self.classifiers):
            clf.train(X_train, y_train[:, i], epochs=epochs, batch_size=batch_size)
    
    def predict(self, X):
        predictions = []
        for clf in self.classifiers:
            pred = clf.predict(X)
            predictions.append(pred.flatten())
        return np.column_stack(predictions)