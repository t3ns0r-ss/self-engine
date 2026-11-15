#include <bits/stdc++.h>
using namespace std;

map<vector<int>, bool> memo;
bool win(const vector<int>& p) {  // a search over all positions
    auto it = memo.find(p);
    if (it != memo.end()) return it->second;
    bool result = false;
    for (size_t k = 1; k < p.size() && !result; k++)
        for (int take = 1; take <= p[k] && !result; take++) {
            vector<int> next = p;
            next[k] -= take, next[k - 1] += take;
            result = !win(next);
        }
    return memo[p] = result;
}
int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int& x : p) cin >> x;
    cout << (win(p) ? "first" : "second") << "\n";
}
