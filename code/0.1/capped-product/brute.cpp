// Uses the 128-bit type __int128 (a GCC extension), capping the product at 10^18 + 1 after each step.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    const __int128 LIMIT = 1000000000000000000LL;
    __int128 p = 1;
    for (long long x : a) {
        p *= x;  // at most (10^18 + 1) * 10^18, well inside the 128-bit range
        if (p > LIMIT) p = LIMIT + 1;
    }
    if (p > LIMIT) cout << -1 << "\n";
    else cout << (long long)p << "\n";
}
