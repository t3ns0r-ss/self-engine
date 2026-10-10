#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: for each element of 50 10 50 7, the number of distinct smaller values. Brute: a set per element.
    // Method: the rank after compression.
    vector<int> a = {50, 10, 50, 7};
    vector<pair<int, int>> v;
    for (int i = 0; i < 4; i++) v.push_back({a[i], i});
    sort(v.begin(), v.end());
    vector<int> rank(4);
    int r = 0;
    for (int k = 0; k < 4; k++) { if (k && v[k].first != v[k - 1].first) r++; rank[v[k].second] = r; }
    string brute, method;
    for (int i = 0; i < 4; i++) {
        set<int> smaller;
        for (int x : a) if (x < a[i]) smaller.insert(x);
        brute += (i ? "," : "") + to_string(smaller.size());
        method += (i ? "," : "") + to_string(rank[i]);
    }
    cout << "P1 brute=" << brute << " method=" << method << '\n';
    // P2: the number of distinct values below 10 in 50 10 50 7.
    set<int> below;
    for (int x : a) if (x < 10) below.insert(x);
    cout << "P2 brute=" << below.size() << " method=" << rank[1] << '\n';
    // N1: the total length of the union of the intervals [1, 3] and [10, 12]. Method: the same sum after compressing
    // the ends 1, 3, 10, 12 to ranks 0, 1, 2, 3.
    cout << "N1 brute=" << (3 - 1) + (12 - 10) << " method=" << (1 - 0) + (3 - 2) << '\n';
    // N2: the sum of 7 10 50, computed on the ranks 0 1 2 instead.
    cout << "N2 brute=" << 7 + 10 + 50 << " method=" << 0 + 1 + 2 << '\n';
}
