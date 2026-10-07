/*
Problem: CSES 1074 Stick Lengths. Make all n sticks the same length; changing a length by x costs x.
Input: n (1 <= n <= 2*10^5), then p_1 .. p_n (1 <= p_i <= 10^9).
Output: the minimum total cost.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> p(n);
    for (auto& x : p) cin >> x;
    sort(p.begin(), p.end());
    long long target = p[n / 2];  // a median is an optimal length
    long long cost = 0;           // up to 2*10^5 * 10^9 = 2*10^14
    for (long long x : p) cost += llabs(x - target);
    cout << cost << "\n";
}
