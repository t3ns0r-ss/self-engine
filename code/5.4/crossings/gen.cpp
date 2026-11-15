#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 8);
    int side = randInt(2, 6);  // coordinates 0 .. side; a small side makes shared endpoints and equal rows common
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        int a = randInt(0, side - 1), b = randInt(a + 1, side), fixed = randInt(0, side);
        if (randInt(0, 1)) cout << a << " " << fixed << " " << b << " " << fixed << "\n";  // horizontal
        else cout << fixed << " " << a << " " << fixed << " " << b << "\n";                 // vertical
    }
}
