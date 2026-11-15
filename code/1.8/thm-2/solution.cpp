#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.8.2. a[1..n] are different numbers; a[0] and a[n + 1] count as infinitely large.
// Returns a position whose number is smaller than both neighbours, after at most ceil(log2 n) rounds of 2 questions.
int localMin(const vector<long long>& a, int n, int& questions) {
    int lo = 1, hi = n;  // invariant: a[lo - 1] > a[lo] and a[hi] < a[hi + 1]
    questions = 0;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        questions += 2;                   // the two numbers a[mid] and a[mid + 1]
        if (a[mid] > a[mid + 1]) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}
// snippet:end

bool isLocalMin(const vector<long long>& a, int n, int p) {
    return p >= 1 && p <= n && a[p] < a[p - 1] && a[p] < a[p + 1];
}

int main() {
    const long long INF = LLONG_MAX;
    vector<vector<long long>> shown = {{4, 2, 5, 3, 1, 6}, {1, 2, 3, 4, 5}, {7}};
    for (const auto& v : shown) {
        int n = (int)v.size();
        vector<long long> a(n + 2, INF);
        for (int i = 1; i <= n; i++) a[i] = v[i - 1];
        int questions;
        int p = localMin(a, n, questions);
        cout << "a =";
        for (long long x : v) cout << " " << x;
        cout << ": position " << p << ", " << questions << " questions\n";
    }
    // The check: every ordering of 1..n for n up to 8.
    for (int n = 1; n <= 8; n++) {
        vector<long long> a(n + 2, INF);
        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 1);
        int rounds = 0;
        while ((1 << rounds) < n) rounds++;
        do {
            for (int i = 1; i <= n; i++) a[i] = perm[i - 1];
            int questions;
            int p = localMin(a, n, questions);
            if (!isLocalMin(a, n, p) || questions > 2 * rounds) return 1;
        } while (next_permutation(perm.begin(), perm.end()));
    }
    return 0;
}
