#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](long long lo, long long hi) { return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo; };
    int N = randInt(2, 8);
    bool big = randInt(0, 3) == 0;
    cout << N << " " << randInt(1, 60) << "\n";
    for (int i = 0; i < N; i++) cout << (big ? randInt(900000, 1000000) : randInt(1, 9)) << (i + 1 < N ? " " : "\n");
}
