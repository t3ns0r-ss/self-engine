#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    while (q--) {
        int l, r;
        cin >> l >> r;
        set<int> s(a.begin() + l - 1, a.begin() + r);
        cout << s.size() << "\n";
    }
}
