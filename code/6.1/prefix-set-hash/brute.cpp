#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n;
    vector<int> a(n), b(n);
    for (int& x : a) cin >> x;
    for (int& x : b) cin >> x;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        set<int> sa(a.begin(), a.begin() + x), sb(b.begin(), b.begin() + y);
        cout << (sa == sb ? "Yes" : "No") << "\n";
    }
}
