// Tries every number of units of every good (n and a_i small).
#include <bits/stdc++.h>
using namespace std;

int n;
long long W, best = 0;
vector<long long> a, v;

void go(int i, long long used, long long value) {
    if (i == n) {
        best = max(best, value);
        return;
    }
    for (long long k = 0; k <= a[i] && used + k <= W; k++) go(i + 1, used + k, value + k * v[i]);
}

int main() {
    cin >> n >> W;
    a.resize(n);
    v.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> v[i];
    go(0, 0, 0);
    cout << best << "\n";
}
