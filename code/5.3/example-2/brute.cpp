#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cin >> m;
    string line;
    getline(cin, line);
    while (m--) {
        getline(cin, line);
        istringstream in(line);
        long long lf, rg, v;
        in >> lf >> rg;
        bool inc = static_cast<bool>(in >> v);
        long long best = LLONG_MAX;
        for (int i = lf;; i = (i + 1) % n) {
            if (inc) a[i] += v;
            else best = min(best, a[i]);
            if (i == rg) break;
        }
        if (!inc) cout << best << "\n";
    }
}
