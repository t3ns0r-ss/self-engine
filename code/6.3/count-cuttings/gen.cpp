#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int sigma = randInt(1, 2), n = randInt(1, 10), k = randInt(1, 4);
    auto word = [&](int len) {
        string w(len, 'a');
        for (char& c : w) c = 'a' + randInt(0, sigma - 1);
        return w;
    };
    printf("%s\n%d\n", word(n).c_str(), k);
    for (int i = 0; i < k; i++) printf("%s\n", word(randInt(1, 3)).c_str());
}
