#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<array<long long, 3>> visits(n);
    for (auto& v : visits) cin >> v[0] >> v[1] >> v[2];
    long long lo = LLONG_MAX, hi = LLONG_MIN;
    for (auto& v : visits) lo = min(lo, v[0]), hi = max(hi, v[1]);
    long long mostVisits = 0, mostWeight = 0;
    vector<long long> atLeast(n + 2, 0);
    for (long long x = lo; x <= hi; x++) {  // look at every second
        long long count = 0, weight = 0;
        for (auto& v : visits)
            if (v[0] <= x && x <= v[1]) count++, weight += v[2];
        mostVisits = max(mostVisits, count), mostWeight = max(mostWeight, weight);
        for (long long k = 1; k <= count; k++) atLeast[k]++;
    }
    cout << mostVisits << "\n" << mostWeight << "\n";
    for (int k = 1; k <= n; k++) cout << atLeast[k] << (k < n ? ' ' : '\n');
}
