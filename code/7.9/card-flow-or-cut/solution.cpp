#include <bits/stdc++.h>
using namespace std;

// Card unit for "Maximum flow or minimum cut". Each line prints the brute-force answer and the answer of the card's method for one
// inline example, in the order of the examples in the topic file.

const int N = 6;
long long cap[N][N];
long long maxFlow(int s, int t) {  // the matrix version of Theorem 7.9.1
    long long flow = 0;
    while (true) {
        int parent[N];
        fill(parent, parent + N, -1);
        parent[s] = s;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < N; v++)
                if (parent[v] < 0 && cap[u][v] > 0) { parent[v] = u; q.push(v); }
        }
        if (parent[t] < 0) return flow;
        long long push = LLONG_MAX;
        for (int v = t; v != s; v = parent[v]) push = min(push, cap[parent[v]][v]);
        for (int v = t; v != s; v = parent[v]) { cap[parent[v]][v] -= push; cap[v][parent[v]] += push; }
        flow += push;
    }
}

int main() {
    // P1: s = 0, a = 1, b = 2, t = 3. Edges s->a 2, s->b 2, a->b 1, a->t 1, b->t 2. Brute force: the cheapest cut over all vertex sets.
    vector<array<long long, 3>> e1 = {{0, 1, 2}, {0, 2, 2}, {1, 2, 1}, {1, 3, 1}, {2, 3, 2}};
    long long bestCut = LLONG_MAX;
    for (int mask = 0; mask < 16; mask++) {
        if (!(mask & 1) || (mask & 8)) continue;
        long long total = 0;
        for (auto& e : e1)
            if ((mask >> e[0] & 1) && !(mask >> e[1] & 1)) total += e[2];
        bestCut = min(bestCut, total);
    }
    memset(cap, 0, sizeof cap);
    for (auto& e : e1) cap[e[0]][e[1]] += e[2];
    cout << "P1 brute=" << bestCut << " method=" << maxFlow(0, 3) << "\n";

    // P2: a row of four cells B ? ? W; colour the ? cells to maximise the number of neighbouring cells with different colours.
    // Brute force: try all four fillings. Method: flip the colour of every second cell, so that "different" becomes "equal";
    // the answer is the number of neighbouring pairs minus the cheapest cut (fixed cells are tied to the source or the sink with infinite capacity).
    int bestDifferent = 0;
    for (int fill = 0; fill < 4; fill++) {
        int c[4] = {1, fill & 1, fill >> 1 & 1, 0};  // 1 = black, 0 = white
        int different = 0;
        for (int i = 0; i + 1 < 4; i++) different += c[i] != c[i + 1];
        bestDifferent = max(bestDifferent, different);
    }
    const long long INF = 1000000;
    memset(cap, 0, sizeof cap);
    // cells 0..3, source 4, sink 5. After flipping the odd cells: cell 0 is black, cell 3 (white, odd) becomes black.
    cap[4][0] = INF;
    cap[4][3] = INF;
    for (int i = 0; i + 1 < 4; i++) cap[i][i + 1] = cap[i + 1][i] = 1;
    cout << "P2 brute=" << bestDifferent << " method=" << 3 - maxFlow(4, 5) << "\n";

    // N1: the cheapest route from 1 to 3 with edge costs 1->2: 2, 2->3: 2, 1->3: 5. Brute force: the cheaper of the two routes.
    // Wrong method: read the costs as capacities and ask for the maximum flow.
    memset(cap, 0, sizeof cap);
    cap[0][1] = 2; cap[1][2] = 2; cap[0][2] = 5;
    cout << "N1 brute=" << min(2 + 2, 5) << " method=" << maxFlow(0, 2) << "\n";

    // N2: how many different paths from s to t in the graph s->a, s->b, a->b, a->t, b->t. Brute force: count the paths.
    // Wrong method: the largest number of paths without a shared edge.
    int paths = 0;  // s-a-t, s-b-t, s-a-b-t
    int adj[4][4] = {{0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}};
    function<void(int)> count = [&](int u) {
        if (u == 3) { paths++; return; }
        for (int v = 0; v < 4; v++)
            if (adj[u][v]) count(v);
    };
    count(0);
    memset(cap, 0, sizeof cap);
    for (int u = 0; u < 4; u++)
        for (int v = 0; v < 4; v++) cap[u][v] = adj[u][v];
    cout << "N2 brute=" << paths << " method=" << maxFlow(0, 3) << "\n";
}
