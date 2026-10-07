/*
Problem: n integers and q queries "L R"; for each, print how many of the integers lie in [L, R].
Input: n q (1 <= n, q <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9), then q lines "L R" (L <= R).
Output: one count per line.
*/
#include <bits/stdc++.h>
using namespace std;

int n;
vector<long long> a;

// First index i with a[i] >= x, or n if there is none (Theorem 1.4.1 with p(i) = a[i] >= x).
int firstAtLeast(long long x) {
    int lo = -1, hi = n;  // invariant: lo is -1 or a[lo] < x; hi is n or a[hi] >= x
    while (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;  // strictly between lo and hi
        if (a[mid] >= x) hi = mid;
        else lo = mid;
    }
    return hi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> n >> q;
    a.resize(n);
    for (auto& x : a) cin >> x;
    sort(a.begin(), a.end());  // the predicate a[i] >= x is monotone only on a sorted array
    while (q--) {
        long long L, R;
        cin >> L >> R;
        // elements <= R minus elements < L (Theorem 1.4.2, part 2); "<= R" is "< R + 1"
        cout << firstAtLeast(R + 1) - firstAtLeast(L) << "\n";
    }
}
