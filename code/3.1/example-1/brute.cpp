// Brute force: every sequence of K + 1 cells (as a number in base H*W), checked against all three rules.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int H, W, K;
    cin >> H >> W >> K;
    vector<string> g(H);
    for (auto& row : g) cin >> row;
    int cells = H * W;
    long long total = 1;
    for (int i = 0; i <= K; i++) total *= cells;
    long long count = 0;
    vector<int> seq(K + 1);
    for (long long code = 0; code < total; code++) {
        long long x = code;
        for (int i = 0; i <= K; i++) {
            seq[i] = x % cells;
            x /= cells;
        }
        bool ok = true;
        for (int i = 0; i <= K && ok; i++) {
            int r = seq[i] / W, c = seq[i] % W;
            if (g[r][c] == '#') ok = false;
            if (i > 0) {
                int pr = seq[i - 1] / W, pc = seq[i - 1] % W;
                if (abs(r - pr) + abs(c - pc) != 1) ok = false;
            }
            for (int j = 0; j < i; j++)
                if (seq[j] == seq[i]) ok = false;
        }
        if (ok) count++;
    }
    cout << count << "\n";
}
