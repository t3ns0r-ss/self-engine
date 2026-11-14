#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 6);
    vector<int> label(n);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end(), rng);
    vector<pair<int, int>> facts;
    int kind = randInt(0, 3);
    if (kind == 0) {
        // The chain of a hidden order, so the answer is yes; sometimes a link is left out or a shortcut is added.
        for (int i = 0; i + 1 < n; i++) facts.push_back({label[i], label[i + 1]});
        if (randInt(0, 1) && !facts.empty()) facts.erase(facts.begin() + randInt(0, (int)facts.size() - 1));
        if (randInt(0, 2) == 0 && n >= 3) facts.push_back({label[0], label[n - 1]});
    } else {
        // Random facts along a hidden order, so no cycle; some inputs have several orders.
        int m = randInt(0, 8);
        for (int i = 0; i < m && n > 1; i++) {
            int a = randInt(0, n - 2);
            int b = randInt(a + 1, n - 1);
            facts.push_back({label[a], label[b]});
        }
        if (kind == 3 && n >= 3) facts.push_back({label[n - 1], label[0]});  // a cycle: no order at all
    }
    cout << n << " " << facts.size() << "\n";
    for (auto [x, y] : facts) cout << x << " " << y << "\n";
}
