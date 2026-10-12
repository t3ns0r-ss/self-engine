#include <bits/stdc++.h>
using namespace std;


// snippet:begin
// Theorem 7.5.3. For a heap with the allowed removals, g(x) = mex of g(x - r) over the removals r <= x, where mex is the least
// non-negative number that is not in the set. A sum of heaps is lost for the player to move exactly when the xor of the g values is 0.
vector<int> grundyTable(const vector<int>& removals, int n) {
    vector<int> g(n + 1, 0);
    for (int x = 1; x <= n; x++) {
        vector<char> seen(removals.size() + 2, 0);
        for (int r : removals)
            if (r <= x && g[x - r] < (int)seen.size()) seen[g[x - r]] = 1;
        while (seen[g[x]]) g[x]++;
    }
    return g;
}
bool firstPlayerWins(const vector<int>& heaps, const vector<int>& g) {
    int total = 0;
    for (int h : heaps) total ^= g[h];
    return total != 0;
}
// snippet:end

map<vector<int>, bool> memo;
bool bruteWin(vector<int> heaps, const vector<int>& removals) {  // a search over the positions of the sum
    sort(heaps.begin(), heaps.end());
    auto it = memo.find(heaps);
    if (it != memo.end()) return it->second;
    bool win = false;
    for (size_t i = 0; i < heaps.size() && !win; i++)
        for (int r : removals)
            if (r <= heaps[i] && !win) {
                vector<int> next = heaps;
                next[i] -= r;
                win = !bruteWin(next, removals);
            }
    return memo[heaps] = win;
}

int main() {
    vector<int> removals = {1, 3, 4};
    auto g = grundyTable(removals, 8);
    cout << "g:";
    for (int x : g) cout << " " << x;
    cout << "\nheaps 5 3 6: " << (firstPlayerWins({5, 3, 6}, g) ? "first" : "second") << "\n";
    // Check (not printed): for the removal sets {1,2}, {1,3,4}, {2,3}, {1,2,5} all sums of up to 3 heaps of sizes up to 9.
    for (auto rem : vector<vector<int>>{{1, 2}, {1, 3, 4}, {2, 3}, {1, 2, 5}}) {
        memo.clear();
        auto table = grundyTable(rem, 9);
        for (int a = 0; a <= 9; a++)
            for (int b = 0; b <= 9; b++)
                for (int c = 0; c <= 9; c++)
                    if (firstPlayerWins({a, b, c}, table) != bruteWin({a, b, c}, rem)) return 1;
    }
}
