/*
Problem: CSES 1640 Sum of Two Values. Find positions i < j with a_i + a_j = x, or print IMPOSSIBLE.
Any pair is accepted; this program prints the pair with the smallest j, and for it the smallest i.
Input: n x (1 <= n <= 2*10^5, 1 <= x <= 10^9), then a_1 .. a_n (1 <= a_i <= 10^9).
Output: "i j" (1-based) or IMPOSSIBLE.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Positions i < j (1-based) with a_i + a_j = x, found with a map from value to its first position;
// {-1, -1} if there is none.
pair<int, int> twoSum(const vector<long long>& a, long long x) {
    map<long long, int> firstPos;
    for (int j = 0; j < (int)a.size(); j++) {
        auto it = firstPos.find(x - a[j]);  // find, not [], so no empty entries are created
        if (it != firstPos.end()) return {it->second + 1, j + 1};
        if (!firstPos.count(a[j])) firstPos[a[j]] = j;
    }
    return {-1, -1};
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    pair<int, int> r = twoSum(a, x);
    if (r.first < 0) cout << "IMPOSSIBLE\n";
    else cout << r.first << " " << r.second << "\n";
}
