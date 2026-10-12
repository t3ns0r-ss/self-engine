#include <bits/stdc++.h>
using namespace std;

int main() {
    int H, W, M;
    cin >> H >> W >> M;
    set<pair<int, int>> has;
    for (int i = 0; i < M; i++) {
        int r, c;
        cin >> r >> c;
        has.insert({r, c});
    }
    int best = 0;
    for (int r = 1; r <= H; r++)
        for (int c = 1; c <= W; c++) {
            int cnt = 0;
            for (auto [a, b] : has) cnt += (a == r || b == c);
            best = max(best, cnt);
        }
    cout << best << "\n";
}
