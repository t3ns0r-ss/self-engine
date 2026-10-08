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
    int t = randInt(1, 5);
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        int k = randInt(1, 6);  // a common factor makes gcd > 1 likely
        int a = k * randInt(1, 40), b = k * randInt(1, 40);
        if (randInt(0, 3) == 0) a = randInt(1, 3000), b = randInt(1, 3000);
        cout << a << " " << b << " " << randInt(0, 5000) << "\n";
    }
}
