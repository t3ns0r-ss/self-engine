#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> words(n);
    for (string& w : words) cin >> w;
    long long total = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            size_t k = 0;
            while (k < words[i].size() && k < words[j].size() && words[i][k] == words[j][k]) k++;
            total += k;
        }
    cout << total << "\n";
}
