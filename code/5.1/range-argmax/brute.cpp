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
        int best = l - 1;
        for (int i = l - 1; i < r; i++)
            if (a[i] > a[best]) best = i;
        cout << best + 1 << "\n";
    }
}
