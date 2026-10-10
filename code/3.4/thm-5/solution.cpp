#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 3.4.5. E[i][j] = the edit distance of the prefixes: delete a_i, insert b_j, or align them (replace when they differ).
int editDistance(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> E(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) E[i][0] = i;
    for (int j = 0; j <= m; j++) E[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            E[i][j] = min({E[i - 1][j] + 1, E[i][j - 1] + 1, E[i - 1][j - 1] + (a[i - 1] != b[j - 1])});
    return E[n][m];
}
// snippet:end

int main() {
    cout << "cat -> cut: " << editDistance("cat", "cut") << ", kitten -> sitting: " << editDistance("kitten", "sitting") << '\n';
    mt19937 rng(35);
    for (int round = 0; round < 200; round++) {
        string x, y;
        for (int i = rng() % 5; i > 0; i--) x += 'a' + rng() % 2;
        for (int i = rng() % 5; i > 0; i--) y += 'a' + rng() % 2;
        // breadth-first search over strings by single edits (a different method)
        map<string, int> dist;
        queue<string> q;
        dist[x] = 0, q.push(x);
        while (!q.empty()) {
            string s = q.front();
            q.pop();
            if (dist[s] >= 8) continue;
            vector<string> next;
            for (size_t i = 0; i <= s.size(); i++) for (char c = 'a'; c <= 'b'; c++) next.push_back(s.substr(0, i) + c + s.substr(i));
            for (size_t i = 0; i < s.size(); i++) {
                next.push_back(s.substr(0, i) + s.substr(i + 1));
                for (char c = 'a'; c <= 'b'; c++) next.push_back(s.substr(0, i) + c + s.substr(i + 1));
            }
            for (auto& t : next) if (!dist.count(t) && t.size() <= 8) dist[t] = dist[s] + 1, q.push(t);
        }
        if (dist[y] != editDistance(x, y)) return 1;
    }
}
