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
    int t = randInt(0, 1), n = randInt(1, 18), d = randInt(1, n);
    vector<int> all(n);
    iota(all.begin(), all.end(), 1);
    shuffle(all.begin(), all.end(), rng);
    int m = randInt(1, min(n, 5));
    cout << t << " " << n << " " << d << " " << m << "\n";
    for (int i = 0; i < m; i++) cout << all[i] << (i + 1 < m ? " " : "\n");
}
