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
    int n = 2 * randInt(1, 3);  // even, at most 6: the brute force tries 8^n assignments
    vector<int> x(n);
    int all = 0;
    for (auto& v : x) v = randInt(0, 7), all ^= v;
    cout << n << "\n";
    for (int i = 0; i < n; i++) cout << (all ^ x[i]) << (i + 1 < n ? ' ' : '\n');
}
