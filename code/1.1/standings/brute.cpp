// Repeatedly picks the best contestant not yet printed, comparing the rules one by one. O(n^2).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> s(n), p(n);
    for (int i = 0; i < n; i++) cin >> s[i] >> p[i];
    vector<bool> used(n, false);
    vector<int> out;
    for (int step = 0; step < n; step++) {
        int b = -1;
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            if (b == -1) { b = i; continue; }
            bool better = false;
            if (s[i] > s[b]) better = true;
            else if (s[i] == s[b] && p[i] < p[b]) better = true;
            else if (s[i] == s[b] && p[i] == p[b] && i < b) better = true;
            if (better) b = i;
        }
        used[b] = true;
        out.push_back(b + 1);
    }
    for (int i = 0; i < n; i++) cout << out[i] << (i + 1 < n ? ' ' : '\n');
}
