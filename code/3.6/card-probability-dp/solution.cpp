#include <bits/stdc++.h>
using namespace std;

vector<double> heads(const vector<double>& p) {
    vector<double> prob = {1.0};
    for (double q : p) {
        vector<double> next(prob.size() + 1, 0.0);
        for (size_t h = 0; h < prob.size(); h++) next[h] += prob[h] * (1 - q), next[h + 1] += prob[h] * q;
        prob = next;
    }
    return prob;
}
// Expected rolls of a fair die until a 6, with at most k rolls (table over the rolls left).
double rolls(int k) {
    double e = 0;
    for (int i = 1; i <= k; i++) e = 1 + 5.0 / 6.0 * e;
    return e;
}
int main() {
    cout << setprecision(4);
    // P1: three coins with heads probabilities 0.5, 0.4, 0.1; the probability of more heads than tails (at least 2 heads).
    vector<double> p = {0.5, 0.4, 0.1};
    double brute = 0;
    for (int mask = 0; mask < 8; mask++) {
        double w = 1;
        for (int i = 0; i < 3; i++) w *= (mask >> i & 1) ? p[i] : 1 - p[i];
        if (__builtin_popcount(mask) >= 2) brute += w;
    }
    auto d = heads(p);
    cout << "P1 brute=" << brute << " method=" << d[2] + d[3] << '\n';
    // P2: expected rolls of a fair die until a 6, stopping after at most 2 rolls. Brute: add up the two outcomes by hand.
    cout << "P2 brute=" << 1.0 * (1.0 / 6) + 2.0 * (5.0 / 6) << " method=" << rolls(2) << '\n';
    // N1: draw 2 cards without replacement from 2 red and 2 black; both red. Brute: 1 of the C(4, 2) = 6 pairs.
    // Method (wrong): the table with the fixed probability 1/2 for every draw.
    cout << "N1 brute=" << 1.0 / 6 << " method=" << 0.5 * 0.5 << '\n';
    // N2: expected tosses of a fair coin until the first head is 2. Method: the table with at most 3 tosses.
    double e = 0;
    for (int i = 1; i <= 3; i++) e = 1 + 0.5 * e;
    cout << "N2 brute=" << 2.0 << " method=" << e << '\n';
}
