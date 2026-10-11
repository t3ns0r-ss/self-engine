#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    long long total = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) total += a[i] > a[j];
    cout << total << "\n";
}
