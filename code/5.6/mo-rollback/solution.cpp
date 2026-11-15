#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers; q questions (l, r): the largest number of times one value occurs in a_l..a_r.
Input: n q, the n numbers, then q lines l r (1-based).
Output: one line per question, in the order of the input.
*/

// snippet:begin
// Mo's algorithm that only adds, with a rollback: the largest count of one value in a[l..r], for many (l, r).
vector<int> mostFrequent(const vector<int>& a, const vector<array<int, 2>>& queries) {
    int n = a.size(), B = max(1, (int)(n / sqrt((double)queries.size())));
    vector<int> order(queries.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int x, int y) {
        return make_pair(queries[x][0] / B, queries[x][1]) < make_pair(queries[y][0] / B, queries[y][1]);
    });
    vector<int> cnt(*max_element(a.begin(), a.end()) + 1, 0), answer(queries.size());
    int best = 0;  // the most frequent count in the window a[end + 1..r]
    auto add = [&](int i) { best = max(best, ++cnt[a[i]]); };
    int block = -1, end = -1, r = -1;
    for (int q : order) {
        auto [ql, qr] = queries[q];
        if (ql / B != block) {  // a new block of left ends: the window starts empty, right after the block
            block = ql / B, end = min(n - 1, (block + 1) * B - 1), r = end;
            fill(cnt.begin(), cnt.end(), 0), best = 0;
        }
        while (r < qr) add(++r);
        int saved = best;
        for (int i = ql; i <= min(qr, end); i++) add(i);  // the part of the query inside the block
        answer[q] = best;
        for (int i = ql; i <= min(qr, end); i++) cnt[a[i]]--;  // roll back
        best = saved;
    }
    return answer;
}
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    vector<array<int, 2>> queries(q);
    for (auto& x : queries) cin >> x[0] >> x[1], x[0]--, x[1]--;
    for (int x : mostFrequent(a, queries)) cout << x << "\n";
}
