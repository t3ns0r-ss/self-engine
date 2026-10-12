#include <bits/stdc++.h>
using namespace std;

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
};

// snippet:begin
// Theorem 6.3.3. The lengths of the dictionary words that are prefixes of s[i..], found by one walk of s[i..] down the trie
// (the walk stops at the first missing edge). Uses the Trie of Theorem 6.3.1, where the words were inserted.
vector<int> wordLengthsAt(const Trie& t, const string& s, int i) {
    vector<int> lengths;
    int v = 0;
    for (int j = i; j < (int)s.size(); j++) {
        v = t.child[v][s[j] - 'a'];
        if (!v) break;                          // no dictionary word begins with s[i..j]
        if (t.end[v]) lengths.push_back(j - i + 1);
    }
    return lengths;
}
// The number of ways to cut s into dictionary words: ways[i] = the sum of ways[i + length] over the words starting at i.
long long countSplits(const Trie& t, const string& s) {
    int n = s.size();
    vector<long long> ways(n + 1, 0);
    ways[n] = 1;
    for (int i = n - 1; i >= 0; i--)
        for (int len : wordLengthsAt(t, s, i)) ways[i] += ways[i + len];
    return ways[0];
}
// snippet:end

long long bruteSplits(const set<string>& dict, const string& s, int i) {
    if (i == (int)s.size()) return 1;
    long long total = 0;
    for (int len = 1; i + len <= (int)s.size(); len++)
        if (dict.count(s.substr(i, len))) total += bruteSplits(dict, s, i + len);
    return total;
}

int main() {
    auto build = [&](vector<string> words) {
        Trie t;
        for (const string& w : words) t.insert(w);
        return t;
    };
    {
        Trie t = build({"a", "ab", "b"});
        cout << "dictionary a ab b, at 0 of abab:";
        for (int x : wordLengthsAt(t, "abab", 0)) cout << " " << x;
        cout << "; splits of abab: " << countSplits(t, "abab") << "\n";
    }
    {
        Trie t = build({"aa", "a"});
        cout << "dictionary aa a: splits of aaaa: " << countSplits(t, "aaaa") << "\n";
    }
    {
        Trie t = build({"ab", "c"});
        cout << "dictionary ab c: splits of abac: " << countSplits(t, "abac") << "\n";
    }
    // Check (not printed): the walk lists exactly the dictionary words that begin at each place, and the number of splits
    // equals a plain recursion, for every string of length 1..8 over {a, b} and the dictionaries {a, ab}, {a, aa, b}, {ab, b, aab}.
    vector<vector<string>> dicts = {{"a", "ab"}, {"a", "aa", "b"}, {"ab", "b", "aab"}};
    for (const auto& words : dicts) {
        Trie t = build(words);
        set<string> dict(words.begin(), words.end());
        for (int n = 1; n <= 8; n++)
            for (int code = 0; code < (1 << n); code++) {
                string s(n, 'a');
                for (int i = 0; i < n; i++) s[i] = 'a' + (code >> i & 1);
                if (countSplits(t, s) != bruteSplits(dict, s, 0)) return 1;
                for (int i = 0; i < n; i++) {
                    vector<int> want;
                    for (int len = 1; i + len <= n; len++)
                        if (dict.count(s.substr(i, len))) want.push_back(len);
                    if (wordLengthsAt(t, s, i) != want) return 1;
                }
            }
    }
}
