#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 9);
    int maxEdges = n * (n - 1) / 2;
    int m = randInt(0, min(maxEdges, 10));
    if (randInt(0, 5) == 0) m = 0;  // no edges at all
    set<pair<int, int>> used;
    while ((int)used.size() < m) {
        int a = randInt(1, n), b = randInt(1, n);
        if (a == b) continue;
        used.insert({min(a, b), max(a, b)});
    }
    cout << n << " " << m << "\n";
    for (auto [a, b] : used) {
        if (randInt(0, 1)) swap(a, b);
        cout << a << " " << b << "\n";
    }
}
