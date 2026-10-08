// Brute force: choose how many coins of each value, by recursion over the coin values (each multiset once).
#include <bits/stdc++.h>
using namespace std;

int m, x;
vector<int> coin;
long long ways = 0;
int fewest = INT_MAX;

void go(int j, int left, int used) {
    if (j == m) {
        if (left == 0) {
            ways++;
            fewest = min(fewest, used);
        }
        return;
    }
    for (int k = 0; k * coin[j] <= left; k++) go(j + 1, left - k * coin[j], used + k);
}

int main() {
    cin >> m >> x;
    coin.resize(m);
    for (int& c : coin) cin >> c;
    go(0, x, 0);
    cout << (fewest == INT_MAX ? -1 : fewest) << "\n" << ways % 1000000007 << "\n";
}
