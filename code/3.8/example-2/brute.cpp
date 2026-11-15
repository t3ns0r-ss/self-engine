// Brute force: try every permutation of the indices.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    long long count = 0;
    do {
        bool ok = true;
        for (int i = 0; i + 1 < n; i++) {
            long long x = a[p[i]], y = a[p[i + 1]];
            ok = ok && (x % y == 0 || y % x == 0);
        }
        count += ok;
    } while (next_permutation(p.begin(), p.end()));
    cout << count % 1'000'000'007 << "\n";
}
