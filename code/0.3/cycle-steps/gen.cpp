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
    int k = randInt(1, 8);
    int x = randInt(0, k - 1);
    int t = randInt(0, 3) == 0 ? randInt(0, 3) : randInt(0, 60);  // includes T = 0
    cout << k << " " << x << " " << t << "\n";
    for (int i = 0; i < k; i++) cout << (randInt(0, 4) == 0 ? i : randInt(0, k - 1)) << (i + 1 < k ? ' ' : '\n');  // self-loops too
}
