#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int m = randInt(2, 8);
    int n = randInt(1, 40);
    if (randInt(0, 4) == 0) n = randInt(1, m + 1);
    cout << n << " " << m << "\n";
}
