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
    int n = randInt(0, 12), k = randInt(1, 5);
    cout << n << " " << k << "\n";
    for (int i = 0; i < k; i++) cout << (randInt(0, 2) == 0 ? randInt(0, 4) : 0) << (i + 1 < k ? ' ' : '\n');
}
