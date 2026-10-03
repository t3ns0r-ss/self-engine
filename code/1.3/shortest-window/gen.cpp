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
    int n = randInt(1, 8);
    int maxV = randInt(1, 10);
    vector<int> a(n);
    for (auto& x : a) x = randInt(1, maxV);
    if (randInt(0, 4) == 0) fill(a.begin(), a.end(), a[0]);  // all equal
    int total = accumulate(a.begin(), a.end(), 0);
    int S = randInt(1, total + 2);
    if (randInt(0, 4) == 0) S = total;  // boundary: only the whole array may reach S
    cout << n << " " << S << "\n";
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? ' ' : '\n');
}
