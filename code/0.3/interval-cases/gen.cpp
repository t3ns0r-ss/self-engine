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
    int a = randInt(-8, 8), b = a + randInt(0, 6);
    int c = randInt(-8, 8), d = c + randInt(0, 6);
    if (randInt(0, 3) == 0) c = b;  // touching ends
    if (d < c) d = c;
    cout << a << " " << b << " " << c << " " << d << "\n";
}
