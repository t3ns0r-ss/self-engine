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
    int n = randInt(1, 8), lo = randInt(0, 40), hi = lo + randInt(0, 30);
    cout << n << " " << lo << " " << hi << "\n";
    for (int i = 0; i < n; i++) cout << randInt(0, 15) << (i + 1 < n ? ' ' : '\n');
}
