#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), g(61, 0);
    for (int& x : a) cin >> x;
    for (int x = 2; x <= 60; x++) {  // the Grundy value by the definition
        set<int> reach;
        for (int d = 1; d < x; d++)
            if (x % d == 0) reach.insert(g[d]);
        while (reach.count(g[x])) g[x]++;
    }
    int total = 0;
    for (int x : a) total ^= g[x];
    cout << (total ? "Anna" : "Bruno") << "\n";
}
