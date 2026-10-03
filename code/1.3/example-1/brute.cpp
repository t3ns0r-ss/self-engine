#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> k(n);
    for (auto& x : k) cin >> x;
    int best = 0;
    for (int l = 0; l < n; l++)
        for (int r = l; r < n; r++) {
            set<int> s(k.begin() + l, k.begin() + r + 1);
            if ((int)s.size() == r - l + 1) best = max(best, r - l + 1);
        }
    cout << best << "\n";
}
