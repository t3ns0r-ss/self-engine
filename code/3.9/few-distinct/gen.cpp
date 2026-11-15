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
    long long top = 1;
    for (int e = randLL(0, 18); e > 0; e--) top *= 10;   // A up to 10^e
    long long a = randLL(0, top), b = a + randLL(0, 1500);
    if (b > 1000000000000000000LL) b = 1000000000000000000LL;
    if (a > b) a = b;
    cout << a << " " << b << " " << randLL(1, 4) << "\n";
}
