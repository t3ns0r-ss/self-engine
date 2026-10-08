#include <bits/stdc++.h>
using namespace std;

bool isPrime(int x) {
    if (x < 2) return false;
    for (int d = 2; d < x; d++)
        if (x % d == 0) return false;
    return true;
}

int main() {
    int N, q;
    cin >> N >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        int c = 0;
        for (int x = l; x <= r; x++) c += isPrime(x);
        cout << c << "\n";
    }
}
