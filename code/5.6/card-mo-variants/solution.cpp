#include <bits/stdc++.h>
using namespace std;

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

int main() {
    // P1: a = 1 2 1 3 2 and the change a[1] = 3; the number of different values in positions 0..3 after the change.
    {
        vector<int> a = {1, 2, 1, 3, 2};
        auto got = distinctWithChanges(4, a, {{1, 3}}, {{0, 3, 1}});
        vector<int> after = {1, 3, 1, 3};
        cout << "P1 brute=" << set<int>(after.begin(), after.end()).size() << " method=" << got[0] << "\n";
    }
    // P2: a = 2 1 2 2 1; the largest value of x * (number of times x occurs) in positions 1..3.
    {
        vector<int> a = {2, 1, 2, 2, 1};
        auto got = heaviestValue(3, a, {{1, 3}});
        map<int, int> c;
        long long brute = 0;
        for (int i = 1; i <= 3; i++) brute = max(brute, (long long)a[i] * ++c[a[i]]);
        cout << "P2 brute=" << brute << " method=" << got[0] << "\n";
    }
    // N1: a = 1 1 2 3. The first question is (0, 3) with the answer 3. The second is written (1, 2) and means
    // ((1 + 3) mod 4, (2 + 3) mod 4) = (0, 1). Sorting the written pairs as if they were the real ranges answers (1, 2).
    {
        vector<int> a = {1, 1, 2, 3};
        int last = set<int>(a.begin(), a.end()).size();
        int l = (1 + last) % 4, r = (2 + last) % 4;
        cout << "N1 brute=" << set<int>(a.begin() + l, a.begin() + r + 1).size() << " method=" << set<int>(a.begin() + 1, a.begin() + 3).size() << "\n";
    }
}
