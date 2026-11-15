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
    int n = randInt(1, 18), m = randInt(1, min(n, 4));
    set<int> st;
    while ((int)st.size() < m) st.insert(randInt(1, min(n, 5)));
    cout << n << " " << m << "\n";
    int i = 0;
    for (int x : st) cout << x << (++i < m ? ' ' : '\n');
}
