#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> out(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        out[a - 1].push_back(b - 1);
    }
    long long count = 0;
    function<void(int)> go = [&](int v) {
        if (v == n - 1) count++;
        for (int u : out[v]) go(u);
    };
    go(0);
    cout << count % 1000000007 << "\n";
}
