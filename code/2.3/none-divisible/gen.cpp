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
    int N = randInt(1, 2000), m = randInt(1, 6);
    cout << N << " " << m << "\n";
    for (int i = 0; i < m; i++) cout << (randInt(0, 3) == 0 ? randInt(1, 3000) : randInt(1, 30)) << (i + 1 < m ? ' ' : '\n');
}
