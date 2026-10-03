// GCD: the largest d dividing all; LCM: the smallest m in 1..C divisible by all.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long C;
    cin >> n >> C;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long g = 0;
    for (long long d = *min_element(a.begin(), a.end()); d >= 1 && g == 0; d--) {
        bool all = true;
        for (long long x : a) all = all && x % d == 0;
        if (all) g = d;
    }
    long long L = -1;
    for (long long m = 1; m <= C && L == -1; m++) {
        bool all = true;
        for (long long x : a) all = all && m % x == 0;
        if (all) L = m;
    }
    cout << g << " " << L << "\n";
}
