#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.3.3. Unbounded knapsack: the amount loop runs upwards, so a coin can be used again. With the coin loop outside each
// multiset is counted once; with the amount loop outside each ordered sequence is counted.
long long multisets(const vector<int>& coins, int x) {
    vector<long long> ways(x + 1, 0);
    ways[0] = 1;
    for (int c : coins) for (int s = c; s <= x; s++) ways[s] += ways[s - c];
    return ways[x];
}
long long sequences(const vector<int>& coins, int x) {
    vector<long long> ways(x + 1, 0);
    ways[0] = 1;
    for (int s = 1; s <= x; s++) for (int c : coins) if (c <= s) ways[s] += ways[s - c];
    return ways[x];
}
// snippet:end

int main() {
    cout << "coins 1 2, total 3: " << multisets({1, 2}, 3) << " multisets, " << sequences({1, 2}, 3) << " ordered sequences\n";
    for (int x = 0; x <= 15; x++) for (auto coins : vector<vector<int>>{{1, 2}, {2, 3, 5}, {1, 4, 6}}) {
        long long seqBrute = 0;
        function<void(int)> go = [&](int left) { if (left == 0) { seqBrute++; return; } for (int c : coins) if (c <= left) go(left - c); };
        go(x);
        if (seqBrute != sequences(coins, x)) return 1;
    }
}
