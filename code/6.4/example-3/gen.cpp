#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 7), sigma = randInt(1, 3);
    vector<int> sa(n);
    if (randInt(0, 3) == 0) {  // a random permutation: usually not a suffix array
        iota(sa.begin(), sa.end(), 0);
        shuffle(sa.begin(), sa.end(), rng);
    } else {                   // the suffix array of a random string
        string s(n, 'a');
        for (char& c : s) c = 'a' + randInt(0, sigma - 1);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(), [&](int a, int b) { return s.substr(a) < s.substr(b); });
    }
    printf("%d\n", n);
    for (int i = 0; i < n; i++) printf("%d%c", sa[i] + 1, i + 1 < n ? ' ' : '\n');
}
