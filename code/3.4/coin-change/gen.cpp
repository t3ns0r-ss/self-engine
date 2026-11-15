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
    int m = randInt(1, 4), x = randInt(1, 40);
    set<int> st;
    while ((int)st.size() < m) st.insert(randInt(1, randInt(1, 2) == 1 ? 5 : 45));
    cout << m << " " << x << "\n";
    int i = 0;
    for (int c : st) cout << c << (++i < m ? ' ' : '\n');
}
