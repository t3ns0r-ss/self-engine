#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<pair<int, int>> r;
    for (int k = 1; k <= n; k++) {
        if (k < n && s.compare(0, k, s, n - k, k) != 0) continue;
        int count = 0;
        for (int i = 0; i + k <= n; i++) count += s.compare(i, k, s, 0, k) == 0;
        r.push_back({k, count});
    }
    cout << r.size() << "\n";
    for (auto [len, count] : r) cout << len << " " << count << "\n";
}
