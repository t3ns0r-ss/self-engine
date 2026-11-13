#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937_64 rng(atoi(argv[1]));
    auto r = [&](long long lo, long long hi) { return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo; };
    int n = r(1, 4);
    long long secret = r(0, 500);
    bool consistent = rng() % 2;
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        long long m = r(1, 12), res = consistent ? secret % m : r(0, 40);
        cout << res << " " << m << "\n";
    }
}
