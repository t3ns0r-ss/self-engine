#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long K;
    cin >> n >> K;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    int best = 0;
    for (int l = 0; l < n; l++)
        for (int r = l; r < n; r++) {
            long long s = 0;
            for (int i = l; i <= r; i++) s += a[i];
            if (s <= K) best = max(best, r - l + 1);
        }
    cout << best << "\n";
}
