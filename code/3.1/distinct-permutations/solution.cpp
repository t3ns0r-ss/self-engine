/*
Problem: list every distinct arrangement of n values in lexicographic order.
Input: n (1 <= n <= 9), then n integers.
Output: the number of distinct arrangements, then one per line.
*/
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a, current;
vector<bool> used;
vector<vector<int>> found;

void rec() {
    if ((int)current.size() == n) {
        found.push_back(current);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        // equal values are placed left to right: skip a[i] if an equal, earlier copy is still unused
        if (i > 0 && a[i] == a[i - 1] && !used[i - 1]) continue;
        used[i] = true;
        current.push_back(a[i]);
        rec();
        current.pop_back();  // undo both changes
        used[i] = false;
    }
}

int main() {
    cin >> n;
    a.resize(n);
    for (int& x : a) cin >> x;
    sort(a.begin(), a.end());
    used.assign(n, false);
    rec();
    cout << found.size() << "\n";
    for (auto& p : found)
        for (int i = 0; i < n; i++) cout << p[i] << (i + 1 < n ? ' ' : '\n');
}
