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
    while (q--) {
        long long L = randInt(0, 40), R = L + randInt(0, 40);
        if (randInt(0, 3) == 0) {  // large values: a window of at most 60 numbers near 10^18
            L = 1000000000000000000LL - randInt(0, 100);
            R = min(1000000000000000000LL, L + randInt(0, 60));
        }
        cout << L << " " << R << "\n";
    }
}
