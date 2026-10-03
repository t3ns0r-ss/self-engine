#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    int best = 0;
    for (int l = 0; l + k <= n; l++) {
        set<int> s(a.begin() + l, a.begin() + l + k);
        best = max(best, (int)s.size());
    }
    cout << best << "\n";
}
