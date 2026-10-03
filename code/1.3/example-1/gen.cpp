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
    int n = randInt(1, 9);
    int maxV = randInt(1, 6);
    if (randInt(0, 5) == 0) maxV = 1000000000;  // large ids: all different
    vector<int> k(n);
    for (auto& x : k) x = randInt(1, maxV);
    cout << n << "\n";
    for (int i = 0; i < n; i++) cout << k[i] << (i + 1 < n ? ' ' : '\n');
}
