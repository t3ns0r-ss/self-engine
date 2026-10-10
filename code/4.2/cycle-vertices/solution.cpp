/*
Problem: towns with one road each.
Input: n, then n integers next_1 .. next_n: the town that the one-way road from town i leads to, or 0 if town i has no road.
Output: how many towns lie on a cycle of roads.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 4.2.4 for graphs where every vertex has at most one arrow (next[v] = 0 means none): how many vertices lie on a cycle.
int verticesOnCycles(const vector<int>& next) {
    int n = next.size() - 1, onCycle = 0;
    vector<int> state(n + 1, 0);  // 0 not entered, 1 on the current route, 2 finished
    for (int s = 1; s <= n; s++) {
        if (state[s] != 0) continue;
        vector<int> route;
        int v = s;
        while (v != 0 && state[v] == 0) {  // follow the arrows until the route ends or meets a known vertex
            state[v] = 1;
            route.push_back(v);
            v = next[v];
        }
        if (v != 0 && state[v] == 1)  // the route ran into itself: the cycle is the part of the route from v on
            onCycle += route.end() - find(route.begin(), route.end(), v);
        for (int u : route) state[u] = 2;
    }
    return onCycle;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> next(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> next[i];
    cout << verticesOnCycles(next) << "\n";
}
