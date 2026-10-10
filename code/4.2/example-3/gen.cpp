#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 8);
    int percent = randInt(0, 50);
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        vector<int> targets;
        for (int j = 0; j < n; j++)
            if (j != i && randInt(1, 100) <= percent) targets.push_back(j);
        cout << targets.size();
        for (int v : targets) cout << " " << v;
        cout << "\n";
    }
}
