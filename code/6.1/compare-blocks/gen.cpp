#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 12), sigma = randInt(1, 3), q = randInt(1, 10);
    string s(n, 'a');
    for (char& c : s) c = 'a' + randInt(0, sigma - 1);
    printf("%s\n%d\n", s.c_str(), q);
    for (int i = 0; i < q; i++) {
        int len = randInt(1, n), a = randInt(1, n - len + 1), b = randInt(1, n - len + 1);
        printf("%d %d %d\n", a, b, len);
    }
}
