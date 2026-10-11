#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<string> board(n + 1);
    for (int r = 1; r <= n; r++) {
        cin >> board[r];
        board[r] = " " + board[r];
    }
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int r, c;
            cin >> r >> c;
            board[r][c] = board[r][c] == '1' ? '0' : '1';
        } else {
            int r1, c1, r2, c2, s = 0;
            cin >> r1 >> c1 >> r2 >> c2;
            for (int r = r1; r <= r2; r++)
                for (int c = c1; c <= c2; c++) s += board[r][c] == '1';
            cout << s << "\n";
        }
    }
}
