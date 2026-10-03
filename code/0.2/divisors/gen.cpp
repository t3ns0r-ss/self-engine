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
    int mode = randInt(0, 3);
    long long n;
    if (mode == 0) n = randInt(1, 30);
    else if (mode == 1) { long long r = randInt(1, 300); n = r * r; }  // perfect squares
    else if (mode == 2) n = vector<int>{720, 5040, 30030, 83160, 1, 2, 97, 99991}[randInt(0, 7)];  // many or few divisors
    else n = randInt(1, 100000);
    cout << n << "\n";
}
