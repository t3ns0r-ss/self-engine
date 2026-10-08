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
    int n = randInt(2, 6), kind = randInt(0, 2);
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        int v;
        if (kind == 0) v = randInt(1, 30);                  // small values, all three answers
        else if (kind == 1) v = randInt(1, 1000000);        // large values
        else v = 2 * randInt(1, 500000);                    // all even: not coprime
        cout << v << (i + 1 < n ? ' ' : '\n');
    }
}
