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
    int n = randInt(1, 14), letters = randInt(1, 3);
    string s;
    for (int i = 0; i < n; i++) s += char('a' + randInt(0, letters - 1));
    cout << n << "\n" << s << "\n";
}
