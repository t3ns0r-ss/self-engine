#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int rows = randInt(1, 4), cols = randInt(2, 5);
    if (rows * cols < 2) cols = 2;
    vector<string> grid(rows, string(cols, '.'));
    const string pool = "..#a..A#b.B.cC.dD";  // weighted towards floor and walls
    for (auto& row : grid)
        for (auto& ch : row) ch = pool[randInt(0, (int)pool.size() - 1)];
    int cells = rows * cols;
    int s = randInt(0, cells - 1), t = randInt(0, cells - 1);
    while (t == s) t = randInt(0, cells - 1);
    grid[s / cols][s % cols] = 'S';
    grid[t / cols][t % cols] = 'T';
    cout << rows << " " << cols << "\n";
    for (auto& row : grid) cout << row << "\n";
}
