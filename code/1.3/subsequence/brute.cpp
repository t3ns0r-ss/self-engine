#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    int n = s.size();
    bool found = false;
    for (int mask = 0; mask < (1 << n); mask++) {  // every choice of kept positions
        string kept;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) kept += s[i];
        if (kept == t) found = true;
    }
    cout << (found ? "YES" : "NO") << "\n";
}
