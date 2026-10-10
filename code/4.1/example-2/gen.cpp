#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int rows = randInt(1, 5), cols = randInt(1, 6);
    if (rows * cols < 2) cols = 2;
    int wallPercent = randInt(0, 55);
    vector<string> grid(rows, string(cols, '.'));
    for (auto& row : grid)
        for (auto& ch : row) ch = randInt(1, 100) <= wallPercent ? '#' : '.';
    int cells = rows * cols;
    int a = randInt(0, cells - 1), b = randInt(0, cells - 1);
    while (b == a) b = randInt(0, cells - 1);
    grid[a / cols][a % cols] = 'A';
    grid[b / cols][b % cols] = 'B';
    cout << rows << " " << cols << "\n";
    for (auto& row : grid) cout << row << "\n";
}
