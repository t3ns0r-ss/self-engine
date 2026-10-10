#include <bits/stdc++.h>
using namespace std;

// Method: queue-based search over the numbers; moves "add 1" and "times 3" (never above `limit`).
int fewestPresses(int start, int target, int limit) {
    map<int, int> dist;
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == target) return dist[u];
        for (int w : {u + 1, u * 3}) {
            if (w > limit || dist.count(w)) continue;
            dist[w] = dist[u] + 1;
            q.push(w);
        }
    }
    return -1;
}
// Brute force for the same question: a table filled in increasing order of the number (both moves increase it).
int fewestPressesTable(int start, int target, int limit) {
    const int INF = 1e9;
    vector<int> best(limit + 1, INF);
    best[start] = 0;
    for (int x = start; x <= limit; x++) {
        if (best[x] == INF) continue;
        if (x + 1 <= limit) best[x + 1] = min(best[x + 1], best[x] + 1);
        if (3 * x <= limit) best[3 * x] = min(best[3 * x], best[x] + 1);
    }
    return best[target] == INF ? -1 : best[target];
}

// Two jugs of sizes 3 and 5: fewest operations (fill, empty, pour) until one jug holds 4. Method: queue-based search over (a, b).
int jugsSearch() {
    map<pair<int, int>, int> dist;
    queue<pair<int, int>> q;
    dist[{0, 0}] = 0;
    q.push({0, 0});
    while (!q.empty()) {
        auto [a, b] = q.front();
        q.pop();
        if (a == 4 || b == 4) return dist[{a, b}];
        int pourAB = min(a, 5 - b), pourBA = min(b, 3 - a);
        vector<pair<int, int>> next = {{3, b}, {a, 5}, {0, b}, {a, 0}, {a - pourAB, b + pourAB}, {a + pourBA, b - pourBA}};
        for (auto s : next)
            if (!dist.count(s)) {
                dist[s] = dist[{a, b}] + 1;
                q.push(s);
            }
    }
    return -1;
}
// Brute force for the jugs: allow a sequence of at most `depth` operations, trying every sequence; increase the depth until 4 appears.
bool jugsTry(int a, int b, int left) {
    if (a == 4 || b == 4) return true;
    if (left == 0) return false;
    int pourAB = min(a, 5 - b), pourBA = min(b, 3 - a);
    int next[6][2] = {{3, b}, {a, 5}, {0, b}, {a, 0}, {a - pourAB, b + pourAB}, {a + pourBA, b - pourBA}};
    for (auto& s : next)
        if (jugsTry(s[0], s[1], left - 1)) return true;
    return false;
}
int jugsBrute() {
    for (int depth = 0; depth <= 12; depth++)
        if (jugsTry(0, 0, depth)) return depth;
    return -1;
}

int main() {
    // P1: counter shows 2; moves "add 1" or "times 3"; fewest presses to show exactly 29 (never above 10000).
    cout << "P1 brute=" << fewestPressesTable(2, 29, 10000) << " method=" << fewestPresses(2, 29, 10000) << "\n";
    // P2: the two jugs.
    cout << "P2 brute=" << jugsBrute() << " method=" << jugsSearch() << "\n";
    // N1: walk from 0 to 6 on a line; the move +1 costs 1 and the move +3 costs 5; the cheapest total cost.
    // Brute force: table by increasing position. Method: fewest moves (a queue search), reported as the cost of that route.
    int cost[7];
    cost[0] = 0;
    for (int x = 1; x <= 6; x++) {
        cost[x] = cost[x - 1] + 1;
        if (x >= 3) cost[x] = min(cost[x], cost[x - 3] + 5);
    }
    vector<int> moves(7, -1), costOfFewest(7, 0);
    queue<int> q;
    moves[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        // moves are tried in the order +1, +3
        if (u + 1 <= 6 && moves[u + 1] == -1) {
            moves[u + 1] = moves[u] + 1;
            costOfFewest[u + 1] = costOfFewest[u] + 1;
            q.push(u + 1);
        }
        if (u + 3 <= 6 && moves[u + 3] == -1) {
            moves[u + 3] = moves[u] + 1;
            costOfFewest[u + 3] = costOfFewest[u] + 5;
            q.push(u + 3);
        }
    }
    cout << "N1 brute=" << cost[6] << " method=" << costOfFewest[6] << "\n";
}
