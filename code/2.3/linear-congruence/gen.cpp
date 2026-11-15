#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937_64 rng(atoi(argv[1]));
    auto r = [&](long long lo, long long hi) { return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo; };
    long long m = r(1, 60), a = r(0, 300), b = r(0, 300);
    if (rng() % 3 == 0) b = a * r(0, 59) % (m * 5);   // often solvable
    cout << a << " " << b << " " << m << "\n";
}
