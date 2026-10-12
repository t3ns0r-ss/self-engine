#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(2, 7);
    string s;
    for (int i = 0; i < n; i++) s += randInt(0, 1) ? '1' : '0';
    if (randInt(0, 1)) {  // a candidate that meets the necessary conditions most of the time
        s[0] = '1';
        s[n - 1] = '0';
        for (int i = 1; i < n; i++) s[n - i - 1] = s[i - 1];
        s[n - 1] = '0';
    }
    cout << s << "\n";
}
