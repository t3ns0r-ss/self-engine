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
    int n = randInt(1, 7), m = randInt(1, 7);
    int maxV = randInt(1, 12);
    vector<int> a(n), b(m);
    for (auto& x : a) x = randInt(-maxV, maxV);
    for (auto& x : b) x = randInt(-maxV, maxV);
    if (randInt(0, 4) == 0) b.assign(m, a[0]);  // all of b equal to a value in a
    cout << n << " " << m << "\n";
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? ' ' : '\n');
    for (int i = 0; i < m; i++) cout << b[i] << (i + 1 < m ? ' ' : '\n');
}
