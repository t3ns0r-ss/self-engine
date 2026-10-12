#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    long long k;
    cin >> s >> k;
    int n = s.size();
    set<string> all;
    for (int i = 0; i < n; i++)
        for (int len = 1; i + len <= n; len++) all.insert(s.substr(i, len));
    auto it = all.begin();
    advance(it, k - 1);
    cout << *it << "\n";
}
