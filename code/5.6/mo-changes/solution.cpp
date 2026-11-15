#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers; U changes "set a_p to x" in time order; q questions (l, r, t): the sum over the values v of v * (number of times v occurs in a_l..a_r)^2,
for the array after the first t changes.
Input: n U q, the n numbers, U lines p x, then q lines l r t (1-based positions, 0 <= t <= U).
Output: one line per question, in the order of the input.
*/

// snippet:begin
// Mo's algorithm with changes: the questions are sorted by (block of l, block of r, t) with blocks of about n^(2/3) positions.
vector<long long> powerWithChanges(vector<int> a, vector<array<int, 2>> changes, const vector<array<int, 3>>& queries) {
    int top = *max_element(a.begin(), a.end());
    for (auto& c : changes) top = max(top, c[1]);
    int B = max(1, (int)cbrt((double)a.size() * a.size()));
    vector<int> order(queries.size());
    iota(order.begin(), order.end(), 0);
    auto key = [&](int i) { return array<int, 3>{queries[i][0] / B, queries[i][1] / B, queries[i][2]}; };
    sort(order.begin(), order.end(), [&](int x, int y) { return key(x) < key(y); });
    vector<int> cnt(top + 1, 0);
    vector<long long> answer(queries.size());
    long long power = 0;  // the sum of v * count^2 over the window
    auto add = [&](int i) { power += (long long)a[i] * (2 * cnt[a[i]]++ + 1); };
    auto remove = [&](int i) { power -= (long long)a[i] * (2 * --cnt[a[i]] + 1); };
    int l = 0, r = -1, t = 0;
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
        answer[q] = power;
    }
    return answer;
}
// snippet:end

int main() {
    int n, U, q;
    cin >> n >> U >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    vector<array<int, 2>> changes(U);
    for (auto& c : changes) cin >> c[0] >> c[1], c[0]--;
    vector<array<int, 3>> queries(q);
    for (auto& x : queries) cin >> x[0] >> x[1] >> x[2], x[0]--, x[1]--;
    for (long long x : powerWithChanges(a, changes, queries)) cout << x << "\n";
}
