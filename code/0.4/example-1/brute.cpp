// Tries every sequence of attacks (memoised on the sorted list of alive healths).
#include <bits/stdc++.h>
using namespace std;

map<vector<int>, int> memo;

int best(vector<int> v) {
    sort(v.begin(), v.end());
    if (v.size() == 1) return v[0];
    auto it = memo.find(v);
    if (it != memo.end()) return it->second;
    int res = INT_MAX;
    for (size_t i = 0; i < v.size(); i++)
        for (size_t j = 0; j < v.size(); j++) {
            if (i == j) continue;
            vector<int> w = v;
            w[j] -= w[i];  // i attacks j
            if (w[j] <= 0) w.erase(w.begin() + j);
            res = min(res, best(w));
        }
    return memo[v] = res;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << best(a) << "\n";
}
