#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 6.3.1. A trie of lower-case words. Node 0 is the root; child[v][c] is the node reached from v by the letter c
// (0 means "no such edge"). pass[v] = how many inserted words go through v; end[v] = how many end exactly at v.
struct Trie {
    vector<array<int, 26>> child = {array<int, 26>{}};
    vector<int> pass = {0}, end = {0};
    void insert(const string& w) {
        int v = 0;
        pass[0]++;
        for (char ch : w) {
            int c = ch - 'a';
            if (!child[v][c]) {  // a new node for a new beginning
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
    int find(const string& u) const {  // the node of the string u, or -1 if no inserted word begins with u
        int v = 0;
        for (char ch : u) {
            v = child[v][ch - 'a'];
            if (!v) return -1;
        }
        return v;
    }
};
// snippet:end

int main() {
    Trie t;
    for (string w : {"ab", "abc", "abd", "b"}) t.insert(w);
    cout << "words ab abc abd b: nodes = " << t.child.size() << "\n";
    auto withPrefix = [&](const string& u) { int v = t.find(u); return v < 0 ? 0 : t.pass[v]; };  // Theorem 6.3.1 (b), (c)
    auto equalTo = [&](const string& u) { int v = t.find(u); return v < 0 ? 0 : t.end[v]; };
    for (string u : {"a", "ab", "abc", "b", "c"}) cout << "with prefix " << u << ": " << withPrefix(u) << "\n";
    for (string u : {"ab", "a"}) cout << "equal to " << u << ": " << equalTo(u) << "\n";
    // Check (not printed): on every multiset of up to 4 words of length 1..3 over {a, b} (including repeated words),
    // the counts equal those found by scanning the words, and the number of nodes is at most the total length + 1.
    vector<string> all;
    for (int len = 1; len <= 3; len++)
        for (int code = 0; code < (1 << len); code++) {
            string w(len, 'a');
            for (int i = 0; i < len; i++) w[i] = 'a' + (code >> i & 1);
            all.push_back(w);
        }
    int m = all.size();
    for (int a = -1; a < m; a++)
        for (int b = -1; b < m; b++)
            for (int c = -1; c < m; c++)
                for (int d = -1; d < m; d++) {
                    vector<string> words;
                    for (int x : {a, b, c, d})
                        if (x >= 0) words.push_back(all[x]);
                    Trie tr;
                    size_t total = 0;
                    for (const string& w : words) tr.insert(w), total += w.size();
                    if (tr.child.size() > total + 1) return 1;
                    for (const string& u : all) {
                        int v = tr.find(u), withPrefix = 0, equal = 0;
                        for (const string& w : words) withPrefix += w.compare(0, u.size(), u) == 0, equal += w == u;
                        if ((v < 0 ? 0 : tr.pass[v]) != withPrefix || (v < 0 ? 0 : tr.end[v]) != equal) return 1;
                    }
                }
}
