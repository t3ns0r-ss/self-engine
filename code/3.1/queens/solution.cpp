/*
Problem: count the ways to place n queens on an n x n board, one per row, so that no two share a
column or a diagonal and no queen stands on a blocked square.
Input: n (1 <= n <= 12), then n rows of n characters: '.' free, '*' blocked.
Output: the number of placements.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.1.1. Place one queen per row; a column is tried only if the square is free and no earlier queen shares its
// column, diagonal (row - c) or anti-diagonal (row + c). The marks are cleared after each call.
long long queens(const vector<string>& board) {
    int n = board.size();
    vector<bool> colUsed(n, false), diagUsed(2 * n - 1, false), antiUsed(2 * n - 1, false);
    function<long long(int)> rec = [&](int row) -> long long {
        if (row == n) return 1;  // all rows filled: one valid placement
        long long ways = 0;
        for (int c = 0; c < n; c++) {
            if (board[row][c] == '*' || colUsed[c] || diagUsed[row - c + n - 1] || antiUsed[row + c]) continue;
            colUsed[c] = diagUsed[row - c + n - 1] = antiUsed[row + c] = true;
            ways += rec(row + 1);
            colUsed[c] = diagUsed[row - c + n - 1] = antiUsed[row + c] = false;  // undo
        }
        return ways;
    };
    return rec(0);
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<string> board(n);
    for (auto& row : board) cin >> row;
    cout << queens(board) << "\n";
}
