#include <bits/stdc++.h>
using namespace std;

// Card example unit for "Place plus a set". Prints, for every inline example of the card in the order of the data file, the answer
// of a brute force and the answer of the card's method, e.g. "P1 brute=4 method=4".

struct Edge {
    int to;
    int weight;
};

// Method: breadth-first search over (vertex, set of vertices seen), counting edges; returns the walk length and the total weight of
// the first full walk it finds (starts in order of the vertex number, neighbours in the order the edges were added).
pair<int, int> searchOverVertexAndSet(const vector<vector<Edge>>& adj) {
    int n = adj.size(), full = (1 << n) - 1;
    vector<vector<int>> dist(n, vector<int>(1 << n, -1)), cost(n, vector<int>(1 << n, 0));
    queue<pair<int, int>> q;
    for (int v = 0; v < n; v++) {
        dist[v][1 << v] = 0;
        q.push({v, 1 << v});
    }
    while (!q.empty()) {
        auto [v, seen] = q.front();
        q.pop();
        if (seen == full) return {dist[v][seen], cost[v][seen]};
        for (auto [w, weight] : adj[v]) {
            int next = seen | (1 << w);
            if (dist[w][next] != -1) continue;
            dist[w][next] = dist[v][seen] + 1;
            cost[w][next] = cost[v][seen] + weight;
            q.push({w, next});
        }
    }
    return {-1, -1};
}

// Brute force: every order of first visits, the sum of the cheapest distances between consecutive vertices (weighted or not).
int cheapestOverOrders(const vector<vector<Edge>>& adj, bool useWeights) {
    int n = adj.size();
    const int INF = 1000000;
    vector<vector<int>> d(n, vector<int>(n, INF));
    for (int v = 0; v < n; v++) {
        d[v][v] = 0;
        for (auto [w, weight] : adj[v]) d[v][w] = min(d[v][w], useWeights ? weight : 1);
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    int best = INF;
    do {
        int total = 0;
        for (int i = 0; i + 1 < n; i++) total += d[order[i]][order[i + 1]];
        best = min(best, total);
    } while (next_permutation(order.begin(), order.end()));
    return best;
}

int main() {
    auto build = [&](int n, vector<array<int, 3>> edges) {
        vector<vector<Edge>> adj(n);
        for (auto [a, b, w] : edges) {
            adj[a].push_back({b, w});
            adj[b].push_back({a, w});
        }
        return adj;
    };
    // P1: star with centre 0 and leaves 1, 2, 3; fewest moves of a walk that visits every vertex.
    auto star = build(4, {{0, 1, 1}, {0, 2, 1}, {0, 3, 1}});
    cout << "P1 brute=" << cheapestOverOrders(star, false) << " method=" << searchOverVertexAndSet(star).first << "\n";
    // P2: a 2 x 2 board "11" / "00"; a flip toggles the chosen cell and its side neighbours; fewest flips to reach all zeros.
    // Brute force: every subset of the four flips (a flip twice cancels, and the order does not matter).
    vector<int> flipMask(4, 0);
    for (int r = 0; r < 2; r++)
        for (int c = 0; c < 2; c++) {
            int m = 1 << (r * 2 + c);
            if (r == 0) m |= 1 << ((r + 1) * 2 + c);
            if (r == 1) m |= 1 << ((r - 1) * 2 + c);
            if (c == 0) m |= 1 << (r * 2 + c + 1);
            if (c == 1) m |= 1 << (r * 2 + c - 1);
            flipMask[r * 2 + c] = m;
        }
    int start = 0b0011;  // cells (0,0) and (0,1) are 1
    int bruteFlips = INT_MAX;
    for (int subset = 0; subset < 16; subset++) {
        int board = start;
        for (int i = 0; i < 4; i++)
            if (subset >> i & 1) board ^= flipMask[i];
        if (board == 0) bruteFlips = min(bruteFlips, __builtin_popcount(subset));
    }
    // Method: breadth-first search over the 16 boards.
    vector<int> dist(16, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int board = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int next = board ^ flipMask[i];
            if (dist[next] == -1) dist[next] = dist[board] + 1, q.push(next);
        }
    }
    cout << "P2 brute=" << bruteFlips << " method=" << dist[0] << "\n";
    // N1: a path of 25 vertices. Brute force: the walk along the path has 24 moves (the distance between the two ends). Method: the
    // search over (vertex, set) would need 25 * 2^25 states.
    long long states = 25LL << 25;
    int pathMoves = 0;  // moves along the path from one end to the other
    for (int v = 1; v < 25; v++) pathMoves++;
    cout << "N1 brute=" << pathMoves << " method=too-slow\n";
    cout << "states of the search for 25 vertices: " << states << "\n";
    // N2: triangle with the edges 0-1 (5), 1-2 (5), 0-2 (1); the cheapest total weight of a walk that visits every vertex.
    auto triangle = build(3, {{0, 1, 5}, {1, 2, 5}, {0, 2, 1}});
    cout << "N2 brute=" << cheapestOverOrders(triangle, true) << " method=" << searchOverVertexAndSet(triangle).second << "\n";
}
