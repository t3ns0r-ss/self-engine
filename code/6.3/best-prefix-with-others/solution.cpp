#include <bits/stdc++.h>
using namespace std;

/*
Problem: n words. For every word, print the length of the longest common prefix it has with any OTHER word of the list
(an equal word counts, with its whole length).
Input: n, then the n words (lower-case letters, total length up to 5·10^5).
Output: n numbers, one per word, on one line.
*/

struct Trie {
    vector<array<int, 26>> child = {array<int, 26>{}};
    vector<int> pass = {0}, end = {0};
    void insert(const string& w) {
        int v = 0;
        pass[0]++;
        for (char ch : w) {
            int c = ch - 'a';
            if (!child[v][c]) {
                child[v][c] = child.size();
                child.push_back(array<int, 26>{});
                pass.push_back(0);
                end.push_back(0);
            }
            v = child[v][c];
            pass[v]++;
        }
        end[v]++;
    }
    int find(const string& u) const {
        int v = 0;
        for (char ch : u) {
            v = child[v][ch - 'a'];
            if (!v) return -1;
        }
        return v;
    }
};

// snippet:begin
// For every word, the depth of the deepest node on its path that at least two words pass through (Theorem 6.3.2 (c)).
// Uses the Trie of Theorem 6.3.1.
vector<int> longestWithOthers(const vector<string>& words) {
    Trie t;
    for (const string& w : words) t.insert(w);
    vector<int> result;
    for (const string& w : words) {
        int v = 0, best = 0;
        for (size_t depth = 1; depth <= w.size(); depth++) {
            v = t.child[v][w[depth - 1] - 'a'];
            if (t.pass[v] >= 2) best = depth;  // another word goes through this node
        }
        result.push_back(best);
    }
    return result;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<string> words(n);
    for (string& w : words) cin >> w;
    vector<int> r = longestWithOthers(words);
    for (int i = 0; i < n; i++) cout << r[i] << (i + 1 < n ? ' ' : '\n');
}
