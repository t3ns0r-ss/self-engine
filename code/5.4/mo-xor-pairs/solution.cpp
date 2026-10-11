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
Problem: n numbers and a number k; q questions (l, r): the number of pairs (i, j), l <= i <= j <= r, such that a_i xor ... xor a_j = k.
Input: n q k, the n numbers (below 2^20), then q lines l r (1-based).
Output: one line per question, in the order of the input.
*/

// snippet:begin
// With prefix XORs p[0..n], the XOR of a_i..a_j is p[i-1] ^ p[j]. A question (l, r) counts the pairs x < y in the window of prefix
// indices l-1..r with p[x] ^ p[y] == k; Mo's algorithm moves that window and a count array of the prefix values.
vector<long long> xorPairs(const vector<int>& a, int k, const vector<array<int, 2>>& queries) {
    int n = a.size();
    vector<int> p(n + 1, 0), cnt(1 << 20, 0);
    for (int i = 0; i < n; i++) p[i + 1] = p[i] ^ a[i];
    vector<array<int, 2>> win(queries.size());  // 1-based (l, r) becomes the window l-1..r over prefix indices
    for (size_t i = 0; i < queries.size(); i++) win[i] = {queries[i][0] - 1, queries[i][1]};
    vector<long long> answer(queries.size());
    long long pairs = 0;
    auto add = [&](int i) { pairs += cnt[p[i] ^ k], cnt[p[i]]++; };     // new pairs with every earlier index in the window
    auto remove = [&](int i) { cnt[p[i]]--, pairs -= cnt[p[i] ^ k]; };  // the pairs it had with the others
    int l = 0, r = -1;
    for (int q : moOrder(win, n + 1)) {
        while (l > win[q][0]) add(--l);
        while (r < win[q][1]) add(++r);
        while (l < win[q][0]) remove(l++);
        while (r > win[q][1]) remove(r--);
        answer[q] = pairs;
    }
    return answer;
}
// snippet:end

int main() {
    int n, q, k;
    cin >> n >> q >> k;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    vector<array<int, 2>> queries(q);
    for (auto& [l, r] : queries) cin >> l >> r;
    for (long long x : xorPairs(a, k, queries)) cout << x << "\n";
}
