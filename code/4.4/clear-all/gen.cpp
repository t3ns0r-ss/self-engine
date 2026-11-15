#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](long long lo, long long hi) { return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo; };
    int k = randInt(1, 4), m = randInt(0, 6);
    bool big = randInt(0, 3) == 0;
    cout << k << " " << m << "\n";
    for (int i = 0; i < m; i++) {
        long long days = big ? randInt(900000000, 1000000000) : randInt(1, 9);
        int cure = randInt(0, (1 << k) - 1), cause = randInt(0, 2) == 0 ? randInt(0, (1 << k) - 1) : 0;
        cout << days << " " << cure << " " << cause << "\n";
    }
}
