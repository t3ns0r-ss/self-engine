#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, c = 0;
        cin >> x;
        for (int d = 1; d <= x; d++) c += (x % d == 0);
        cout << c << "\n";
    }
}
