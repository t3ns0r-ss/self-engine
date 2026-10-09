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
    int n = randInt(2, 8), hi = (randInt(0, 1) == 0) ? 24 : 1000000000;
    set<int> s;
    while ((int)s.size() < n) s.insert(randInt(1, hi));
    vector<int> v(s.begin(), s.end());
    shuffle(v.begin(), v.end(), rng);
    cout << n << "\n";
    for (int i = 0; i < n; i++) cout << v[i] << (i + 1 < n ? " " : "\n");
}
