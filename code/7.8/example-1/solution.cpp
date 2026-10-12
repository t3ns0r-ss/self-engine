#include <bits/stdc++.h>
using namespace std;

/*
Problem: AtCoder ABC176 E, Bomber. A grid of H rows and W columns holds M targets (distinct cells). One bomb is placed on any cell and destroys
every target in its row and in its column. Print the largest number of targets that one bomb destroys.
Input: H, W, M, then M lines "row column".
*/

// snippet:begin
// A bomb on (r, c) destroys rows[r] + cols[c] targets, minus one if (r, c) itself holds a target (it was counted in both). Take the busiest
// rows and the busiest columns: the answer is R + C, or R + C - 1 when every such crossing cell holds a target.
long long bomber(int H, int W, const vector<pair<int, int>>& targets) {
    vector<int> rows(H + 1), cols(W + 1);
    for (auto [r, c] : targets) rows[r]++, cols[c]++;
    int R = *max_element(rows.begin(), rows.end()), C = *max_element(cols.begin(), cols.end());
    long long crossings = 0, hit = 0;
    for (int r = 1; r <= H; r++) crossings += rows[r] == R ? 1 : 0;
    long long busyColumns = count(cols.begin() + 1, cols.end(), C);
    crossings *= busyColumns;
    for (auto [r, c] : targets) hit += rows[r] == R && cols[c] == C;
    return R + C - (hit == crossings ? 1 : 0);
}
// snippet:end

int main() {
    int H, W, M;
    cin >> H >> W >> M;
    vector<pair<int, int>> targets(M);
    for (auto& [r, c] : targets) cin >> r >> c;
    cout << bomber(H, W, targets) << "\n";
}
