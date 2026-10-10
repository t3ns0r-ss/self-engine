#include <bits/stdc++.h>
using namespace std;

long long kthInTable(long long n, long long k, long long top, bool strict) {
    auto count = [&](long long x) {
        long long c = 0;
        for (long long i = 1; i <= n; i++) c += min(n, (strict ? (x - 1) : x) / i);
        return c;
    };
    long long lo = 0, hi = top + 1;
    while (hi - lo > 1) {
        long long mid = lo + (hi - lo) / 2;
        if (count(mid) >= k) hi = mid;
        else lo = mid;
    }
    return hi;
}

int main() {
    // P1 and P2: the 5th and 9th smallest of the 3 x 3 multiplication table. Brute: list and sort.
    vector<int> all;
    for (int i = 1; i <= 3; i++) for (int j = 1; j <= 3; j++) all.push_back(i * j);
    sort(all.begin(), all.end());
    cout << "P1 brute=" << all[4] << " method=" << kthInTable(3, 5, 9, false) << '\n';
    cout << "P2 brute=" << all[8] << " method=" << kthInTable(3, 9, 9, false) << '\n';
    // N1: the 9th smallest, searching only x in 1..5, where the answer does not lie.
    cout << "N1 brute=" << all[8] << " method=" << kthInTable(3, 9, 5, false) << '\n';
    // N2: the 5th smallest, with count(x) counting the elements strictly below x.
    cout << "N2 brute=" << all[4] << " method=" << kthInTable(3, 5, 9, true) << '\n';
}
