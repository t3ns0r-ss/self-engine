#include <bits/stdc++.h>
using namespace std;

map<pair<int, int>, int> memo;
int grundy(int stones, int used) {  // the Grundy value of one pile, by the definition
    auto key = make_pair(stones, used);
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;
    set<int> reach;
    for (int i = 1; i <= stones; i++)
        if (!(used >> i & 1)) reach.insert(grundy(stones - i, used | 1 << i));
    int g = 0;
    while (reach.count(g)) g++;
    return memo[key] = g;
}
int main() {
    int n;
    cin >> n;
    int total = 0;
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        total ^= grundy(s, 0);
    }
    cout << (total == 0 ? "YES" : "NO") << "\n";
}
