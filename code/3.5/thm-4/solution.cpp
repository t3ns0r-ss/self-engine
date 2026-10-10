#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.5.4. Range transitions with prefix sums: person i takes t in [0, cap] items, so dp[i][j] is the sum of dp[i-1][k] for
// k in [j - cap, j], a range of the previous row. Returns the last row.
vector<long long> shares(int K, const vector<int>& caps, vector<vector<long long>>* rows = nullptr) {
    vector<long long> dp(K + 1, 0), prefix(K + 2, 0);
    dp[0] = 1;
    if (rows) rows->push_back(dp);
    for (int cap : caps) {
        for (int j = 0; j <= K; j++) prefix[j + 1] = prefix[j] + dp[j];
        for (int j = 0; j <= K; j++) dp[j] = prefix[j + 1] - prefix[max(0, j - cap)];
        if (rows) rows->push_back(dp);
    }
    return dp;
}
// snippet:end

int main() {
    vector<vector<long long>> rows;
    auto last = shares(3, {2, 1, 2}, &rows);
    cout << "j = 0 1 2 3\n";
    for (auto& r : rows) {
        for (int j = 0; j <= 3; j++) cout << r[j] << (j < 3 ? ' ' : '\n');
    }
    cout << "ways to give 3 candies with caps 2 1 2: " << last[3] << '\n';
    mt19937 rng(42);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 4, K = rng() % 8;
        vector<int> caps(n);
        for (int& c : caps) c = rng() % 5;
        long long brute = 0;
        function<void(int, int)> go = [&](int i, int left) {
            if (i == n) { brute += left == 0; return; }
            for (int t = 0; t <= caps[i] && t <= left; t++) go(i + 1, left - t);
        };
        go(0, K);
        if (shares(K, caps)[K] != brute) return 1;
    }
}
