#include <bits/stdc++.h>
using namespace std;

// Hidden test: "n budget" and the n different numbers. The budget is 2 * ceil(log2 n).
int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 30);
    int rounds = 0;
    while ((1 << rounds) < n) rounds++;
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    int shape = randInt(0, 3);
    if (shape == 0) {
        // increasing
    } else if (shape == 1) {
        reverse(a.begin(), a.end());
    } else {
        shuffle(a.begin(), a.end(), rng);
    }
    cout << n << " " << 2 * rounds << "\n";
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
}
