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
    int n = randInt(2, 12), q = randInt(1, 8);
    string letters = randInt(0, 1) ? "AC" : "ACGT";  // mostly A and C, so "AC" is frequent
    cout << n << " " << q << "\n";
    for (int i = 0; i < n; i++) cout << letters[randInt(0, (int)letters.size() - 1)];
    cout << "\n";
    for (int i = 0; i < q; i++) {
        int l = randInt(1, n - 1), r = randInt(l + 1, n);
        cout << l << " " << r << "\n";
    }
}
