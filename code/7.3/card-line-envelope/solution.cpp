#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX / 4;
using Line = array<long long, 2>;  // {slope, intercept}
long long at(const Line& l, long long x) { return l[0] * x + l[1]; }
bool useless(const Line& p, const Line& q, const Line& r) {
    return (__int128)(q[1] - p[1]) * (q[0] - r[0]) >= (__int128)(r[1] - q[1]) * (p[0] - q[0]);
}

// frog: dp[i] = min over j < i of dp[j] + (h[i] - h[j])^2 + C, by the deque of lines (the card's method)
long long frogMethod(const vector<long long>& h, long long C) {
    int n = h.size();
    vector<long long> dp(n, 0);
    deque<Line> hull = {{-2 * h[0], h[0] * h[0]}};
    for (int i = 1; i < n; i++) {
        while (hull.size() >= 2 && at(hull[1], h[i]) <= at(hull[0], h[i])) hull.pop_front();
        dp[i] = at(hull.front(), h[i]) + h[i] * h[i] + C;
        Line now = {-2 * h[i], dp[i] + h[i] * h[i]};
        while (hull.size() >= 2 && useless(hull[hull.size() - 2], hull.back(), now)) hull.pop_back();
        hull.push_back(now);
    }
    return dp[n - 1];
}
long long frogBrute(const vector<long long>& h, long long C) {
    int n = h.size();
    vector<long long> dp(n, INF);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++) dp[i] = min(dp[i], dp[j] + (h[i] - h[j]) * (h[i] - h[j]) + C);
    return dp[n - 1];
}

// Li Chao tree over the points 0..size-1 (minimum)
struct LiChao {
    int size;
    vector<long long> slope, icpt;
    LiChao(int size) : size(size), slope(4 * size, 0), icpt(4 * size, INF) {}
    long long val(int node, long long x) const { return slope[node] * x + icpt[node]; }
    void add(long long m, long long c) {
        int node = 1, lo = 0, hi = size - 1;
        while (true) {
            int mid = (lo + hi) / 2;
            if (m * mid + c < val(node, mid)) { swap(m, slope[node]); swap(c, icpt[node]); }
            if (lo == hi) return;
            if (m * lo + c < val(node, lo)) { node = 2 * node; hi = mid; }
            else if (m * hi + c < val(node, hi)) { node = 2 * node + 1; lo = mid + 1; }
            else return;
        }
    }
    long long query(long long x) const {
        int node = 1, lo = 0, hi = size - 1;
        long long best = INF;
        while (true) {
            best = min(best, val(node, x));
            if (lo == hi) return best;
            int mid = (lo + hi) / 2;
            if (x <= mid) { node = 2 * node; hi = mid; }
            else { node = 2 * node + 1; lo = mid + 1; }
        }
    }
};

long long minOver(const vector<Line>& lines, long long x) {
    long long best = INF;
    for (const Line& l : lines) best = min(best, at(l, x));
    return best;
}
// the monotone deque used although the slopes were NOT inserted in falling order, then one query
long long dequeAnswer(const vector<Line>& lines, long long x) {
    deque<Line> hull;
    for (const Line& l : lines) {
        while (hull.size() >= 2 && useless(hull[hull.size() - 2], hull.back(), l)) hull.pop_back();
        hull.push_back(l);
    }
    while (hull.size() >= 2 && at(hull[1], x) <= at(hull[0], x)) hull.pop_front();
    return at(hull.front(), x);
}
// the front pointer used although the queries do NOT rise: returns the answer of the last query
long long pointerAnswer(const vector<Line>& lines, const vector<long long>& xs) {
    size_t p = 0;
    long long last = 0;
    for (long long x : xs) {
        while (p + 1 < lines.size() && at(lines[p + 1], x) <= at(lines[p], x)) p++;
        last = at(lines[p], x);
    }
    return last;
}

int main() {
    vector<long long> h = {1, 2, 4, 7};
    cout << "P1 brute=" << frogBrute(h, 3) << " method=" << frogMethod(h, 3) << "\n";
    LiChao tree(16);
    vector<Line> p2 = {{3, 0}, {-2, 12}, {0, 5}};  // added in this order, the slopes neither rise nor fall
    for (const Line& l : p2) tree.add(l[0], l[1]);
    cout << "P2 brute=" << minOver(p2, 3) << " method=" << tree.query(3) << "\n";
    vector<Line> n1 = {{0, 0}, {1, -1}, {2, 0}};  // slopes rise, but the deque expects them to fall
    cout << "N1 brute=" << minOver(n1, 0) << " method=" << dequeAnswer(n1, 0) << "\n";
    vector<Line> n2 = {{3, 0}, {2, 1}, {1, 3}};
    cout << "N2 brute=" << minOver(n2, 0) << " method=" << pointerAnswer(n2, {1, 0}) << "\n";
}
