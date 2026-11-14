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
    int n = randInt(0, 3) == 0 ? randInt(1, 300) : randInt(1, 40);  // lengths around 25 and 26 are covered too
    cout << n << "\n";
    for (int i = 0; i < n; i++) cout << randInt(0, 9) << (i + 1 < n ? " " : "\n");
}
