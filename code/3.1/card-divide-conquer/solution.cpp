#include <bits/stdc++.h>
using namespace std;

long long countInversions(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int m = (l + r) / 2;
    long long cnt = countInversions(a, tmp, l, m) + countInversions(a, tmp, m, r);
    int i = l, j = m, k = l;
    while (i < m || j < r) {
        if (j == r || (i < m && a[i] <= a[j])) tmp[k++] = a[i++];
        else { cnt += m - i; tmp[k++] = a[j++]; }
    }
    copy(tmp.begin() + l, tmp.begin() + r, a.begin() + l);
    return cnt;
}

long long maxSubarray(const vector<int>& a, int l, int r) {
    if (r - l == 1) return a[l];
    int m = (l + r) / 2;
    long long best = max(maxSubarray(a, l, m), maxSubarray(a, m, r));
    long long sum = 0, bestLeft = LLONG_MIN, bestRight = LLONG_MIN;
    for (int i = m - 1; i >= l; i--) { sum += a[i]; bestLeft = max(bestLeft, sum); }
    sum = 0;
    for (int j = m; j < r; j++) { sum += a[j]; bestRight = max(bestRight, sum); }
    return max(best, bestLeft + bestRight);
}

// The longest subarray a[l..r-1] in which every value appears at most k times (every subarray is tried).
int longestGood(const vector<int>& a, int l, int r, int k) {
    int best = 0;
    for (int i = l; i < r; i++) {
        map<int, int> cnt;
        for (int j = i; j < r; j++) {
            if (++cnt[a[j]] > k) break;
            best = max(best, j - i + 1);
        }
    }
    return best;
}

int main() {
    // P1: the inversions of 4 3 1 2. Brute: every pair. Method: two halves and a merge.
    vector<int> a = {4, 3, 1, 2}, tmp(4);
    int brute = 0;
    for (int i = 0; i < 4; i++) for (int j = i + 1; j < 4; j++) brute += a[i] > a[j];
    cout << "P1 brute=" << brute << " method=" << countInversions(a, tmp, 0, 4) << '\n';
    // P2: the largest sum of a non-empty subarray of -2 1 -3 4 -1 2 1 -5 4. Brute: every subarray. Method: halves and the crossing part.
    vector<int> b = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    long long best = LLONG_MIN;
    for (int i = 0; i < 9; i++) { long long s = 0; for (int j = i; j < 9; j++) { s += b[j]; best = max(best, s); } }
    cout << "P2 brute=" << best << " method=" << maxSubarray(b, 0, 9) << '\n';
    // N1: the longest subarray of 1 2 3 1 2 3 1 2 with every value at most twice. Brute: every subarray.
    // The halves alone (no cross term) miss the answer, which lies across the middle.
    vector<int> c = {1, 2, 3, 1, 2, 3, 1, 2};
    int halves = max(longestGood(c, 0, 4, 2), longestGood(c, 4, 8, 2));
    cout << "N1 brute=" << longestGood(c, 0, 8, 2) << " method=" << halves << '\n';
}
