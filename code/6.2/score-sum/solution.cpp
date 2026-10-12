#include <bits/stdc++.h>
using namespace std;

/*
Problem: the score of a string s is the sum, over all its suffixes, of the length of the longest common beginning of the
suffix and s (the whole string scores its length). Print the score.
Input: s (lower-case letters, length up to 10^5).
Output: the score.
*/

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
// The sum of the Z-function (Theorem 6.2.5); the sum can reach n * (n + 1) / 2, so it is a long long. Uses zFunction.
long long score(const string& s) {
    long long total = 0;
    for (int x : zFunction(s)) total += x;
    return total;
}
// snippet:end

int main() {
    string s;
    cin >> s;
    cout << score(s) << "\n";
}
