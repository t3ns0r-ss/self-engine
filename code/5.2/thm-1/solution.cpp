#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.2.1. tree[i] = a[i - lowbit(i) + 1] + ... + a[i] (positions 1..n, a[0] unused); prefix(i) = a[1] + ... + a[i].
vector<long long> buildTree(const vector<long long>& a) {
    int n = a.size() - 1;
    vector<long long> tree(n + 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = i - (i & -i) + 1; j <= i; j++) tree[i] += a[j];  // the block of positions that ends at i
    return tree;
}
long long prefix(const vector<long long>& tree, int i) {
    long long sum = 0;
    for (; i > 0; i -= i & -i) sum += tree[i];  // each step removes the lowest set bit of i
    return sum;
}
// snippet:end

static void show(const vector<long long>& values, const vector<int>& queries) {
    vector<long long> a = {0};
    a.insert(a.end(), values.begin(), values.end());
    auto tree = buildTree(a);
    cout << "a =";
    for (size_t i = 1; i < a.size(); i++) cout << ' ' << a[i];
    cout << "\n";
    cout << "tree =";
    for (size_t i = 1; i < tree.size(); i++) cout << ' ' << tree[i];
    cout << "\n";
    for (int q : queries) {
        cout << "prefix(" << q << ") = " << prefix(tree, q) << " via";
        for (int i = q; i > 0; i -= i & -i) cout << ' ' << i;
        cout << "\n";
    }
}

int main() {
    show({3, 1, 4, 1, 5, 9, 2, 6}, {7, 6, 8});
    show({5}, {1});
    show({1, 1, 1, 1, 1, 1, 1}, {7});
    // Check against: the plain sum, on every array of length 1..6 over {0, 1, 2}, for every prefix.
    for (int n = 1; n <= 6; n++) {
        int total = 1;
        for (int i = 0; i < n; i++) total *= 3;
        for (int code = 0; code < total; code++) {
            vector<long long> a(n + 1, 0);
            for (int i = 1, c = code; i <= n; i++, c /= 3) a[i] = c % 3;
            auto tree = buildTree(a);
            long long sum = 0;
            for (int i = 1; i <= n; i++) {
                sum += a[i];
                if (prefix(tree, i) != sum) return 1;
            }
        }
    }
}
