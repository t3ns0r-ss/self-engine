#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    long long count = 0;
    for (int l = 0; l < n; l++) {
        int x = 0;
        for (int r = l; r < n; r++) {
            x ^= a[r];
            if (x == k) count++;
        }
    }
    cout << count << "\n";
}
