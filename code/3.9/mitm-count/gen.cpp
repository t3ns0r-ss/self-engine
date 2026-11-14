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
    int n = randInt(1, 12);
    int hi = randInt(1, 2) == 1 ? 5 : 1000000000;
    vector<long long> a(n);
    long long sum = 0;
    for (auto& x : a) {
        x = randInt(1, hi);
        sum += x;
    }
    long long T = (long long)(rng() % (unsigned long long)(sum + 2));  // from 0 to sum + 1
    if (randInt(1, 10) == 1) T = 0;
    cout << n << " " << T << "\n";
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? ' ' : '\n');
}
