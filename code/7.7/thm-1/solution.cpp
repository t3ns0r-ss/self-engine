#include <bits/stdc++.h>
using namespace std;

// snippet:begin
// Theorem 7.7.1. For a string s of n letters 'I' and 'D' there is a permutation p_0 ... p_n of 0 ... n with p_i < p_(i+1) when s_i = 'I' and
// p_i > p_(i+1) when s_i = 'D'. The unused values are always the interval [lo, hi]: an 'I' takes the smallest of them, a 'D' the largest.
vector<int> matchPattern(const string& s) {
    int lo = 0, hi = s.size();
    vector<int> p;
    for (char c : s) p.push_back(c == 'I' ? lo++ : hi--);
    p.push_back(lo);  // lo == hi: the last unused value
    return p;
}
// snippet:end

bool matches(const string& s, const vector<int>& p) {
    vector<int> sorted = p;
    sort(sorted.begin(), sorted.end());
    for (size_t i = 0; i < sorted.size(); i++)
        if (sorted[i] != (int)i) return false;
    for (size_t i = 0; i < s.size(); i++)
        if ((s[i] == 'I') != (p[i] < p[i + 1])) return false;
    return true;
}

int main() {
    for (string s : {"IDID", "III", "DDD"}) {
        cout << s << ":";
        for (int x : matchPattern(s)) cout << " " << x;
        cout << "\n";
    }
    // Check (not printed): every string of I and D of length 0 to 12.
    for (int n = 0; n <= 12; n++)
        for (int mask = 0; mask < (1 << n); mask++) {
            string s;
            for (int i = 0; i < n; i++) s += (mask >> i & 1) ? 'I' : 'D';
            if (!matches(s, matchPattern(s))) return 1;
        }
}
