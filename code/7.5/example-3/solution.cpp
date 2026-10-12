#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 2207, Grundy's Game. A heap of n coins (n up to 2000). A move splits one heap into two non-empty heaps of different sizes. The player
who cannot move loses. For each of t heap sizes print "first" if the first player wins and "second" otherwise.
Input: t, then t numbers n.
Output: t lines.
*/


// snippet:begin
// Theorem 7.5.3: a heap of x coins has the Grundy value g(x) = mex of g(a) xor g(x - a) over the splits a < x - a (the two parts are
// independent games, so their values combine by xor). The first player wins exactly when g(n) is not 0.
vector<int> grundyOfSplits(int n) {
    vector<int> g(n + 1, 0);
    for (int x = 1; x <= n; x++) {
        set<int> reach;
        for (int a = 1; a < x - a; a++) reach.insert(g[a] ^ g[x - a]);
        while (reach.count(g[x])) g[x]++;
    }
    return g;
}
// snippet:end

int main() {
    int t;
    cin >> t;
    vector<int> ns(t);
    for (int& n : ns) cin >> n;
    auto g = grundyOfSplits(*max_element(ns.begin(), ns.end()));
    for (int n : ns) cout << (g[n] ? "first" : "second") << "\n";
}
