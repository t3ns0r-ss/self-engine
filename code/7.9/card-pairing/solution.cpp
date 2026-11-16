#include <bits/stdc++.h>
using namespace std;

// Card unit for "Bipartite matching and König's theorem". Each line prints the brute-force answer and the answer of the card's method
// for one inline example, in the order of the examples in the topic file.

struct Matching {  // Kuhn's algorithm (Theorem 7.9.6)
    vector<vector<int>> adj;
    vector<int> matchOf;
    vector<bool> seen;
    Matching(int L, int R) : adj(L), matchOf(R, -1), seen(R) {}
    bool tryAugment(int u) {
        for (int v : adj[u]) {
            if (seen[v]) continue;
            seen[v] = true;
            if (matchOf[v] < 0 || tryAugment(matchOf[v])) { matchOf[v] = u; return true; }
        }
        return false;
    }
    int solve() {
        int size = 0;
        for (int u = 0; u < (int)adj.size(); u++) { fill(seen.begin(), seen.end(), false); size += tryAugment(u); }
        return size;
    }
};

int main() {
    // P1: left 1: {a, b}, left 2: {a}, left 3: {a}. Brute force: try every way to give each left vertex a free right vertex or none.
    vector<vector<int>> lists = {{0, 1}, {0}, {0}};
    int best = 0;
    function<void(int, int, int)> rec = [&](int i, int used, int count) {
        if (i == 3) { best = max(best, count); return; }
        rec(i + 1, used, count);
        for (int v : lists[i])
            if (!(used >> v & 1)) rec(i + 1, used | 1 << v, count + 1);
    };
    rec(0, 0, 0);
    Matching m1(3, 2);
    m1.adj = lists;
    cout << "P1 brute=" << best << " method=" << m1.solve() << "\n";

    // P2: a 3 x 3 grid with coins at (1,1), (1,2), (2,1), (3,3); a move clears a row or a column.
    // Brute force: try every set of the 6 lines. Method: the largest matching between rows and columns (one edge per coin).
    int coins[4][2] = {{0, 0}, {0, 1}, {1, 0}, {2, 2}};
    int fewest = 6;
    for (int mask = 0; mask < 64; mask++) {  // bits 0..2: rows, bits 3..5: columns
        bool ok = true;
        for (auto& c : coins)
            if (!(mask >> c[0] & 1) && !(mask >> (3 + c[1]) & 1)) ok = false;
        if (ok) fewest = min(fewest, __builtin_popcount(mask));
    }
    Matching m2(3, 3);
    for (auto& c : coins) m2.adj[c[0]].push_back(c[1]);
    cout << "P2 brute=" << fewest << " method=" << m2.solve() << "\n";

    // N1: three people who are all friends with each other, to be paired up (a triangle); not a bipartite graph.
    // Brute force: any two of the three can be paired, and then one is left over. Wrong method: split each person into a left copy and a
    // right copy and run Kuhn on the doubled graph (person i on the left with friend j on the right).
    Matching m3(3, 3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (i != j) m3.adj[i].push_back(j);
    cout << "N1 brute=" << 1 << " method=" << m3.solve() << "\n";

    // N2: three people who each like all three hats; in how many ways can they wear different hats? Brute force: count the permutations.
    // Wrong method: the size of a largest matching.
    int ways = 0;
    vector<int> hat = {0, 1, 2};
    do ways++; while (next_permutation(hat.begin(), hat.end()));
    Matching m4(3, 3);
    for (int i = 0; i < 3; i++) m4.adj[i] = {0, 1, 2};
    cout << "N2 brute=" << ways << " method=" << m4.solve() << "\n";
}
