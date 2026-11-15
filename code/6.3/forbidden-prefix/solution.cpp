#include <bits/stdc++.h>
using namespace std;

/*
Problem: two multisets of strings, X and Y, both empty at the start. Q queries "1 s" (put s into X) or "2 s" (put s into Y).
After each query print how many strings of Y have no string of X as a prefix.
Input: Q, then Q lines with the type and the string (lower-case letters).
Output: Q numbers, one per line.
*/

struct CountTrie {
    vector<array<int, 26>> child = {array<int, 26>{}};
    vector<int> pass = {0};
    vector<bool> blocked = {false};
    int step(int v, char ch) {
        int c = ch - 'a';
        if (!child[v][c]) {
            child[v][c] = child.size();
            child.push_back(array<int, 26>{});
            pass.push_back(0);
            blocked.push_back(false);
        }
        return child[v][c];
    }
};

// snippet:begin
// Counts that change (Theorem 6.3.4) and a blocked flag: pass[v] counts the strings of Y that are still alive below v.
vector<int> forbiddenPrefix(const vector<pair<int, string>>& queries) {
    CountTrie t;
    vector<int> answers;
    for (const auto& [type, s] : queries) {
        vector<int> path = {0};
        int v = 0;
        bool covered = false;
        for (char ch : s) {
            v = t.step(v, ch);
            if (t.blocked[v]) covered = true;  // a string of X is a prefix of s
            path.push_back(v);
        }
        if (!covered) {
            if (type == 2) {
                for (int u : path) t.pass[u]++;  // one more live string of Y
            } else {
                int k = t.pass[v];
                for (int u : path) t.pass[u] -= k;  // all live strings below v die; the ancestors lose them too
                t.blocked[v] = true;
            }
        }
        answers.push_back(t.pass[0]);
    }
    return answers;
}
// snippet:end

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    vector<pair<int, string>> queries(q);
    for (auto& [type, s] : queries) cin >> type >> s;
    for (int a : forbiddenPrefix(queries)) cout << a << "\n";
}
