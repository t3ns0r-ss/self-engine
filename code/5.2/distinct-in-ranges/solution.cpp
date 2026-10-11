#include <bits/stdc++.h>
using namespace std;

/*
Problem: n lamps with colours c_i; q questions (l, r): the number of different colours among lamps l..r.
Input: n q, the n colours (up to 10^9), then q lines l r (1-based).
Output: one answer per line, in the order of the questions.
*/

// snippet:begin
// Distinct values in a[l..r] for every query, 1-based, answered offline: sort the queries by right end and sweep.
vector<int> distinctInRanges(const vector<int>& a, const vector<pair<int, int>>& queries) {
    int n = a.size();
    vector<int> tree(n + 1, 0);  // a 1 at the last occurrence (so far) of every value
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
        for (; r < queries[q].second; r++) {  // move the right end to the end of this query
            if (last.count(a[r])) add(last[a[r]], -1);  // the old last occurrence stops counting
            last[a[r]] = r + 1;
            add(r + 1, 1);
        }
        answer[q] = prefix(queries[q].second) - prefix(queries[q].first - 1);
    }
    return answer;
}
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    vector<pair<int, int>> queries(q);
    for (auto& [l, r] : queries) cin >> l >> r;
    for (int x : distinctInRanges(a, queries)) cout << x << "\n";
}
