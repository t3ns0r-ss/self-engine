/*
Problem: list every distinct sub-multiset of n values (each different collection of values once),
in lexicographic order of the sorted value lists, starting with the empty one.
Input: n (1 <= n <= 15), then n integers.
Output: the number of sub-multisets, then one per line: its size followed by its values in non-decreasing order.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.1.2. Every distinct sub-multiset once: the next index is larger than the last one taken, and inside one loop
// a value equal to the previous try is skipped. The values must be sorted.
vector<vector<int>> distinctSubsets(vector<int> a) {
    sort(a.begin(), a.end());
    int n = a.size();
    vector<vector<int>> found;
    vector<int> chosen;
    function<void(int)> rec = [&](int start) {
        found.push_back(chosen);  // every node is one sub-multiset
        for (int i = start; i < n; i++) {
            if (i > start && a[i] == a[i - 1]) continue;  // same value as the previous try in this loop
            chosen.push_back(a[i]);
            rec(i + 1);
            chosen.pop_back();  // undo
        }
    };
    rec(0);
    return found;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    auto found = distinctSubsets(a);
    cout << found.size() << "\n";
    for (auto& s : found) {
        cout << s.size();
        for (int x : s) cout << " " << x;
        cout << "\n";
    }
}
