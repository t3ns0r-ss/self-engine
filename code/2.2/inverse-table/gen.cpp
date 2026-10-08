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
    const int primes[] = {2, 3, 5, 7, 11, 13, 101, 997};
    int p = primes[randInt(0, 7)];
    cout << randInt(1, min(p - 1, 60)) << " " << p << "\n";
}
