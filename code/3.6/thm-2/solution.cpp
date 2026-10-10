#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.6.2. best[l][r] = the least cost of merging piles l..r into one: the last merge joins [l, k] and [k + 1, r] and costs the
// total of the segment. Returns the whole table.
vector<vector<long long>> mergeTable(const vector<long long>& a) {
    int n = a.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + a[i];
    vector<vector<long long>> best(n, vector<long long>(n, 0));
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            long long low = LLONG_MAX;
            for (int k = l; k < r; k++) low = min(low, best[l][k] + best[k + 1][r]);
            best[l][r] = low + prefix[r + 1] - prefix[l];
        }
    return best;
}
// snippet:end

long long brute(vector<long long> a) {  // every order of merging neighbours
    if (a.size() == 1) return 0;
    long long best = LLONG_MAX;
    for (size_t i = 0; i + 1 < a.size(); i++) {
        vector<long long> b = a;
        b[i] += b[i + 1];
        b.erase(b.begin() + i + 1);
        best = min(best, a[i] + a[i + 1] + brute(b));
    }
    return best;
}
int main() {
    auto t = mergeTable({4, 1, 2, 3});
    cout << "best costs for the piles 4 1 2 3, rows l, columns r:\n";
    for (int l = 0; l < 4; l++) {
        for (int r = 0; r < 4; r++) cout << (r >= l ? to_string(t[l][r]) : string("-")) << (r < 3 ? ' ' : '\n');
    }
    mt19937 rng(52);
    for (int round = 0; round < 200; round++) {
        int n = 1 + rng() % 7;
        vector<long long> a(n);
        for (auto& x : a) x = 1 + rng() % 9;
        if (mergeTable(a)[0][n - 1] != brute(a)) return 1;
    }
}
