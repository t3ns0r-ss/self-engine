#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.7.4. The loop visits every non-empty submask of m exactly once, in decreasing order.
vector<int> submasks(int m) {
    vector<int> out;
    for (int s = m; s > 0; s = (s - 1) & m) out.push_back(s);
    return out;
}
// snippet:end

int main() {
    cout << "non-empty submasks of 11:";
    for (int s : submasks(11)) cout << ' ' << s;
    cout << '\n';
    for (int n = 1; n <= 8; n++) {
        long long pairs = 0;
        for (int m = 0; m < (1 << n); m++) {
            auto v = submasks(m);
            pairs += v.size() + 1;  // plus the empty submask
            set<int> seen(v.begin(), v.end());
            if (seen.size() != v.size() || !is_sorted(v.rbegin(), v.rend())) return 1;
            for (int s : v) if ((s & m) != s) return 1;
            if ((int)v.size() != (1 << __builtin_popcount(m)) - 1) return 1;
        }
        long long three = 1;
        for (int i = 0; i < n; i++) three *= 3;
        if (pairs != three) return 1;
    }
}
