// Brute force: every subsequence as a bitmask, checked with a stack.
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size(), best = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        string st;
        bool ok = true;
        int len = 0;
        for (int i = 0; i < n && ok; i++) {
            if (!((mask >> i) & 1)) continue;
            len++;
            char c = s[i];
            if (c == '(' || c == '[') st += c;
            else if (st.empty() || st.back() != (c == ')' ? '(' : '[')) ok = false;
            else st.pop_back();
        }
        if (ok && st.empty()) best = max(best, len);
    }
    cout << best << "\n";
}
