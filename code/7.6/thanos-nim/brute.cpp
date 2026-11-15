#include <bits/stdc++.h>
using namespace std;

map<vector<int>, bool> memo;
bool win(vector<int> piles) {  // the player to move wins? a search over all positions
    sort(piles.begin(), piles.end());
    auto it = memo.find(piles);
    if (it != memo.end()) return it->second;
    int n = piles.size();
    bool result = false;
    for (int mask = 0; mask < (1 << n) && !result; mask++) {  // the chosen piles
        if (__builtin_popcount(mask) != n / 2) continue;
        bool ok = true;
        for (int i = 0; i < n; i++)
            if ((mask >> i & 1) && piles[i] == 0) ok = false;
        if (!ok) continue;
        // every way of removing a positive number from each chosen pile
        function<bool(int, vector<int>&)> go = [&](int i, vector<int>& cur) {
            if (i == n) return !win(cur);
            if (!(mask >> i & 1)) return go(i + 1, cur);
            int old = cur[i];
            for (int take = 1; take <= old; take++) {
                cur[i] = old - take;
                if (go(i + 1, cur)) return cur[i] = old, true;
            }
            cur[i] = old;
            return false;
        };
        vector<int> cur = piles;
        result = go(0, cur);
    }
    return memo[piles] = result;
}
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << (win(a) ? "Alice" : "Bob") << "\n";
}
