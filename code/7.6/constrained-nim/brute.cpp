#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long L, R;
    cin >> n >> L >> R;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    vector<int> g(41, 0);
    for (int x = 1; x <= 40; x++) {  // the Grundy value by the definition
        set<int> reach;
        for (int r = L; r <= R && r <= x; r++) reach.insert(g[x - r]);
        while (reach.count(g[x])) g[x]++;
    }
    int total = 0;
    for (auto x : a) total ^= g[x];
    cout << (total ? "First" : "Second") << "\n";
}
