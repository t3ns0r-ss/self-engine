/*
Problem: an R x C grid of integers and q queries "x1 y1 x2 y2" (1-based rows x1..x2, columns y1..y2);
print the sum of each rectangle.
Input: R C q (R*C <= 10^6, q <= 2*10^5), the grid (|value| <= 10^9), then the queries.
Output: one sum per line.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R, C, q;
    cin >> R >> C >> q;
    // S[x][y] = sum of rows 1..x and columns 1..y; row 0 and column 0 stay 0
    vector<vector<long long>> S(R + 1, vector<long long>(C + 1, 0));
    for (int x = 1; x <= R; x++)
        for (int y = 1; y <= C; y++) {
            long long a;
            cin >> a;
            S[x][y] = S[x - 1][y] + S[x][y - 1] - S[x - 1][y - 1] + a;  // Theorem 1.2.4, part 1
        }
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << S[x2][y2] - S[x1 - 1][y2] - S[x2][y1 - 1] + S[x1 - 1][y1 - 1] << "\n";  // part 2
    }
}
