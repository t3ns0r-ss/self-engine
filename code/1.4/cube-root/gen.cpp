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
    long long c;
    int kind = randInt(0, 2);
    if (kind == 0) c = randInt(-1000, 1000);                                     // small values
    else if (kind == 1) { long long t = randInt(-1000000, 1000000); c = t * t * t; }  // exact cubes
    else c = (long long)randInt(-1000000000, 1000000000) * randInt(1, 1000000000);  // large values
    cout << c << "\n";
}
