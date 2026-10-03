// Checks the definition of a cross of size n centred at (a, b) literally, for every cell and n.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (auto& row : g) cin >> row;
    auto C = [&](int r, int c) { return (r >= 0 && r < h && c >= 0 && c < w) ? g[r][c] : '.'; };
    int N = min(h, w);
    vector<int> s(N + 1, 0);
    for (int a = 0; a < h; a++)
        for (int b = 0; b < w; b++)
            for (int n = 1; n <= N; n++) {
                bool ok = C(a, b) == '#';
                for (int d = 1; d <= n; d++)
                    ok = ok && C(a + d, b + d) == '#' && C(a + d, b - d) == '#' && C(a - d, b + d) == '#' && C(a - d, b - d) == '#';
                int e = n + 1;
                ok = ok && (C(a + e, b + e) == '.' || C(a + e, b - e) == '.' || C(a - e, b + e) == '.' || C(a - e, b - e) == '.');
                if (ok) s[n]++;
            }
    for (int n = 1; n <= N; n++) cout << s[n] << (n < N ? ' ' : '\n');
}
