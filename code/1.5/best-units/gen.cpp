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
    int n = randInt(1, 5);
    cout << n << " " << randInt(0, 12) << "\n";
    for (int i = 0; i < n; i++) cout << randInt(1, 4) << " " << randInt(1, randInt(0, 1) ? 3 : 10000) << "\n";
}
