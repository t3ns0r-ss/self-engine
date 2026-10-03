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
    int big = randInt(0, 3) == 0;  // sometimes values near the limits
    int a = big ? randInt(-1000000, 1000000) : randInt(-10, 10);
    int d = big ? randInt(-1000000, 1000000) : randInt(-10, 10);
    int n = big ? randInt(1, 1000000) : randInt(1, 12);
    cout << a << " " << d << " " << n << "\n";
}
