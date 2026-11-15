#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int t = randInt(1, 6), side = randInt(1, 4);  // small coordinates: touching, overlapping and parallel pairs are common
    cout << t << "\n";
    while (t--) {
        int v[8];
        do {
            for (int& x : v) x = randInt(0, side);
        } while ((v[0] == v[2] && v[1] == v[3]) || (v[4] == v[6] && v[5] == v[7]));
        for (int i = 0; i < 8; i++) cout << v[i] << (i < 7 ? " " : "\n");
    }
}
