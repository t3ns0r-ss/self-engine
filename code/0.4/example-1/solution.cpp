/*
Problem: AtCoder ABC 118 C Monsters Battle Royale. An attack lowers the target's health by the
attacker's health; a monster at 0 or below dies. The smallest possible health of the last monster.
Input: N (2 <= N <= 10^5), then A_1 .. A_N (1 <= A_i <= 10^9).
Output: the minimum final health.
*/
#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// The smallest possible health of the last monster is the GCD of all healths (std::gcd runs Euclid's algorithm).
long long finalHealth(const vector<long long>& a) {
    long long g = 0;
    for (long long x : a) g = gcd(g, x);
    return g;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << finalHealth(a) << "\n";
}
