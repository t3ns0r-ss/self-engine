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
    int n = randInt(1, 10), m = randInt(1, 5);
    int letters = randInt(1, 3);
    string s, t;
    for (int i = 0; i < n; i++) s += char('a' + randInt(0, letters - 1));
    for (int i = 0; i < m; i++) t += char('a' + randInt(0, letters - 1));
    if (randInt(0, 2) == 0) {  // often make t a real subsequence of s
        t.clear();
        for (int i = 0; i < n; i++)
            if (randInt(0, 2) == 0) t += s[i];
        if (t.empty()) t = s.substr(0, 1);
    }
    cout << s << "\n" << t << "\n";
}
