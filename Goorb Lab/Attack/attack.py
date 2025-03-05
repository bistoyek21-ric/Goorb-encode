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
from Processing.selected_processing_strategy import *
from Query.selected_query_strategy import *
import csv

def standard_cipher_block(a):
    res = ''
    for e in a:
        if e == 1:
            res += '1'
        else:
            res += '0'
    return res

def standard_plain_block(a):
    res = 0
    for e in a:
        res <<= 1
        if 0.5 <= e:
            res += 1
    return res

def vectorize_plain_block(s, output_bits):
    v = np.zeros(output_bits)
    for i in range(output_bits):
        if (1 << i) & s != 0:
            v[output_bits - i - 1] = 1
    return v

def vectorize_cipher_block(s, input_bits):
    v = np.zeros(input_bits)
    for i in range(len(s)):
        if s[i] == '1':
            v[i] = 1
    return v


def __main__():
    price = [0, 0]
    attack_type, supply, price[0], price[1], dir = open('./description.txt', 'r').read().split('\n')

    attack_type = int(attack_type)
    supply = int(supply)
    price[0] = int(price[0])
    price[1] = int(price[1])
    
    print(supply, flush=True)
    print(price[0], flush=True)
    print(price[1], flush=True)

    input_bits = int(input())
    output_bits = int(input())

    X_train = []
    y_train = []

    if attack_type == 1 or attack_type == 2:
        if attack_type == 1:
            queries = get_queries(input_bits, 9, supply // (511 * price[0]) + 1)
        else:
            sum = 1 + input_bits
            queries = get_queries(input_bits, 2, supply // (sum * price[0]) + 1)
        tmp = supply
        for query in queries:
            if tmp < price[0]:
                break
            tmp -= price[0]
            print(1, flush=True)
            response = input()
            print(standard_cipher_block(query))
            X_train.append(query)
            y_train.append(vectorize_plain_block(int(input()), output_bits))

    elif attack_type == 3:
        queries = get_queries(input_bits, output_bits, supply // price[1])
        tmp = supply
        for query in queries:
            if tmp < price[1]:
                break
            tmp -= price[1]
            print(2, flush=True)
            response = input()
            print(standard_plain_block(query))
            y_train.append(query)
            X_train.append(vectorize_cipher_block(input(), input_bits))
    
    X_train = np.array(X_train)
    y_train = np.array(y_train)

    processor = CombinedClassifier(input_size=input_bits, output_size=output_bits)
    
    processor.train(X_train=X_train, y_train=y_train)

    response = input()
    X = np.zeros(shape=(10000, input_bits))
    for i in range(10000):
        X[i] = vectorize_cipher_block(input(), input_bits)
    
    predictions = processor.predict(np.array(X))

    for i in range(10000):
        print(standard_plain_block(predictions[i]), flush=True)
    
    accuracy = int(input()) / 10000.0

    with open(dir + '/results.csv', 'a', newline='') as f:
        writer = csv.writer(f, delimiter=',')
        writer.writerow([supply, price[0], price[1], accuracy])
    
    return
    
if __name__ == '__main__':
    tf.get_logger().setLevel('ERROR')
    __main__()