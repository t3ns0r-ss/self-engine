#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.1.5. The rank of every value among the distinct values: 0 for the smallest, d - 1 for the largest.
vector<int> compress(const vector<int>& a) {
    int n = a.size();
    vector<pair<int, int>> v(n);  // (value, index)
    for (int i = 0; i < n; i++) v[i] = {a[i], i};
    sort(v.begin(), v.end());
    vector<int> rank(n);
    int r = 0;
    for (int k = 0; k < n; k++) {
        if (k > 0 && v[k].first != v[k - 1].first) r++;  // a new distinct value
        rank[v[k].second] = r;
    }
    return rank;
}
// snippet:end

int main() {
    for (vector<int> a : {vector<int>{50, 10, 50, 7}, vector<int>{3, 3, 3}}) {
        for (int x : a) cout << x << ' ';
        cout << "->";
        for (int x : compress(a)) cout << ' ' << x;
        cout << '\n';
    }
    mt19937 rng(11);
    for (int round = 0; round < 500; round++) {
        int n = rng() % 8 + 1;
        vector<int> a(n);
        for (int& x : a) x = rng() % 6;
        vector<int> r = compress(a);
        for (int i = 0; i < n; i++) {
            set<int> smaller;
            for (int x : a) if (x < a[i]) smaller.insert(x);
            if (r[i] != (int)smaller.size()) return 1;
        }
    }
}
