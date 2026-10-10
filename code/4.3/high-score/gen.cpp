#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](long long lo, long long hi) { return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo; };
    int n = randInt(2, 6), extra = randInt(0, 8);
    int lo = randInt(-6, 0), hi = randInt(1, 6);
    vector<array<long long, 3>> e;
    // a road from 1 to n through some rooms keeps room n reachable
    int cur = 1;
    for (int v = 2; v <= n; v++) if (v == n || randInt(0, 1)) e.push_back({cur, v, randInt(lo, hi)}), cur = v;
    for (int i = 0; i < extra; i++) e.push_back({randInt(1, n), randInt(1, n), randInt(lo, hi)});
    shuffle(e.begin(), e.end(), rng);
    cout << n << " " << e.size() << "\n";
    for (auto& x : e) cout << x[0] << " " << x[1] << " " << x[2] << "\n";
}
