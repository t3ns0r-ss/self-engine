/*
Problem: a process on states 0..K-1 moves from state s to nxt[s]. Starting at state x,
print the state after T steps.
Input: K x T (K <= 2*10^5, T <= 10^18), then nxt[0..K-1].
Output: the state after T steps.
*/
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
        if (step == T) return s;  // reached T before any repeat
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
    int k, x;
    long long t;  // up to 10^18
    cin >> k >> x >> t;
    vector<int> nxt(k);
    for (auto& v : nxt) cin >> v;
    cout << stateAfter(nxt, x, t) << "\n";
}
