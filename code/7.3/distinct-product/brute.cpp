#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    const long long MOD = 1'000'000'007;
    set<vector<int>> seen;
    for (int mask = 1; mask < (1 << n); mask++) {
        vector<int> seq;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) seq.push_back(a[i]);
        if (is_sorted(seq.begin(), seq.end())) seen.insert(seq);
    }
    long long sum = 0;
    for (auto& seq : seen) {
        long long prod = 1;
        for (int x : seq) prod = prod * x % MOD;
        sum = (sum + prod) % MOD;
    }
    cout << sum << "\n";
}
