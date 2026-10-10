#include <bits/stdc++.h>
using namespace std;

// Label propagation: each floor cell starts with its own label; neighbouring floor cells copy the smaller label until nothing changes.
int main() {
    int rows, cols;
    cin >> rows >> cols;
    vector<string> grid(rows);
    for (auto& row : grid) cin >> row;
    vector<int> label(rows * cols);
    iota(label.begin(), label.end(), 0);
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
                        int low = min(label[r * cols + c], label[nr * cols + nc]);
                        if (label[r * cols + c] != low || label[nr * cols + nc] != low) {
                            label[r * cols + c] = label[nr * cols + nc] = low;
                            changed = true;
                        }
                    }
            }
    }
    map<int, int> count;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid[r][c] != '#') count[label[r * cols + c]]++;
    int largest = 0;
    for (auto [l, k] : count) largest = max(largest, k);
    cout << count.size() << " " << largest << "\n";
}
