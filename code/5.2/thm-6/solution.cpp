#include <bits/stdc++.h>
using namespace std;

vector<int> buildCounts(const vector<int>& count) {  // count[1..n]; the Fenwick tree of the counts
    int n = count.size() - 1;
    vector<int> tree(n + 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += j & -j) tree[j] += count[i];
    return tree;
}

// snippet:begin
// Theorem 5.2.6. The smallest position p whose prefix count is at least k (1 <= k <= total), by one walk down the tree.
int kthPosition(const vector<int>& tree, int k) {
    int n = tree.size() - 1, pos = 0, step = 1;
    while (step * 2 <= n) step *= 2;  // the largest power of two that is at most n
    for (; step > 0; step /= 2)
        if (pos + step <= n && tree[pos + step] < k) {  // the block (pos, pos + step] has fewer than k
            pos += step;
            k -= tree[pos];  // skip its elements
        }
    return pos + 1;
}
// snippet:end

int main() {
    {
        vector<int> count = {0, 0, 1, 1, 0, 1, 0, 0, 1};  // present: 2, 3, 5, 8
        auto tree = buildCounts(count);
        cout << "present 2 3 5 8 of 8:";
        for (int k = 1; k <= 4; k++) cout << " k=" << k << " -> " << kthPosition(tree, k) << ";";
        cout << "\n";
    }
    {
        auto tree = buildCounts({0, 1});
        cout << "present 1 of 1: k=1 -> " << kthPosition(tree, 1) << ";\n";
    }
    {
        auto tree = buildCounts({0, 2, 0, 3});  // value 1 twice, value 3 three times
        cout << "counts 2 0 3: k=2 -> " << kthPosition(tree, 2) << "; k=3 -> " << kthPosition(tree, 3) << ";\n";
    }
    // Check against: scanning the counts, for every array of counts over {0, 1, 2} of length 1..7.
    for (int n = 1; n <= 7; n++) {
        int total = 1;
        for (int i = 0; i < n; i++) total *= 3;
        for (int code = 0; code < total; code++) {
            vector<int> count(n + 1, 0);
            int sum = 0;
            for (int i = 1, c = code; i <= n; i++, c /= 3) sum += count[i] = c % 3;
            auto tree = buildCounts(count);
            for (int k = 1; k <= sum; k++) {
                int want = 0, run = 0;
                for (int i = 1; i <= n && !want; i++) {
                    run += count[i];
                    if (run >= k) want = i;
                }
                if (kthPosition(tree, k) != want) return 1;
            }
        }
    }
}
