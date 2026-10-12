#include <bits/stdc++.h>
using namespace std;

/*
Problem: n piles of stones (n up to 10^6, sizes up to 60). A move removes i stones from a pile, for a number i >= 1 that has not been used before
on that pile (a different pile may use it again). Sam moves first; the player who cannot move loses. Print YES if Jon (the second player) wins,
and NO otherwise.
Input: n, then the n sizes.
Output: YES or NO.
*/


// snippet:begin
// Theorem 7.5.3: a pile of s stones has the Grundy value k, the largest k with k (k + 1) / 2 <= s (the sizes 1, 2, ..., k can be used, and
// no more); the piles are independent. Jon wins exactly when the xor of the values is 0.
string jonWins(const vector<int>& piles) {
    int total = 0;
    for (int s : piles) {
        int k = 0;
        while ((k + 1) * (k + 2) / 2 <= s) k++;
        total ^= k;
    }
    return total == 0 ? "YES" : "NO";
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> piles(n);
    for (int& s : piles) cin >> s;
    cout << jonWins(piles) << "\n";
}
