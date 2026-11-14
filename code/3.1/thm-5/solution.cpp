#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.1.5. Counting inversions by divide and conquer: the pairs i < j with a[i] > a[j] inside a[l..r-1].
// Count inside each half, then count the pairs that cross the middle while merging the two sorted halves.
// The part a[l..r-1] ends up sorted, and the count is long long (it can reach n(n-1)/2).
long long countInversions(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int m = (l + r) / 2;
    long long cnt = countInversions(a, tmp, l, m) + countInversions(a, tmp, m, r);
    int i = l, j = m, k = l;
    while (i < m || j < r) {
        if (j == r || (i < m && a[i] <= a[j])) {
            tmp[k++] = a[i++];
        } else {
            cnt += m - i;  // a[j] is smaller than all of a[i..m-1]: that many crossing pairs
            tmp[k++] = a[j++];
        }
    }
    copy(tmp.begin() + l, tmp.begin() + r, a.begin() + l);
    return cnt;
}
// snippet:end

long long inversions(vector<int> a) {
    vector<int> tmp(a.size());
    return countInversions(a, tmp, 0, a.size());
}

// Elements visited by all calls when a part of size s is cut into s / 2 and s - s / 2 (an even split) ...
long long visitedEven(int s) { return s <= 1 ? 0 : s + visitedEven(s / 2) + visitedEven(s - s / 2); }
// ... and when it is cut into s - 1 and 0, as a sorted array cut at its largest element is.
long long visitedUneven(int s) { return s <= 1 ? 0 : s + visitedUneven(s - 1); }

int main() {
    cout << "n = 1024, even split: " << visitedEven(1024) << " visits, cut at the largest: " << visitedUneven(1024) << " visits\n";
    cout << "inversions of 4 3 1 2: " << inversions({4, 3, 1, 2}) << '\n';
    cout << "inversions of 5 2 4 6 1 3: " << inversions({5, 2, 4, 6, 1, 3}) << '\n';
    cout << "inversions of 2 2: " << inversions({2, 2}) << '\n';
    int n = 200000;
    vector<int> rev(n);
    for (int i = 0; i < n; i++) rev[i] = n - i;
    cout << "reversed array of " << n << ": " << inversions(rev) << " = n(n-1)/2 = " << (long long)n * (n - 1) / 2 << '\n';
    mt19937 rng(5);
    for (int round = 0; round < 500; round++) {
        int len = rng() % 30;
        vector<int> a(len);
        for (int& x : a) x = rng() % 8;  // many equal values on purpose
        long long brute = 0;
        for (int i = 0; i < len; i++) for (int j = i + 1; j < len; j++) brute += a[i] > a[j];
        if (brute != inversions(a)) return 1;
    }
}
