#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.3.1. The state after T steps of the process s -> nxt[s], starting at x, even for T up to 10^18:
// follow it until a state repeats, then use the period.
int stateAfter(const vector<int>& nxt, int x, long long T) {
    vector<long long> firstSeen(nxt.size(), -1);  // step at which each state first appeared
    vector<int> order;                            // order[i] = state after i steps
    int s = x;
    for (long long step = 0;; step++) {
        if (step == T) return s;   // reached T before any repeat
        if (firstSeen[s] != -1) {  // first repeat: x_mu = x_step
            long long mu = firstSeen[s], lambda = step - mu;
            return order[mu + (T - mu) % lambda];
        }
        firstSeen[s] = step;
        order.push_back(s);
        s = nxt[s];
    }
}
// snippet:end

int main() {
    vector<int> nxt = {1, 2, 3, 1};
    for (long long t : {2LL, 10LL, 1000000000000000000LL})
        cout << "next = 1 2 3 1, start 0, after " << t << " steps: state " << stateAfter(nxt, 0, t) << '\n';
    mt19937 rng(7);
    for (int round = 0; round < 300; round++) {  // random processes on 6 states against stepping one at a time
        vector<int> f(6);
        for (int& v : f) v = rng() % 6;
        for (int x = 0; x < 6; x++)
            for (long long t = 0; t <= 40; t++) {
                int s = x;
                for (long long i = 0; i < t; i++) s = f[s];
                if (s != stateAfter(f, x, t)) return 1;
            }
    }
}
