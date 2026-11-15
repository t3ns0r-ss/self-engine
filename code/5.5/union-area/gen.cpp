#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 6);
    int side = randInt(2, 9);  // coordinates 0 .. side; a small side forces touching and identical rectangles
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        int x1 = randInt(0, side - 1), x2 = randInt(x1 + 1, side);
        int y1 = randInt(0, side - 1), y2 = randInt(y1 + 1, side);
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
    }
}
