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
    int wallPercent = randInt(0, 50), sourcePercent = randInt(0, 30);
    cout << rows << " " << cols << "\n";
    for (int r = 0; r < rows; r++) {
        string row;
        for (int c = 0; c < cols; c++) {
            int x = randInt(1, 100);
            row += x <= wallPercent ? '#' : (x <= wallPercent + sourcePercent ? 'S' : '.');
        }
        cout << row << "\n";
    }
}
