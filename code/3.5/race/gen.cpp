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
    int a = randInt(1, 8), b = randInt(1, 8);
    long long den = randInt(0, 1) ? randInt(2, 10) : randInt(2, 1000000000);
    long long num = randInt(1, den - 1);
    cout << a << " " << b << " " << num << " " << den << "\n";
}
