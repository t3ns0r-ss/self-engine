#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](long long lo, long long hi) { return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo; };
    int n = randInt(2, 7);
    bool big = randInt(0, 3) == 0;
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end(), rng);
    cout << n << "\n";
    for (int i = 1; i < n; i++) cout << p[i] << " " << p[randInt(0, i - 1)] << " " << (big ? randInt(900000000, 1000000000) : randInt(1, 9)) << "\n";
}
