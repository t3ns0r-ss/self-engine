#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int L = randInt(1, 12), A = randInt(1, 120), B = randInt(1, 60), M = randInt(2, 1000);
    if (randInt(0, 3) == 0) M = randInt(2, 12);
    cout << L << " " << A << " " << B << " " << M << "\n";
}
