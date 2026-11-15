#include <bits/stdc++.h>
using namespace std;

// Hidden test: "n budget" and then the string S (S_1 = 0, S_n = 1). The budget is ceil(log2(n - 1)).
int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](int lo, int hi) { return (int)(rng() % (unsigned)(hi - lo + 1)) + lo; };
    int n = randInt(2, 40);
    int budget = 0;
    while ((1 << budget) < n - 1) budget++;
    int ones = randInt(0, 3);  // sometimes a long run of zeros then ones, sometimes mixed
    string s(n, '0');
    s[n - 1] = '1';
    for (int i = 1; i + 1 < n; i++) s[i] = (ones == 0) ? (i * 2 >= n ? '1' : '0') : (rng() % 2 ? '1' : '0');
    cout << n << " " << budget << "\n" << s << "\n";
}
