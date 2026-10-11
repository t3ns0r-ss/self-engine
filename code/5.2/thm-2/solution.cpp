#include <bits/stdc++.h>
using namespace std;

vector<long long> buildTree(const vector<long long>& a) {  // by the definition of Theorem 5.2.1
    int n = a.size() - 1;
    vector<long long> tree(n + 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = i - (i & -i) + 1; j <= i; j++) tree[i] += a[j];
    return tree;
}

// snippet:begin
// Theorem 5.2.2. Adding d to a[i] changes exactly tree[i], tree[i + lowbit(i)], tree[...], ... while the index is at most n.
void add(vector<long long>& tree, int i, long long d) {
    int n = tree.size() - 1;
    for (; i <= n; i += i & -i) tree[i] += d;  // each step moves to the next block that contains position i
}
// snippet:end

static void show(vector<long long> values, int pos, long long d) {
    vector<long long> a = {0};
    a.insert(a.end(), values.begin(), values.end());
    auto tree = buildTree(a);
    add(tree, pos, d);
    cout << "n = " << values.size() << ", add " << d << " at " << pos << " touches";
    int n = values.size();
    for (int i = pos; i <= n; i += i & -i) cout << ' ' << i;
    cout << "; tree =";
    for (int i = 1; i <= n; i++) cout << ' ' << tree[i];
    cout << "\n";
}

int main() {
    show({3, 1, 4, 1, 5, 9, 2, 6}, 3, 10);
    show({3, 1, 4, 1, 5, 9, 2, 6}, 8, 1);
    show({1, 1, 1, 1, 1, 1}, 5, 2);
    // Check against: rebuilding the tree by its definition after the change, and against the set of blocks that contain
    // position i, for every n up to 20, every position and a few random arrays.
    mt19937 rng(5202);
    for (int n = 1; n <= 20; n++)
        for (int trial = 0; trial < 20; trial++) {
            vector<long long> a(n + 1, 0);
            for (int i = 1; i <= n; i++) a[i] = rng() % 10;
            auto tree = buildTree(a);
            for (int i = 1; i <= n; i++) {
                auto changed = tree;
                add(changed, i, 7);
                a[i] += 7;
                if (changed != buildTree(a)) return 1;
                a[i] -= 7;
                for (int j = 1; j <= n; j++) {
                    bool contains = j - (j & -j) < i && i <= j;  // block of tree[j] = (j - lowbit(j), j]
                    if (contains != (changed[j] != tree[j])) return 1;
                }
            }
        }
}
