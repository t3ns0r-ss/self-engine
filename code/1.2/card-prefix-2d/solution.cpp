#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<vector<int>> a = {{1, 2, 3}, {4, 5, 6}};
    vector<vector<int>> S(3, vector<int>(4, 0));
    for (int x = 1; x <= 2; x++) for (int y = 1; y <= 3; y++) S[x][y] = S[x - 1][y] + S[x][y - 1] - S[x - 1][y - 1] + a[x - 1][y - 1];
    // P1: the rectangle of rows 0..1 and columns 1..2. Brute: add the cells. Method: four corners.
    cout << "P1 brute=" << 2 + 3 + 5 + 6 << " method=" << S[2][3] - S[0][3] - S[2][1] + S[0][1] << '\n';
    // P2: the whole grid.
    cout << "P2 brute=" << 1 + 2 + 3 + 4 + 5 + 6 << " method=" << S[2][3] - S[0][3] - S[2][0] + S[0][0] << '\n';
    // N1: the rectangle of row 1, columns 1..2 (values 5 and 6) with the last corner term forgotten.
    cout << "N1 brute=" << 5 + 6 << " method=" << S[2][3] - S[1][3] - S[2][1] << '\n';
    // N2: the main diagonal (cells (0,0) and (1,1)), asked as the rectangle rows 0..1, columns 0..1.
    cout << "N2 brute=" << 1 + 5 << " method=" << S[2][2] - S[0][2] - S[2][0] + S[0][0] << '\n';
}
