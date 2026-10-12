#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> words(n);
    for (string& w : words) cin >> w;
    for (int i = 0; i < n; i++) {
        int best = 0;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            int k = 0;
            while (k < (int)words[i].size() && k < (int)words[j].size() && words[i][k] == words[j][k]) k++;
            best = max(best, k);
        }
        cout << best << (i + 1 < n ? ' ' : '\n');
    }
}
