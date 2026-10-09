// Brute force: try every permutation of the women and count those where every pair is compatible.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto& row : a)
        for (auto& x : row) cin >> x;
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    long long count = 0;
    do {
        bool ok = true;
        for (int i = 0; i < n; i++) ok = ok && a[i][p[i]];
        count += ok;
    } while (next_permutation(p.begin(), p.end()));
    cout << count % 1'000'000'007 << "\n";
}
