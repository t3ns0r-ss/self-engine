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
    int N = randInt(0, 1) ? randInt(2, 30) : randInt(2, 2000), q = randInt(1, 5);
    cout << N << " " << q << "\n";
    for (int i = 0; i < q; i++) {
        int l = randInt(1, N), r = randInt(1, N);
        if (l > r) swap(l, r);
        cout << l << " " << r << "\n";
    }
}
