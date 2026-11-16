#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 7.9.1. cap[u][v] is the capacity of the edge u -> v (0 when there is none).
// maxFlow pushes flow along augmenting paths (paths of positive residual capacity) until none is left
// and returns the flow value. At the end inS[v] says whether v can still be reached from s;
// the set of such vertices is a minimum cut.
const int N = 4;
long long cap[N][N];  // long long: capacities up to 4 * 10^18 are used in an example
bool inS[N];
long long maxFlow(int s, int t) {
    long long flow = 0;
    while (true) {
        int parent[N];
        fill(parent, parent + N, -1);
        parent[s] = s;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {  // breadth-first search in the residual graph
            int u = q.front();
            q.pop();
            for (int v = 0; v < N; v++)
                if (parent[v] < 0 && cap[u][v] > 0) { parent[v] = u; q.push(v); }
        }
        for (int v = 0; v < N; v++) inS[v] = parent[v] >= 0;
        if (parent[t] < 0) return flow;  // no augmenting path: the flow is maximum
        long long push = LLONG_MAX;
        for (int v = t; v != s; v = parent[v]) push = min(push, cap[parent[v]][v]);
        for (int v = t; v != s; v = parent[v]) { cap[parent[v]][v] -= push; cap[v][parent[v]] += push; }
        flow += push;
    }
}
// snippet:end

long long orig[N][N];

// Capacity of the cut given by the side mask (bit v set: v is on the source side).
long long cutCapacity(int mask) {
    long long total = 0;
    for (int u = 0; u < N; u++)
        for (int v = 0; v < N; v++)
            if ((mask >> u & 1) && !(mask >> v & 1)) total += orig[u][v];
    return total;
}

void show(const char* name, long long flow) {
    int mask = 0;
    cout << name << ": flow = " << flow << ", source side = {";
    bool first = true;
    for (int v = 0; v < N; v++)
        if (inS[v]) {
            cout << (first ? "" : ",") << v;
            first = false;
            mask |= 1 << v;
        }
    cout << "}, cut capacity = " << cutCapacity(mask) << "\n";
}

void load(initializer_list<array<long long, 3>> edges) {
    memset(cap, 0, sizeof cap);
    for (auto e : edges) cap[e[0]][e[1]] += e[2];
    memcpy(orig, cap, sizeof cap);
}

int main() {
    // Vertices: 0 = s, 3 = t.
    load({{0, 1, 2}, {0, 2, 2}, {1, 2, 1}, {1, 3, 1}, {2, 3, 2}});
    show("tiny", maxFlow(0, 3));
    load({{0, 1, 1}, {0, 2, 1}, {1, 2, 1}, {1, 3, 1}, {2, 3, 1}});
    show("diamond", maxFlow(0, 3));
    load({{0, 1, 5}});
    show("no path", maxFlow(0, 3));
    load({{0, 1, 4000000000000000000LL}, {1, 3, 4000000000000000000LL}});
    show("huge", maxFlow(0, 3));

    // Check the theorem on every graph on 4 vertices with capacities 0, 1 or 2: the flow equals the capacity of the cut
    // given by inS, and no cut has a smaller capacity (all 4 cuts are tried).
    int pairs[12][2], k = 0;
    for (int u = 0; u < N; u++)
        for (int v = 0; v < N; v++)
            if (u != v) { pairs[k][0] = u; pairs[k][1] = v; k++; }
    long long total = 1;
    for (int i = 0; i < 12; i++) total *= 3;
    for (long long code = 0; code < total; code++) {
        long long c = code;
        memset(cap, 0, sizeof cap);
        for (int i = 0; i < 12; i++) { cap[pairs[i][0]][pairs[i][1]] = c % 3; c /= 3; }
        memcpy(orig, cap, sizeof cap);
        long long flow = maxFlow(0, 3);
        int mask = 0;
        for (int v = 0; v < N; v++) mask |= inS[v] << v;
        if (!(mask & 1) || (mask & 8) || cutCapacity(mask) != flow) return 1;
        for (int m = 0; m < 16; m++)
            if ((m & 1) && !(m & 8) && cutCapacity(m) < flow) return 1;
    }
}
