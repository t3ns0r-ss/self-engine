#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int& x : p) cin >> x;
    vector<int> target(n);
    iota(target.begin(), target.end(), 1);
    map<vector<int>, int> dist;
    queue<vector<int>> q;
    dist[p] = 0;
    q.push(p);
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (cur == target) break;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                auto next = cur;
                swap(next[i], next[j]);
                if (!dist.count(next)) dist[next] = dist[cur] + 1, q.push(next);
            }
    }
    cout << dist[target] << "\n";
}
