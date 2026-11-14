#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int m = randInt(1, 5), n = randInt(1, 9);
    cout << n << " " << m << "\n";
    for (int i = 0; i < n; i++) {
        cout << (randInt(0, 1) ? '+' : '-') << " " << randInt(1, m) << " " << (randInt(0, 1) ? '+' : '-') << " " << randInt(1, m) << "\n";
    }
}
