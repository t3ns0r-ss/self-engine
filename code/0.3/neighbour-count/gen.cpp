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
    int h = randInt(1, 5), w = randInt(1, 5), dens = randInt(0, 4);
    cout << h << " " << w << "\n";
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) cout << (randInt(0, 4) < dens ? '#' : '.');
        cout << "\n";
    }
}
