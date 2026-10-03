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
    int mode = randInt(0, 3);
    int n = mode == 0 ? randInt(1, 20) : randInt(1, 1000000);
    if (mode == 3) n = vector<int>{113383, 134379, 159487, 997823, 1000000}[randInt(0, 4)];  // values pass 2^31
    cout << n << "\n";
}
