#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long S;
    cin >> n >> S;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    int best = 0;
    for (int l = 0; l < n; l++)
        for (int r = l; r < n; r++) {
            long long s = 0;
            for (int i = l; i <= r; i++) s += a[i];
            if (s >= S && (best == 0 || r - l + 1 < best)) best = r - l + 1;
        }
    cout << best << "\n";
}
