/*
Problem: list every distinct sub-multiset of n values (each different collection of values once),
in lexicographic order of the sorted value lists, starting with the empty one.
Input: n (1 <= n <= 15), then n integers.
Output: the number of sub-multisets, then one per line: its size followed by its values in non-decreasing order.
*/
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a, chosen;
vector<vector<int>> found;

void rec(int start) {
    found.push_back(chosen);  // every node is one sub-multiset (its values in increasing index order)
    for (int i = start; i < n; i++) {
        if (i > start && a[i] == a[i - 1]) continue;  // same value as the previous try in this loop (Theorem 3.1.2)
        chosen.push_back(a[i]);
        rec(i + 1);  // later choices only from larger indices
        chosen.pop_back();  // undo
    }
}

int main() {
    cin >> n;
    a.resize(n);
    for (int& x : a) cin >> x;
    sort(a.begin(), a.end());  // equal values next to each other
    rec(0);
    cout << found.size() << "\n";
    for (auto& s : found) {
        cout << s.size();
        for (int x : s) cout << " " << x;
        cout << "\n";
    }
}
