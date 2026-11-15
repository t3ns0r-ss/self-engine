#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 6), m = randInt(0, 9), length = randInt(0, 12);
    if (randInt(0, 4) == 0) length = randInt(0, 2);
    cout << n << " " << m << " " << length << "\n";
    for (int i = 0; i < m; i++) cout << randInt(0, n - 1) << " " << randInt(0, n - 1) << "\n";
    cout << randInt(0, n - 1) << " " << randInt(0, n - 1) << "\n";
}
