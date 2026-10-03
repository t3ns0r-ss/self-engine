#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937_64 rng(atoi(argv[1]));
    auto randLL = [&](long long lo, long long hi) {
        return lo + (long long)(rng() % (unsigned long long)(hi - lo + 1));
    };
    int q = randLL(1, 6);
    cout << q << "\n";
    for (int i = 0; i < q; i++) {
        long long x;
        int mode = randLL(0, 3);
        if (mode == 0) x = randLL(0, 100);
        else if (mode == 1) x = randLL(0, 1000000000000000000LL);
        else {
            long long r = randLL(0, 1000000000);          // a square, or one below or above it
            x = r * r + randLL(-1, 1);
            if (x < 0) x = 0;
            if (x > 1000000000000000000LL) x = 1000000000000000000LL;
        }
        cout << x << "\n";
    }
}
