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
    int a = randInt(0, 7), b = randInt(0, 7), q = randInt(1, 4);
    cout << a << " " << b << " " << q << "\n";
    for (int i = 0; i < q; i++) cout << randInt(0, a + 1) << " " << randInt(0, b + 1) << "\n";
}
