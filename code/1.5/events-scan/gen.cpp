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
    int n = randInt(1, 6), top = randInt(0, 1) ? 6 : 14;
    cout << n << "\n";
    int prevEnd = randInt(0, top);
    for (int i = 0; i < n; i++) {
        int l = randInt(0, top), r;
        int kind = randInt(0, 3);
        if (kind == 0) l = prevEnd + 1 > top ? prevEnd : prevEnd + 1;  // starts right after the previous end
        if (kind == 1) l = prevEnd;                                    // starts on the previous end
        r = randInt(l, top);
        if (randInt(0, 5) == 0) r = l;  // a single second
        cout << l << " " << r << " " << randInt(1, 5) << "\n";
        prevEnd = r;
    }
}
