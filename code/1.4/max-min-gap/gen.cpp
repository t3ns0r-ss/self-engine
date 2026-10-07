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
    int n = randInt(2, 10), m = randInt(2, n), hi = randInt(0, 1) ? 20 : 1000000000;
    set<int> s;
    while ((int)s.size() < n) s.insert(randInt(0, hi));
    vector<int> v(s.begin(), s.end());
    shuffle(v.begin(), v.end(), rng);
    cout << n << " " << m << "\n";
    for (int i = 0; i < n; i++) cout << v[i] << (i + 1 < n ? ' ' : '\n');
}
