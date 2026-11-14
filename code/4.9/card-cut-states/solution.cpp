#include <bits/stdc++.h>
using namespace std;

// Card example unit for "Cut the state down". Prints, for every inline example of the card in the order of the data file, the answer
// of a brute force and the answer of the card's method, e.g. "P1 brute=4 method=4".

// Fewest steps from the top-left to the bottom-right cell with at most k obstacles entered.
// Brute force: a search over every state (cell, obstacles used). Method: the same search, entering a state only if it has more
// obstacles left than every earlier visit of that cell.
int fullStates(const vector<string>& grid, int k) {
    int rows = grid.size(), cols = grid[0].size();
    vector<int> dist(rows * cols * (k + 1), -1);
    queue<array<int, 3>> q;
    dist[0] = 0;
    q.push({0, 0, 0});
    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    int answer = -1;
    while (!q.empty()) {
        auto [r, c, used] = q.front();
        q.pop();
        int here = dist[(r * cols + c) * (k + 1) + used];
        if (r == rows - 1 && c == cols - 1 && (answer == -1 || here < answer)) answer = here;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            int nu = used + (grid[nr][nc] == '#');
            if (nu > k) continue;
            int& slot = dist[(nr * cols + nc) * (k + 1) + nu];
            if (slot == -1) slot = here + 1, q.push({nr, nc, nu});
        }
    }
    return answer;
}
int withDomination(const vector<string>& grid, int k) {
    int rows = grid.size(), cols = grid[0].size();
    vector<int> bestLeft(rows * cols, -1);
    queue<array<int, 4>> q;
    bestLeft[0] = k;
    q.push({0, 0, k, 0});
    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    while (!q.empty()) {
        auto [r, c, left, steps] = q.front();
        q.pop();
        if (r == rows - 1 && c == cols - 1) return steps;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            int nextLeft = left - (grid[nr][nc] == '#');
            if (nextLeft < 0 || nextLeft <= bestLeft[nr * cols + nc]) continue;
            bestLeft[nr * cols + nc] = nextLeft;
            q.push({nr, nc, nextLeft, steps + 1});
        }
    }
    return -1;
}

// Cheapest trip from 1 to 3 on the one-way roads 1 to 2 (4) and 2 to 3 (10) when ONE road may be driven for free.
// Brute force: Dijkstra over (vertex, free roads left). Method: keep only the cheapest cost per vertex, whatever is left.
int cheapestTrip(bool keepOnlyCheapest) {
    struct Road {
        int to, price;
    };
    vector<vector<Road>> adj(4);
    adj[1].push_back({2, 4});
    adj[2].push_back({3, 10});
    const int INF = 1e9;
    vector<array<int, 2>> dist(4, {INF, INF});  // dist[v][left]
    vector<int> bestCost(4, INF);               // used by the method only
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> heap;  // cost, vertex, left
    dist[1][1] = 0;
    bestCost[1] = 0;
    heap.push({0, 1, 1});
    while (!heap.empty()) {
        auto [d, u, left] = heap.top();
        heap.pop();
        if (d > dist[u][left]) continue;
        if (keepOnlyCheapest && d > bestCost[u]) continue;  // the method forgot this state: a cheaper one reached u
        for (auto [v, price] : adj[u]) {
            for (int useFree = 0; useFree <= left; useFree++) {
                int nd = d + (useFree ? 0 : price), nl = left - useFree;
                if (keepOnlyCheapest) {
                    if (nd >= bestCost[v]) continue;  // a state at v with a cost no larger exists: drop this one
                    bestCost[v] = nd;
                } else if (nd >= dist[v][nl]) {
                    continue;
                }
                dist[v][nl] = nd;
                heap.push({nd, v, nl});
            }
        }
    }
    return min(dist[3][0], dist[3][1]);
}

int main() {
    vector<string> g1 = {".#.", "###", "..."}, g2 = {".##", "#.#", "##."};
    cout << "P1 brute=" << fullStates(g1, 1) << " method=" << withDomination(g1, 1) << "\n";
    cout << "P2 brute=" << fullStates(g2, 2) << " method=" << withDomination(g2, 2) << "\n";
    cout << "N1 brute=" << cheapestTrip(false) << " method=" << cheapestTrip(true) << "\n";
}
