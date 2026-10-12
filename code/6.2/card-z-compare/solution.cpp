#include <bits/stdc++.h>
using namespace std;

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

int lcp(const string& s, int i) {
    int len = 0;
    while (i + len < (int)s.size() && s[len] == s[i + len]) len++;
    return len;
}

int main() {
    {
        string s = "aabxaab";
        int brute = 0, method = 0;
        for (int i = 0; i < (int)s.size(); i++) brute += lcp(s, i);
        for (int x : zFunction(s)) method += x;
        cout << "P1 brute=" << brute << " method=" << method << "\n";
    }
    {
        string s = "abcabcab";
        int n = s.size(), brute = 0, method = 0;
        for (int i = 1; i < n; i++) brute += s.compare(i, n - i, s, 0, n - i) == 0;
        vector<int> z = zFunction(s);
        for (int i = 1; i < n; i++) method += z[i] == n - i;
        cout << "P2 brute=" << brute << " method=" << method << "\n";
    }
    {
        // N1: pairs of places with equal blocks of length 2, neither of them at the beginning of the string.
        string s = "cabab";
        int n = s.size(), brute = 0, method = 0;
        for (int i = 0; i + 2 <= n; i++)
            for (int j = i + 1; j + 2 <= n; j++) brute += s.compare(i, 2, s, j, 2) == 0;
        vector<int> z = zFunction(s);
        for (int i = 1; i < n; i++) method += z[i] >= 2;
        cout << "N1 brute=" << brute << " method=" << method << "\n";
    }
}
