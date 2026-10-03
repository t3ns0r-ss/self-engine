#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    long long pairs = 0, closest = LLONG_MAX;
    for (auto x : a)
        for (auto y : b) {
            if (y < x) pairs++;
            closest = min(closest, llabs(x - y));
        }
    cout << pairs << "\n" << closest << "\n";
}
