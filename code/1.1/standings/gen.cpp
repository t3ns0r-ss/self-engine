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
    // sometimes more than 16 contestants: below that, sort switches to a stable insertion sort,
    // which would hide a missing tie-break
    int n = randInt(0, 1) ? randInt(1, 10) : randInt(17, 40), hs = randInt(0, 1) ? 2 : 100, hp = randInt(0, 1) ? 2 : 1000000000;
    cout << n << "\n";
    for (int i = 0; i < n; i++) cout << randInt(0, hs) << " " << randInt(0, hp) << "\n";
}
