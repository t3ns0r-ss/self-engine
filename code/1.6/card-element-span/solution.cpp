// Card example unit (PLAN.md Section 8.6) for the card "Span of an element": the numbers behind its inline
// examples. "P<k>" lines are positive examples, "N<k>" negative ones; each shows brute force and the method.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Sum of subarray minima by the span formula of Theorem 1.6.2 (L: previous smaller, R: next smaller-or-equal).
ll span_sum(const vector<int>& a) {
    int n = a.size();
    ll total = 0;
    for (int i = 0; i < n; i++) {
        int L = i - 1, R = i + 1;
        while (L >= 0 && a[L] >= a[i]) L--;
        while (R < n && a[R] > a[i]) R++;
        total += (ll)a[i] * (i - L) * (R - i);
    }
    return total;
}

// Largest rectangle under bars by the span of the lowest bar (both sides strictly smaller).
ll span_rect(const vector<int>& h) {
    int n = h.size();
    ll best = 0;
    for (int i = 0; i < n; i++) {
        int L = i - 1, R = i + 1;
        while (L >= 0 && h[L] >= h[i]) L--;
        while (R < n && h[R] >= h[i]) R++;
        best = max(best, (ll)h[i] * (R - L - 1));
    }
    return best;
}

int main() {
    // P1: sum of minima of all subarrays of (2, 4, 1, 3).
    vector<int> a = {2, 4, 1, 3};
    ll brute = 0;
    for (int l = 0; l < 4; l++) for (int r = l; r < 4; r++) brute += *min_element(a.begin() + l, a.begin() + r + 1);
    cout << "P1 brute=" << brute << " method=" << span_sum(a) << '\n';

    // P2: largest rectangle under the bars (1, 3, 5, 6, 2, 2, 4).
    vector<int> h = {1, 3, 5, 6, 2, 2, 4};
    ll bestRect = 0;
    for (int l = 0; l < 7; l++) for (int r = l; r < 7; r++) bestRect = max(bestRect, (ll)*min_element(h.begin() + l, h.begin() + r + 1) * (r - l + 1));
    cout << "P2 brute=" << bestRect << " method=" << span_rect(h) << '\n';

    // N1: the sum of ALL elements of every subarray of (3, 1, 2); the span formula answers a different question.
    vector<int> b = {3, 1, 2};
    ll sums = 0;
    for (int l = 0; l < 3; l++) for (int r = l; r < 3; r++) sums += accumulate(b.begin() + l, b.begin() + r + 1, 0);
    cout << "N1 brute=" << sums << " method=" << span_sum(b) << '\n';

    // N2: the sum of the minimum over all non-empty SUBSEQUENCES of (2, 1, 4).
    vector<int> c = {2, 1, 4};
    ll seq = 0;
    for (int mask = 1; mask < 8; mask++) {
        int m = INT_MAX;
        for (int i = 0; i < 3; i++) if (mask >> i & 1) m = min(m, c[i]);
        seq += m;
    }
    cout << "N2 brute=" << seq << " method=" << span_sum(c) << '\n';
}
