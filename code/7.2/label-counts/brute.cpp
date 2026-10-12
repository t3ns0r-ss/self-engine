#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    string letters;
    cin >> letters;
    vector<vector<int>> out(n);
    vector<vector<char>> reach(n, vector<char>(n, 0));
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        out[a - 1].push_back(b - 1), reach[a - 1][b - 1] = 1;
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (reach[i][k] && reach[k][j]) reach[i][j] = 1;
    for (int v = 0; v < n; v++)
        if (reach[v][v]) return cout << -1 << "\n", 0;
    int best = 0;
    vector<int> count(26, 0);
    function<void(int)> go = [&](int v) {
        count[letters[v] - 'a']++;
        best = max(best, *max_element(count.begin(), count.end()));
        for (int u : out[v]) go(u);
        count[letters[v] - 'a']--;
    };
    for (int s = 0; s < n; s++) go(s);
    cout << best << "\n";
}
