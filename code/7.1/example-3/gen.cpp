#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 12);
    printf("%d %d\n", n, randInt(1, 6));
    vector<int> label(n);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin() + 1, label.end(), rng);  // the root stays 1
    for (int i = 1; i < n; i++) printf("%d %d\n", label[i], label[randInt(0, i - 1)]);
}
