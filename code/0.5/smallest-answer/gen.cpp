#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) {
        return (int)(rng() % (unsigned)(hi - lo + 1)) + lo;
    };
    int k = randInt(0, 3) == 0 ? randInt(1, 1000000) : randInt(1, 200);  // mostly small K, some huge
    cout << randInt(1, 60) << " " << k << "\n";
}
