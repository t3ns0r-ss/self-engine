/*
Problem: CSES 2183 Missing Coin Sum. Print the smallest positive sum that no subset of the coins
can make.
Input: n (1 <= n <= 2*10^5), then x_1 .. x_n (1 <= x_i <= 10^9).
Output: the smallest sum that cannot be made.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The smallest sum that cannot be made from the coins: every sum 0..reach is possible with the coins so far.
long long smallestUnreachable(vector<long long> x) {
    sort(x.begin(), x.end());
    long long reach = 0;  // up to 2*10^14
    for (long long v : x) {
        if (v > reach + 1) break;  // reach + 1 can never be made
        reach += v;                // the sums v..v + reach are new, so 0..reach + v are all possible
    }
    return reach + 1;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> x(n);
    for (auto& v : x) cin >> v;
    cout << smallestUnreachable(x) << "\n";
}
