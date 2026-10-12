#include <bits/stdc++.h>
using namespace std;

// method: the first player wins when the xor of the pile sizes is not 0 (plain Nim); brute: a search over all positions with the given rule.
map<pair<vector<int>, int>, bool> memo;
bool bruteWin(vector<int> piles, int limit) {  // limit: the most stones that a move may take (large = plain Nim)
    sort(piles.begin(), piles.end());
    auto key = make_pair(piles, limit);
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;
    bool win = false;
    for (size_t i = 0; i < piles.size() && !win; i++)
        for (int take = 1; take <= min(piles[i], limit) && !win; take++) {
            vector<int> next = piles;
            next[i] -= take;
            win = !bruteWin(next, limit);
        }
    return memo[key] = win;
}
bool method(const vector<int>& piles) {
    int x = 0;
    for (int p : piles) x ^= p;
    return x != 0;
}
// the stair game: a move takes balls from a stair k >= 2 to the stair k - 1; brute: a search; method: the xor of the even stairs.
map<vector<int>, bool> stairMemo;
bool stairBrute(const vector<int>& p) {
    auto it = stairMemo.find(p);
    if (it != stairMemo.end()) return it->second;
    bool win = false;
    for (size_t k = 1; k < p.size() && !win; k++)
        for (int take = 1; take <= p[k] && !win; take++) {
            vector<int> next = p;
            next[k] -= take, next[k - 1] += take;
            win = !stairBrute(next);
        }
    return stairMemo[p] = win;
}
bool stairMethod(const vector<int>& p) {
    int x = 0;
    for (size_t k = 1; k < p.size(); k += 2) x ^= p[k];
    return x != 0;
}
int main() {
    auto name = [](bool first) { return first ? "first" : "second"; };
    cout << "P1 brute=" << name(bruteWin({3, 4, 5}, 100)) << " method=" << name(method({3, 4, 5})) << "\n";
    vector<int> stairs = {5, 2, 7, 2};
    cout << "P2 brute=" << name(stairBrute(stairs)) << " method=" << name(stairMethod(stairs)) << "\n";
    cout << "N1 brute=" << name(bruteWin({3}, 2)) << " method=" << name(method({3})) << "\n";  // at most 2 stones per move
}
