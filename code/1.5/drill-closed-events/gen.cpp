#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](long long lo, long long hi) {
        return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo;
    };
    int n = randInt(1, 7);
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        int l = randInt(1, 12), r = randInt(l, std::min<long long>(l + 6, 30));
        cout << l << " " << r << "\n";
    }
}
