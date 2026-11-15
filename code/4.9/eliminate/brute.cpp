#include <bits/stdc++.h>
using namespace std;

// Brute force: breadth-first search over every state (cell, obstacles used), with no skipping of any state.
int main() {
    int rows, cols, k;
    cin >> rows >> cols >> k;
    vector<string> grid(rows);
    for (auto& row : grid) cin >> row;
    vector<int> dist(rows * cols * (k + 1), -1);
    queue<array<int, 3>> q;
    dist[0] = 0;
    q.push({0, 0, 0});
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
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
            if (slot != -1) continue;
            slot = here + 1;
            q.push({nr, nc, nu});
        }
    }
    cout << answer << "\n";
}
