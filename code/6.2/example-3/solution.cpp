#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 2107 String Functions. For a string of n letters indexed 1..n: z(i) is the length of the longest substring
that begins at i and is a prefix of the string, with z(1) = 0; pi(i) is the length of the longest substring that ends at i,
is a prefix of the string, and has length at most i - 1. Print all z values, then all pi values (n up to 10^6).
Input: the string. Output: two lines.
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
vector<int> zFunction(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}

// snippet:begin
// Both functions of the problem. The problem sets z(1) = 0, while the Z-function of Theorem 6.2.5 has z[0] = n; the prefix
// function of Theorem 6.2.3 is pi(i) as asked. Uses zFunction and prefixFunction.
pair<vector<int>, vector<int>> stringFunctions(const string& s) {
    vector<int> z = zFunction(s);
    z[0] = 0;
    return {z, prefixFunction(s)};
}
// snippet:end

int main() {
    string s;
    cin >> s;
    auto [z, pi] = stringFunctions(s);
    int n = s.size();
    for (int i = 0; i < n; i++) cout << z[i] << (i + 1 < n ? ' ' : '\n');
    for (int i = 0; i < n; i++) cout << pi[i] << (i + 1 < n ? ' ' : '\n');
}
