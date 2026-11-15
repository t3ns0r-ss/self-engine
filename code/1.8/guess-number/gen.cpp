#include <bits/stdc++.h>
using namespace std;

// Writes a hidden test for the judge: n x budget mode. Seeds alternate between a fixed number and an adaptive judge.
int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 40);
    if (rng() % 8 == 0) n = 1;
    int x = randInt(1, n);
    int budget = 0;
    while ((1LL << budget) < n) budget++;
    bool adaptive = rng() % 2 == 0;
    cout << n << " " << (adaptive ? 0 : x) << " " << budget << " " << (adaptive ? "adaptive" : "fixed") << "\n";
}
