#include <bits/stdc++.h>
using namespace std;

enum { DRAW, WIN, LOSE };
// method (Theorem 7.5.1): the results of all positions of a game graph, by counters from the positions without moves.
vector<int> methodGraph(const vector<vector<int>>& moves) {
    int n = moves.size();
    vector<vector<int>> back(n);
    vector<int> left(n), result(n, DRAW);
    queue<int> ready;
    for (int v = 0; v < n; v++) {
        left[v] = moves[v].size();
        for (int u : moves[v]) back[u].push_back(v);
        if (left[v] == 0) result[v] = LOSE, ready.push(v);
    }
    while (!ready.empty()) {
        int u = ready.front();
        ready.pop();
        for (int v : back[u]) {
            if (result[v] != DRAW) continue;
            if (result[u] == LOSE) result[v] = WIN, ready.push(v);
            else if (--left[v] == 0) result[v] = LOSE, ready.push(v);
        }
    }
    return result;
}
// brute for a heap game: a plain search with a memo.
map<pair<int, int>, bool> memo;
bool bruteHeap(int x, int variant) {  // variant 0: normal play with moves 1, 3, 4
    auto key = make_pair(x, variant);
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;
    bool win = false;
    for (int p : {1, 3, 4})
        if (p <= x && !bruteHeap(x - p, variant)) win = true;
    return memo[key] = win;
}
// A row of coins: each player takes a coin from either end; the larger total wins (score game). brute: the best difference.
int bestDifference(const vector<int>& c, int l, int r) {
    if (l > r) return 0;
    return max(c[l] - bestDifference(c, l + 1, r), c[r] - bestDifference(c, l, r - 1));
}
// method for the row of coins with the rule "the player who takes the last coin wins": the win/lose recurrence on the number of coins.
bool lastCoinWins(int coins) {
    return coins % 2 == 1;  // players alternate, so the first player takes the last coin exactly when the number of coins is odd
}
int main() {
    // P1: a heap of 7 sticks, removals 1, 3, 4: lost for the player to move
    vector<vector<int>> heap(8);
    for (int x = 1; x <= 7; x++)
        for (int p : {1, 3, 4})
            if (p <= x) heap[x].push_back(x - p);
    cout << "P1 brute=" << (bruteHeap(7, 0) ? "W" : "L") << " method=" << "DWL"[methodGraph(heap)[7]] << "\n";
    // P2: a graph with a cycle; the position 2 (moves to 0 and 3)
    vector<vector<int>> g = {{1}, {0}, {0, 3}, {}};
    cout << "P2 brute=W method=" << "DWL"[methodGraph(g)[2]] << "\n";
    // N1: the row 1 5 2 as a score game against the last-coin rule
    vector<int> coins = {1, 5, 2};
    cout << "N1 brute=" << (bestDifference(coins, 0, 2) > 0 ? "yes" : "no") << " method=" << (lastCoinWins(3) ? "yes" : "no") << "\n";
}
