#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](long long lo, long long hi) { return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo; };
    auto labelOf = [&](int n) { vector<int> p(n); iota(p.begin(), p.end(), 1); shuffle(p.begin(), p.end(), rng); return p; };
    int n = randInt(1, 10), q = randInt(1, 8);
    auto p = labelOf(n);
    cout << n << " " << q << "\n";
    for (int i = 1; i < n; i++) {
        int a = p[i], b = p[randInt(0, i - 1)];
        if (randInt(0, 1)) swap(a, b);
        cout << a << " " << b << "\n";
    }
    for (int i = 0; i < q; i++) cout << randInt(1, n) << " " << randInt(1, n) << "\n";
}
