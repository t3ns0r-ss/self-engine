// Brute force: next_permutation from the sorted list (Theorem 0.5.3).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    sort(a.begin(), a.end());
    vector<vector<int>> all;
    do all.push_back(a); while (next_permutation(a.begin(), a.end()));
    cout << all.size() << "\n";
    for (auto& p : all)
        for (int i = 0; i < n; i++) cout << p[i] << (i + 1 < n ? ' ' : '\n');
}
