#include <bits/stdc++.h>
using namespace std;

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

int hashFree(const string& t, const string& s) {  // the card's method: the prefix function of t#s ('?' is an ordinary letter)
    string w = t + '#' + s;
    vector<int> pi = prefixFunction(w);
    int count = 0, m = t.size();
    for (size_t j = 0; j < s.size(); j++) count += pi[m + 1 + j] == m;
    return count;
}
int brute(const string& t, const string& s, bool wildcard) {
    int count = 0, m = t.size();
    for (size_t i = 0; i + m <= s.size(); i++) {
        bool ok = true;
        for (int k = 0; k < m; k++) ok = ok && (s[i + k] == t[k] || (wildcard && t[k] == '?'));
        count += ok;
    }
    return count;
}

int main() {
    cout << "P1 brute=" << brute("aba", "ababa", false) << " method=" << hashFree("aba", "ababa") << "\n";
    cout << "P2 brute=" << brute("aa", "aaaa", false) << " method=" << hashFree("aa", "aaaa") << "\n";
    // N1: '?' in the pattern matches any letter; the prefix function treats it as an ordinary letter.
    cout << "N1 brute=" << brute("a?b", "acbaab", true) << " method=" << hashFree("a?b", "acbaab") << "\n";
}
