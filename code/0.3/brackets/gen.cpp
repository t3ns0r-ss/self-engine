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
    int n = randInt(1, 6);
    string s;
    if (randInt(0, 1)) {  // often a valid sequence: random walk that never goes below 0 and closes
        int open = 0;
        for (int i = 0; i < 2 * n; i++) {
            int left = 2 * n - i;
            if (open > 0 && (open == left || randInt(0, 1))) {
                s += ')';
                open--;
            } else {
                s += '(';
                open++;
            }
        }
    } else {
        for (int i = 0; i < 2 * n - randInt(0, 1); i++) s += "()"[randInt(0, 1)];
    }
    cout << s << "\n";
}
