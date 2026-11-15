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

/*
Problem (Codeforces 1514D, Cut and Stick): n numbers (1 <= a_i <= n) and q questions (l, r): the fewest pieces into which a_l..a_r can be
cut as a sequence of subsequences, so that in every piece no value occurs more than ceil(len / 2) times. The answer is max(1, 2f - len),
where f is the highest number of occurrences of one value in the range and len = r - l + 1.
Input: n q, the n numbers, then q lines l r (1-based).
Output: one line per question, in the order of the input.
*/

// snippet:begin
// Mo's algorithm for f, the highest number of occurrences in the window: cnt[v] is the count of v, ofCount[c] is how many values have
// count c, and f only drops by one when the last value with the top count loses one occurrence.
vector<int> cutAndStick(const vector<int>& a, const vector<array<int, 2>>& queries) {
    int n = a.size(), f = 0;
    vector<int> cnt(n + 1, 0), ofCount(n + 2, 0), answer(queries.size());
    auto add = [&](int i) {
        ofCount[cnt[a[i]]]--, ofCount[++cnt[a[i]]]++;
        f = max(f, cnt[a[i]]);
    };
    auto remove = [&](int i) {
        if (cnt[a[i]] == f && ofCount[f] == 1) f--;  // the only value with the top count is about to lose one
        ofCount[cnt[a[i]]]--, ofCount[--cnt[a[i]]]++;
    };
    int l = 0, r = -1;
    for (int q : moOrder(queries, n)) {
        auto [ql, qr] = queries[q];
        while (l > ql) add(--l);
        while (r < qr) add(++r);
        while (l < ql) remove(l++);
        while (r > qr) remove(r--);
        answer[q] = max(1, 2 * f - (qr - ql + 1));
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
    for (auto& [l, r] : queries) cin >> l >> r, l--, r--;
    for (int x : cutAndStick(a, queries)) cout << x << "\n";
}
