#include <bits/stdc++.h>
using namespace std;

map<int, bool> memo;
vector<int> moves;
bool wins(int x) {  // the player to move wins? a search from the top
    auto it = memo.find(x);
    if (it != memo.end()) return it->second;
    bool w = false;
    for (int p : moves)
        if (p <= x && !wins(x - p)) w = true;
    return memo[x] = w;
}
int main() {
    int n, k;
    cin >> n >> k;
    moves.resize(k);
    for (int& p : moves) cin >> p;
    for (int x = 1; x <= n; x++) cout << (wins(x) ? 'W' : 'L');
    cout << "\n";
}
