#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1729, Stick Game. A heap of n sticks (up to 10^6) and a set of k allowed moves p_1..p_k (k up to 100): a move removes p_i sticks, if
the heap has at least p_i. The player who cannot move loses. For every heap size 1..n print W if the player to move wins and L otherwise.
Input: n and k, then the k moves.
Output: a string of n characters.
*/


// snippet:begin
// Theorem 7.5.1: win[x] is true exactly when some move leads to a heap that is lost for the player to move there (win[0] is false).
string winLose(int n, const vector<int>& moves) {
    vector<char> win(n + 1, 0);
    for (int x = 1; x <= n; x++)
        for (int p : moves)
            if (p <= x && !win[x - p]) win[x] = 1;
    string out;
    for (int x = 1; x <= n; x++) out += win[x] ? 'W' : 'L';
    return out;
}
// snippet:end

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> moves(k);
    for (int& p : moves) cin >> p;
    cout << winLose(n, moves) << "\n";
}
