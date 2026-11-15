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
    int n, m;
    do n = randInt(1, 4), m = randInt(1, 4); while (n * m < 2 || n * m > 12);
    cout << n << " " << m << " " << randInt(2, n * m) << "\n";
}
