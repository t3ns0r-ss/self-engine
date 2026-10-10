#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int rows = randInt(1, 6), cols = randInt(1, 7);
    int wallPercent = randInt(0, 40), monsterPercent = randInt(0, 20);
    vector<string> grid(rows, string(cols, '.'));
    for (auto& row : grid)
        for (auto& ch : row) {
            int x = randInt(1, 100);
            ch = x <= wallPercent ? '#' : (x <= wallPercent + monsterPercent ? 'M' : '.');
        }
    int a = randInt(0, rows * cols - 1);
    grid[a / cols][a % cols] = 'A';
    cout << rows << " " << cols << "\n";
    for (auto& row : grid) cout << row << "\n";
}
