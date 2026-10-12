#include <bits/stdc++.h>
using namespace std;

/*
Problem: for every prefix of s that is also a suffix of s (including s itself), print its length and the number of times
it occurs in s (occurrences may overlap).
Input: s (lower-case letters, length up to 10^5).
Output: the number r of such prefixes; then r lines "length count" in increasing order of the length.
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
// The prefixes that are also suffixes, with their numbers of occurrences, in increasing order of length.
// occ[k] is the number of occurrences of the prefix of length k (Theorem 6.2.6); the lengths are the chain of Theorem 6.2.1.
vector<pair<int, int>> borderCounts(const string& s) {
    int n = s.size();
    vector<int> pi = prefixFunction(s), occ(n + 1, 0);
    for (int i = 0; i < n; i++) occ[pi[i]]++;
    for (int k = n; k >= 1; k--) occ[pi[k - 1]] += occ[k];  // push the counts down to the longest border
    vector<pair<int, int>> result;
    for (int k = n; k > 0; k = pi[k - 1]) result.push_back({k, occ[k] + 1});  // +1: the occurrence at the place 0
    reverse(result.begin(), result.end());
    return result;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    vector<pair<int, int>> r = borderCounts(s);
    cout << r.size() << "\n";
    for (auto [len, count] : r) cout << len << " " << count << "\n";
}
