#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](long long lo, long long hi) { return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo; };
    int n = randInt(1, 5), m = randInt(0, 6);
    bool big = randInt(0, 3) == 0;
    auto price = [&]() { return big ? randInt(900000000, 1000000000) : randInt(1, 9); };
    cout << n << " " << m << "\n";
    for (int i = 0; i < n; i++) cout << price() << (i + 1 < n ? " " : "\n");
    for (int i = 0; i < m; i++) cout << randInt(1, n) << " " << randInt(1, n) << " " << price() << "\n";
}
