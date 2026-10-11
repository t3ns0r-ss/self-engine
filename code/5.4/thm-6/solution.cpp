#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.4.6. For every question (l, r) (0-based) count the values x that occur exactly x times in a[l..r].
// Only values x that occur at least x times in the whole array can qualify; there are at most sqrt(2n) of them.
vector<int> exactlyXTimes(const vector<int>& a, const vector<array<int, 2>>& queries) {
    int n = a.size();
    vector<int> total(n + 1, 0), answer(queries.size(), 0), prefix(n + 1, 0);
    for (int x : a)
        if (x <= n) total[x]++;
    for (int x = 1; x <= n; x++) {
        if (total[x] < x) continue;  // this value cannot reach x occurrences anywhere
        for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + (a[i] == x);  // one pass for this value
        for (size_t j = 0; j < queries.size(); j++) answer[j] += prefix[queries[j][1] + 1] - prefix[queries[j][0]] == x;
    }
    return answer;
}
// snippet:end

int main() {
    vector<int> a = {3, 1, 2, 2, 3, 3, 1, 3};
    vector<array<int, 2>> queries = {{0, 7}, {0, 4}, {2, 5}, {6, 7}};
    cout << "answers:";
    for (int x : exactlyXTimes(a, queries)) cout << ' ' << x;
    cout << "\n";
    vector<int> w;  // the array 1, 2, 2, 3, 3, 3, ..., 100 repeated x times: every value x qualifies, and n = 5050
    for (int x = 1; x <= 100; x++)
        for (int j = 0; j < x; j++) w.push_back(x);
    cout << "array of length " << w.size() << " with the values 1.." << 100 << ": answer " << exactlyXTimes(w, {{0, (int)w.size() - 1}})[0] << ", bound sqrt(2n) = " << (int)sqrt(2.0 * w.size()) << "\n";
    // Check against: counting inside the range, on random arrays and queries.
    mt19937 rng(6);
    for (int round = 0; round < 3000; round++) {
        int n = rng() % 14 + 1, q = rng() % 10 + 1;
        vector<int> v(n);
        for (int& x : v) x = rng() % 5 + 1;
        vector<array<int, 2>> qs(q);
        for (auto& x : qs) {
            x[0] = rng() % n, x[1] = rng() % n;
            if (x[0] > x[1]) swap(x[0], x[1]);
        }
        vector<int> got = exactlyXTimes(v, qs);
        for (int i = 0; i < q; i++) {
            map<int, int> cnt;
            for (int j = qs[i][0]; j <= qs[i][1]; j++) cnt[v[j]]++;
            int want = 0;
            for (auto [x, c] : cnt) want += x == c;
            if (want != got[i]) return 1;
        }
    }
}
