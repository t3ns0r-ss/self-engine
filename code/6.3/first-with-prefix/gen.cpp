#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int sigma = randInt(1, 3), n = randInt(1, 6), q = randInt(1, 8);
    auto word = [&](int len) {
        string w(len, 'a');
        for (char& c : w) c = 'a' + randInt(0, sigma - 1);
        return w;
    };
    printf("%d\n", n);
    for (int i = 0; i < n; i++) printf("%s\n", word(randInt(1, 5)).c_str());
    printf("%d\n", q);
    for (int i = 0; i < q; i++) printf("%s\n", word(randInt(1, 5)).c_str());
}
