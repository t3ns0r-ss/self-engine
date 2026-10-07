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
    int t = randInt(1, 5);
    cout << t << "\n";
    while (t--) {
        int a = randInt(0, 40), b = randInt(0, 40);
        if (randInt(0, 1)) cout << a + b << " " << (a ^ b) << "\n";  // a valid pair exists
        else cout << randInt(0, 80) << " " << randInt(0, 80) << "\n";
    }
}
