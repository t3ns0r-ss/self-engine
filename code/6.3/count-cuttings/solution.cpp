#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1731 Word Combinations style. The number of ways to cut the string s into dictionary words (a word may be used
many times), modulo 10^9 + 7.
Input: s (up to 5000 letters), k, then the k dictionary words (total length up to 10^6).
Output: the number of ways modulo 10^9 + 7.
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
// ways[i] = the number of cuttings of s[i..]: the sum of ways[i + length] over the dictionary words that begin at i, found by
// one walk down the trie (Theorem 6.3.3). Uses the Trie of Theorem 6.3.1.
long long countCuttings(const Trie& dictionary, const string& s) {
    const long long MOD = 1e9 + 7;
    int n = s.size();
    vector<long long> ways(n + 1, 0);
    ways[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        int v = 0;
        for (int j = i; j < n; j++) {
            v = dictionary.child[v][s[j] - 'a'];
            if (!v) break;                                   // no dictionary word begins with s[i..j]
            if (dictionary.end[v]) ways[i] = (ways[i] + ways[j + 1]) % MOD;  // a word ends here: continue after it
        }
    }
    return ways[0];
}
// snippet:end

int main() {
    string s;
    int k;
    cin >> s >> k;
    Trie dictionary;
    for (int i = 0; i < k; i++) {
        string w;
        cin >> w;
        dictionary.insert(w);
    }
    cout << countCuttings(dictionary, s) << "\n";
}
