// Brute force: try every order of the cities 1..n-1.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<long long>> d(n, vector<long long>(n));
    for (auto& row : d)
        for (auto& x : row) cin >> x;
    vector<int> p;
    for (int i = 1; i < n; i++) p.push_back(i);
    long long best = LLONG_MAX;
    do {
        long long t = 0;
        int at = 0;
        for (int v : p) t += d[at][v], at = v;
        t += d[at][0];
        best = min(best, t);
    } while (next_permutation(p.begin(), p.end()));
    cout << best << "\n";
}
