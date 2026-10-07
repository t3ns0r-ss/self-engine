#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    int best = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) best = max(best, a[i] & a[j]);
    cout << best << "\n";
}
