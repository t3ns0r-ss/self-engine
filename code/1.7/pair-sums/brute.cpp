#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long sx = 0, sa = 0, so = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            sx += a[i] ^ a[j];
            sa += a[i] & a[j];
            so += a[i] | a[j];
        }
    cout << sx << " " << sa << " " << so << "\n";
}
