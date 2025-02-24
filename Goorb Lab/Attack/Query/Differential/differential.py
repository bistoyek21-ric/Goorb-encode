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

def bit_xor(a, b):
    return np.bitwise_xor(a, b)

def m_element_subsets(n, m):
    res = []
    a = np.zeros(n, dtype=int)
    def back_track(i, m):
        if i == n:
            if m == 0:
                res.append(a.copy())
            return
        if n - i < m:
            return
        if 0 < m:
            a[i] = 1
            back_track(i + 1, m - 1)
        if m <= n - i - 1:
            a[i] = 0
            back_track(i + 1, m)
    back_track(0, m)
    return np.array(res)

# differential queries
def get_queries(n, m, k):
    res = []
    queries = []
    for i in range(m):
        queries.extend(m_element_subsets(n, i))
    queries = np.array(queries)
    for _ in range(k):
        a = np.random.randint(0, 2, size=n)
        for i in range(m):
            for e in queries:
                res.append(bit_xor(a, e))
    return np.array(res).astype(float)

if __name__ == '__main__':
    print(get_queries(5, 3, 1))