#include <bits/stdc++.h>
using namespace std;

/*
Problem: a list of n numbers; n times a place p is given: print the element at place p of the current list and remove it.
Input: n, the n numbers, then the n places p_1..p_n (p_i <= n - i + 1).
Output: the removed numbers, in order, separated by spaces.
*/

// snippet:begin
// The original place of the k-th element still present, by one walk down a Fenwick tree of counts (Theorem 5.2.6).
int kthPlace(const vector<int>& tree, int k) {
    int n = tree.size() - 1, pos = 0, step = 1;
    while (step * 2 <= n) step *= 2;
    for (; step > 0; step /= 2)
        if (pos + step <= n && tree[pos + step] < k) {
            pos += step;
            k -= tree[pos];
        }
    return pos + 1;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> x(n + 1), tree(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> x[i];
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += j & -j) tree[j]++;  // a 1 at every place: the tree of all ones
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        int place = kthPlace(tree, p);
        cout << x[place] << (i + 1 < n ? ' ' : '\n');
        for (int j = place; j <= n; j += j & -j) tree[j]--;  // remove it
    }
}
