#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 4);
    cout << n << "\n";
    // half of the cases are reachable: do random moves from all ones
    vector<int> a(n, 1);
    if (randInt(0, 1)) {
        for (int step = randInt(0, 6); step > 0; step--) {
            int sum = accumulate(a.begin(), a.end(), 0);
            if (sum > 60) break;
            a[randInt(0, n - 1)] = sum;
        }
    } else {
        for (int& x : a) x = randInt(1, 13);
    }
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? " " : "\n");
}
