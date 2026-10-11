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
Problem: n numbers; q questions (l, r): print the sum, over every value v, of v multiplied by the square of the number of times v occurs in a_l..a_r.
Input: n q, the n numbers (up to 10^6), then q lines l r (1-based).
Output: one line per question, in the order of the input.
*/

// snippet:begin
// Mo's algorithm: the questions are answered in the order of Theorem 5.4.3 and the window [l, r] is moved by add and remove.
vector<long long> powerOfRanges(const vector<int>& a, const vector<array<int, 2>>& queries) {
    vector<int> cnt(*max_element(a.begin(), a.end()) + 1, 0);
    vector<long long> answer(queries.size());
    long long power = 0;  // the sum of v * cnt[v]^2 over the window
    auto add = [&](int i) { power += (long long)a[i] * (2 * cnt[a[i]]++ + 1); };      // c^2 -> (c+1)^2 adds 2c + 1 (times v)
    auto remove = [&](int i) { power -= (long long)a[i] * (2 * --cnt[a[i]] + 1); };  // (c+1)^2 -> c^2 takes away 2c + 1
    int l = 0, r = -1;
    for (int q : moOrder(queries, a.size())) {
        auto [ql, qr] = queries[q];
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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    vector<array<int, 2>> queries(q);
    for (auto& [l, r] : queries) cin >> l >> r, l--, r--;
    for (long long x : powerOfRanges(a, queries)) cout << x << "\n";
}
