// Brute force: for each cell, add the ways of every earlier cell from which some allowed jump lands here.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    set<int> jumps;
    for (int s = 0; s < k; s++) {
        int l, r;
        cin >> l >> r;
        for (int d = l; d <= r; d++) jumps.insert(d);
    }
    vector<long long> ways(n + 1, 0);
    ways[1] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j < i; j++)
            if (jumps.count(i - j)) ways[i] = (ways[i] + ways[j]) % 998244353;
    cout << ways[n] << "\n";
}
