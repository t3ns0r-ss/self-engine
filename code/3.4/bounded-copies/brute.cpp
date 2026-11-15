// Brute force: try every number of copies of every kind, by recursion.
#include <bits/stdc++.h>
using namespace std;

int n, W;
vector<long long> w, v;
vector<int> c;
long long best = 0;

void go(int i, long long weight, long long value) {
    if (i == n) {
        best = max(best, value);
        return;
    }
    for (int k = 0; k <= c[i] && weight + k * w[i] <= W; k++) go(i + 1, weight + k * w[i], value + k * v[i]);
}

int main() {
    cin >> n >> W;
    w.resize(n);
    v.resize(n);
    c.resize(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i] >> c[i];
    go(0, 0, 0);
    cout << best << "\n";
}
