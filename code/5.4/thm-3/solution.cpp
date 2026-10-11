#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.4.3. The order of the queries (l, r) for Mo's algorithm: by block of l, and r going up in even blocks and down in odd blocks.
vector<int> moOrder(const vector<array<int, 2>>& queries, int n) {
    int B = max(1, (int)(n / sqrt((double)max<size_t>(1, queries.size()))));  // about n / sqrt(q)
    vector<int> order(queries.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int x, int y) {
        int bx = queries[x][0] / B, by = queries[y][0] / B;
        if (bx != by) return bx < by;
        return bx % 2 == 0 ? queries[x][1] < queries[y][1] : queries[x][1] > queries[y][1];
    });
    return order;
}
// snippet:end

// For the check only: the number of steps the two ends take when the queries are visited in this order, starting from the empty window.
static long long moves(const vector<array<int, 2>>& queries, const vector<int>& order) {
    long long total = 0;
    int l = 0, r = -1;
    for (int q : order) {
        total += abs(queries[q][0] - l) + abs(queries[q][1] - r);
        l = queries[q][0], r = queries[q][1];
    }
    return total;
}

int main() {
    vector<array<int, 2>> queries = {{5, 9}, {0, 3}, {6, 7}, {1, 8}, {4, 4}, {0, 9}};
    vector<int> order = moOrder(queries, 10);
    cout << "order:";
    for (int q : order) cout << ' ' << q;
    cout << "\nmoves = " << moves(queries, order) << " (in the input order: " << moves(queries, {0, 1, 2, 3, 4, 5}) << ")\n";
    // Check: for random queries the movement is at most q * B + 2 * n * ceil(n / B) + 4 * n + 2 * B, for several n and q.
    mt19937 rng(21);
    for (int n : {10, 100, 1000, 20000})
        for (int q : {1, 10, 100, 1000, 20000}) {
            vector<array<int, 2>> qs(q);
            for (auto& x : qs) {
                x[0] = rng() % n, x[1] = rng() % n;
                if (x[0] > x[1]) swap(x[0], x[1]);
            }
            vector<int> o = moOrder(qs, n);
            int B = max(1, (int)(n / sqrt((double)q)));
            long long bound = (long long)q * B + 2LL * n * ((n + B - 1) / B) + 4LL * n + 2 * B;
            if (moves(qs, o) > bound) return 1;
            if (set<int>(o.begin(), o.end()).size() != (size_t)q) return 1;
        }
}
