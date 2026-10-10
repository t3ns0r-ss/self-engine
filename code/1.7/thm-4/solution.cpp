#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.7.4. The largest a_i & a_j over pairs i < j: decide the bits from the top; keep a bit when two values
// contain every decided bit and this one.
int maxAndPair(const vector<int>& a) {
    int ans = 0;
    for (int b = 29; b >= 0; b--) {
        int want = ans | (1 << b);
        int c = 0;  // values containing every bit of want
        for (int x : a)
            if ((x & want) == want) c++;
        if (c >= 2) ans = want;
    }
    return ans;
}
// snippet:end

int main() {
    cout << "5 6 3: largest AND of a pair " << maxAndPair({5, 6, 3}) << '\n';
    cout << "7 7: largest AND of a pair " << maxAndPair({7, 7}) << '\n';
    cout << "1 2: largest AND of a pair " << maxAndPair({1, 2}) << '\n';
    mt19937 rng(4);
    for (int round = 0; round < 400; round++) {
        int n = rng() % 6 + 2;
        vector<int> a(n);
        for (int& x : a) x = rng() % 64;
        int best = 0;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) best = max(best, a[i] & a[j]);
        if (best != maxAndPair(a)) return 1;
    }
}
