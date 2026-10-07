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
    int R = randInt(1, 5), C = randInt(1, 5), q = randInt(1, 8), hi = randInt(0, 1) ? 5 : 1000000000;
    cout << R << " " << C << " " << q << "\n";
    for (int x = 0; x < R; x++)
        for (int y = 0; y < C; y++) cout << randInt(-hi, hi) << (y + 1 < C ? ' ' : '\n');
    for (int i = 0; i < q; i++) {
        int x1 = randInt(1, R), x2 = randInt(1, R), y1 = randInt(1, C), y2 = randInt(1, C);
        cout << min(x1, x2) << " " << min(y1, y2) << " " << max(x1, x2) << " " << max(y1, y2) << "\n";
    }
}
