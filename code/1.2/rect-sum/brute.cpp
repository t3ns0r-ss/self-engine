// Adds up every queried rectangle cell by cell.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int R, C, q;
    cin >> R >> C >> q;
    vector<vector<long long>> a(R + 1, vector<long long>(C + 1));
    for (int x = 1; x <= R; x++)
        for (int y = 1; y <= C; y++) cin >> a[x][y];
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        long long s = 0;
        for (int x = x1; x <= x2; x++)
            for (int y = y1; y <= y2; y++) s += a[x][y];
        cout << s << "\n";
    }
}
