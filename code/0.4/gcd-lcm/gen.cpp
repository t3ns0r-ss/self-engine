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
    int n = randInt(1, 5), C = randInt(1, 3000);
    int base = randInt(1, 6);  // a common factor in about half of the inputs
    cout << n << " " << C << "\n";
    for (int i = 0; i < n; i++) cout << (randInt(0, 1) ? base * randInt(1, 8) : randInt(1, 40)) << (i + 1 < n ? ' ' : '\n');
}
