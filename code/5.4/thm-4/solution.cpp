#include <bits/stdc++.h>
using namespace std;

vector<int> moOrder(const vector<array<int, 2>>& queries, int n) {
    int B = max(1, (int)(n / sqrt((double)max<size_t>(1, queries.size()))));
    vector<int> order(queries.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int x, int y) {
        int bx = queries[x][0] / B, by = queries[y][0] / B;
        if (bx != by) return bx < by;
        return bx % 2 == 0 ? queries[x][1] < queries[y][1] : queries[x][1] > queries[y][1];
    });
    return order;
}

// snippet:begin
// Theorem 5.4.4. Mo's algorithm for the number of different values in a[l..r] (0-based). The window [l, r] starts empty (r = l - 1).
vector<int> distinctByMo(const vector<int>& a, const vector<array<int, 2>>& queries) {
    vector<int> cnt(*max_element(a.begin(), a.end()) + 1, 0), answer(queries.size());
    int l = 0, r = -1, distinct = 0;  // the window holds a[l..r]; distinct is the answer for it
    auto add = [&](int i) { distinct += cnt[a[i]]++ == 0; };
    auto remove = [&](int i) { distinct -= --cnt[a[i]] == 0; };
    for (int q : moOrder(queries, a.size())) {
        auto [ql, qr] = queries[q];
        while (l > ql) add(--l);  // grow first, so that the window never has a negative length
        while (r < qr) add(++r);
        while (l < ql) remove(l++);
        while (r > qr) remove(r--);
        answer[q] = distinct;
    }
    return answer;
}
// snippet:end

int main() {
    vector<int> a = {1, 2, 1, 3, 2, 2, 4, 1};
    vector<array<int, 2>> queries = {{0, 3}, {1, 4}, {2, 2}, {0, 7}, {5, 6}, {3, 7}};
    cout << "distinct:";
    for (int x : distinctByMo(a, queries)) cout << ' ' << x;
    cout << "\n";
    // Check against: a set of the range, on random arrays and queries.
    mt19937 rng(8);
    for (int round = 0; round < 3000; round++) {
        int n = rng() % 12 + 1, q = rng() % 12 + 1;
        vector<int> w(n);
        for (int& x : w) x = rng() % 5;
        vector<array<int, 2>> qs(q);
        for (auto& x : qs) {
            x[0] = rng() % n, x[1] = rng() % n;
            if (x[0] > x[1]) swap(x[0], x[1]);
        }
        vector<int> got = distinctByMo(w, qs);
        for (int i = 0; i < q; i++)
            if ((int)set<int>(w.begin() + qs[i][0], w.begin() + qs[i][1] + 1).size() != got[i]) return 1;
    }
}
