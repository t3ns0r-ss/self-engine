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
    const int near[] = {35, 36, 99, 100, 195, 196, 255, 256, 440, 441, 1224, 1225};
    if (randInt(0, 2) == 0) cout << near[randInt(0, 11)] << "\n";  // around 36, 100, 196, 256, 441, 1225
    else cout << randInt(1, 3000) << "\n";
}
