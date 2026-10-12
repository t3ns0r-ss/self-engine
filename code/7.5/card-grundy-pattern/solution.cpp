#include <bits/stdc++.h>
using namespace std;

// method (Theorem 7.5.4): g(n) for a subtraction game by the first repeated window; brute: the plain table up to n.
int methodBig(const vector<int>& removals, long long n) {
    int m = *max_element(removals.begin(), removals.end());
    vector<int> g;
    map<vector<int>, int> firstSeen;
    for (int i = 0;; i++) {
        if (n < i) return g[n];
        if (i >= m) {
            auto [it, fresh] = firstSeen.emplace(vector<int>(g.end() - m, g.end()), i);
            if (!fresh) {
                int start = it->second, period = i - start;
                return g[start + (n - start) % period];
            }
        }
        set<int> reach;
        for (int r : removals)
            if (r <= i) reach.insert(g[i - r]);
        int mex = 0;
        while (reach.count(mex)) mex++;
        g.push_back(mex);
    }
}
int bruteTable(const vector<int>& removals, int n) {
    vector<int> g(n + 1, 0);
    for (int x = 1; x <= n; x++) {
        set<int> reach;
        for (int r : removals)
            if (r <= x) reach.insert(g[x - r]);
        while (reach.count(g[x])) g[x]++;
    }
    return g[n];
}
// A partisan game: Alice may remove the numbers in A, Bob those in B; the last mover wins; brute: a search with the player to move.
map<pair<int, int>, bool> memo;
bool partisanBrute(const vector<int>& A, const vector<int>& B, int n, int who) {
    auto key = make_pair(n, who);
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;
    bool win = false;
    for (int r : who == 0 ? A : B)
        if (r <= n && !partisanBrute(A, B, n - r, 1 - who)) win = true;
    return memo[key] = win;
}
int main() {
    cout << "P1 brute=" << bruteTable({1, 3, 4}, 100) << " method=" << methodBig({1, 3, 4}, 100) << "\n";
    cout << "P2 brute=" << bruteTable({1, 2}, 1000) << " method=" << methodBig({1, 2}, 1000) << "\n";
    // N1: Alice may remove 1 or 2 stones, Bob only 1, heap of 3; the method treats both players as having the moves 1 and 2 (g(3) = 0: lost)
    bool alice = partisanBrute({1, 2}, {1}, 3, 0);
    cout << "N1 brute=" << (alice ? "Alice" : "Bob") << " method=" << (methodBig({1, 2}, 3) ? "Alice" : "Bob") << "\n";
}
