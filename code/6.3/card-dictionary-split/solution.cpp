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

long long trieSplits(const vector<string>& words, const string& s) {
    Trie t;
    for (const string& w : words) t.insert(w);
    int n = s.size();
    vector<long long> ways(n + 1, 0);
    ways[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        int v = 0;
        for (int j = i; j < n; j++) {
            v = t.child[v][s[j] - 'a'];
            if (!v) break;
            if (t.end[v]) ways[i] += ways[j + 1];
        }
    }
    return ways[0];
}
// Cuttings in which each dictionary word is used at most once (brute force over the order of the cuts).
long long cutOnce(const vector<string>& words, const string& s, int i, int usedMask) {
    if (i == (int)s.size()) return 1;
    long long total = 0;
    for (size_t k = 0; k < words.size(); k++)
        if (!(usedMask >> k & 1) && s.compare(i, words[k].size(), words[k]) == 0)
            total += cutOnce(words, s, i + words[k].size(), usedMask | 1 << k);
    return total;
}
long long cutAny(const vector<string>& words, const string& s, int i) {
    if (i == (int)s.size()) return 1;
    long long total = 0;
    for (const string& w : words)
        if (s.compare(i, w.size(), w) == 0) total += cutAny(words, s, i + w.size());
    return total;
}

int main() {
    cout << "P1 brute=" << cutAny({"a", "ab", "b"}, "abab", 0) << " method=" << trieSplits({"a", "ab", "b"}, "abab") << "\n";
    cout << "P2 brute=" << cutAny({"aa", "a"}, "aaaa", 0) << " method=" << trieSplits({"aa", "a"}, "aaaa") << "\n";
    // N1: each word may be used at most once; the count of cuttings with free reuse answers another question.
    cout << "N1 brute=" << cutOnce({"a", "ab", "b"}, "abab", 0, 0) << " method=" << trieSplits({"a", "ab", "b"}, "abab") << "\n";
}
