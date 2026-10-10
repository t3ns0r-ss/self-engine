#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 0.2.4. Lengths of the maximal blocks of equal characters. j only moves forward,
// so the inner loop runs at most n times in all, although the loops are nested.
vector<int> blockLengths(const string& s) {
    vector<int> len;
    int n = s.size(), i = 0;
    while (i < n) {
        int j = i;
        while (j < n && s[j] == s[i]) j++;
        len.push_back(j - i);
        i = j;  // the next block starts where this one ended
    }
    return len;
}
// snippet:end

int main() {
    for (string s : {"aabccc", "abc", "aaaa"}) {
        cout << s << ":";
        for (int x : blockLengths(s)) cout << ' ' << x;
        cout << '\n';
    }
    for (int code = 0; code < (1 << 10); code++) {  // every string over {a, b} of length 10: the inner iterations are at most n
        string s;
        for (int i = 0; i < 10; i++) s += (code >> i & 1) ? 'b' : 'a';
        int inner = 0, i = 0;
        while (i < 10) {
            int j = i;
            while (j < 10 && s[j] == s[i]) j++, inner++;
            i = j;
        }
        if (inner > 10) return 1;
    }
}
