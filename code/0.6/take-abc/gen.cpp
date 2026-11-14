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
    int n = randInt(1, 14);
    bool nested = randInt(0, 2) == 0;  // sometimes build nested ABC pieces, which are the hard case
    string s;
    if (nested) {
        while ((int)s.size() < n) {
            int pos = randInt(0, (int)s.size());
            s.insert(pos, "ABC");
        }
    } else {
        for (int i = 0; i < n; i++) s += "ABC"[randInt(0, 2)];
    }
    cout << s << "\n";
}
