#include <bits/stdc++.h>
using namespace std;

map<vector<int>, bool> memo;
bool win(vector<int> heaps) {  // the player to move wins? a search over all multisets of heaps
    sort(heaps.begin(), heaps.end());
    auto it = memo.find(heaps);
    if (it != memo.end()) return it->second;
    bool result = false;
    for (size_t i = 0; i < heaps.size() && !result; i++)
        for (int a = 1; a < heaps[i] - a && !result; a++) {
            vector<int> next = heaps;
            next[i] = a;
            next.push_back(heaps[i] - a);
            result = !win(next);
        }
    return memo[heaps] = result;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << (win({n}) ? "first" : "second") << "\n";
    }
}
