#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.4.1. The first position in L..R where the monotone predicate p is true (R + 1 if there is none).
// Invariant: p(lo) is false and p(hi) is true, with L - 1 and R + 1 agreed to be false and true.
int firstTrue(int L, int R, const function<bool(int)>& p, int& tests) {
    int lo = L - 1, hi = R + 1;
    tests = 0;
    while (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;  // strictly between lo and hi
        tests++;
        if (p(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}
// snippet:end

int main() {
    vector<int> a = {1, 3, 5, 5, 8};
    int tests;
    for (int x : {5, 9, 0}) {
        int answer = firstTrue(0, 4, [&](int i) { return a[i] >= x; }, tests);
        cout << "first index with a_i >= " << x << " in 1 3 5 5 8: " << answer << " after " << tests << " tests\n";
    }
    for (int n = 1; n <= 40; n++)
        for (int t = 0; t <= n; t++) {  // every threshold: p(i) = (i >= t) on 0..n-1
            int c = firstTrue(0, n - 1, [&](int i) { return i >= t; }, tests);
            if (c != t || tests > (int)ceil(log2(n + 1.0)) + 1) return 1;
        }
}
