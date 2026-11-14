/*
Brute force for unique-order: try every permutation A of 1..n and count those with A_x < A_y for every fact.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> before(m);
    for (auto& [x, y] : before) cin >> x >> y;
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);  // a[i] is the value A_{i+1}
    int count = 0;
    vector<int> found;
    do {
        bool ok = true;
        for (auto [x, y] : before)
            if (a[x - 1] > a[y - 1]) ok = false;
        if (ok) {
            count++;
            found = a;
        }
    } while (next_permutation(a.begin(), a.end()));
    if (count != 1) {
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    for (int v = 0; v < n; v++) cout << found[v] << (v + 1 < n ? " " : "\n");
}
