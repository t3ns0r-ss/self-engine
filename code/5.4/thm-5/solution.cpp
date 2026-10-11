#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 5.4.5. Queries (p, k): the sum of a[p], a[p + k], a[p + 2k], ... up to the end (p is 0-based, k >= 1).
// Steps k < B are answered from a table; steps k >= B by walking, at most n / B jumps.
struct StepSums {
    int n, B;
    vector<long long> a;
    vector<vector<long long>> table;  // table[k][p] = a[p] + table[k][p + k]
    StepSums(const vector<long long>& v, int threshold) : n(v.size()), B(threshold), a(v), table(threshold) {
        for (int k = 1; k < B; k++) {
            table[k].assign(n + k, 0);  // the extra entries stay 0: positions past the end
            for (int p = n - 1; p >= 0; p--) table[k][p] = a[p] + table[k][p + k];
        }
    }
    long long query(int p, int k) const {
        if (k < B) return table[k][p];
        long long s = 0;
        for (; p < n; p += k) s += a[p];  // at most n / k <= n / B jumps
        return s;
    }
};
// snippet:end

int main() {
    vector<long long> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    StepSums s(v, 3);
    cout << "table[2] =";
    for (int p = 0; p < 10; p++) cout << ' ' << s.table[2][p];
    cout << "\n";
    cout << "(p=1,k=2) = " << s.query(1, 2) << ", (p=0,k=3) = " << s.query(0, 3) << ", (p=4,k=7) = " << s.query(4, 7) << ", (p=9,k=1) = " << s.query(9, 1) << "\n";
    // Check against: a loop, for every p and k, on random arrays and several thresholds.
    mt19937 rng(2);
    for (int n = 1; n <= 25; n++)
        for (int th : {1, 2, 3, 5, 8}) {
            vector<long long> w(n);
            for (auto& x : w) x = (long long)(rng() % 21) - 10;
            StepSums t(w, th);
            for (int p = 0; p < n; p++)
                for (int k = 1; k <= n + 2; k++) {
                    long long want = 0;
                    for (int i = p; i < n; i += k) want += w[i];
                    if (t.query(p, k) != want) return 1;
                }
        }
}
