#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.1.1. Merge sort on (key, tag) pairs, comparing keys only. buf is room for the merged output.
typedef pair<int, char> Item;

void mergeSort(vector<Item>& a, vector<Item>& buf, int lo, int hi) {
    if (hi - lo <= 1) return;  // one element is already sorted
    int mid = (lo + hi) / 2;
    mergeSort(a, buf, lo, mid);
    mergeSort(a, buf, mid, hi);
    int i = lo, j = mid, k = lo;
    while (i < mid && j < hi) {
        if (a[j].first < a[i].first) buf[k++] = a[j++];  // right only when strictly smaller: stable
        else buf[k++] = a[i++];
    }
    while (i < mid) buf[k++] = a[i++];
    while (j < hi) buf[k++] = a[j++];
    for (int t = lo; t < hi; t++) a[t] = buf[t];
}
// snippet:end

int main() {
    vector<Item> a = {{5, 'a'}, {2, 'b'}, {4, 'c'}, {1, 'd'}}, buf(4);
    mergeSort(a, buf, 0, 4);
    cout << "5 2 4 1 sorted:";
    for (auto& x : a) cout << ' ' << x.first;
    cout << '\n';
    vector<Item> b = {{2, 'a'}, {1, 'b'}, {2, 'c'}}, buf2(3);
    mergeSort(b, buf2, 0, 3);
    cout << "2a 1b 2c sorted:";
    for (auto& x : b) cout << ' ' << x.first << x.second;
    cout << '\n';
    mt19937 rng(3);
    for (int round = 0; round < 500; round++) {  // against stable_sort
        int n = rng() % 12;
        vector<Item> c(n), d, e(n);
        for (int i = 0; i < n; i++) c[i] = {(int)(rng() % 5), char('a' + i)};
        d = c;
        mergeSort(c, e, 0, n);
        stable_sort(d.begin(), d.end(), [](const Item& x, const Item& y) { return x.first < y.first; });
        if (c != d) return 1;
    }
}
