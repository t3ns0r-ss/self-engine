#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    long long total = 0;
    for (int l = 0; l < n; l++)
        for (int r = l; r < n; r++) {
            set<int> s(a.begin() + l, a.begin() + r + 1);
            if ((int)s.size() <= k) total++;
        }
    cout << total << "\n";
}
