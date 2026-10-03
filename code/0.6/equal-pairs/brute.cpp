// Compares every pair; counts each value's occurrences by scanning the whole array.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    long long pairs = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] == a[j]) pairs++;
    int best = 0, bestValue = 0;
    for (int i = 0; i < n; i++) {
        int c = 0;
        for (int j = 0; j < n; j++) c += a[j] == a[i];
        if (c > best || (c == best && a[i] < bestValue)) {
            best = c;
            bestValue = a[i];
        }
    }
    cout << pairs << " " << bestValue << "\n";
}
