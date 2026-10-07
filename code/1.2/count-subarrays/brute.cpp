// Tries every subarray and adds it up directly.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long K, m;
    cin >> n >> K >> m;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long equalK = 0, divisible = 0;
    for (int l = 0; l < n; l++) {
        long long s = 0;
        for (int r = l; r < n; r++) {
            s += a[r];
            equalK += s == K;
            divisible += s % m == 0;
        }
    }
    cout << equalK << " " << divisible << "\n";
}
