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
    const long long E18 = 1000000000000000000LL;
    int q = randLL(1, 6);
    cout << q << "\n";
    for (int i = 0; i < q; i++) {
        long long a, b;
        if (randLL(0, 1)) {
            a = randLL(-20, 20);
            b = randLL(-6, 6);
        } else {
            a = randLL(-E18, E18);
            b = randLL(0, 1) ? randLL(-1000, 1000) : randLL(-E18, E18);
        }
        if (b == 0) b = 1;
        if (randLL(0, 4) == 0) a = b * randLL(-3, 3);  // exact multiples
        cout << a << " " << b << "\n";
    }
}
