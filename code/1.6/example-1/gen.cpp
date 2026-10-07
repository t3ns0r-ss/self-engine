#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    int n = rng() % 10 + 1;
    vector<int> h(n);
    iota(h.begin(), h.end(), 1);
    shuffle(h.begin(), h.end(), rng);
    cout << n << "\n";
    for (int i = 0; i < n; i++) cout << h[i] << (i + 1 < n ? ' ' : '\n');
}
