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
    int n = randInt(1, 8);
    int range = randInt(1, 4) == 1 ? 1 : randInt(2, 5);  // small ranges force many repeats
    cout << n << "\n";
    for (int i = 0; i < n; i++) cout << randInt(-range, range) << (i + 1 < n ? ' ' : '\n');
}
