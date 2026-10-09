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
    int n = randInt(1, 9);
    long long cap = (randInt(0, 1) == 0) ? randInt(1, 12) : 1000000000;
    cout << n << " " << cap << "\n";
    for (int i = 0; i < n; i++) cout << randInt(1, cap) << (i + 1 < n ? " " : "\n");
}
