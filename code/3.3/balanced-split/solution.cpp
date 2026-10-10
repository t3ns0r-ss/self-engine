/*
Problem: split n numbers into two groups so that the difference of the group sums is as small as possible.
Input: n (1 <= n <= 1000), then n integers (1 <= a_i <= 1000), so the total is at most 10^6.
Output: the smallest possible difference.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.3.4. bit s of reach is 1 when some subset sums to s; reach |= reach << x adds a number, each used once.
// The best split has one group sum s as close to total / 2 as possible.
int balancedSplit(const vector<int>& a) {
    static bitset<1000001> reach;
    reach.reset();
    reach[0] = 1;
    int total = 0;
    for (int x : a) reach |= reach << x, total += x;
    for (int s = total / 2; s >= 0; s--)
        if (reach[s]) return total - 2 * s;
    return total;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << balancedSplit(a) << "\n";
}
