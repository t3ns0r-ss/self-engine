#include <bits/stdc++.h>
using namespace std;


// snippet:begin
// Theorem 7.5.2. Nim: remove any positive number of stones from one pile; the player who cannot move loses. The position is lost for the
// player to move exactly when the xor of the pile sizes is 0. From a non-zero xor s, take the pile that has the highest bit of s and cut
// it to (size xor s): the new xor is 0. Returns the (pile, new size) of such a move, or (-1, -1) if the xor is 0.
pair<int, int> winningMove(const vector<int>& piles) {
    int s = 0;
    for (int x : piles) s ^= x;
    if (s == 0) return {-1, -1};
    int bit = 1 << (31 - __builtin_clz(s));  // the highest bit of s
    for (size_t i = 0; i < piles.size(); i++)
        if (piles[i] & bit) return {(int)i, piles[i] ^ s};
    return {-1, -1};  // not reached
}
// snippet:end

map<vector<int>, bool> memo;
bool bruteWin(vector<int> piles) {  // the player to move wins? a search over all positions
    sort(piles.begin(), piles.end());
    auto it = memo.find(piles);
    if (it != memo.end()) return it->second;
    bool win = false;
    for (size_t i = 0; i < piles.size() && !win; i++)
        for (int take = 1; take <= piles[i] && !win; take++) {
            vector<int> next = piles;
            next[i] -= take;
            win = !bruteWin(next);
        }
    return memo[piles] = win;
}

int main() {
    for (auto piles : vector<vector<int>>{{3, 4, 5}, {1, 2, 3}}) {
        auto [i, to] = winningMove(piles);
        if (i < 0) cout << "piles 1 2 3: the player to move loses\n";
        else cout << "piles 3 4 5: take from the pile " << i << ", leave " << to << "\n";
    }
    // Check (not printed): all positions of up to 4 piles with sizes up to 5: the winner is decided by the xor, and the move leads to xor 0.
    for (int mask = 0; mask < 6 * 6 * 6 * 6; mask++) {
        vector<int> p = {mask % 6, mask / 6 % 6, mask / 36 % 6, mask / 216};
        auto [i, to] = winningMove(p);
        if ((i >= 0) != bruteWin(p)) return 1;
        if (i >= 0) {
            if (to >= p[i]) return 1;
            p[i] = to;
            if (bruteWin(p)) return 1;
        }
    }
}
