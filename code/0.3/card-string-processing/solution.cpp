#include <bits/stdc++.h>
using namespace std;

int main() {
    // P1: the maximum depth of "(()())". Brute: remove "()" pairs level by level and count the rounds.
    // Method: one pass with the depth as the state.
    string s = "(()())";
    int rounds = 0;
    string t = s;
    while (!t.empty()) {
        string next;
        for (size_t i = 0; i < t.size();) {
            if (i + 1 < t.size() && t[i] == '(' && t[i + 1] == ')') i += 2;
            else next += t[i++];
        }
        // "(()())" -> "(())" takes one round per level only when the innermost pairs go first
        t = next, rounds++;
    }
    int depth = 0, best = 0;
    for (char ch : s) depth += ch == '(' ? 1 : -1, best = max(best, depth);
    cout << "P1 brute=" << rounds << " method=" << best << '\n';
    // N1: can the letters of "aabbc" be rearranged into a palindrome? Brute: try every rearrangement.
    // Method: a scan that checks whether the string is already a palindrome.
    string u = "aabbc";
    sort(u.begin(), u.end());
    bool any = false;
    do {
        any |= u == string(u.rbegin(), u.rend());
    } while (next_permutation(u.begin(), u.end()));
    string orig = "aabbc", rev(orig.rbegin(), orig.rend());
    bool asIs = orig == rev;
    cout << "N1 brute=" << (any ? "yes" : "no") << " method=" << (asIs ? "yes" : "no") << '\n';
    // N2: is ")(" valid? Brute: no. Method: only the final depth is checked (it is 0).
    string v = ")(";
    int dep = 0;
    bool ok = true;
    for (char ch : v) dep += ch == '(' ? 1 : -1, ok &= dep >= 0;
    cout << "N2 brute=" << (ok && dep == 0 ? "yes" : "no") << " method=" << (dep == 0 ? "yes" : "no") << '\n';
}
