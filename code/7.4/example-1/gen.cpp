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
    vector<int> h(n);
    iota(h.begin(), h.end(), 1);
    shuffle(h.begin(), h.end(), rng);
    printf("%d\n", n);
    for (int x : h) printf("%d ", x);
    printf("\n");
    for (int i = 0; i < n; i++) printf("%d ", randInt(1, 20));
    printf("\n");
}
