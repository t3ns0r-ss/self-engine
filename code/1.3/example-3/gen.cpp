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
    int n = randInt(2, 9);
    int maxH = randInt(0, 10);
    vector<int> h(n);
    for (auto& x : h) x = randInt(0, maxH);
    if (randInt(0, 4) == 0) fill(h.begin(), h.end(), h[0]);  // all equal (ties on every step)
    cout << n << "\n";
    for (int i = 0; i < n; i++) cout << h[i] << (i + 1 < n ? ' ' : '\n');
}
