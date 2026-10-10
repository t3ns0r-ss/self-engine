#include <bits/stdc++.h>
using namespace std;

int match(vector<int> g, vector<int> c) {
    sort(g.begin(), g.end());
    sort(c.begin(), c.end());
    int count = 0, j = 0;
    for (int x : g) {
        while (j < (int)c.size() && c[j] < x) j++;
        if (j == (int)c.size()) break;
        count++, j++;
    }
    return count;
}

int main() {
    // P1 and P2: children by greed, cookies by size. Brute: try every assignment of cookies to children.
    auto brute = [](vector<int> g, vector<int> c) {
        int best = 0, n = g.size(), m = c.size();
        function<void(int, int, int)> rec = [&](int i, int used, int got) {
            best = max(best, got);
            if (i == n) return;
            rec(i + 1, used, got);
            for (int j = 0; j < m; j++) if (!(used >> j & 1) && c[j] >= g[i]) rec(i + 1, used | 1 << j, got + 1);
        };
        rec(0, 0, 0);
        return best;
    };
    cout << "P1 brute=" << brute({1, 2, 3}, {1, 1}) << " method=" << match({1, 2, 3}, {1, 1}) << '\n';
    cout << "P2 brute=" << brute({1, 2}, {1, 2, 3}) << " method=" << match({1, 2}, {1, 2, 3}) << '\n';
    // N1: the children (greed, taste) = (1, a), (2, b) and cookies (size, flavour) = (3, b), (3, b): a cookie works only
    // for the same taste. Brute: the real best. Method: sizes only.
    vector<array<int, 2>> ch = {{1, 0}, {2, 1}}, co = {{3, 1}, {3, 1}};
    int real = 0;
    for (int mask = 0; mask < 4; mask++) {  // which child gets which cookie: child i gets cookie (mask >> i & 1)
        if ((mask & 1) == (mask >> 1 & 1)) continue;
        int s = 0;
        for (int i = 0; i < 2; i++) s += co[mask >> i & 1][0] >= ch[i][0] && co[mask >> i & 1][1] == ch[i][1];
        real = max(real, s);
    }
    cout << "N1 brute=" << real << " method=" << match({1, 2}, {3, 3}) << '\n';
    // N2: greed 1 3 and cookies 3 1, giving each child the LARGEST cookie that satisfies it, taking the children in order.
    vector<int> c = {1, 3};
    int count = 0;
    for (int greed : {1, 3}) {
        int pick = -1;
        for (int j = 0; j < (int)c.size(); j++) if (c[j] >= greed && (pick < 0 || c[j] > c[pick])) pick = j;
        if (pick >= 0) count++, c.erase(c.begin() + pick);
    }
    cout << "N2 brute=" << brute({1, 3}, {3, 1}) << " method=" << count << '\n';
}
