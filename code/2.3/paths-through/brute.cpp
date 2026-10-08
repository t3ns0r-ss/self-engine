#include <bits/stdc++.h>
using namespace std;

long long a, b, x, y, cnt;

void walk(long long i, long long j, bool seen) {  // every path, one step at a time
    seen = seen || (i == x && j == y);
    if (i == a && j == b) {
        if (seen) cnt++;
        return;
    }
    if (i < a) walk(i + 1, j, seen);
    if (j < b) walk(i, j + 1, seen);
}

int main() {
    int q;
    cin >> a >> b >> q;
    x = 0, y = 0, cnt = 0;
    walk(0, 0, true);
    cout << cnt % 998244353 << "\n";
    while (q--) {
        cin >> x >> y;
        cnt = 0;
        walk(0, 0, false);
        cout << cnt % 998244353 << "\n";
    }
}
