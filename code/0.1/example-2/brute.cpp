// Reads every test fully into a vector first, then counts.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    vector<vector<long long>> tests(t);
    for (auto& v : tests) {
        int n;
        cin >> n;
        v.resize(n);
        for (auto& x : v) cin >> x;
    }
    for (auto& v : tests) cout << count_if(v.begin(), v.end(), [](long long x) { return x % 2 != 0; }) << "\n";
}
