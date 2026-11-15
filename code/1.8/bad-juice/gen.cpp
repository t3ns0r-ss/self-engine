#include <bits/stdc++.h>
using namespace std;

// Hidden test: "n x mode"; x is the bad bottle (ignored in adaptive mode).
int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(2, 30);
    int x = randInt(1, n);
    bool adaptive = rng() % 2 == 0;
    cout << n << " " << x << " " << (adaptive ? "adaptive" : "fixed") << "\n";
}
