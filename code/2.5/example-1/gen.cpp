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
    if (randInt(0, 1)) {  // a reachable target, built from move counts
        int a = randInt(0, 9), b = randInt(0, 9);
        if (a + b == 0) a = 1;
        cout << a + 2 * b << " " << 2 * a + b << "\n";
    } else {
        cout << randInt(1, 25) << " " << randInt(1, 25) << "\n";
    }
}
