#include <bits/stdc++.h>
using namespace std;

/*
Problem: an n x n board of lamps (0 off, 1 on); q operations: "1 r c" flips the lamp at row r, column c,
"2 r1 c1 r2 c2" asks for the number of lit lamps in the rectangle (rows r1..r2, columns c1..c2). Positions are 1-based.
Input: n q, then n rows of n characters, then q operations.
Output: one line per operation of the second kind.
*/

// snippet:begin
// A Fenwick tree in two dimensions: the loops of Theorems 5.2.1 and 5.2.2 are nested, one for the row and one for the column.
struct Fenwick2D {
    int n;
    vector<vector<int>> tree;
    Fenwick2D(int size) : n(size), tree(size + 1, vector<int>(size + 1, 0)) {}
    void add(int r, int c, int d) {
        for (int i = r; i <= n; i += i & -i)
            for (int j = c; j <= n; j += j & -j) tree[i][j] += d;
    }
    int prefix(int r, int c) const {  // lamps in rows 1..r and columns 1..c
        int sum = 0;
        for (int i = r; i > 0; i -= i & -i)
            for (int j = c; j > 0; j -= j & -j) sum += tree[i][j];
        return sum;
    }
    int rectangle(int r1, int c1, int r2, int c2) const {  // four prefixes by inclusion and exclusion
        return prefix(r2, c2) - prefix(r1 - 1, c2) - prefix(r2, c1 - 1) + prefix(r1 - 1, c1 - 1);
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<string> board(n + 1);
    Fenwick2D f(n);
    for (int r = 1; r <= n; r++) {
        cin >> board[r];
        board[r] = " " + board[r];
        for (int c = 1; c <= n; c++)
            if (board[r][c] == '1') f.add(r, c, 1);
    }
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int r, c;
            cin >> r >> c;
            int d = board[r][c] == '1' ? -1 : 1;
            board[r][c] = board[r][c] == '1' ? '0' : '1';
            f.add(r, c, d);
        } else {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            cout << f.rectangle(r1, c1, r2, c2) << "\n";
        }
    }
}
