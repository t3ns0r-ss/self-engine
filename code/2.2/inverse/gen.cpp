#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937_64 rng(atoi(argv[1]));
    auto randLL = [&](long long lo, long long hi) {
        return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo;
    };
    int t = (int)randLL(1, 5);
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        long long m = randLL(2, randLL(0, 1) ? 12 : 3000);
        long long a = randLL(0, 1) ? randLL(0, 3 * m) : randLL(0, 1000000000000000000LL);
        cout << a << " " << m << "\n";
    }
}
