// Tries every order with next_permutation (n small).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> t(n), w(n);
    for (int i = 0; i < n; i++) cin >> t[i] >> w[i];
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    long long best = LLONG_MAX;
    do {
        long long time = 0, total = 0;
        for (int i : p) {
            time += t[i];
            total += w[i] * time;
        }
        best = min(best, total);
    } while (next_permutation(p.begin(), p.end()));
    cout << best << "\n";
}
