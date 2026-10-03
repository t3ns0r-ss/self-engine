#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long T;
    cin >> n >> T;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    bool found = false;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] + a[j] == T) found = true;
    cout << (found ? "YES" : "NO") << "\n";
}
