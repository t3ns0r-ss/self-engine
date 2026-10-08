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
    const int primes[] = {2, 3, 5, 7, 11, 13};
    int t = randInt(1, 5);
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        int p = primes[randInt(0, 5)];
        int a = randInt(0, 3) == 0 ? p * randInt(0, 3) : randInt(0, 40);  // multiples of p too
        int b = randInt(0, 6), c = randInt(0, 6);  // b^c <= 46656
        cout << a << " " << b << " " << c << " " << p << "\n";
    }
}
