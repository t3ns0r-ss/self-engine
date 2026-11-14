#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    // Palindrome: count the positions that differ from the reversed string; each change fixes two of them.
    string r(s.rbegin(), s.rend());
    int diff = 0;
    for (int i = 0; i < n; i++) diff += s[i] != r[i];
    cout << diff / 2 << "\n";
    // Runs: cut the string where two neighbours differ.
    vector<int> cuts = {0};
    for (int i = 1; i < n; i++)
        if (s[i] != s[i - 1]) cuts.push_back(i);
    cuts.push_back(n);
    for (size_t k = 0; k + 1 < cuts.size(); k++) cout << cuts[k + 1] - cuts[k] << (k + 2 < cuts.size() ? " " : "\n");
    // Alternating case with explicit letter ranges.
    bool ok = true;
    for (int i = 0; i < n; i++) {
        bool lower = s[i] >= 'a' && s[i] <= 'z';
        bool upper = s[i] >= 'A' && s[i] <= 'Z';
        if (i % 2 == 0 ? !lower : !upper) ok = false;
    }
    cout << (ok ? "Yes" : "No") << "\n";
}
