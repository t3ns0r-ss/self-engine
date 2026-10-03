#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long K;
    cin >> n >> K;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long cnt = 0;
    for (int l = 0; l < n; l++) {
        long long s = 0;
        for (int r = l; r < n; r++) {
            s += a[r];
            if (s >= K) cnt++;
        }
    }
    cout << cnt << "\n";
}
