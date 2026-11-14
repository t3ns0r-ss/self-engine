#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(2, 5);
    set<pair<int, int>> teleporters;
    if (randInt(0, 2) == 0) {
        // Arbitrary teleporters.
        int m = randInt(1, 7);
        for (int i = 0; i < m; i++) teleporters.insert({randInt(1, n), randInt(1, n)});
    } else {
        // A walk from 1 to n, plus sometimes a closed walk that may touch it or not.
        int at = 1;
        int steps = randInt(1, 5);
        for (int i = 0; i < steps; i++) {
            int to = i == steps - 1 ? n : randInt(1, n);
            teleporters.insert({at, to});
            at = to;
        }
        if (randInt(0, 2) == 0) {
            int first = randInt(1, n), cur = first;
            int len = randInt(1, 3);
            for (int i = 0; i < len; i++) {
                int to = randInt(1, n);
                teleporters.insert({cur, to});
                cur = to;
            }
            teleporters.insert({cur, first});
        }
        if (randInt(0, 4) == 0 && teleporters.size() > 1) teleporters.erase(teleporters.begin());
    }
    while (teleporters.size() > 8) teleporters.erase(teleporters.begin());
    cout << n << " " << teleporters.size() << "\n";
    for (auto [a, b] : teleporters) cout << a << " " << b << "\n";
}
