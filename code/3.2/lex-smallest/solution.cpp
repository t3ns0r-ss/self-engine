/*
Problem: choose elements of an array of positive integers, no two adjacent, with the largest sum; among all
choices with that sum, print the one whose list of positions is lexicographically smallest.
Input: n (1 <= n <= 10^5), then a_1..a_n (1 <= a_i <= 10^9).
Output: the largest sum, then the number of chosen positions, then the positions (1-based) in increasing order.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.2.6. The suffix table best[i] = the largest sum from positions i..n-1; walking forward, take position i
// whenever taking it still reaches the optimum, which makes the first chosen position, then the second, as small as possible.
pair<long long, vector<int>> lexSmallest(const vector<long long>& a) {
    int n = a.size();
    vector<long long> best(n + 2, 0);
    for (int i = n - 1; i >= 0; i--) best[i] = max(best[i + 1], a[i] + best[i + 2]);
    vector<int> chosen;
    for (int i = 0; i < n;) {
        if (a[i] + best[i + 2] == best[i]) chosen.push_back(i + 1), i += 2;
        else i += 1;
    }
    return {best[0], chosen};
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    auto [sum, chosen] = lexSmallest(a);
    cout << sum << "\n" << chosen.size() << "\n";
    for (int j = 0; j < (int)chosen.size(); j++) cout << chosen[j] << (j + 1 < (int)chosen.size() ? ' ' : '\n');
}
