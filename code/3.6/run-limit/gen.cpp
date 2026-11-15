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
    int k = randInt(1, 4);
    int n = (k == 1) ? randInt(1, 12) : randInt(1, (k == 2) ? 14 : (k == 3) ? 9 : 7);
    cout << n << " " << k << " " << randInt(1, 5) << "\n";
}
