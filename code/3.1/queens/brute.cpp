// Brute force: every assignment of a column to each row (n^n of them), checked pair by pair.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> board(n);
    for (auto& row : board) cin >> row;
    long long total = 1;
    for (int i = 0; i < n; i++) total *= n;
    long long count = 0;
    vector<int> col(n);
    for (long long code = 0; code < total; code++) {
        long long x = code;
        for (int r = 0; r < n; r++) {
            col[r] = x % n;
            x /= n;
        }
        bool ok = true;
        for (int r = 0; r < n && ok; r++) {
            if (board[r][col[r]] == '*') ok = false;
            for (int s = 0; s < r && ok; s++)
                if (col[s] == col[r] || abs(col[s] - col[r]) == r - s) ok = false;
        }
        if (ok) count++;
    }
    cout << count << "\n";
}
