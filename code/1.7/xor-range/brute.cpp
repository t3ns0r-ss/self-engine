#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    while (q--) {
        long long L, R, x = 0;
        cin >> L >> R;
        for (long long v = L; v <= R; v++) x ^= v;
        cout << x << "\n";
    }
}
