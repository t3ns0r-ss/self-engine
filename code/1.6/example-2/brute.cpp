#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    vector<long long> x(n);
    for (auto& v : x) cin >> v;
    long long best = LLONG_MIN;
    for (int l = 0; l < n; l++)
        for (int r = l + a - 1; r < n && r - l + 1 <= b; r++) {
            long long s = 0;
            for (int k = l; k <= r; k++) s += x[k];
            best = max(best, s);
        }
    cout << best << "\n";
}
