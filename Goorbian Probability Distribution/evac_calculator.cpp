#include<bits/stdc++.h>
using namespace std;

// Stirling's formula:
// fact(i) =  i * ln(i) - i + ln(2PIi)
// fact'(i) = ln(i) + 1/i

// Definition of F(i, k):
// F(i, k) = e(i) -> I ~ GOORB(n, k)

// F(i, k) and It's derivative by respect k in this problem the i is given:
// F(i, k) =  (k - i) * ln(n - 1) - (k - 1) * ln(n) + fact(k) - fact(i) - fact(k - i)
// F(i, k)/dk = ln(n - 1) - ln(n) + k'fact'(k) - (k - i)'fact'(k - i)

// Solution: At first we need know what is the pick of F(i, k) if the i is constant
// since the graph has exactly 1 local maximum the answer is bigger than pick. And
// it will be done by 2 binary searches consider to the approximated graph shape.

double fact(int64_t n){
    if(n <= 1)// fact(i) is a function for approximation of ln(i!)
        return 0;
    return (n + 1) * (log(n) - 1) + log(2 * M_PI) + 1;
}

int main(){
    cout << "Goorb encode Project\n";
    cout << "Author: Kasra Fouladi\n";
    cout << "Company: bistoyek(21)\n";
    cout << "Calculator of evac(i, epsilon) in I ~ GOORB(n, k)\n";
    while(true){
        int64_t n, i;
        double e;
        cout << "n : ";
        cin >> n;
        cout << "i : ";
        cin >> i;
        cout << "epsilon: ";
        cin >> e;
        int64_t l = 0, r = 1e18; // r = max(1e18, n * n * i) was the right upper bound but numbers are bounded in computers
        while(r - l > 1){
            int64_t mid = (r + l) / 2;
            // Checking when F(i, mid)/d(mid) will be non-positive
            if(log(mid) - log(mid - i) + 1.0/mid - 1.0/(mid - i) <= log(n) - log(n - 1))
                r = mid;
            else
                l = mid;
        }
        //   At first we simulated the graph with a function F: R^2 -> R but in fact k can only be non-negative integer
        // so there is still a chance that F(i, r) < F(i, r - 1) consider the fact that r can be real pick or it's ceil
        int integer_pick = r - 1;
        if(2 * log(n) + log(r - i) < log(n - 1) + log(r)) // Simplified comparison of F(i, r) and F(i, r - 1)
            integer_pick = r;
        cout << "-------------\n";
        cout << " pick of this place is in k = " << integer_pick << '\n';
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
