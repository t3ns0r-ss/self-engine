#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.5.3. The complement: the compositions of n from the given parts, all of them minus those that use only parts below d.
long long compositions(int n, const vector<int>& parts) {
    vector<long long> f(n + 1, 0);
    f[0] = 1;
    for (int m = 1; m <= n; m++)
        for (int p : parts) if (p <= m) f[m] += f[m - p];
    return f[n];
}
long long atLeastOneBig(int n, int d, const vector<int>& parts) {
    vector<int> small;
    for (int p : parts) if (p < d) small.push_back(p);
    return compositions(n, parts) - compositions(n, small);
}
// snippet:end

int main() {
    cout << "compositions of m = 0..4 with parts 1 2 3:";
    for (int m = 0; m <= 4; m++) cout << ' ' << compositions(m, {1, 2, 3});
    cout << '\n';
    cout << "compositions of 4 with a part >= 2: " << atLeastOneBig(4, 2, {1, 2, 3}) << '\n';
    for (int n = 0; n <= 10; n++) {
        long long brute = 0;
        function<void(int, bool)> go = [&](int left, bool big) {
            if (left == 0) { brute += big; return; }
            for (int p : {1, 2, 3}) if (p <= left) go(left - p, big || p >= 2);
        };
        go(n, false);
        if (n >= 1 && brute != atLeastOneBig(n, 2, {1, 2, 3})) return 1;
    }
}
