#include <bits/stdc++.h>
using namespace std;

/*
Problem: n stairs numbered 1..n, the stair k has p_k balls. A move chooses a stair k >= 2 that has a ball and moves any positive number of its
balls to the stair k - 1. The player who cannot move loses; the first player moves first. Print first or second (the winner).
Input: n, then p_1 ... p_n.
Output: first or second.
*/


// snippet:begin
// The even stairs are Nim heaps (Theorem 7.5.2): a move from an even stair removes balls from a heap and puts them on an odd stair; a move from
// an odd stair puts balls on an even stair, and the other player undoes it by moving the same balls on to the next odd stair. So the first
// player wins exactly when the xor of p_2, p_4, ... is not 0.
string winner(const vector<int>& p) {  // p[0] is the stair 1
    int total = 0;
    for (size_t k = 1; k < p.size(); k += 2) total ^= p[k];
    return total ? "first" : "second";
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int& x : p) cin >> x;
    cout << winner(p) << "\n";
}
