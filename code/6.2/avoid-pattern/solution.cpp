#include <bits/stdc++.h>
using namespace std;

/*
Problem: count the strings of n lower-case letters that contain the pattern t as a substring, modulo 10^9 + 7.
Input: n, then t (n up to 1000, |t| up to 100).
Output: the number of such strings modulo 10^9 + 7.
*/

vector<int> prefixFunction(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int k = pi[i - 1];
        while (k > 0 && s[i] != s[k]) k = pi[k - 1];
        if (s[i] == s[k]) k++;
        pi[i] = k;
    }
    return pi;
}

// snippet:begin
// The number of strings of length n over 'a'..'z' that do NOT contain t, modulo 10^9 + 7, by a DP over the state of the
// matching automaton (Theorem 6.2.4 (b)): ways[k] = the number of strings read so far with k letters of t matched at the end.
// Uses prefixFunction.
long long avoidingCount(int n, const string& t) {
    const long long MOD = 1e9 + 7;
    int m = t.size();
    vector<int> pi = prefixFunction(t);
    vector<array<int, 26>> next(m + 1);
    for (int k = 0; k <= m; k++)
        for (int c = 0; c < 26; c++)
            next[k][c] = (k < m && t[k] - 'a' == c) ? k + 1 : (k == 0 ? 0 : next[pi[k - 1]][c]);
    vector<long long> ways(m + 1, 0);
    ways[0] = 1;
    for (int step = 0; step < n; step++) {
        vector<long long> after(m + 1, 0);
        for (int k = 0; k < m; k++)  // the state m (a full match) is dropped: those strings contain t
            for (int c = 0; c < 26; c++) {
                int to = next[k][c];
                if (to < m) after[to] = (after[to] + ways[k]) % MOD;
            }
        ways = after;
    }
    long long total = 0;
    for (int k = 0; k < m; k++) total = (total + ways[k]) % MOD;
    return total;
}
// snippet:end

int main() {
    int n;
    string t;
    cin >> n >> t;
    long long all = 1;
    for (int i = 0; i < n; i++) all = all * 26 % 1000000007;
    cout << ((all - avoidingCount(n, t)) % 1000000007 + 1000000007) % 1000000007 << "\n";
}
