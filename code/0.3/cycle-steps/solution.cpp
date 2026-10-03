/*
Problem: a process on states 0..K-1 moves from state s to nxt[s]. Starting at state x,
print the state after T steps.
Input: K x T (K <= 2*10^5, T <= 10^18), then nxt[0..K-1].
Output: the state after T steps.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int k, x;
    long long t;  // up to 10^18
    cin >> k >> x >> t;
    vector<int> nxt(k);
    for (auto& v : nxt) cin >> v;

    vector<long long> firstSeen(k, -1);  // step at which each state first appeared
    vector<int> order;                   // order[i] = state after i steps
    int s = x;
    for (long long step = 0;; step++) {
        if (step == t) {  // reached T before any repeat
            cout << s << "\n";
            return 0;
        }
        if (firstSeen[s] != -1) {  // first repeat: x_mu = x_step (Theorem 0.3.1)
            long long mu = firstSeen[s], lambda = step - mu;
            cout << order[mu + (t - mu) % lambda] << "\n";
            return 0;
        }
        firstSeen[s] = step;
        order.push_back(s);
        s = nxt[s];
    }
}
