#include <bits/stdc++.h>
using namespace std;

/*
Problem: AtCoder ABC 353 E, Yet Another Sigma Problem. For strings x and y let f(x, y) be the length of their longest common
prefix. Given N strings S_1..S_N, print the sum of f(S_i, S_j) over all pairs i < j.
Input: N, then the N strings (lower-case letters, total length up to 3·10^5).
Output: the sum (it can need 64 bits).
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
// The sum of the longest common prefixes over all pairs: insert the strings with pass counts, then add C(pass, 2) over the
// non-root nodes (Theorem 6.3.2 (b)). Uses the Trie of Theorem 6.3.1.
long long sumOfCommonPrefixes(const vector<string>& words) {
    Trie t;
    for (const string& w : words) t.insert(w);
    long long total = 0;
    for (size_t v = 1; v < t.pass.size(); v++) total += (long long)t.pass[v] * (t.pass[v] - 1) / 2;
    return total;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<string> words(n);
    for (string& w : words) cin >> w;
    cout << sumOfCommonPrefixes(words) << "\n";
}
