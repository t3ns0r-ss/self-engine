#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.2.1. Optimal substructure for the frog: the state is the stone, best(i) = min over the jumps into i of
// best(from) + cost, and the answer is best(n - 1).
vector<long long> frogBest(const vector<int>& h, int k) {
    int n = h.size();
    vector<long long> best(n, LLONG_MAX);
    best[0] = 0;
    for (int i = 1; i < n; i++)
        for (int j = max(0, i - k); j < i; j++) best[i] = min(best[i], best[j] + abs(h[i] - h[j]));
    return best;
}
// snippet:end

long long brute(const vector<int>& h, int k, int i = 0) {  // every jump sequence
    if (i == (int)h.size() - 1) return 0;
    long long r = LLONG_MAX;
    for (int j = i + 1; j <= min((int)h.size() - 1, i + k); j++) r = min(r, abs(h[j] - h[i]) + brute(h, k, j));
    return r;
}
int main() {
    vector<int> h = {10, 30, 40, 20};
    auto best = frogBest(h, 2);
    cout << "best for the heights 10 30 40 20:";
    for (long long b : best) cout << ' ' << b;
    cout << " (the answer is " << best.back() << ")\n";
    mt19937 rng(8);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 9, k = 1 + rng() % 3;
        vector<int> g(n);
        for (int& x : g) x = 1 + rng() % 20;
        if (frogBest(g, k).back() != brute(g, k)) return 1;
    }
}
