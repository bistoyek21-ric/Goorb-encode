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

def __main__():
    price = [0, 0]
    attack_type, supply, price[0], price[1], dir = open('./description.txt', 'r').read().split()
    
    supply = int(supply)
    price[0] = int(price[0])
    price[1] = int(price[1])
    
    print(supply, flush=True)
    print(price[0], flush=True)
    print(price[0], flush=True)

    input_bits = int(input())
    output_size = int(input())

    output_bits = 0
    num = 1
    while num < output_size:
        num *= 2
        output_bits += 1

    X_train = []
    y_train = []

    if attack_type == 1 or attack_type == 2:
        if attack_type == 1:
            queries = get_queries(input_bits, 12, 16)
        else:
            sum = 1 + input_bits + input_bits * (input_bits - 1) // 2
            queries = get_queries(input_bits, 3,  2**17 // sum)

        # building: X_train, y_train

    elif attack_type == 3:
        queries = get_queries(input_bits, output_size, supply // price[1])

        # building: X_train, y_train

    processor = CombinedClassifier(input_size=input_bits, num_classifiers=output_bits)
    
    processor.train(X_train=X_train, y_train=y_train)

    for i in range(10000):
        cipher_block = input()
        X = []
        for e in cipher_block:
            if e == '1':
                X.append(1.0)
            else:
                X.append(0.0)
        prd = processor.predict(np.array(X))
        ans = 0
        for e in prd:
            ans = (ans * 2) + e
        print(ans, flush=True)

    accuracy = int(input()) / 10000.0

    # supply,x,y,accuracy
    with open(dir + 'results.csv', 'w+', newline='') as f:
        writer = csv.writer(f, delimiter=',')
        writer.writerow([supply, price[0], price[1], accuracy])

    return
    
if __name__ == '__main__':
    __main__()