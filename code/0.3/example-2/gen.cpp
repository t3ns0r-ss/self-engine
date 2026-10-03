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
    int n = randInt(1, 12);
    string s;
    for (int i = 0; i < n; i++) s += "a,,\""[randInt(0, 3)];
    if (count(s.begin(), s.end(), '"') % 2 == 1) s += '"';  // keep the number of quotes even
    cout << s.size() << "\n" << s << "\n";
}
