// Brute force: the quadratic table of Theorem 3.4.1 (a different method).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    vector<int> L(n, 1);
    int best = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) L[i] = max(L[i], L[j] + 1);
        best = max(best, L[i]);
    }
    cout << best << "\n";
}
