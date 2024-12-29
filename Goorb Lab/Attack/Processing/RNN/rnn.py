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

# Import necessary libraries
import numpy as np
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import SimpleRNN, Dense
from tensorflow.keras.optimizers import Adam

class MultiModelRNN:
    def __init__(self, l, input_dim, timesteps):
        self.l = l
        self.models = []
        self.input_dim = input_dim
        self.timesteps = timesteps
        # Create l models
        for _ in range(l):
            model = Sequential()
            model.add(SimpleRNN(64, input_shape=(timesteps, input_dim), activation='relu', return_sequences=True))
            model.add(SimpleRNN(64, activation='relu'))
            model.add(Dense(1, activation='sigmoid'))
            model.compile(loss='binary_crossentropy', optimizer=Adam(learning_rate=0.001), metrics=['accuracy'])
            self.models.append(model)
    
    def train(self, X, y_list, epochs=10, batch_size=32):
        for i in range(self.l):
            self.models[i].fit(X, y_list[:, i], epochs=epochs, batch_size=batch_size)
    
    def predict(self, X):
        predictions = np.zeros((X.shape[0], self.l))
        for i in range(self.l):
            predictions[:, i] = self.models[i].predict(X).flatten()
        return predictions

if __name__ == '__main__':
    # Number of models
    l = 5
    # Input dimension
    input_dim = 20
    # Number of timesteps
    timesteps = 10
    # Create instance of the class
    multi_model = MultiModelRNN(l, input_dim, timesteps)
    # Generate dummy data
    X = np.random.rand(1000, timesteps, input_dim)
    y_list = np.random.randint(2, size=(1000, l))
    # Train the models
    multi_model.train(X, y_list, epochs=10, batch_size=32)
    # Predict with the models
    predictions = multi_model.predict(X)
    print(predictions)
