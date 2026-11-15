#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX / 4;

template <class Cost>
void fillLayer(int lo, int hi, int optLo, int optHi, const vector<long long>& prev, vector<long long>& cur, Cost cost) {
    if (lo > hi) return;
    int mid = (lo + hi) / 2, bestJ = optLo;
    long long best = INF;
    for (int j = optLo; j <= min(mid - 1, optHi); j++) {
        long long cand = prev[j] + cost(j, mid);
        if (cand < best) { best = cand; bestJ = j; }
    }
    cur[mid] = best;
    fillLayer(lo, mid - 1, optLo, bestJ, prev, cur, cost);
    fillLayer(mid + 1, hi, bestJ, optHi, prev, cur, cost);
}

// k groups, the card's method (divide and conquer on every layer), for any cost(j, i) of the group j+1..i
template <class Cost>
long long method(int n, int k, Cost cost) {
    vector<long long> prev(n + 1, INF), cur(n + 1, INF);
    for (int i = 1; i <= n; i++) prev[i] = cost(0, i);
    for (int t = 2; t <= k; t++) {
        fillLayer(t, n, t - 1, n - 1, prev, cur, cost);
        prev = cur;
    }
    return prev[n];
}
template <class Cost>
long long brute(int n, int k, Cost cost) {
    vector<vector<long long>> dp(k + 1, vector<long long>(n + 1, INF));
    dp[0][0] = 0;
    for (int t = 1; t <= k; t++)
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < i; j++)
                if (dp[t - 1][j] < INF) dp[t][i] = min(dp[t][i], dp[t - 1][j] + cost(j, i));
    return dp[k][n];
}

int main() {
    auto prefix = [](const vector<long long>& a) {
        vector<long long> P(a.size() + 1, 0);
        for (size_t i = 0; i < a.size(); i++) P[i + 1] = P[i] + a[i];
        return P;
    };
    {   // P1: the square of the sum of each group
        vector<long long> P = prefix({3, 1, 4, 1, 5});
        auto cost = [&](int j, int i) { return (P[i] - P[j]) * (P[i] - P[j]); };
        cout << "P1 brute=" << brute(5, 2, cost) << " method=" << method(5, 2, cost) << "\n";
    }
    {   // P2: houses at 1 4 8 10 20, the sum of the distances to the median house of each group
        vector<long long> X = {0, 1, 4, 8, 10, 20}, S(6, 0);
        for (int i = 1; i <= 5; i++) S[i] = S[i - 1] + X[i];
        auto cost = [&](int j, int i) {
            int m = (j + 1 + i) / 2;
            return (X[m] * (m - j) - (S[m] - S[j])) + ((S[i] - S[m]) - X[m] * (i - m));
        };
        cout << "P2 brute=" << brute(5, 2, cost) << " method=" << method(5, 2, cost) << "\n";
    }
    {   // N1: the cost is MINUS the square of the sum, so the groups should be as uneven as possible
        vector<long long> P = prefix({1, 1, 0, 2});
        auto cost = [&](int j, int i) { return -(P[i] - P[j]) * (P[i] - P[j]); };
        cout << "N1 brute=" << brute(4, 2, cost) << " method=" << method(4, 2, cost) << "\n";
    }
    {   // N2: the same cost on another array
        vector<long long> P = prefix({1, 1, 0, 3});
        auto cost = [&](int j, int i) { return -(P[i] - P[j]) * (P[i] - P[j]); };
        cout << "N2 brute=" << brute(4, 2, cost) << " method=" << method(4, 2, cost) << "\n";
    }
}
