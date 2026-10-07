/*
Problem: sort n integers in non-decreasing order, with merge sort.
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9).
Output: the sorted values.
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> a, buf;  // buf: room for merged output (Theorem 1.1.1, condition 2)

// Sorts a[lo .. hi - 1].
void mergeSort(int lo, int hi) {
    if (hi - lo <= 1) return;  // one element is already sorted
    int mid = (lo + hi) / 2;
    mergeSort(lo, mid);
    mergeSort(mid, hi);
    int i = lo, j = mid, k = lo;
    while (i < mid && j < hi) {
        if (a[j] < a[i]) buf[k++] = a[j++];  // right only when strictly smaller: stable
        else buf[k++] = a[i++];
    }
    while (i < mid) buf[k++] = a[i++];  // one half may still have elements left
    while (j < hi) buf[k++] = a[j++];
    for (int t = lo; t < hi; t++) a[t] = buf[t];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    a.resize(n);
    buf.resize(n);
    for (auto& x : a) cin >> x;
    mergeSort(0, n);
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? ' ' : '\n');
}
