#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](long long lo, long long hi) { return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo; };
    int n = randInt(2, 8);
    bool big = randInt(0, 3) == 0;
    cout << n << "\n";
    vector<int> label(n);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end(), rng);
    for (int i = 1; i < n; i++) {
        int parent = randInt(0, i - 1);
        long long w = big ? randInt(9000000, 10000000) : randInt(1, 9);
        if (randInt(0, 1)) cout << label[i] << " " << label[parent] << " " << w << "\n";
        else cout << label[parent] << " " << label[i] << " " << w << "\n";
    }
}
