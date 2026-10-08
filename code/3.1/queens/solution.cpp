/*
Problem: count the ways to place n queens on an n x n board, one per row, so that no two share a
column or a diagonal and no queen stands on a blocked square.
Input: n (1 <= n <= 12), then n rows of n characters: '.' free, '*' blocked.
Output: the number of placements.
*/
#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> board;
vector<bool> colUsed, diagUsed, antiUsed;  // marks of the queens placed so far

long long rec(int row) {
    if (row == n) return 1;  // all rows filled: one valid placement
    long long ways = 0;
    for (int c = 0; c < n; c++) {
        // squares on one diagonal share row - c; on one anti-diagonal they share row + c
        if (board[row][c] == '*' || colUsed[c] || diagUsed[row - c + n - 1] || antiUsed[row + c]) continue;
        colUsed[c] = diagUsed[row - c + n - 1] = antiUsed[row + c] = true;
        ways += rec(row + 1);
        colUsed[c] = diagUsed[row - c + n - 1] = antiUsed[row + c] = false;  // undo (Theorem 3.1.1, condition 2)
    }
    return ways;
}

int main() {
    cin >> n;
    board.resize(n);
    for (auto& row : board) cin >> row;
    colUsed.assign(n, false);
    diagUsed.assign(2 * n - 1, false);
    antiUsed.assign(2 * n - 1, false);
    cout << rec(0) << "\n";
}
