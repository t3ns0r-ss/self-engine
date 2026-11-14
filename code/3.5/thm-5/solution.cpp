#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.5.5. Forward: after coin i, prob[h] = the probability of h heads, prob'[h] = prob[h] (1 - p) + prob[h - 1] p.
// Backward: with k rolls left, E[k] = 1 + (5/6) E[k - 1] and E[0] = 0, the expected rolls until a 6 (at most k rolls).
vector<double> headsDistribution(const vector<double>& p) {
    vector<double> prob = {1.0};
    for (double q : p) {
        vector<double> next(prob.size() + 1, 0.0);
        for (size_t h = 0; h < prob.size(); h++) {
            next[h] += prob[h] * (1 - q);  // this coin shows tails
            next[h + 1] += prob[h] * q;    // this coin shows heads
        }
        prob = next;
    }
    return prob;
}
vector<double> expectedRolls(int maxRolls) {
    vector<double> E(maxRolls + 1, 0.0);
    for (int k = 1; k <= maxRolls; k++) E[k] = 1 + 5.0 / 6.0 * E[k - 1];
    return E;
}
// snippet:end

int main() {
    cout << fixed << setprecision(4);
    auto d = headsDistribution({0.5, 1.0 / 3.0});
    cout << "heads 0 1 2:";
    for (double x : d) cout << ' ' << x;
    cout << '\n';
    auto E = expectedRolls(2);
    cout << "rolls with 1 left: " << E[1] << ", with 2 left: " << E[2] << '\n';
    mt19937 rng(35);
    for (int round = 0; round < 300; round++) {
        int n = 1 + rng() % 8;
        vector<double> p(n);
        for (double& x : p) x = (rng() % 11) / 10.0;
        auto got = headsDistribution(p);
        vector<double> brute(n + 1, 0.0);
        for (int mask = 0; mask < (1 << n); mask++) {
            double w = 1;
            for (int i = 0; i < n; i++) w *= (mask >> i & 1) ? p[i] : 1 - p[i];
            brute[__builtin_popcount(mask)] += w;
        }
        for (int h = 0; h <= n; h++)
            if (fabs(got[h] - brute[h]) > 1e-9) return 1;
    }
    for (int k = 1; k <= 8; k++) {
        double sum = 0, miss = 1;  // expected rolls = sum over j of P(still rolling before roll j)
        for (int j = 1; j <= k; j++) { sum += miss; miss *= 5.0 / 6.0; }
        if (fabs(sum - expectedRolls(k)[k]) > 1e-9) return 1;
    }
}
