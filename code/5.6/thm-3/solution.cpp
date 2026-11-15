#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.6.3. Mo's algorithm with changes: the query (l, r, t) asks for the number of different values
// in a[l..r] after the first t changes (a change is {position, new value}); the values are 0..V-1.
vector<int> distinctWithChanges(int V, vector<int> a, vector<array<int, 2>> changes, const vector<array<int, 3>>& queries) {
    int B = max(1, (int)cbrt((double)a.size() * a.size()));  // about n^(2/3)
    vector<int> order(queries.size());
    iota(order.begin(), order.end(), 0);
    auto key = [&](int i) { return array<int, 3>{queries[i][0] / B, queries[i][1] / B, queries[i][2]}; };
    sort(order.begin(), order.end(), [&](int x, int y) { return key(x) < key(y); });
    vector<int> cnt(V, 0), answer(queries.size());
    int l = 0, r = -1, t = 0, distinct = 0;  // the window a[l..r] after t changes
    auto add = [&](int i) { distinct += cnt[a[i]]++ == 0; };
    auto remove = [&](int i) { distinct -= --cnt[a[i]] == 0; };
    auto apply = [&](int k) {  // a second application undoes the change: the values are swapped
        auto& [pos, value] = changes[k];
        if (l <= pos && pos <= r) remove(pos), swap(a[pos], value), add(pos);
        else swap(a[pos], value);
    };
    for (int q : order) {
        auto [ql, qr, qt] = queries[q];
        while (t < qt) apply(t++);
        while (t > qt) apply(--t);
        while (l > ql) add(--l);
        while (r < qr) add(++r);
        while (l < ql) remove(l++);
        while (r > qr) remove(r--);
        answer[q] = distinct;
    }
    return answer;
}
// snippet:end

int main() {
    // a = 1 2 1 3 2, the changes a[1] = 3 and a[3] = 1, and five queries (l, r, t) given in this order.
    vector<int> a = {1, 2, 1, 3, 2};
    vector<array<int, 2>> changes = {{1, 3}, {3, 1}};
    vector<array<int, 3>> queries = {{2, 4, 1}, {0, 3, 2}, {0, 3, 0}, {1, 4, 2}, {0, 3, 1}};
    cout << "different values:";
    for (int x : distinctWithChanges(4, a, changes, queries)) cout << ' ' << x;
    cout << "\n";
    // Check against: recomputing the range after applying the first t changes, on random inputs;
    // and check that the moves of l, r and t stay below the bound of the theorem.
    mt19937 rng(11);
    for (int round = 0; round < 3000; round++) {
        int n = rng() % 12 + 1, U = rng() % 6, q = rng() % 12 + 1, V = 4;
        vector<int> w(n);
        for (int& x : w) x = rng() % V;
        vector<array<int, 2>> ch(U);
        for (auto& c : ch) c = {(int)(rng() % n), (int)(rng() % V)};
        vector<array<int, 3>> qs(q);
        for (auto& x : qs) {
            x[0] = rng() % n, x[1] = rng() % n, x[2] = rng() % (U + 1);
            if (x[0] > x[1]) swap(x[0], x[1]);
        }
        vector<int> got = distinctWithChanges(V, w, ch, qs);
        for (int i = 0; i < q; i++) {
            vector<int> b = w;
            for (int k = 0; k < qs[i][2]; k++) b[ch[k][0]] = ch[k][1];
            if ((int)set<int>(b.begin() + qs[i][0], b.begin() + qs[i][1] + 1).size() != got[i]) return 1;
        }
        // The same order as in the function, to count the moves of the three pointers.
        int B = max(1, (int)cbrt((double)n * n));
        vector<int> order(q);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int x, int y) {
            return array<int, 3>{qs[x][0] / B, qs[x][1] / B, qs[x][2]} < array<int, 3>{qs[y][0] / B, qs[y][1] / B, qs[y][2]};
        });
        long long moves = 0;
        array<int, 3> at = {0, -1, 0};
        for (int i : order) {
            for (int k = 0; k < 3; k++) moves += abs(at[k] - qs[i][k]);
            at = qs[i];
        }
        long long groups = (n + B - 1) / B;
        if (moves > 2LL * (q + 1) * B + 2 * (groups + 1) * (n + B) + 2LL * U * groups * groups) return 2;
    }
}
