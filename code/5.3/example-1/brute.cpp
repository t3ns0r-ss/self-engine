#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) a[x - 1] = y;
        else cout << *min_element(a.begin() + x - 1, a.begin() + y) << "\n";
    }
}
