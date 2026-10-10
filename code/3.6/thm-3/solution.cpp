#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.6.3. D[l][r] = the score difference for the player to move on a[l..r]: take an end, and the opponent is then ahead by
// D of what remains. The first player's total is (sum + D) / 2.
long long firstTotal(const vector<long long>& a) {
    int n = a.size();
    vector<vector<long long>> D(n, vector<long long>(n, 0));
    for (int l = 0; l < n; l++) D[l][l] = a[l];
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            D[l][r] = max(a[l] - D[l + 1][r], a[r] - D[l][r - 1]);
        }
    return (accumulate(a.begin(), a.end(), 0LL) + D[0][n - 1]) / 2;
}
// snippet:end

long long minimax(const vector<long long>& a, int l, int r) {  // the best total of the player to move on a[l..r]
    if (l > r) return 0;
    long long rest = accumulate(a.begin() + l, a.begin() + r + 1, 0LL);
    return rest - min(minimax(a, l + 1, r), minimax(a, l, r - 1));
}
int main() {
    cout << "row 3 9 1 2: the first player gets " << firstTotal({3, 9, 1, 2}) << " of 15\n";
    mt19937 rng(53);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 9;
        vector<long long> a(n);
        for (auto& x : a) x = 1 + rng() % 9;
        if (firstTotal(a) != minimax(a, 0, n - 1)) return 1;
    }
}
