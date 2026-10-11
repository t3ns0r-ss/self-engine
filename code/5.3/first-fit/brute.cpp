#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    for (int j = 0; j < q; j++) {
        long long g;
        cin >> g;
        int room = 0;
        for (int i = 0; i < n; i++)
            if (a[i] >= g) {
                room = i + 1;
                a[i] -= g;
                break;
            }
        cout << room << (j + 1 < q ? ' ' : '\n');
    }
}
