#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937_64 rng(atoi(argv[1]));
    auto r = [&](long long lo, long long hi) { return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo; };
    long long a = r(-12, 12), b = r(-12, 12);
    if (rng() % 8 == 0) a = 0;
    if (rng() % 8 == 0) b = 0;
    long long x1 = r(-30, 30), y1 = r(-30, 30);
    long long x2 = x1 + r(-2, 40), y2 = y1 + r(-2, 40);   // sometimes empty
    long long c = rng() % 5 == 0 ? r(-200, 200) : a * r(x1, max(x1, x2)) + b * r(y1, max(y1, y2));
    cout << a << " " << b << " " << c << " " << x1 << " " << x2 << " " << y1 << " " << y2 << "\n";
}
