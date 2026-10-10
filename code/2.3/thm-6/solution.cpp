#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.3.6. Inclusion-exclusion: sum over the sets S of properties of (-1)^|S| N(S). Here, the permutations of
// n elements with no fixed point: N(S) = (n - |S|)! when the elements of S are fixed, and C(n, j) sets of size j.
long long derangements(int n) {
    vector<long long> fact(n + 1, 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
    long long total = 0;
    for (int j = 0; j <= n; j++) {
        long long c = fact[n] / (fact[j] * fact[n - j]);  // the number of sets of size j
        total += (j % 2 == 0 ? 1 : -1) * c * fact[n - j];
    }
    return total;
}
// snippet:end

int main() {
    int divisible = 0;
    for (int x = 1; x <= 100; x++) divisible += x % 2 == 0 || x % 3 == 0 || x % 5 == 0;
    cout << "divisible by 2, 3 or 5 among 1..100: 50 + 33 + 20 - 16 - 10 - 6 + 3 = " << 50 + 33 + 20 - 16 - 10 - 6 + 3 << " (checked: " << divisible << "), by none: " << 100 - divisible << '\n';
    cout << "permutations of 4 with no fixed point: " << derangements(4) << '\n';
    for (int n = 1; n <= 7; n++) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        long long brute = 0;
        do {
            bool ok = true;
            for (int i = 0; i < n; i++) if (p[i] == i) ok = false;
            brute += ok;
        } while (next_permutation(p.begin(), p.end()));
        if (brute != derangements(n)) return 1;
    }
}
