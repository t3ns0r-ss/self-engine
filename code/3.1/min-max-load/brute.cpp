// Brute force: every one of the k^n assignments, without any cut.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> job(n);
    for (auto& x : job) cin >> x;
    long long total = 1;
    for (int i = 0; i < n; i++) total *= k;
    long long best = LLONG_MAX;
    for (long long code = 0; code < total; code++) {
        vector<long long> load(k, 0);
        long long x = code;
        for (int i = 0; i < n; i++) {
            load[x % k] += job[i];
            x /= k;
        }
        best = min(best, *max_element(load.begin(), load.end()));
    }
    cout << best << "\n";
}
