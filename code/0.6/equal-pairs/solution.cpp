/*
Problem: for n integers, print the number of pairs i < j with a_i = a_j, and the most frequent value
(the smallest one if several are tied).
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9).
Output: "pairs value".
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.6.3. The number of pairs i < j with a_i = a_j, and the most frequent value (the smallest if tied).
pair<long long, int> equalPairs(const vector<int>& a) {
    map<int, int> cnt;
    long long pairs = 0;  // up to n(n-1)/2, about 2*10^10
    for (int x : a) {
        pairs += cnt[x];  // earlier elements equal to x
        cnt[x]++;
    }
    int best = 0, bestValue = 0;
    for (auto [value, c] : cnt)  // keys in increasing order, so ties keep the smallest value
        if (c > best) best = c, bestValue = value;
    return {pairs, bestValue};
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    pair<long long, int> r = equalPairs(a);
    cout << r.first << " " << r.second << "\n";
}
