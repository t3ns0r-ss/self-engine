#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> target(n);
    for (int& x : target) cin >> x;
    int cap = *max_element(target.begin(), target.end());
    set<vector<int>> seen;
    queue<vector<int>> q;
    vector<int> start(n, 1);
    seen.insert(start);
    q.push(start);
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (cur == target) {
            cout << "YES\n";
            return 0;
        }
        int sum = accumulate(cur.begin(), cur.end(), 0);
        if (sum > cap) continue;
        for (int i = 0; i < n; i++) {
            auto next = cur;
            next[i] = sum;
            if (!seen.count(next)) seen.insert(next), q.push(next);
        }
    }
    cout << "NO\n";
}
