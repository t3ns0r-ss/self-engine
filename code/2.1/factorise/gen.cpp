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
    int kind = randInt(0, 2);
    long long n;
    if (kind == 0) n = randInt(2, 3000);
    else if (kind == 1) {  // a product of small primes, many divisors
        const int ps[] = {2, 3, 5, 7};
        n = 1;
        while (n < 2 || randInt(0, 3)) {
            int p = ps[randInt(0, 3)];
            if (n * p > 4000) break;
            n *= p;
        }
        if (n < 2) n = 2;
    } else {  // a square of a prime, or a prime times a small number
        const int ps[] = {41, 43, 47, 53, 59, 61};
        int p = ps[randInt(0, 5)];
        n = randInt(0, 1) ? (long long)p * p : (long long)p * randInt(1, 60);
    }
    cout << n << "\n";
}
