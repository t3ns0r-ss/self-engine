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
    int n = randInt(2, 7), dens = randInt(30, 90);  // edge probability in percent
    vector<pair<int, int>> e;
    for (int a = 1; a <= n; a++)
        for (int b = a + 1; b <= n; b++)
            if (randInt(1, 100) <= dens) e.push_back({a, b});
    cout << n << " " << e.size() << "\n";
    for (auto [a, b] : e) cout << a << " " << b << "\n";
}
