#include <bits/stdc++.h>
using namespace std;

long long firstTotal(const vector<long long>& a) {
    int n = a.size();
    vector<vector<long long>> D(n, vector<long long>(n, 0));
    for (int l = 0; l < n; l++) D[l][l] = a[l];
    for (int len = 2; len <= n; len++) for (int l = 0; l + len - 1 < n; l++) {
        int r = l + len - 1;
        D[l][r] = max(a[l] - D[l + 1][r], a[r] - D[l][r - 1]);
    }
    return (accumulate(a.begin(), a.end(), 0LL) + D[0][n - 1]) / 2;
}
long long minimax(const vector<long long>& a, int l, int r) {
    if (l > r) return 0;
    return accumulate(a.begin() + l, a.begin() + r + 1, 0LL) - min(minimax(a, l + 1, r), minimax(a, l, r - 1));
}
long long bestOfK(const vector<long long>& a, int k) {  // single player, exactly k cards from the two ends
    long long best = 0;
    for (int left = 0; left <= k; left++) {
        long long s = 0;
        for (int i = 0; i < left; i++) s += a[i];
        for (int i = 0; i < k - left; i++) s += a[a.size() - 1 - i];
        best = max(best, s);
    }
    return best;
}
long long anywhere(vector<long long> a) {  // two players take from anywhere: the largest, then the next, ...
    sort(a.rbegin(), a.rend());
    long long s = 0;
    for (size_t i = 0; i < a.size(); i += 2) s += a[i];
    return s;
}
int main() {
    // P1: the row 3 9 1 2. P2: the row 1 5 2. Brute: minimax over all plays. Method: the score-difference table.
    cout << "P1 brute=" << minimax({3, 9, 1, 2}, 0, 3) << " method=" << firstTotal({3, 9, 1, 2}) << '\n';
    cout << "P2 brute=" << minimax({1, 5, 2}, 0, 2) << " method=" << firstTotal({1, 5, 2}) << '\n';
    // N1: one player takes exactly 3 cards from the ends of 1 79 80 1 1 1 200 1; the table assumes an opponent.
    vector<long long> cards = {1, 79, 80, 1, 1, 1, 200, 1};
    cout << "N1 brute=" << bestOfK(cards, 3) << " method=" << firstTotal(cards) << '\n';
    // N2: two players take from anywhere in 1 3 9 3; the table only allows the ends.
    cout << "N2 brute=" << anywhere({1, 3, 9, 3}) << " method=" << firstTotal({1, 3, 9, 3}) << '\n';
}
