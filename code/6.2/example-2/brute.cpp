#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> b;
    for (int k = 1; k < n; k++)
        if (s.compare(0, k, s, n - k, k) == 0) b.push_back(k);
    for (size_t i = 0; i < b.size(); i++) cout << b[i] << (i + 1 < b.size() ? ' ' : '\n');
    if (b.empty()) cout << "\n";
}
