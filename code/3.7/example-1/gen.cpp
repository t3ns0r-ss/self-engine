#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) {
        return (int)(rng() % (unsigned)(hi - lo + 1)) + lo;
    };
    int n = randInt(1, 8), percent = randInt(20, 100);
    cout << n << "\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cout << (randInt(1, 100) <= percent ? 1 : 0) << (j + 1 < n ? " " : "\n");
}
