#include <bits/stdc++.h>
using namespace std;

// Brute force: write every line through two points as a x + b y = c in lowest terms, collect the different lines, count their points.
int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    if (k == 1) {
        cout << "Infinity\n";
        return 0;
    }
    set<array<long long, 3>> lines;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            long long a = y[j] - y[i], b = x[i] - x[j];
            long long g = __gcd(llabs(a), llabs(b));
            a /= g, b /= g;
            if (a < 0 || (a == 0 && b < 0)) a = -a, b = -b;
            lines.insert({a, b, a * x[i] + b * y[i]});
        }
    long long ans = 0;
    for (auto& l : lines) {
        int cnt = 0;
        for (int i = 0; i < n; i++) cnt += l[0] * x[i] + l[1] * y[i] == l[2];
        if (cnt >= k) ans++;
    }
    cout << ans << "\n";
}
