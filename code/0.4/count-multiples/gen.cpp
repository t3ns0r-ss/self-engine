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
    int q = randInt(1, 5);
    cout << q << "\n";
    for (int i = 0; i < q; i++) {
        int l = randInt(-30, 30), r = randInt(l, l + randInt(0, 40)), k = randInt(1, 12);
        cout << l << " " << r << " " << k << "\n";
    }
}
