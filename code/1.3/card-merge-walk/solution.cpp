#include <bits/stdc++.h>
using namespace std;

vector<int> forwardCounts(const vector<int>& a, const vector<int>& b, bool lessOrEqual) {
    vector<int> p;
    int j = 0;
    for (int x : a) {
        while (j < (int)b.size() && (lessOrEqual ? b[j] <= x : b[j] < x)) j++;
        p.push_back(j);
    }
    return p;
}
string show(const vector<int>& v) {
    string s;
    for (size_t i = 0; i < v.size(); i++) s += (i ? "," : "") + to_string(v[i]);
    return s;
}

int main() {
    // P1: for a = 2 5 5 9 and b = 1 3 5 7, the number of b below each a. Brute: count. Method: the forward pointer.
    vector<int> a = {2, 5, 5, 9}, b = {1, 3, 5, 7}, brute;
    for (int x : a) { int c = 0; for (int y : b) c += y < x; brute.push_back(c); }
    cout << "P1 brute=" << show(brute) << " method=" << show(forwardCounts(a, b, false)) << '\n';
    // P2: is "ace" a subsequence of "abcde"? Brute: try every subset of positions. Method: one walk.
    string s = "abcde", t = "ace";
    bool any = false;
    for (int mask = 0; mask < 32; mask++) { string u; for (int i = 0; i < 5; i++) if (mask >> i & 1) u += s[i]; any |= u == t; }
    size_t j = 0;
    for (char c : s) if (j < t.size() && c == t[j]) j++;
    cout << "P2 brute=" << (any ? "yes" : "no") << " method=" << (j == t.size() ? "yes" : "no") << '\n';
    // N1: the same counts for the UNSORTED a = 9 2: the pointer cannot move back.
    vector<int> c = {9, 2}, bb = {1, 3, 5, 7}, brute2;
    for (int x : c) { int k = 0; for (int y : bb) k += y < x; brute2.push_back(k); }
    cout << "N1 brute=" << show(brute2) << " method=" << show(forwardCounts(c, bb, false)) << '\n';
    // N2: the number of b = 5 below each a = 5 5, with the walk using b[j] <= a[i] instead of b[j] < a[i].
    vector<int> d = {5, 5}, e = {5};
    cout << "N2 brute=0,0 method=" << show(forwardCounts(d, e, true)) << '\n';
}
