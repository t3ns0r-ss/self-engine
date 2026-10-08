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
    int n = randInt(1, 12), k = randInt(1, n);
    int hi = randInt(1, 2) == 1 ? 5 : 1000000000;
    cout << n << " " << k << "\n";
    for (int i = 0; i < n; i++) cout << randInt(-hi, hi) << (i + 1 < n ? ' ' : '\n');
}
