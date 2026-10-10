#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 2.1.3. d(n) and sigma(n) from the exponents, and gcd and lcm as the minimum and maximum exponents.
map<long long, int> factorise(long long n) {
    map<long long, int> f;
    for (long long d = 2; d * d <= n; d++)
        while (n % d == 0) f[d]++, n /= d;
    if (n > 1) f[n]++;
    return f;
}
pair<long long, long long> countAndSum(const map<long long, int>& f) {
    long long cnt = 1, sum = 1;
    for (auto [p, e] : f) {
        long long term = 1, pw = 1;
        for (int k = 1; k <= e; k++) pw *= p, term += pw;  // 1 + p + ... + p^e
        cnt *= e + 1, sum *= term;
    }
    return {cnt, sum};
}
pair<long long, long long> gcdAndLcm(long long a, long long b) {
    auto fa = factorise(a), fb = factorise(b);
    map<long long, int> all = fa;
    for (auto [p, e] : fb) all[p] = 0;
    for (auto [p, e] : fa) all[p] = 0;
    long long g = 1, l = 1;
    for (auto [p, unused] : all) {
        int x = fa.count(p) ? fa[p] : 0, y = fb.count(p) ? fb[p] : 0;
        for (int k = 0; k < min(x, y); k++) g *= p;  // minimum exponent
        for (int k = 0; k < max(x, y); k++) l *= p;  // maximum exponent
    }
    return {g, l};
}
// snippet:end

int main() {
    auto [cnt, sum] = countAndSum(factorise(360));
    cout << "360: d = " << cnt << ", sigma = " << sum << '\n';
    auto [g, l] = gcdAndLcm(360, 84);
    cout << "gcd(360, 84) = " << g << ", lcm(360, 84) = " << l << '\n';
    for (long long n = 1; n <= 500; n++) {
        long long c = 0, s = 0;
        for (long long d = 1; d <= n; d++) if (n % d == 0) c++, s += d;
        auto [fc, fs] = countAndSum(factorise(n));
        if (c != fc || s != fs) return 1;
    }
    for (long long a = 1; a <= 60; a++)
        for (long long b = 1; b <= 60; b++) {
            auto [gg, ll] = gcdAndLcm(a, b);
            if (gg != __gcd(a, b) || ll != a / __gcd(a, b) * b) return 1;
        }
}
