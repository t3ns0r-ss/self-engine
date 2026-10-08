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
    int n = randInt(1, 10), days = randInt(1, 2) == 1 ? 6 : 1000000000;
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        int a = randInt(1, days), b = randInt(1, days);
        if (a > b) swap(a, b);
        cout << a << " " << b << " " << randInt(1, randInt(1, 2) == 1 ? 5 : 1000000000) << "\n";
    }
}
