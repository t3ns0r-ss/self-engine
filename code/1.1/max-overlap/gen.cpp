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
    int n = randInt(1, 8), hi = randInt(0, 1) ? 6 : 20;
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        int l = randInt(0, hi), r = randInt(0, hi);
        if (randInt(0, 3) == 0) r = l;  // single points
        cout << min(l, r) << " " << max(l, r) << "\n";
    }
}
