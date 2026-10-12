#include <bits/stdc++.h>
using namespace std;

/*
Problem: print every border and every period of a string s.
Input: s (lower-case letters, length up to 10^6).
Output: the number of borders and the borders in increasing order; then the number of periods and the periods in
increasing order.
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
// All border lengths of s in increasing order (Theorem 6.2.1): the chain pi[n-1], pi[pi[n-1]-1], ... Uses prefixFunction.
vector<int> allBorders(const string& s) {
    vector<int> pi = prefixFunction(s), borders;
    for (int k = pi.back(); k > 0; k = pi[k - 1]) borders.push_back(k);
    reverse(borders.begin(), borders.end());
    return borders;
}
// All periods of s in increasing order: p is a period exactly when n - p is a border length, or p = n.
vector<int> allPeriods(const string& s) {
    int n = s.size();
    vector<int> borders = allBorders(s), periods;
    for (int i = (int)borders.size() - 1; i >= 0; i--) periods.push_back(n - borders[i]);  // longest border = smallest period
    periods.push_back(n);
    return periods;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    for (const vector<int>& v : {allBorders(s), allPeriods(s)}) {
        cout << v.size();
        for (int x : v) cout << " " << x;
        cout << "\n";
    }
}
