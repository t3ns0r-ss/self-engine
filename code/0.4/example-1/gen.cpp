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
    int n = randInt(2, 4), f = randInt(1, 3);  // a common factor f in many inputs
    cout << n << "\n";
    for (int i = 0; i < n; i++) cout << f * randInt(1, 12) << (i + 1 < n ? ' ' : '\n');
}
