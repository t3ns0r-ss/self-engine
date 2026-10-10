#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](long long lo, long long hi) { return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo; };
    int n = randInt(1, 7), m = randInt(0, 10), q = randInt(1, 8);
    bool big = randInt(0, 3) == 0;
    auto weight = [&]() { return big ? randInt(900000000, 1000000000) : randInt(1, 9); };
    cout << n << " " << m << " " << q << "\n";
    for (int i = 0; i < m; i++) cout << randInt(1, n) << " " << randInt(1, n) << " " << weight() << "\n";
    for (int i = 0; i < q; i++) cout << randInt(1, n) << " " << randInt(1, n) << " " << (big ? randInt(899999999, 1000000000) : randInt(0, 10)) << "\n";
}
