#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 7), q = randInt(1, 14);
    set<pair<int, int>> used;
    vector<string> lines;
    for (int i = 0; i < q; i++) {
        int type = randInt(1, 3);
        if (type == 1 && n >= 2) {
            int u = randInt(1, n - 1), v = randInt(u + 1, n);
            if (used.insert({u, v}).second) { lines.push_back("1 " + to_string(u) + " " + to_string(v)); continue; }
        }
        lines.push_back((type == 2 ? "2 " : "3 ") + to_string(randInt(1, n)));
    }
    cout << n << " " << lines.size() << "\n";
    for (auto& l : lines) cout << l << "\n";
}
