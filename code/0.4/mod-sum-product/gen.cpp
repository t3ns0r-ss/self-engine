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
    int n = (int)randLL(1, 6);
    long long m = randLL(0, 1) ? randLL(1, 20) : randLL(1, 2000000000LL);
    const long long E = 1000000000000000000LL;
    long long lim = randLL(0, 2) == 0 ? 50 : E;  // small values sometimes, the full range otherwise
    cout << n << " " << m << "\n";
    for (int i = 0; i < n; i++) cout << randLL(-lim, lim) << " " << randLL(-lim, lim) << "\n";
}
