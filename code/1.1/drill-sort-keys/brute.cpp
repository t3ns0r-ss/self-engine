#include <bits/stdc++.h>
using namespace std;

// Brute force: selection sort with a hand-written "ranks before" test.
int main() {
    int n;
    cin >> n;
    vector<array<long long, 3>> v(n);  // {id, score, penalty}
    for (auto& c : v) cin >> c[0] >> c[1] >> c[2];
    auto before = [](const array<long long, 3>& x, const array<long long, 3>& y) {
        if (x[1] != y[1]) return x[1] > y[1];
        if (x[2] != y[2]) return x[2] < y[2];
        return x[0] < y[0];
    };
    for (int i = 0; i < n; i++) {
        int best = i;
        for (int j = i + 1; j < n; j++) if (before(v[j], v[best])) best = j;
        swap(v[i], v[best]);
        cout << v[i][0] << "\n";
    }
}
