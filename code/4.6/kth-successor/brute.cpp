#include <bits/stdc++.h>
using namespace std;

// Use the teleporters one at a time. The generator keeps k small.
int main() {
    int n, q;
    cin >> n >> q;
    vector<int> next(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> next[i];
    while (q--) {
        int x;
        long long k;
        cin >> x >> k;
        for (long long i = 0; i < k; i++) x = next[x];
        cout << x << "\n";
    }
}
