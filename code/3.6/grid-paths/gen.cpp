#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) {
        return (int)(rng() % (unsigned)(hi - lo + 1)) + lo;
    };
    int h = randInt(1, 8), w = randInt(1, 8), percent = randInt(0, 40);
    cout << h << " " << w << "\n";
    for (int r = 0; r < h; r++) {
        string row;
        for (int c = 0; c < w; c++) row += (randInt(1, 100) <= percent) ? '#' : '.';
        cout << row << "\n";
    }
}
