#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    long long cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) cnt += a[i] > a[j];
    cout << cnt << "\n";
}
