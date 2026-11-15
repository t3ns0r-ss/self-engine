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
    int n = randInt(1, 7), m = randInt(2, 3);
    int hi = randInt(1, 2) == 1 ? 3 : 10000;
    cout << n << " " << m << "\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cout << randInt(0, hi) << (j + 1 < m ? ' ' : '\n');
}
