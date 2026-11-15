#include <bits/stdc++.h>
using namespace std;

// method: the Grundy value of each pile, and the xor over the piles. brute: a search over the positions of the sum.
vector<int> grundyTable(const vector<int>& removals, int n) {
    vector<int> g(n + 1, 0);
    for (int x = 1; x <= n; x++) {
        set<int> reach;
        for (int r : removals)
            if (r <= x) reach.insert(g[x - r]);
        while (reach.count(g[x])) g[x]++;
    }
    return g;
}
map<vector<int>, bool> memo;
vector<int> rule;
bool bruteWin(vector<int> heaps) {  // each move removes r in `rule` from one heap
    sort(heaps.begin(), heaps.end());
    auto it = memo.find(heaps);
    if (it != memo.end()) return it->second;
    bool win = false;
    for (size_t i = 0; i < heaps.size() && !win; i++)
        for (int r : rule)
            if (r <= heaps[i] && !win) {
                vector<int> next = heaps;
                next[i] -= r;
                win = !bruteWin(next);
            }
    return memo[heaps] = win;
}
// Another Game: a move chooses any non-empty set of non-empty piles and removes one stone from each. brute: a search.
map<vector<int>, bool> anotherMemo;
bool anotherBrute(const vector<int>& piles) {
    auto it = anotherMemo.find(piles);
    if (it != anotherMemo.end()) return it->second;
    bool win = false;
    int n = piles.size();
    for (int mask = 1; mask < (1 << n) && !win; mask++) {
        vector<int> next = piles;
        bool ok = true;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) {
                if (next[i] == 0) ok = false;
                else next[i]--;
            }
        if (ok && !anotherBrute(next)) win = true;
    }
    return anotherMemo[piles] = win;
}
int main() {
    auto name = [](bool first) { return first ? "first" : "second"; };
    rule = {1, 3, 4};
    auto g = grundyTable(rule, 9);
    auto xorOf = [&](const vector<int>& heaps) {
        int x = 0;
        for (int h : heaps) x ^= g[h];
        return x != 0;
    };
    cout << "P1 brute=" << name(bruteWin({5, 3, 6})) << " method=" << name(xorOf({5, 3, 6})) << "\n";
    memo.clear();
    rule = {2, 3};  // Constrained Nim with L = 2, R = 3
    g = grundyTable(rule, 9);
    cout << "P2 brute=" << name(bruteWin({4, 7})) << " method=" << name(xorOf({4, 7})) << "\n";
    // N1: two piles of 1 in Another Game; each pile alone is a game with the single removal 1 (value x mod 2), the xor of two 1s is 0
    cout << "N1 brute=" << name(anotherBrute({1, 1})) << " method=" << name(false) << "\n";
}
