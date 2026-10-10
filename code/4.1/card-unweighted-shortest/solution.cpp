#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cost;
};

// Method: the route with the fewest edges from queue-based search (ties by first discovery); returns the total COST of that route.
int bfsRouteCost(int n, const vector<array<int, 3>>& edges, int from, int to) {
    vector<vector<Edge>> adj(n + 1);
    for (auto [a, b, c] : edges) {
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    vector<int> dist(n + 1, -1), cost(n + 1, 0);
    queue<int> q;
    dist[from] = 0;
    q.push(from);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (Edge e : adj[u])
            if (dist[e.to] == -1) {
                dist[e.to] = dist[u] + 1;
                cost[e.to] = cost[u] + e.cost;
                q.push(e.to);
            }
    }
    return cost[to];
}
int bfsEdges(int n, const vector<array<int, 3>>& edges, int from, int to) {
    vector<vector<int>> adj(n + 1);
    for (auto [a, b, c] : edges) {
        (void)c;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[from] = 0;
    q.push(from);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int w : adj[u])
            if (dist[w] == -1) {
                dist[w] = dist[u] + 1;
                q.push(w);
            }
    }
    return dist[to];
}

// Brute force: try every simple route (each vertex at most once) by recursion; returns {fewest edges, least cost}.
void tryRoutes(int u, int to, int edgesUsed, int costUsed, vector<bool>& seen, const vector<vector<Edge>>& adj, int& bestEdges, int& bestCost) {
    if (u == to) {
        bestEdges = min(bestEdges, edgesUsed);
        bestCost = min(bestCost, costUsed);
        return;
    }
    seen[u] = true;
    for (Edge e : adj[u])
        if (!seen[e.to]) tryRoutes(e.to, to, edgesUsed + 1, costUsed + e.cost, seen, adj, bestEdges, bestCost);
    seen[u] = false;
}
pair<int, int> allRoutes(int n, const vector<array<int, 3>>& edges, int from, int to) {
    vector<vector<Edge>> adj(n + 1);
    for (auto [a, b, c] : edges) {
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    vector<bool> seen(n + 1, false);
    int bestEdges = INT_MAX, bestCost = INT_MAX;
    tryRoutes(from, to, 0, 0, seen, adj, bestEdges, bestCost);
    return {bestEdges, bestCost};
}

int main() {
    // P1: 6 rooms, corridors 1-2 2-3 3-4 4-5 1-6 6-5 (cost 1 each); fewest corridors from room 1 to room 5.
    vector<array<int, 3>> corridors = {{1, 2, 1}, {2, 3, 1}, {3, 4, 1}, {4, 5, 1}, {1, 6, 1}, {6, 5, 1}};
    cout << "P1 brute=" << allRoutes(6, corridors, 1, 5).first << " method=" << bfsEdges(6, corridors, 1, 5) << "\n";
    // N1: edges 1-2 (cost 10), 1-3 (cost 1), 3-2 (cost 1); the cheapest route from 1 to 2 (the search above counts edges, not cost).
    vector<array<int, 3>> weighted = {{1, 2, 10}, {1, 3, 1}, {3, 2, 1}};
    cout << "N1 brute=" << allRoutes(3, weighted, 1, 2).second << " method=" << bfsRouteCost(3, weighted, 1, 2) << "\n";
}
