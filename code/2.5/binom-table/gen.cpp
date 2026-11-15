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
    int q = randInt(1, 5);
    cout << q << "\n";
    for (int i = 0; i < q; i++) {
        int n = randInt(0, 200);
        cout << n << " " << randInt(0, n + 3) << "\n";
    }
}
