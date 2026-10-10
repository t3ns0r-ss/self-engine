#include <bits/stdc++.h>
using namespace std;

long long tableAt(const vector<string>& g, int tr, int tc) {
    int h = g.size(), w = g[0].size();
    vector<vector<long long>> cnt(h, vector<long long>(w, 0));
    for (int r = 0; r < h; r++) for (int c = 0; c < w; c++) {
        if (g[r][c] == '#') continue;
        if (r == 0 && c == 0) cnt[r][c] = 1;
        else cnt[r][c] = (r > 0 ? cnt[r - 1][c] : 0) + (c > 0 ? cnt[r][c - 1] : 0);
    }
    return cnt[tr][tc];
}
long long brute(const vector<string>& g, int r, int c) {
    if (r < 0 || c < 0 || g[r][c] == '#') return 0;
    if (r == 0 && c == 0) return 1;
    return brute(g, r - 1, c) + brute(g, r, c - 1);
}
int main() {
    // P1: the right/down paths in the grid .... / .#.. / .... Brute: recursion backwards from the end. Method: the table.
    vector<string> g = {"....", ".#..", "...."};
    cout << "P1 brute=" << brute(g, 2, 3) << " method=" << tableAt(g, 2, 3) << '\n';
    // N1: can the top-right cell of .#. / ... be reached from the top-left moving in four directions? Brute: search with visited marks.
    vector<string> m = {".#.", "..."};
    vector<vector<bool>> seen(2, vector<bool>(3, false));
    function<void(int, int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= 2 || c < 0 || c >= 3 || m[r][c] == '#' || seen[r][c]) return;
        seen[r][c] = true;
        dfs(r + 1, c), dfs(r - 1, c), dfs(r, c + 1), dfs(r, c - 1);
    };
    dfs(0, 0);
    cout << "N1 brute=" << seen[0][2] << " method=" << tableAt(m, 0, 2) << '\n';
    // N2: the right/down paths in an empty grid of 100000 x 100000 cells; the table has 10^10 cells, the count is one binomial coefficient.
    const long long MOD = 1000000007;
    long long num = 1, den = 1;
    for (long long i = 1; i <= 199998; i++) { num = num * i % MOD; if (i <= 99999) den = den * i % MOD; }
    auto power = [&](long long b, long long e) { long long r = 1; b %= MOD; while (e) { if (e & 1) r = r * b % MOD; b = b * b % MOD; e >>= 1; } return r; };
    long long answer = num * power(den, MOD - 2) % MOD * power(den, MOD - 2) % MOD;
    long long cells = 100000LL * 100000LL;
    cout << "N2 brute=" << answer << " method=" << (cells > 100000000LL ? "too-slow" : "ok") << '\n';
}
