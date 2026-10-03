/*
Problem: for n integers, print the number of pairs i < j with a_i = a_j, and the most frequent value
(the smallest one if several are tied).
Input: n (1 <= n <= 2*10^5), then a_1 .. a_n (|a_i| <= 10^9).
Output: "pairs value".
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    map<int, int> cnt;
    long long pairs = 0;  // up to n(n-1)/2, about 2*10^10
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        pairs += cnt[a];  // earlier elements equal to a (Theorem 0.6.3)
        cnt[a]++;
    }
    int best = 0, bestValue = 0;
    for (auto [value, c] : cnt)  // keys in increasing order, so ties keep the smallest value
        if (c > best) {
            best = c;
            bestValue = value;
        }
    cout << pairs << " " << bestValue << "\n";
}
