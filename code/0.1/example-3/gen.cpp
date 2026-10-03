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
    long long a = randLL(0, 2) == 0 ? randLL(0, 5) : randLL(0, E18 - 100);  // a = 0 often
    long long b = a + randLL(0, 60);
    long long x = randLL(0, 2) ? randLL(1, 12) : randLL(1, E18);
    cout << a << " " << b << " " << x << "\n";
}
