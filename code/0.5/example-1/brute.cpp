// Recursion: each apple goes to group 1 or group 2; both sums are carried along.
#include <bits/stdc++.h>
using namespace std;

int n;
vector<long long> p;

long long go(int i, long long g1, long long g2) {
    if (i == n) return llabs(g1 - g2);
    return min(go(i + 1, g1 + p[i], g2), go(i + 1, g1, g2 + p[i]));
}

int main() {
    cin >> n;
    p.resize(n);
    for (auto& x : p) cin >> x;
    cout << go(0, 0, 0) << "\n";
}
