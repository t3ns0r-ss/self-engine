#include <bits/stdc++.h>
using namespace std;

// Hidden test: n, then the n numbers.
int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(3, 12);
    int range = rng() % 3 == 0 ? 1000000000 : 6;
    cout << n << "\n";
    for (int i = 0; i < n; i++) cout << randInt(0, range) << " \n"[i + 1 == n];
}
