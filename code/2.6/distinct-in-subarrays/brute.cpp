#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long total = 0;
    for (int l = 0; l < n; l++)
        for (int r = l; r < n; r++) total += set<long long>(a.begin() + l, a.begin() + r + 1).size();
    cout << total << "\n";
}
