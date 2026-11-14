#include <bits/stdc++.h>
using namespace std;


// snippet:begin
// Theorem 7.3.5. dp[i] = min over j < i of dp[j] + b[j] * a[i], with b falling and a rising (dp[0] = 0). Each j is the line
// y = b[j] x + dp[j]; a deque keeps the lines that can still be lowest, with the falling slopes in order.
struct Line { long long m, c; };
long long at(const Line& l, long long x) { return l.m * x + l.c; }
bool useless(const Line& p, const Line& q, const Line& r) {  // q is never strictly the lowest of the three (slopes fall p, q, r)
    return (__int128)(q.c - p.c) * (q.m - r.m) >= (__int128)(r.c - q.c) * (p.m - q.m);
}
vector<long long> cheapest(const vector<long long>& a, const vector<long long>& b) {
    int n = a.size();
    vector<long long> dp(n, 0);
    deque<Line> hull = {{b[0], 0}};
    for (int i = 1; i < n; i++) {
        while (hull.size() >= 2 && at(hull[1], a[i]) <= at(hull[0], a[i])) hull.pop_front();  // x only grows
        dp[i] = at(hull.front(), a[i]);
        Line now = {b[i], dp[i]};
        while (hull.size() >= 2 && useless(hull[hull.size() - 2], hull.back(), now)) hull.pop_back();
        hull.push_back(now);
    }
    return dp;
}
// snippet:end

vector<long long> bruteCheapest(const vector<long long>& a, const vector<long long>& b) {
    int n = a.size();
    vector<long long> dp(n, 0);
    for (int i = 1; i < n; i++) {
        dp[i] = LLONG_MAX;
        for (int j = 0; j < i; j++) dp[i] = min(dp[i], dp[j] + b[j] * a[i]);
    }
    return dp;
}

int main() {
    auto show = [](const vector<long long>& a, const vector<long long>& b) {
        auto dp = cheapest(a, b);
        cout << "dp:";
        for (long long x : dp) cout << " " << x;
        cout << "\n";
    };
    show({1, 2, 3, 4}, {4, 3, 1, 0});
    show({1, 3, 4}, {2, 1, 0});
    cout << "middle line useless: " << (useless({3, 0}, {2, 5}, {1, 6}) ? "yes" : "no") << "\n";
    // Check (not printed): 3000 random inputs of up to 8 numbers, against the O(n^2) definition.
    mt19937 rng(5);
    for (int it = 0; it < 3000; it++) {
        int n = rng() % 8 + 1;
        vector<long long> a(n), b(n);
        long long x = rng() % 3 + 1, y = 0;
        for (int i = 0; i < n; i++) { a[i] = x; x += rng() % 5 + 1; }
        for (int i = n - 1; i >= 0; i--) { b[i] = y; y += rng() % 5 + 1; }
        if (cheapest(a, b) != bruteCheapest(a, b)) return 1;
    }
}
