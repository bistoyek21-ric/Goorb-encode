/*
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

*/
#include<bits/stdc++.h>
using namespace std;

// Stirling's formula:
// fact(i) =  i * ln(i) - i + 0.5 * ln(2PIi)
// fact'(i) = ln(i) + 0.5/i

// Definition of F(i, k):
// F(i, k) = e(i) -> I ~ GOORB(n, k)

// F(i, k) and It's derivative by respect k in this problem the i is given:
// F(i, k) =  (k - i) * ln(n - 1) - (k - 1) * ln(n) + fact(k) - fact(i) - fact(k - i)
// F(i, k)/dk = ln(n - 1) - ln(n) + fact'(k) - fact'(k - i)

// Solution: At first we need know what is the pick of F(i, k) if the i is constant
// since the graph has exactly 1 local maximum the answer is bigger than pick. And
// it will be done by 2 binary searches consider to the approximated graph shape.

double fact(int64_t n){
    if(n <= 1)// fact(i) is a function for approximation of ln(i!)
        return 0;
    return n * log(n) - n + 0.5 * (log(2) + log(M_PI) + log(n));
}

int main(){
    cout << "Goorb encode Project\n";
    cout << "Author: Kasra Fouladi\n";
    cout << "Company: bistoyek(21)\n";
    cout << "Calculator of evac(i, epsilon) in I ~ GOORB(n, k)\n";
    while(true){
        int64_t n, i;
        double e;
        cout << "*inputs have to be valid*\n";
        cout << "n : ";
        cin >> n;
        cout << "i : ";
        cin >> i;
        cout << "epsilon : ";
        cin >> e;
        int64_t l = 2 * i, r = 1e18; // r = n * n * (i + 1) was the right upper bound but numbers are bounded in computers
        while(r - l > 1){
            int64_t mid = (r + l) / 2;
            // Checking when F(i, mid)/d(mid) will be non-positive
            if(log(mid) - log(mid - i) + 0.5/mid - 0.5/(mid - i) <= log(n) - log(n - 1))
                r = mid;
            else
                l = mid;
        }
        //   At first we simulated the graph with a function F: R^2 -> R but in fact k can only be non-negative integer
        // so there is still a chance that F(i, r) < F(i, r - 1) consider the fact that r can be real pick or it's ceil
        double maxpop0 = (r - 1 - i) * log(n - 1) - (r - 1 - 1) * log(n) + fact(r - 1) - fact(i) - fact(r - 1 - i);
        double maxpop1 = (r - i) * log(n - 1) - (r - 1) * log(n) + fact(r - 1) - fact(i) - fact(r - i);
        int integer_pick = r - 1;
        if(maxpop0 < maxpop1) // Comparison between F(i, r) and F(i, r - 1)
            integer_pick = r;
        cout << "-------------\n";
        cout << " pick of this place is in k = " << integer_pick << '\n';
        cout << " with this population ~= " << exp(max(maxpop0, maxpop1)) << '\n';
        if(max(maxpop0, maxpop1) < log(e)){
            cout << "-------------\n";
            cout << " -> evac(" << i << ", " << e << ") = " << 0 << '\n';
            cout << "___________________________________\n";
            continue;
        }
        l = integer_pick, r = 1e18;
        while(r - l > 1){
            int64_t mid = (r + l) / 2;
            if((mid - i) * log(n - 1) - (mid - 1) * log(n) + fact(mid) - fact(i) - fact(mid - i) <= log(e))
                r = mid;
            else
                l = mid;
        }
        int res = r;
        if((l - i) * log(n - 1) - (l - 1) * log(n) + fact(l) - fact(i) - fact(l - i) <= log(e))
            res = l;
        cout << "-------------\n";
        cout << " -> evac(" << i << ", " << e << ") = " << res << '\n';
        cout << "___________________________________\n";
    }
    return 0;
}
