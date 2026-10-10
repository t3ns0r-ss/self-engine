/*
Problem: list every distinct arrangement of n values in lexicographic order.
Input: n (1 <= n <= 9), then n integers.
Output: the number of distinct arrangements, then one per line.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.1.2. Every distinct arrangement once: equal values are placed left to right, so an index is skipped when an
// equal, earlier copy is still unused. The values must be sorted.
vector<vector<int>> distinctPermutations(vector<int> a) {
    sort(a.begin(), a.end());
    int n = a.size();
    vector<bool> used(n, false);
    vector<int> current;
    vector<vector<int>> found;
    function<void()> rec = [&]() {
        if ((int)current.size() == n) {
            found.push_back(current);
            return;
        }
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            if (i > 0 && a[i] == a[i - 1] && !used[i - 1]) continue;
            used[i] = true;
            current.push_back(a[i]);
            rec();
            current.pop_back();  // undo both changes
            used[i] = false;
        }
    };
    rec();
    return found;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    auto found = distinctPermutations(a);
    cout << found.size() << "\n";
    for (auto& p : found)
        for (int i = 0; i < n; i++) cout << p[i] << (i + 1 < n ? ' ' : '\n');
}
