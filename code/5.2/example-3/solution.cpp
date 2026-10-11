#include <bits/stdc++.h>
using namespace std;

/*
Problem (CSES 1749, List Removals): a list of n numbers; then n places p_1..p_n: each time print the element at place p_i of the current list and remove it.
Input: n, the n numbers, then the n places.
Output: the removed numbers, separated by spaces.
*/

// snippet:begin
// The elements removed one by one by their current place: a Fenwick tree of ones, and a walk down it for the k-th one.
vector<int> removals(const vector<int>& x, const vector<int>& places) {
    int n = x.size();
    vector<int> tree(n + 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += j & -j) tree[j]++;  // a 1 at every place
    int top = 1;
    while (top * 2 <= n) top *= 2;
    vector<int> removed;
    for (int k : places) {
        int pos = 0;
        for (int step = top; step > 0; step /= 2)
            if (pos + step <= n && tree[pos + step] < k) {
                pos += step;
                k -= tree[pos];
            }
        removed.push_back(x[pos]);  // pos + 1 is the place (1-based), so x[pos] is the element
        for (int i = pos + 1; i <= n; i += i & -i) tree[i]--;
    }
    return removed;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> x(n), p(n);
    for (int& v : x) cin >> v;
    for (int& v : p) cin >> v;
    vector<int> out = removals(x, p);
    for (int i = 0; i < n; i++) cout << out[i] << (i + 1 < n ? ' ' : '\n');
}
