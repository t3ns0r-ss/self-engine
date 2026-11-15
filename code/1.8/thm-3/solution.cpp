#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 1.8.3. sum(i, j) is the reply to "? i j": a_i + a_j. Three replies give a_1, a_2, a_3; each other a_i
// needs one reply with a_1. In all n questions. The long long holds sums up to 2 * 10^9.
vector<long long> restore(int n, const function<long long(int, int)>& sum) {
    vector<long long> a(n + 1);
    long long s12 = sum(1, 2), s13 = sum(1, 3), s23 = sum(2, 3);
    a[1] = (s12 + s13 - s23) / 2;  // s12 + s13 - s23 = 2 * a_1, an even number
    a[2] = s12 - a[1];
    a[3] = s13 - a[1];
    for (int i = 4; i <= n; i++) a[i] = sum(1, i) - a[1];
    return a;
}
// snippet:end

int main() {
    vector<vector<long long>> shown = {{7, 2, 9, 4}, {-5, 5, 0}, {3, 3, 3, 3}};
    for (const auto& v : shown) {
        int n = (int)v.size();
        vector<long long> replies;
        auto sum = [&](int i, int j) {
            replies.push_back(v[i - 1] + v[j - 1]);
            return replies.back();
        };
        vector<long long> a = restore(n, sum);
        for (int i = 0; i < n; i++) cout << v[i] << (i + 1 == n ? ": replies" : " ");
        for (long long r : replies) cout << " " << r;
        cout << ", found";
        for (int i = 1; i <= n; i++) cout << " " << a[i];
        cout << "\n";
    }
    // The check: every array of 3 to 5 numbers in -2..2 is restored with exactly n questions.
    for (int n = 3; n <= 5; n++) {
        int total = 1;
        for (int i = 0; i < n; i++) total *= 5;
        for (int code = 0; code < total; code++) {
            vector<long long> v(n);
            int c = code;
            for (int i = 0; i < n; i++, c /= 5) v[i] = c % 5 - 2;
            int asked = 0;
            auto sum = [&](int i, int j) {
                asked++;
                return v[i - 1] + v[j - 1];
            };
            vector<long long> a = restore(n, sum);
            if (asked != n) return 1;
            for (int i = 1; i <= n; i++)
                if (a[i] != v[i - 1]) return 1;
        }
    }
    return 0;
}
