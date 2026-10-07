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
    int n = randInt(2, 10), hi = randInt(0, 1) ? 5 : 1000000000;
    bool negative = randInt(0, 3) == 0;  // sometimes all values negative
    cout << n << "\n";
    for (int i = 0; i < n; i++) cout << (negative ? -randInt(1, hi) : randInt(-hi, hi)) << (i + 1 < n ? ' ' : '\n');
}
