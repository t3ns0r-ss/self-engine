// Marks every subset sum (n and values small) and finds the first missing positive sum.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto& v : x) cin >> v;
    set<long long> sums;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long s = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) s += x[i];
        sums.insert(s);
    }
    long long k = 1;
    while (sums.count(k)) k++;
    cout << k << "\n";
}
