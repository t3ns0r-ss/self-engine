#include <bits/stdc++.h>
using namespace std;

// Monster times by repeated relaxation; then my own earliest times by repeated relaxation in which a cell may be entered at
// time t only if t is smaller than the monster time of the cell; the answer is the smallest time over boundary cells.
int main() {
    int rows, cols;
    cin >> rows >> cols;
    vector<string> grid(rows);
    for (auto& row : grid) cin >> row;
    const int INF = 1e9;
    vector<vector<int>> monster(rows, vector<int>(cols, INF)), me(rows, vector<int>(cols, INF));
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 'M') monster[r][c] = 0;
            if (grid[r][c] == 'A') me[r][c] = 0;
        }
    for (int phase = 0; phase < 2; phase++) {
        auto& dist = phase == 0 ? monster : me;
        bool changed = true;
        while (changed) {
            changed = false;
            for (int r = 0; r < rows; r++)
                for (int c = 0; c < cols; c++) {
                    if (grid[r][c] == '#') continue;
                    for (int dr = -1; dr <= 1; dr++)
                        for (int dc = -1; dc <= 1; dc++) {
                            if (abs(dr) + abs(dc) != 1) continue;
                            int nr = r + dr, nc = c + dc;
                            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == '#') continue;
                            int t = dist[nr][nc] + 1;
                            if (phase == 1 && t >= monster[r][c]) continue;
                            if (dist[nr][nc] < INF && t < dist[r][c]) {
                                dist[r][c] = t;
                                changed = true;
                            }
                        }
                }
        }
    }
    int best = INF;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1) best = min(best, me[r][c]);
    if (best >= INF) cout << "NO\n";
    else cout << "YES\n" << best << "\n";
}
