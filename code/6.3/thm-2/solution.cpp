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
// Theorem 6.3.2 (b). The sum of lcp(a, b), the length of the longest common prefix, over all pairs of different words:
// every non-root node v is shared by C(pass[v], 2) pairs, and lcp(a, b) is the number of non-root nodes shared by both words.
// Uses the Trie of Theorem 6.3.1.
long long sumOfCommonPrefixes(const Trie& t) {
    long long total = 0;
    for (size_t v = 1; v < t.pass.size(); v++) total += (long long)t.pass[v] * (t.pass[v] - 1) / 2;
    return total;
}
// Theorem 6.3.2 (c). The longest common prefix of the word w (already inserted) with any other inserted word:
// the depth of the deepest node on the path of w that at least two words pass through.
int longestWithOthers(const Trie& t, const string& w) {
    int v = 0, best = 0;
    for (size_t depth = 1; depth <= w.size(); depth++) {
        v = t.child[v][w[depth - 1] - 'a'];
        if (t.pass[v] >= 2) best = depth;
    }
    return best;
}
// snippet:end

int lcpOf(const string& a, const string& b) {
    size_t k = 0;
    while (k < a.size() && k < b.size() && a[k] == b[k]) k++;
    return k;
}

int main() {
    auto build = [&](vector<string> words) {
        Trie t;
        for (const string& w : words) t.insert(w);
        return t;
    };
    {
        vector<string> words = {"ab", "ac", "b"};
        Trie t = build(words);
        cout << "ab ac b: sum = " << sumOfCommonPrefixes(t) << ", with others: " << longestWithOthers(t, "ab") << " " << longestWithOthers(t, "b") << "\n";
    }
    {
        vector<string> words = {"aaa", "aab", "aac", "ab"};
        Trie t = build(words);
        cout << "aaa aab aac ab: sum = " << sumOfCommonPrefixes(t) << ", with others: " << longestWithOthers(t, "aab") << " " << longestWithOthers(t, "ab") << "\n";
    }
    {
        vector<string> words = {"a", "a"};
        Trie t = build(words);
        cout << "a a: sum = " << sumOfCommonPrefixes(t) << ", with others: " << longestWithOthers(t, "a") << "\n";
    }
    // Check (not printed): on every list of up to 4 words of length 1..3 over {a, b}, the sum of pair lcp values equals the
    // direct sum, and the value for each word equals the best lcp with the other words.
    vector<string> all;
    for (int len = 1; len <= 3; len++)
        for (int code = 0; code < (1 << len); code++) {
            string w(len, 'a');
            for (int i = 0; i < len; i++) w[i] = 'a' + (code >> i & 1);
            all.push_back(w);
        }
    int m = all.size();
    for (int a = 0; a < m; a++)
        for (int b = -1; b < m; b++)
            for (int c = -1; c < m; c++)
                for (int d = -1; d < m; d++) {
                    vector<string> words = {all[a]};
                    for (int x : {b, c, d})
                        if (x >= 0) words.push_back(all[x]);
                    Trie t = build(words);
                    long long direct = 0;
                    for (size_t i = 0; i < words.size(); i++) {
                        int best = 0;
                        for (size_t j = 0; j < words.size(); j++)
                            if (i != j) {
                                best = max(best, lcpOf(words[i], words[j]));
                                if (i < j) direct += lcpOf(words[i], words[j]);
                            }
                        if (longestWithOthers(t, words[i]) != best) return 1;
                    }
                    if (sumOfCommonPrefixes(t) != direct) return 1;
                }
}
