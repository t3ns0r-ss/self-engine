#include <bits/stdc++.h>
using namespace std;

/*
Problem: a permutation of 1 ... n (n up to 10^5). Sort it with the fewest swaps of two elements (any two positions) and print the number of swaps.
Input: n, then the permutation.
Output: the number of swaps (after the program has checked that its swaps sort the array).
*/

// snippet:begin
// Theorem 7.7.4: n - c swaps, where c is the number of cycles; for each i, swap the value i into the position i.
vector<pair<int, int>> sortBySwaps(vector<int> p) {  // p[0] is the position 1; returns the swapped positions (from 1)
    int n = p.size();
    vector<int> where(n + 1);
    for (int i = 0; i < n; i++) where[p[i]] = i;
    vector<pair<int, int>> swaps;
    for (int i = 0; i < n; i++) {
        if (p[i] == i + 1) continue;
        int j = where[i + 1];
        swap(p[i], p[j]);
        where[p[j]] = j;
        where[p[i]] = i;
        swaps.push_back({i + 1, j + 1});
    }
    return swaps;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int& x : p) cin >> x;
    auto swaps = sortBySwaps(p);
    auto q = p;
    for (auto [a, b] : swaps) swap(q[a - 1], q[b - 1]);
    cout << (is_sorted(q.begin(), q.end()) ? (int)swaps.size() : -1) << "\n";
}
