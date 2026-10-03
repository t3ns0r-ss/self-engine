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
    int q = randInt(1, 12), hi = randInt(0, 1) ? 5 : 1000000000;
    cout << q << "\n";
    for (int i = 0; i < q; i++) {
        int type = randInt(1, 3);
        if (type == 3) cout << "3\n";
        else cout << type << " " << randInt(0, hi) << "\n";
    }
}
