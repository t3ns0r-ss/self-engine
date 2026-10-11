#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.2.5. The number of distinct values in a[l..r] for every query (l, r), 1-based, answered offline.
vector<int> distinctInRanges(const vector<int>& a, const vector<pair<int, int>>& queries) {
    int n = a.size();
    vector<int> tree(n + 1, 0);  // 1 at the last occurrence (so far) of every value
    auto add = [&](int i, int d) {
        for (; i <= n; i += i & -i) tree[i] += d;
    };
    auto prefix = [&](int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    };
    vector<int> order(queries.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int x, int y) { return queries[x].second < queries[y].second; });
    map<int, int> last;  // value -> its last position so far
    vector<int> answer(queries.size());
    int r = 0;
    for (int q : order) {
        for (; r < queries[q].second; r++) {  // move the right end to the query's right end
            int pos = r + 1;
            if (last.count(a[r])) add(last[a[r]], -1);  // the old last occurrence stops counting
            last[a[r]] = pos;
            add(pos, 1);
        }
        answer[q] = prefix(queries[q].second) - prefix(queries[q].first - 1);
    }
    return answer;
}
// snippet:end

int main() {
    {
        vector<int> a = {1, 2, 1, 3, 2};
        vector<pair<int, int>> qs = {{1, 3}, {2, 5}, {3, 3}, {1, 5}};
        auto ans = distinctInRanges(a, qs);
        cout << "a = 1 2 1 3 2:";
        for (size_t i = 0; i < qs.size(); i++) cout << " [" << qs[i].first << "," << qs[i].second << "] -> " << ans[i] << ";";
        cout << "\n";
    }
    {
        vector<int> a = {7, 7, 7, 7};
        auto ans = distinctInRanges(a, {{1, 4}, {2, 3}});
        cout << "a = 7 7 7 7: [1,4] -> " << ans[0] << "; [2,3] -> " << ans[1] << ";\n";
    }
    // Check against: putting the range into a set, on random arrays and random queries.
    mt19937 rng(5205);
    for (int trial = 0; trial < 20000; trial++) {
        int n = rng() % 10 + 1, q = rng() % 8 + 1;
        vector<int> a(n);
        for (int& x : a) x = rng() % 4;
        vector<pair<int, int>> qs;
        for (int i = 0; i < q; i++) {
            int l = rng() % n + 1, r = l + rng() % (n - l + 1);
            qs.push_back({l, r});
        }
        auto ans = distinctInRanges(a, qs);
        for (int i = 0; i < q; i++) {
            set<int> s(a.begin() + qs[i].first - 1, a.begin() + qs[i].second);
            if ((int)s.size() != ans[i]) return 1;
        }
    }
}
