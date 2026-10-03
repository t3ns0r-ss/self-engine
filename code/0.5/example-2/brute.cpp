// Recursion along the edges: from the current vertex, step to every unvisited neighbour.
#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> nb;
vector<bool> seen;

int go(int v, int visited) {
    if (visited == n) return 1;
    int total = 0;
    for (int w : nb[v])
        if (!seen[w]) {
            seen[w] = true;
            total += go(w, visited + 1);
            seen[w] = false;
        }
    return total;
}

int main() {
    int m;
    cin >> n >> m;
    nb.assign(n, {});
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        nb[a - 1].push_back(b - 1);
        nb[b - 1].push_back(a - 1);
    }
    seen.assign(n, false);
    seen[0] = true;
    cout << go(0, 1) << "\n";
}
