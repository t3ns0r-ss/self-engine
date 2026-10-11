#include <bits/stdc++.h>
using namespace std;

/*
Problem: n numbers; q questions (p, k): the sum of a_p, a_{p+k}, a_{p+2k}, ... up to the end of the array (p is 1-based, k >= 1).
Input: n q, the n numbers, then q lines p k.
Output: one line per question, in the order of the input.
*/

// snippet:begin
// Steps below the threshold B are answered from a table filled from the right; steps from B on by walking (at most n / B jumps).
struct StepSums {
    int n, B;
    vector<long long> a;
    vector<vector<long long>> table;  // table[k][p] = a[p] + table[k][p + k]
    StepSums(const vector<long long>& v, int threshold) : n(v.size()), B(threshold), a(v), table(threshold) {
        for (int k = 1; k < B; k++) {
            table[k].assign(n + k, 0);  // the entries past the end stay 0
            for (int p = n - 1; p >= 0; p--) table[k][p] = a[p] + table[k][p + k];
        }
    }
    long long query(int p, int k) const {
        if (k < B) return table[k][p];
        long long s = 0;
        for (; p < n; p += k) s += a[p];
        return s;
    }
};
// snippet:end

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    StepSums steps(a, max(1, (int)sqrt((double)n)));
    while (q--) {
        int p, k;
        cin >> p >> k;
        cout << steps.query(p - 1, k) << "\n";
    }
}
