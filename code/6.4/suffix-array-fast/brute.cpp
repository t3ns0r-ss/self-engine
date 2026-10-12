#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> sa(n);
    iota(sa.begin(), sa.end(), 0);
    sort(sa.begin(), sa.end(), [&](int a, int b) { return s.substr(a) < s.substr(b); });
    for (int i = 0; i < n; i++) cout << sa[i] << (i + 1 < n ? " " : "\n");
}
