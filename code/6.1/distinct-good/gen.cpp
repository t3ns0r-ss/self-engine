#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(1, 10), sigma = randInt(1, 3);
    string s(n, 'a');
    for (char& c : s) c = 'a' + randInt(0, sigma - 1);
    string flags(26, '0');
    for (char& c : flags) c = '0' + (rng() % 3 == 0);
    printf("%s\n%s\n%d\n", s.c_str(), flags.c_str(), randInt(0, n));
}
