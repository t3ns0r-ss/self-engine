// Brute force: try every sequence of jumps by recursion (topic 3.1), no table.
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> h;

long long go(int i) {  // cheapest way from stone i to the last stone, by trying everything
    if (i == n - 1) return 0;
    long long res = LLONG_MAX;
    for (int j = i + 1; j <= min(n - 1, i + k); j++) res = min(res, abs(h[i] - h[j]) + go(j));
    return res;
}

int main() {
    cin >> n >> k;
    h.resize(n);
    for (int& x : h) cin >> x;
    cout << go(0) << "\n";
}
