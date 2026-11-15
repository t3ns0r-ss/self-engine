#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 8), q = randInt(1, 6);
    int side = randInt(1, 6);  // coordinates 1 .. side: equal x, equal y and repeated points all occur
    cout << n << " " << q << "\n";
    for (int i = 0; i < n; i++) cout << randInt(1, side) << " " << randInt(1, side) << "\n";
    for (int i = 0; i < q; i++) {
        int a = randInt(1, side), b = randInt(a, side), c = randInt(1, side), d = randInt(c, side);
        cout << a << " " << b << " " << c << " " << d << "\n";
    }
}
