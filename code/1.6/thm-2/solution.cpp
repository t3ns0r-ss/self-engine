#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
pair<ll, ll> formula(const vector<int>& a, bool show) {  // Theorem 1.6.2 from L (previous <), R (next <=), R2 (next <)
    int n = a.size(); ll sum = 0, best = 0;
    for (int i = 0; i < n; i++) {
        int L = -1, R = n, R2 = n;
        for (int j = i - 1; j >= 0 && L < 0; j--) if (a[j] < a[i]) L = j;
        for (int j = n - 1; j > i; j--) { if (a[j] <= a[i]) R = j; if (a[j] < a[i]) R2 = j; }
        ll cnt = (ll)(i - L) * (R - i); sum += a[i] * cnt, best = max(best, (ll)a[i] * (R2 - L - 1));
        if (show) cout << "i=" << i << " a=" << a[i] << " L=" << L << " R=" << R << " subarrays=" << cnt << " contribution=" << a[i] * cnt << '\n';
    }
    return {sum, best};
}
pair<ll, ll> brute(const vector<int>& a) {
    ll sum = 0, best = 0;
    for (int l = 0; l < (int)a.size(); l++)
        for (int r = l, m = INT_MAX; r < (int)a.size(); r++) sum += m = min(m, a[r]), best = max(best, (ll)m * (r - l + 1));
    return {sum, best};
}
int main() {
    vector<int> a = {3, 1, 2}, b(5); int bad = 0;
    auto f = formula(a, true), g = brute(a);
    cout << "sum of minima: formula " << f.first << ", brute force " << g.first << '\n' << "largest rectangle: formula " << f.second << ", brute force " << g.second << '\n';
    for (int code = 0; code < 243; code++) {  // every array of length 5 over {1, 2, 3}, ties included
        for (int i = 0, c = code; i < 5; i++, c /= 3) b[i] = c % 3 + 1;
        bad += formula(b, false) != brute(b);
    }
    cout << "all 243 arrays of length 5 over {1,2,3}: formula equals brute force: " << (bad ? "no" : "yes") << '\n';
}
