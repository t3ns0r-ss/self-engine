// Brute force: every one of the m^n plans, checked for repeats.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> p(n, vector<long long>(m));
    for (auto& row : p)
        for (auto& x : row) cin >> x;
    long long total = 1;
    for (int i = 0; i < n; i++) total *= m;
    long long best = 0;
    for (long long code = 0; code < total; code++) {
        long long x = code, sum = 0;
        int prev = -1;
        bool ok = true;
        for (int i = 0; i < n; i++) {
            int a = x % m;
            x /= m;
            if (a == prev) ok = false;
            sum += p[i][a];
            prev = a;
        }
        if (ok) best = max(best, sum);
    }
    cout << best << "\n";
}
