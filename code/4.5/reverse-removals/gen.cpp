#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    auto randInt = [&](long long lo, long long hi) { return (long long)(rng() % (unsigned long long)(hi - lo + 1)) + lo; };
    int n = randInt(2, 7), possible = n * (n - 1) / 2;
    int m = randInt(0, min(possible, 10));
    vector<pair<int, int>> all;
    for (int a = 1; a <= n; a++) for (int b = a + 1; b <= n; b++) all.push_back({a, b});
    shuffle(all.begin(), all.end(), rng);
    cout << n << " " << m << "\n";
    for (int i = 0; i < m; i++) cout << all[i].first << " " << all[i].second << "\n";
}
