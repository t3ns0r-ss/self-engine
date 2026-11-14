#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int rows = randInt(1, 5), cols = randInt(1, 5), k = randInt(0, 4);
    int percent = randInt(10, 70);  // how many cells are obstacles
    cout << rows << " " << cols << " " << k << "\n";
    for (int r = 0; r < rows; r++) {
        string row;
        for (int c = 0; c < cols; c++) {
            bool corner = (r == 0 && c == 0) || (r == rows - 1 && c == cols - 1);
            row += (!corner && randInt(1, 100) <= percent) ? '#' : '.';
        }
        cout << row << "\n";
    }
}
