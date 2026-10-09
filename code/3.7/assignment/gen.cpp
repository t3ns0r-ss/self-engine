#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](long long lo, long long hi) {
        return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo;
    };
    int n = randInt(1, 8);
    long long hi = (randInt(0, 1) == 0) ? 9 : 1000000000;
    cout << n << "\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cout << randInt(0, hi) << (j + 1 < n ? " " : "\n");
}
