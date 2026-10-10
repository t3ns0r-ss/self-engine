#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.3.4. Subset sums: bit s of reach is 1 when some subset sums to s; reach |= reach << a adds a number, used once.
bitset<64> reachable(const vector<int>& a) {
    bitset<64> reach;
    reach[0] = 1;
    for (int x : a) reach |= reach << x;
    return reach;
}
// snippet:end

int main() {
    auto r = reachable({2, 3, 7});
    cout << "reachable sums of 2 3 7:";
    for (int s = 0; s < 64; s++) if (r[s]) cout << ' ' << s;
    cout << '\n';
    mt19937 rng(23);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 8;
        vector<int> a(n);
        for (int& x : a) x = 1 + rng() % 8;
        bitset<64> want;
        for (int mask = 0; mask < (1 << n); mask++) {
            int s = 0;
            for (int i = 0; i < n; i++) if (mask >> i & 1) s += a[i];
            if (s < 64) want[s] = 1;
        }
        if (reachable(a) != want) return 1;
    }
}
