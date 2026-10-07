// Scans outwards from every position.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    for (int i = 0; i < n; i++) {
        int j = i + 1;
        while (j < n && a[j] <= a[i]) j++;
        cout << (j < n ? j + 1 : 0) << (i + 1 < n ? ' ' : '\n');
    }
    for (int i = 0; i < n; i++) {
        int j = i - 1;
        while (j >= 0 && a[j] < a[i]) j--;
        cout << j + 1 << (i + 1 < n ? ' ' : '\n');
    }
}
