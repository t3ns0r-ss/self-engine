#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: is there a pair in 1 2 4 6 9 with sum 8? Brute: all pairs. Method: the pointers.
    vector<int> a = {1, 2, 4, 6, 9};
    bool brute = false, method = false;
    for (int i = 0; i < 5; i++) for (int j = i + 1; j < 5; j++) brute |= a[i] + a[j] == 8;
    for (int l = 0, r = 4; l < r;) { int s = a[l] + a[r]; if (s == 8) { method = true; break; } if (s < 8) l++; else r--; }
    cout << "P1 brute=" << (brute ? "yes" : "no") << " method=" << (method ? "yes" : "no") << '\n';
    // N1: Two Sum on the unsorted 3 2 4 with target 6: the original indices of the pair. Method: positions after sorting.
    vector<int> b = {3, 2, 4};
    string orig;
    for (int i = 0; i < 3; i++) for (int j = i + 1; j < 3; j++) if (b[i] + b[j] == 6) orig = to_string(i) + "-" + to_string(j);
    vector<int> s = b;
    sort(s.begin(), s.end());
    string sorted;
    for (int l = 0, r = 2; l < r;) { int t = s[l] + s[r]; if (t == 6) { sorted = to_string(l) + "-" + to_string(r); break; } if (t < 6) l++; else r--; }
    cout << "N1 brute=" << orig << " method=" << sorted << '\n';
    // N2: is there a pair (two different positions) in 3 5 with sum 6, with pointers allowed to meet (l <= r)?
    vector<int> c = {3, 5};
    bool meet = false;
    for (int l = 0, r = 1; l <= r;) { int t = c[l] + c[r]; if (t == 6) { meet = true; break; } if (t < 6) l++; else r--; }
    cout << "N2 brute=no method=" << (meet ? "yes" : "no") << '\n';
}
