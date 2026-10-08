// Brute force: a full table g[0..n] filled in increasing order (a different method: tabulation).
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    vector<long long> g(n + 1, 0);
    for (long long v = 1; v <= n; v++) g[v] = max(v, g[v / 2] + g[v / 3] + g[v / 4]);
    cout << g[n] << "\n";
}
