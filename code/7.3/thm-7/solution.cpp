#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX / 4;

// snippet:begin
// Theorem 7.3.7. cur[i] = min over j < i of prev[j] + cost(j, i) for i in lo..hi. If the smallest best j never moves left as i
// grows, find it for the middle i, then the left half of the i's looks only at j <= best and the right half only at j >= best.
template <class Cost>
void fillLayer(int lo, int hi, int optLo, int optHi, const vector<long long>& prev, vector<long long>& cur, Cost cost) {
    if (lo > hi) return;
    int mid = (lo + hi) / 2, bestJ = optLo;
    long long best = INF;
    for (int j = optLo; j <= min(mid - 1, optHi); j++) {
        long long cand = prev[j] + cost(j, mid);
        if (cand < best) { best = cand; bestJ = j; }  // strict: the smallest best j
    }
    cur[mid] = best;
    fillLayer(lo, mid - 1, optLo, bestJ, prev, cur, cost);
    fillLayer(mid + 1, hi, bestJ, optHi, prev, cur, cost);
}
// snippet:end

// the smallest best j of every i in 2..n, by trying all of them
vector<int> bruteOpt(const vector<long long>& prev, const vector<long long>& P) {
    int n = P.size() - 1;
    vector<int> opt;
    for (int i = 2; i <= n; i++) {
        int bestJ = 1;
        long long best = INF;
        for (int j = 1; j < i; j++) {
            long long cand = prev[j] + (P[i] - P[j]) * (P[i] - P[j]);
            if (cand < best) { best = cand; bestJ = j; }
        }
        opt.push_back(bestJ);
    }
    return opt;
}

int main() {
    auto run = [](const vector<long long>& a) {
        int n = a.size();
        vector<long long> P(n + 1, 0), prev(n + 1, INF), cur(n + 1, INF);
        for (int i = 0; i < n; i++) P[i + 1] = P[i] + a[i];
        for (int i = 1; i <= n; i++) prev[i] = P[i] * P[i];
        auto cost = [&](int j, int i) { return (P[i] - P[j]) * (P[i] - P[j]); };
        fillLayer(2, n, 1, n - 1, prev, cur, cost);
        cout << "opt:";
        for (int j : bruteOpt(prev, P)) cout << " " << j;
        cout << "\ncost: " << cur[n] << "\n";
    };
    run({1, 2, 3, 4, 5});
    run({0, 0, 0});
    // Check (not printed): 3000 random arrays of up to 9 numbers: the layer equals the O(n^2) definition and the best j never falls.
    mt19937 rng(11);
    for (int it = 0; it < 3000; it++) {
        int n = rng() % 8 + 2;
        vector<long long> a(n), P(n + 1, 0), prev(n + 1, INF), cur(n + 1, INF);
        for (int i = 0; i < n; i++) { a[i] = rng() % 7; P[i + 1] = P[i] + a[i]; }
        for (int i = 1; i <= n; i++) prev[i] = P[i] * P[i];
        auto cost = [&](int j, int i) { return (P[i] - P[j]) * (P[i] - P[j]); };
        fillLayer(2, n, 1, n - 1, prev, cur, cost);
        vector<int> opt = bruteOpt(prev, P);
        for (int i = 2; i <= n; i++) {
            long long best = INF;
            for (int j = 1; j < i; j++) best = min(best, prev[j] + cost(j, i));
            if (cur[i] != best) return 1;
            if (i > 2 && opt[i - 2] < opt[i - 3]) return 1;
        }
    }
}
