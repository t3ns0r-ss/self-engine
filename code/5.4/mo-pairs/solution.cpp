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
Problem: n numbers; q questions (l, r): the number of pairs i < j in l..r with a_i == a_j.
Input: n q, the n numbers, then q lines l r (1-based).
Output: one line per question, in the order of the input.
*/

// snippet:begin
// Mo's algorithm for the number of equal pairs: a value that occurs c times in the window makes c(c-1)/2 pairs.
vector<long long> equalPairs(const vector<int>& a, const vector<array<int, 2>>& queries) {
    vector<int> cnt(*max_element(a.begin(), a.end()) + 1, 0);
    vector<long long> answer(queries.size());
    long long pairs = 0;
    auto add = [&](int i) { pairs += cnt[a[i]]++; };     // the new element pairs with every copy already in the window
    auto remove = [&](int i) { pairs -= --cnt[a[i]]; };  // and loses the pairs with the copies that stay
    int l = 0, r = -1;
    for (int q : moOrder(queries, a.size())) {
        auto [ql, qr] = queries[q];
        while (l > ql) add(--l);
        while (r < qr) add(++r);
        while (l < ql) remove(l++);
        while (r > qr) remove(r--);
        answer[q] = pairs;
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
    for (long long x : equalPairs(a, queries)) cout << x << "\n";
}
