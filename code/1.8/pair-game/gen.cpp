#include <bits/stdc++.h>
using namespace std;

// Hidden test: n, then the judge's preference order: a permutation of 1 .. 2n + 1 (it names the first unused one).
int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: gen <seed>\n";
        return 1;
    }
    mt19937 rng(atoi(argv[1]));
    int n = (int)(rng() % 12) + 1;
    vector<int> order(2 * n + 1);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end(), rng);
    cout << n << "\n";
    for (int i = 0; i < 2 * n + 1; i++) cout << order[i] << " \n"[i + 1 == 2 * n + 1];
}
