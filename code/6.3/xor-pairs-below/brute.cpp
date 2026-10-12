#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    long long pairs = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) pairs += (a[i] ^ a[j]) < k;
    cout << pairs << "\n";
}
