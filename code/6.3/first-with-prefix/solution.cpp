#include <bits/stdc++.h>
using namespace std;

/*
Problem: n words and q queries. For each query string u, print the smallest index (1-based) of a word that begins with u,
or -1 if there is none.
Input: n, the n words, q, the q queries (non-empty lower-case strings; the total length is up to 10^6).
Output: the answer to each query on its own line.
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
// Per-node data (the card "Words that share beginnings"): first[v] = the smallest index of an inserted word that goes through v.
// Uses the Trie of Theorem 6.3.1; the words are inserted in the order of their indices.
vector<int> firstWithPrefix(const vector<string>& words, const vector<string>& queries) {
    Trie t;
    vector<int> first = {INT_MAX};
    for (int i = 0; i < (int)words.size(); i++) {
        t.insert(words[i]);
        first.resize(t.pass.size(), INT_MAX);  // the insertion may have made new nodes
        int v = 0;
        for (char ch : words[i]) {
            v = t.child[v][ch - 'a'];
            first[v] = min(first[v], i);
        }
    }
    vector<int> answer;
    for (const string& u : queries) {
        int v = t.find(u);
        answer.push_back(v < 0 ? -1 : first[v] + 1);
    }
    return answer;
}
// snippet:end

int main() {
    int n, q;
    cin >> n;
    vector<string> words(n);
    for (string& w : words) cin >> w;
    cin >> q;
    vector<string> queries(q);
    for (string& u : queries) cin >> u;
    for (int x : firstWithPrefix(words, queries)) cout << x << "\n";
}
