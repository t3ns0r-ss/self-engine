#include <bits/stdc++.h>
using namespace std;

// method: the recurrence of the card, dp[i] = w[i] + max(0, max dp[j] over earlier j with a[j] < a[i] and i - j >= gap).
long long method(const vector<int>& a, const vector<long long>& w, int gap) {
    int n = a.size();
    vector<long long> dp(n);
    long long best = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        dp[i] = w[i];
        for (int j = 0; j + gap <= i; j++)
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + w[i]);
        best = max(best, dp[i]);
    }
    return best;
}
// brute: every subsequence; consecutive chosen elements must satisfy ok(a[j], a[i]) and be at least gap apart.
template <class Ok>
long long brute(const vector<int>& a, const vector<long long>& w, int gap, Ok ok) {
    int n = a.size();
    long long best = LLONG_MIN;
    for (int mask = 1; mask < (1 << n); mask++) {
        int last = -1;
        long long sum = 0;
        bool good = true;
        for (int i = 0; i < n; i++) {
            if (!(mask >> i & 1)) continue;
            if (last >= 0 && (i - last < gap || !ok(a[last], a[i]))) good = false;
            last = i, sum += w[i];
        }
        if (good) best = max(best, sum);
    }
    return best;
}
int main() {
    auto strictlyIncreasing = [](int x, int y) { return x < y; };
    auto close = [](int x, int y) { return abs(x - y) <= 1; };
    vector<int> a1 = {3, 1, 4, 1, 5}, a2 = {1, 2, 3, 4}, a3 = {3, 2, 1};
    vector<long long> w1 = {2, 3, 1, 4, 5}, w2 = {1, 1, 1, 1}, w3 = {1, 1, 1};
    cout << "P1 brute=" << brute(a1, w1, 1, strictlyIncreasing) << " method=" << method(a1, w1, 1) << "\n";
    cout << "P2 brute=" << brute(a2, w2, 2, strictlyIncreasing) << " method=" << method(a2, w2, 2) << "\n";
    cout << "N1 brute=" << brute(a3, w3, 1, close) << " method=" << method(a3, w3, 1) << "\n";
}
