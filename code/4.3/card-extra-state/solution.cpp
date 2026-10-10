#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX / 4;
typedef vector<array<long long, 3>> Edges;  // {from, to, weight}, one-way

// A voucher changes the cost of ONE road: `mode` 0 = free (cost 0), 1 = paid back (cost -w).
long long voucherCost(long long w, int mode) { return mode == 0 ? 0 : -w; }

// Method: Dijkstra on pairs (vertex, voucher used), finishing a pair the first time it comes out of the heap (Theorem 4.3.5).
long long pairsDijkstra(int n, const Edges& edges, int t, int mode) {
    vector<vector<pair<int, long long>>> adj(2 * n + 2);
    for (auto [a, b, w] : edges) {
        adj[a].push_back({(int)b, w});
        adj[a + n].push_back({(int)b + n, w});
        adj[a].push_back({(int)b + n, voucherCost(w, mode)});
    }
    vector<long long> dist(2 * n + 2, INF);
    vector<bool> done(2 * n + 2, false);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> heap;
    dist[1] = 0;
    heap.push({0, 1});
    while (!heap.empty()) {
        auto [d, u] = heap.top();
        heap.pop();
        if (done[u]) continue;
        done[u] = true;
        for (auto [v, w] : adj[u])
            if (d + w < dist[v]) dist[v] = d + w, heap.push({dist[v], v});
    }
    return min(dist[t], dist[t + n]);
}

// Brute force: try the voucher on each road in turn (and not at all); a plain shortest-path search by repeated relaxation each time.
long long tryEachRoad(int n, const Edges& edges, int t, int mode) {
    auto plain = [&](int chosen) {
        vector<long long> dist(n + 1, INF);
        dist[1] = 0;
        for (int round = 0; round < n; round++)
            for (size_t i = 0; i < edges.size(); i++) {
                auto [a, b, w] = edges[i];
                if ((int)i == chosen) w = voucherCost(w, mode);
                if (dist[a] < INF && dist[a] + w < dist[b]) dist[b] = dist[a] + w;
            }
        return dist[t];
    };
    long long best = plain(-1);
    for (size_t i = 0; i < edges.size(); i++) best = min(best, plain(i));
    return best;
}

const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

// Grid with walls '#': one wall may be broken; fewest steps from the top-left to the top-right cell. Method: search over
// (cell, wall broken yet?) with a queue.
int stepsWithOneBreak(const vector<string>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<array<int, 2>>> dist(rows, vector<array<int, 2>>(cols, {INT_MAX, INT_MAX}));
    queue<array<int, 3>> q;
    dist[0][0][0] = 0;
    q.push({0, 0, 0});
    while (!q.empty()) {
        auto [r, c, used] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            int nu = used + (grid[nr][nc] == '#');
            if (nu > 1 || dist[nr][nc][nu] != INT_MAX) continue;
            dist[nr][nc][nu] = dist[r][c][used] + 1;
            q.push({nr, nc, nu});
        }
    }
    return min(dist[0][cols - 1][0], dist[0][cols - 1][1]);
}
// Brute force: remove each wall in turn (or none), then search over the cells alone.
int bruteBreak(vector<string> grid) {
    int rows = grid.size(), cols = grid[0].size(), best = INT_MAX;
    auto search = [&](const vector<string>& g) {
        vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
        queue<pair<int, int>> q;
        dist[0][0] = 0;
        q.push({0, 0});
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || g[nr][nc] == '#' || dist[nr][nc] != INT_MAX) continue;
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
        return dist[0][cols - 1];
    };
    best = search(grid);
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid[r][c] == '#') {
                grid[r][c] = '.';
                best = min(best, search(grid));
                grid[r][c] = '#';
            }
    return best;
}

int main() {
    // P1: one-way roads 1>2 (5), 2>3 (6), 3>4 (7); one road may be taken for free; the cheapest trip from 1 to 4.
    Edges path = {{1, 2, 5}, {2, 3, 6}, {3, 4, 7}};
    cout << "P1 brute=" << tryEachRoad(4, path, 4, 0) << " method=" << pairsDijkstra(4, path, 4, 0) << "\n";
    // P2: a 3 x 4 map; one wall may be broken; the fewest steps from the top-left to the top-right cell.
    vector<string> map = {"..#.", ".##.", "...."};
    cout << "P2 brute=" << bruteBreak(map) << " method=" << stepsWithOneBreak(map) << "\n";
    // N1: one-way roads 1>3 (1), 1>2 (5), 2>3 (10), 3>4 (1); a bonus voucher pays you the price of ONE road instead of you paying it
    // (the road costs -w). The cheapest (most negative) total from 1 to 4.
    Edges bonus = {{1, 3, 1}, {1, 2, 5}, {2, 3, 10}, {3, 4, 1}};
    cout << "N1 brute=" << tryEachRoad(4, bonus, 4, 1) << " method=" << pairsDijkstra(4, bonus, 4, 1) << "\n";
}
