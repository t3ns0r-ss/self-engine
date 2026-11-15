#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.6.5. Mo's algorithm that only adds elements: the largest value of x * (number of times x occurs)
// in a[l..r], for many (l, r); the values are 1..V-1.
vector<long long> heaviestValue(int V, const vector<int>& a, const vector<array<int, 2>>& queries) {
    int n = a.size(), B = max(1, (int)(n / sqrt((double)queries.size())));
    vector<int> order(queries.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int x, int y) {
        return make_pair(queries[x][0] / B, queries[x][1]) < make_pair(queries[y][0] / B, queries[y][1]);
    });
    vector<long long> answer(queries.size());
    vector<int> cnt(V, 0);
    long long best = 0;  // the answer for the window a[end + 1..r]; it is built by adds only
    auto add = [&](int i) { best = max(best, (long long)a[i] * ++cnt[a[i]]); };
    int block = -1, end = -1, r = -1;
    for (int q : order) {
        auto [ql, qr] = queries[q];
        if (ql / B != block) {  // a new block: start again with an empty window after the end of the block
            block = ql / B, end = min(n - 1, (block + 1) * B - 1), r = end;
            fill(cnt.begin(), cnt.end(), 0), best = 0;
        }
        while (r < qr) add(++r);
        long long saved = best;
        for (int i = ql; i <= min(qr, end); i++) add(i);  // the part of the query inside the block
        answer[q] = best;
        for (int i = ql; i <= min(qr, end); i++) cnt[a[i]]--;  // roll back
        best = saved;
    }
    return answer;
}
// snippet:end

int main() {
    vector<int> a = {2, 1, 2, 2, 1};
    vector<array<int, 2>> queries = {{0, 4}, {1, 3}, {3, 4}, {0, 0}};
    cout << "heaviest:";
    for (long long x : heaviestValue(3, a, queries)) cout << ' ' << x;
    cout << "\n";
    // Check against: counting each range, for every array of length 6 over {1, 2, 3} and every range as one query.
    for (int code = 0; code < 729; code++) {
        vector<int> w(6);
        for (int i = 0, c = code; i < 6; i++, c /= 3) w[i] = c % 3 + 1;
        vector<array<int, 2>> qs;
        for (int l = 0; l < 6; l++)
            for (int r = l; r < 6; r++) qs.push_back({l, r});
        vector<long long> got = heaviestValue(4, w, qs);
        for (size_t i = 0; i < qs.size(); i++) {
            map<int, int> c;
            long long want = 0;
            for (int j = qs[i][0]; j <= qs[i][1]; j++) want = max(want, (long long)w[j] * ++c[w[j]]);
            if (want != got[i]) return 1;
        }
    }
    mt19937 rng(17);  // longer arrays with random queries
    for (int round = 0; round < 3000; round++) {
        int n = rng() % 30 + 1, q = rng() % 20 + 1;
        vector<int> w(n);
        for (int& x : w) x = rng() % 4 + 1;
        vector<array<int, 2>> qs(q);
        for (auto& x : qs) {
            x[0] = rng() % n, x[1] = rng() % n;
            if (x[0] > x[1]) swap(x[0], x[1]);
        }
        vector<long long> got = heaviestValue(5, w, qs);
        for (int i = 0; i < q; i++) {
            map<int, int> c;
            long long want = 0;
            for (int j = qs[i][0]; j <= qs[i][1]; j++) want = max(want, (long long)w[j] * ++c[w[j]]);
            if (want != got[i]) return 2;
        }
    }
}
