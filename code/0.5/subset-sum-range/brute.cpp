// Recursion: each item is either taken or skipped.
#include <bits/stdc++.h>
using namespace std;

int n;
long long lo, hi;
vector<long long> a;

int go(int i, long long sum) {
    if (i == n) return lo <= sum && sum <= hi ? 1 : 0;
    return go(i + 1, sum) + go(i + 1, sum + a[i]);
}

int main() {
    cin >> n >> lo >> hi;
    a.resize(n);
    for (auto& x : a) cin >> x;
    cout << go(0, 0) << "\n";
}
