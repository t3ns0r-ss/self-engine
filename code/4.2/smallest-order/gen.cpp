#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 7);
    int m = randInt(0, 9);
    bool acyclic = randInt(0, 3) != 0;  // most inputs have no cycle, some may
    vector<int> label(n);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end(), rng);
    set<pair<int, int>> used;
    for (int tries = 0; tries < 40 && (int)used.size() < m && n > 1; tries++) {
        int i = randInt(0, n - 1), j = randInt(0, n - 1);
        if (i == j) continue;
        if (acyclic && i > j) swap(i, j);  // arrows follow a hidden order: no cycle
        used.insert({label[i], label[j]});
    }
    cout << n << " " << used.size() << "\n";
    for (auto [a, b] : used) cout << a << " " << b << "\n";
}
