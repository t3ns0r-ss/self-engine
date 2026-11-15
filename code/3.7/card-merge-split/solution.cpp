#include <bits/stdc++.h>
using namespace std;

long long mergeNeighbours(const vector<long long>& a) {
    int n = a.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + a[i];
    vector<vector<long long>> best(n, vector<long long>(n, 0));
    for (int len = 2; len <= n; len++) for (int l = 0; l + len - 1 < n; l++) {
        int r = l + len - 1;
        long long low = LLONG_MAX;
        for (int k = l; k < r; k++) low = min(low, best[l][k] + best[k + 1][r]);
        best[l][r] = low + prefix[r + 1] - prefix[l];
    }
    return best[0][n - 1];
}
long long bruteNeighbours(vector<long long> a) {
    if (a.size() == 1) return 0;
    long long best = LLONG_MAX;
    for (size_t i = 0; i + 1 < a.size(); i++) {
        vector<long long> b = a;
        b[i] += b[i + 1];
        b.erase(b.begin() + i + 1);
        best = min(best, a[i] + a[i + 1] + bruteNeighbours(b));
    }
    return best;
}
long long bruteAnyTwo(vector<long long> a) {
    if (a.size() == 1) return 0;
    long long best = LLONG_MAX;
    for (size_t i = 0; i < a.size(); i++) for (size_t j = i + 1; j < a.size(); j++) {
        vector<long long> b;
        for (size_t k = 0; k < a.size(); k++) if (k != i && k != j) b.push_back(a[k]);
        b.push_back(a[i] + a[j]);
        best = min(best, a[i] + a[j] + bruteAnyTwo(b));
    }
    return best;
}
int main() {
    // P1: merge the piles 4 1 2 3, only neighbours. Brute: every order of merges. Method: the table over segments.
    cout << "P1 brute=" << bruteNeighbours({4, 1, 2, 3}) << " method=" << mergeNeighbours({4, 1, 2, 3}) << '\n';
    // N1: merge the piles 3 1 3 1 when any two may be merged (not only neighbours).
    cout << "N1 brute=" << bruteAnyTwo({3, 1, 3, 1}) << " method=" << mergeNeighbours({3, 1, 3, 1}) << '\n';
}
