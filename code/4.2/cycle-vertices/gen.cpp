#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 9);
    int noneChance = randInt(0, 40);  // percent of towns without a road
    cout << n << "\n";
    for (int i = 1; i <= n; i++) {
        int target = randInt(1, 100) <= noneChance ? 0 : randInt(1, n);  // a road from a town to itself is allowed
        cout << target << (i < n ? " " : "\n");
    }
}
