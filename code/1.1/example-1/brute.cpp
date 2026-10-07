// Tries every target length from 1 to the largest stick (values are small in the generator).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> p(n);
    for (auto& x : p) cin >> x;
    long long best = LLONG_MAX, hi = *max_element(p.begin(), p.end());
    for (long long t = 1; t <= hi; t++) {
        long long c = 0;
        for (long long x : p) c += llabs(x - t);
        best = min(best, c);
    }
    cout << best << "\n";
}
