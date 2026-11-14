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
    int n = randInt(1, 14);
    int mode = randInt(1, 3);
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        int v;
        if (mode == 1) v = randInt(-10000, 10000);
        else if (mode == 2) v = -randInt(1, 5);  // all negative: the answer is the largest element
        else v = randInt(-3, 3);
        cout << v << (i + 1 < n ? ' ' : '\n');
    }
}
