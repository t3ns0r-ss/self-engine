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
    int n = randInt(1, 12), x = randInt(1, 40);
    cout << n << " " << x << "\n";
    for (int i = 0; i < n; i++) cout << randInt(1, 20) << (i + 1 < n ? ' ' : '\n');
    for (int i = 0; i < n; i++) cout << randInt(1, randInt(1, 2) == 1 ? 3 : 1000) << (i + 1 < n ? ' ' : '\n');
}
