/*
Problem: AtCoder ABC 118 C Monsters Battle Royale. An attack lowers the target's health by the
attacker's health; a monster at 0 or below dies. The smallest possible health of the last monster.
Input: N (2 <= N <= 10^5), then A_1 .. A_N (1 <= A_i <= 10^9).
Output: the minimum final health.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long g = 0;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        g = gcd(g, a);  // std::gcd from <numeric>: Euclid (Theorem 0.4.5)
    }
    cout << g << "\n";
}
