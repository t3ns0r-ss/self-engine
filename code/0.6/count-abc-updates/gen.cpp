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
    int n = randInt(3, 9), q = randInt(1, 9);
    string s;
    for (int i = 0; i < n; i++) s += "ABC"[randInt(0, 2)];
    cout << n << " " << q << "\n" << s << "\n";
    for (int i = 0; i < q; i++) cout << randInt(1, n) << " " << "ABC"[randInt(0, 2)] << "\n";
}
