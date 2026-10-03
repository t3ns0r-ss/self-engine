#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (auto& x : h) cin >> x;
    long long best = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) best = max(best, (long long)(j - i) * min(h[i], h[j]));
    cout << best << "\n";
}
