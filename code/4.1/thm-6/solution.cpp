#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.1.6. The fewest moves that turn the number start into target when a move adds 1 or doubles the number and no number may
// exceed limit; -1 if it cannot be done. The states are the numbers; their distances live in a map.
int fewestMoves(int start, int target, int limit) {
    map<int, int> dist;
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == target) return dist[u];
        for (int w : {u + 1, u * 2}) {  // the two moves from state u
            if (w > limit || dist.count(w)) continue;
            dist[w] = dist[u] + 1;
            q.push(w);
        }
    }
    return -1;
}
// snippet:end

int main() {
    cout << "start 3, target 10, limit 100: answer " << fewestMoves(3, 10, 100) << "\n";
    cout << "start 5, target 5, limit 100: answer " << fewestMoves(5, 5, 100) << "\n";
    cout << "start 7, target 3, limit 100: answer " << fewestMoves(7, 3, 100) << "\n";
    // Check against a table filled in increasing order (every move increases the number), for all starts and targets up to 60.
    int limit = 100;
    for (int start = 1; start <= 60; start++) {
        const int INF = 1e9;
        vector<int> best(limit + 1, INF);
        best[start] = 0;
        for (int x = start; x <= limit; x++) {
            if (best[x] == INF) continue;
            if (x + 1 <= limit) best[x + 1] = min(best[x + 1], best[x] + 1);
            if (2 * x <= limit) best[2 * x] = min(best[2 * x], best[x] + 1);
        }
        for (int target = 1; target <= 60; target++) {
            int expected = best[target] == INF ? -1 : best[target];
            if (fewestMoves(start, target, limit) != expected) return 1;
        }
    }
}
