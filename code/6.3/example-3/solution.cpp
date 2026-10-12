#include <bits/stdc++.h>
using namespace std;

/*
Problem: LeetCode 3043 Find the Length of the Longest Common Prefix. A prefix of a positive integer is formed by one or more of
its digits from the left. Given arrays arr1 and arr2, find the length of the longest common prefix over all pairs (x, y) with
x in arr1 and y in arr2; 0 if there is none.
Input: n, m, then the n numbers of arr1, then the m numbers of arr2 (n, m up to 5·10^4, values up to 10^8).
Output: the length.
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
// Insert the decimal digits of every number of arr1 into a trie (digit d is stored as the letter 'a' + d), then walk each
// number of arr2 as far as the trie follows it: the deepest walk is the answer (Theorem 6.3.1 (b)).
// Uses the Trie of Theorem 6.3.1.
int longestCommonPrefixLength(const vector<int>& arr1, const vector<int>& arr2) {
    auto digits = [](int x) {
        string s = to_string(x);
        for (char& c : s) c = 'a' + (c - '0');
        return s;
    };
    Trie t;
    for (int x : arr1) t.insert(digits(x));
    int best = 0;
    for (int y : arr2) {
        int v = 0, depth = 0;
        for (char c : digits(y)) {
            v = t.child[v][c - 'a'];
            if (!v) break;
            depth++;
        }
        best = max(best, depth);
    }
    return best;
}
// snippet:end

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> arr1(n), arr2(m);
    for (int& x : arr1) cin >> x;
    for (int& x : arr2) cin >> x;
    cout << longestCommonPrefixLength(arr1, arr2) << "\n";
}
